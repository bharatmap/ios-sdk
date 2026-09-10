# BharatMaps iOS SDK: Quick Start

## SDK naming and resources

Use `import BharatMaps` and the `BharatMapView` facade. The Objective-C umbrella
header is `<BharatMaps/BharatMaps.h>`. Navigation implementation modules are
packaged inside the SDK; applications do not import them separately.

The framework and its optional static resource bundle are named `BharatMaps`.
The high-level map/navigation API is unchanged by the branding cleanup. Clients
using low-level APIs should rebuild and use `BharatMapsDefaultTileServer`,
`BharatMapsVectorTileSourceEncodingMVT`, `BharatMapsDEMEncodingTerrainRGB`, and
`setMaximumAllowedTiles:`. Required third-party license notices and external
data formats remain intact.

## 1) Install via Swift Package Manager (SPM)

In Xcode:

1. `File` -> `Add Package Dependencies...`
2. Use URL: `https://github.com/bharatmap/ios-sdk.git`
3. Select a version tag
4. Add product `BharatMaps`

## 2) Add required Info.plist key

If you use user location, add:

```xml
<key>NSLocationWhenInUseUsageDescription</key>
<string>We use your location to show your position on the map and enable navigation.</string>
```

Without this key app will throw:
`BharatMapsMissingLocationServicesUsageDescriptionException`.

## 3) Basic map setup (Swift)

```swift
import UIKit
import BharatMaps

final class ViewController: UIViewController, BharatMapsMapViewDelegate {

    private var bharatMapView: BharatMapView!

    override func viewDidLoad() {
        super.viewDidLoad()

        bharatMapView = BharatMapView(frame: view.bounds)
        view.addSubview(bharatMapView)
        bharatMapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        bharatMapView.delegate = self
    }
}
```


## 3A) Built-in map styles

Supported enum cases:
- `.light`
- `.dark`
- `.lightSimplified`
- `.darkSimplified`

Initialize with selected style:

```swift
bharatMapView = BharatMapView(frame: view.bounds, mapStyle: .dark)
```

Switch style at runtime:

```swift
bharatMapView.setMapStyle(.lightSimplified)
// or
bharatMapView.mapStyle = .dark
```

All four variants load their JSON from the SDK bundle, including returning to
`.light`. Switching style preserves the camera, map padding, user-location
visibility and follow state. Reload the current style with:

```swift
bharatMapView.mapView.reloadStyle(nil)
```

Every variant includes the same application overlay definitions:

| Source | Layers | Default data |
| --- | --- | --- |
| `u_pin` | `u_pin` | Bundled vector tile endpoint |
| `dynamic` | `roadevents` | Empty GeoJSON placeholder |
| `ads` | `ads` | Empty GeoJSON placeholder |
| `static` | `slope`, `tolls`, `sharp_turn`, `gates_exit` | Empty GeoJSON placeholder |

These layers retain the light style's definitions, predicates, icon names and
relative order in every variant. They use the same sprite resource. UPin is
hidden by default; `setUPinLayerEnabled(_:)` persists across style changes and
reloads, with the opposite visibility applied to `poi`, `house_name` and
`house_number` before the app's style-loaded callback.

Style loading recreates style-owned objects. Restore app-supplied sources, images,
predicates and layers in `mapView(_:didFinishLoading:)`, using the newly loaded
style. The SDK does not store an application's live endpoint configuration.
To connect a vector endpoint to a placeholder, retain its SDK layer objects and
order, remove those layers and the placeholder source, add your source with the
same identifier, then reinsert the retained layers at their original positions.
Use the public `BharatMapsStyle` source/layer/image APIs for this restoration.
Keep `bharatMapView.delegate = self`; the facade forwards the callback while
retaining its internal delegate.

```swift
func mapView(_ mapView: BharatMapsMapView, didFinishLoading style: BharatMapsStyle) {
    restoreApplicationOverlays(in: style)
}
```

## 3B) Accent color

`accentColor` is optional. When set, SDK uses it for route lines, user puck and accuracy ring.

```swift
let accent = UIColor(red: 1.0, green: 0.42, blue: 0.0, alpha: 1.0)

let map = BharatMapView(frame: view.bounds, mapStyle: .light, accentColor: accent)

// or change it later
map.accentColor = accent

// restore default SDK colors
map.accentColor = nil
```

## 4) Simplified camera API (`BharatMapView`)

```swift
let target = CLLocationCoordinate2D(latitude: 28.6129025571, longitude: 77.2295847994)

bharatMapView.moveCameraTo(location: target, zoom: 14)
bharatMapView.animateCameraTo(location: target, zoom: 14)
bharatMapView.easeCameraTo(location: target, zoom: 14, duration: 1.2)

// advanced variants
bharatMapView.animateCameraTo(location: target, zoom: 14, bearing: 30, pitch: 20)
bharatMapView.moveCameraTo(location: target, zoom: 14, bearing: 0, pitch: 0)
bharatMapView.easeCameraTo(location: target, zoom: 14, bearing: 15, pitch: 10, duration: 1.0)
```

Fit camera to multiple coordinates with inner padding:

```swift
bharatMapView.fitCamera(
    to: [
        CLLocation(latitude: 28.6129025571, longitude: 77.2295847994),
        CLLocation(latitude: 28.6259, longitude: 77.2385)
    ],
    edgePadding: UIEdgeInsets(top: 120, left: 32, bottom: 220, right: 32),
    animated: true,
    duration: 0.35
)
```

For assigned-driver screens, clamp the maximum zoom so driver and user do not get framed too close:

```swift
bharatMapView.fitCamera(
    to: [userLocation, driverLocation],
    edgePadding: UIEdgeInsets(top: 138, left: 40, bottom: 40, right: 40),
    animated: true,
    duration: 0.35,
    maxZoom: 18
)
```

Camera behavior:
- `enableUserLocation()` starts user follow when location is available.
- `centerOnUserLocation(...)` and `recenterCamera()` restore user follow.
- app-owned camera methods (`moveCameraTo`, `animateCameraTo`, `easeCameraTo`, `fitCamera`) stop user follow but keep the user puck visible.
- `requestRoutePreview(..., autoFit: false)` stays draw-only and does not change camera/follow state.

User camera gestures:

```swift
func mapView(_ mapView: BharatMapView, didBeginCameraInteraction reason: BharatMapCameraInteractionReason) {
    pauseAutoFitForUserControl()
}

func mapView(_ mapView: BharatMapView, didEndCameraInteraction reason: BharatMapCameraInteractionReason) {
    // Optional: keep auto-fit paused until your own timeout expires.
}
```

These callbacks are user-only. Programmatic camera calls such as `fitCamera`, `centerOnUserLocation`, `recenterCamera`, and route preview camera fitting do not trigger them.

### Refresh an existing vector tile source

Use the source update API for timestamped traffic generations. It updates the
existing source in place, so source and layer identifiers, predicates, and layer
ordering stay unchanged.

```swift
let revision = trafficSource.updateTileURLTemplates([
    "https://traffic.example.com/{z}/{x}/{y}.mvt?timestamp=\(timestamp)"
]) { event in
    switch event.state {
    case .pending:
        print("traffic refresh \(event.revision) pending")
    case .succeeded:
        print("traffic refresh \(event.revision) ready")
    case .failed:
        print("traffic refresh \(event.revision) failed: \(event.error?.localizedDescription ?? "unknown error")")
    @unknown default:
        break
    }
}
```

`succeeded` is source-specific and revision-specific. It is emitted only after
all tiles required by the current viewport have finished loading and parsing;
an empty tile is a successful tile. A newer update supersedes a pending older
revision. Tile failures produce `failed` without removing the source or any
previous traffic generation managed by the application.

Removing a source with a pending update emits one `failed` terminal event with
`BharatMapsVectorTileSourceUpdateErrorSourceRemoved`, then releases the update
handler and source record. Late tile responses from that removed revision are
ignored. A new source with the same identifier starts with an independent
revision lifecycle.

`mapView(_:sourceDidChange:)` reports source definition/data invalidation. It is
not a viewport tile-readiness callback; use the update event above when switching
traffic generations.

## 5) Validate SDK API key (required)

Call once on app start:

```swift
bharatMapView.validateLicense(apiKey: "BMK_TEST_xxx") { result, error in
    if let error {
        print("license error: \(error.localizedDescription)")
        return
    }
    print("license ok token=\(result?["token"] ?? "")")
}
```

Optional appId override:

```swift
bharatMapView.validateLicense(apiKey: "BMK_TEST_xxx", appId: "com.example.app") { result, error in
    // ...
}
```

Notes:
- SDK sends `platform=ios`
- `appId` defaults to `Bundle.main.bundleIdentifier`
- validation endpoint: `https://portal.bharat-maps.com/sdk/v1/license/validate`
- until validation succeeds, map interaction and navigation/location APIs stay locked
- successful response token is also cached in `bharatMapView.licenseToken`

## 6) Simplified user location API (`BharatMapView`)

```swift
bharatMapView.enableUserLocation()

// optional defaults used before first GPS fix
bharatMapView.defaultLocation = CLLocationCoordinate2D(latitude: 28.6129025571, longitude: 77.2295847994)
bharatMapView.defaultZoom = 16

// returns CLLocation?
let location = bharatMapView.currentUserLocation

// center on user, reset bearing/pitch to 0, enable follow mode again
bharatMapView.centerOnUserLocation(zoom: 14)

// center on user using defaultZoom
bharatMapView.centerOnUserLocation()

bharatMapView.disableUserLocation()
```

Custom pulse ring around the user puck:

```swift
// visual-only ring, not tied to GPS accuracy
bharatMapView.startUserLocationPulseRing(color: UIColor.systemBlue, maxRadius: 44)

// stop pulse ring
bharatMapView.stopUserLocationPulseRing()
```

Custom user puck image:

```swift
let icon = UIImage(named: "map_icon_bike")

// default rendered size
bharatMapView.setUserLocationPuckImage(icon)

// explicit rendered size
bharatMapView.setUserLocationPuckImage(icon, size: CGSize(width: 70, height: 70))

// rotate puck by movement course / heading
bharatMapView.setUserLocationPuckBearingEnabled(true)

// explicit bearing behavior
bharatMapView.setUserLocationPuckBearingMode(.courseThenHeading)

// restore default SDK puck
bharatMapView.setUserLocationPuckImage(nil)
```

Bearing modes:

- `.none`: custom puck is not rotated.
- `.courseOnly`: custom puck rotates only by `CLLocation.course`; compass heading is ignored.
- `.courseThenHeading`: backward-compatible behavior used by `setUserLocationPuckBearingEnabled(true)`. SDK uses movement course first, then device heading.
- `.navigationRoute`: recommended for driver navigation. During active navigation SDK uses snapped route direction / upcoming route segment tangent and never falls back to compass heading. Outside active navigation it behaves like course-only.

Behavior:

- after `enableUserLocation()` map follows user
- manual gesture on map stops follow
- `centerOnUserLocation(zoom:)` restores follow mode
- `centerOnUserLocation()` uses `defaultZoom`
- In normal map mode, recenter animates center, requested zoom, north-up heading and zero pitch together. Location updates continue updating the puck during the transition without interrupting camera animation. After finishing, the camera smoothly catches up to the latest fix at the requested zoom before resuming ordinary follow.
- A user camera gesture, disabling location, a newer recenter, or an app-owned camera movement cancels the previous recenter. Its delayed completion cannot restore follow or reset the camera. GPS updates are never suppressed; no app-side animation workaround is needed.
- `setMapPadding(...)` and `animateMapPadding(...)` are coordinated with startup and explicit recenter. Padding updates cannot interrupt the target user coordinate or requested zoom; an active padding animation resumes after recenter with its remaining duration.
- if GPS is not available yet and `defaultLocation` is valid, center fallback uses `defaultLocation`

### Map padding (instant + animated)

Set map viewport padding instantly. On iOS this uses `contentInset`, so it affects the camera viewport and user-location layout:

```swift
bharatMapView.setMapPadding(UIEdgeInsets(top: 24, left: 16, bottom: 180, right: 16))
// equivalent property style:
bharatMapView.mapPadding = UIEdgeInsets(top: 24, left: 16, bottom: 180, right: 16)
```

Animate map viewport padding:

```swift
bharatMapView.animateMapPadding(
    UIEdgeInsets(top: 24, left: 16, bottom: 180, right: 16),
    duration: 0.35
)
```

### Logo margins

Set additional BharatMaps logo margins:

```swift
bharatMapView.setLogoMargins(UIEdgeInsets(top: 0, left: 16, bottom: 24, right: 0))
```

For bottom-sheet layouts, keep camera padding and logo/attribution visual insets independent:

```swift
bharatMapView.mapPadding = UIEdgeInsets(top: 64, left: 0, bottom: sheetHeight, right: 0)
bharatMapView.setAttributionInsets(UIEdgeInsets(top: 0, left: 0, bottom: safeAreaBottom + 8, right: 0))
```

If `setAttributionInsets(...)` is not called, existing ornament behavior is preserved.

### Navigation camera viewport

`mapPadding` is general camera/user-location viewport padding. `setAttributionInsets(...)` only positions Bharat Maps logo/attribution. Navigation has its own viewport so active navigation follow camera is not overwritten by bottom-sheet hacks:

```swift
// Keep the navigation puck above a bottom sheet while navigation follow is active.
bharatMapView.setNavigationCameraViewport(
    UIEdgeInsets(top: 80, left: 0, bottom: sheetHeight + 24, right: 0)
)
```

Recommended taxi-driver setup:

```swift
let icon = UIImage(named: "map_icon_cab")
bharatMapView.setUserLocationPuckImage(icon, size: CGSize(width: 70, height: 70))
bharatMapView.setUserLocationPuckBearingMode(.navigationRoute)
bharatMapView.setNavigationCameraViewport(
    UIEdgeInsets(top: 80, left: 0, bottom: sheetHeight + 24, right: 0)
)
bharatMapView.setAttributionInsets(UIEdgeInsets(top: 0, left: 0, bottom: safeAreaBottom + 8, right: 0))
bharatMapView.enableUserLocation()
```

When bottom-sheet height changes, call `setNavigationCameraViewport(...)` again. Active navigation follow/recenter uses the latest viewport.

## 7) Quick navigation start (no alternative selection)

`BharatMapView` can start navigation immediately by requesting a route from:

`https://navigation.bharat-maps.com/route/v1/car/...`

Route is drawn automatically and navigation starts right away.

```swift
let destination = CLLocationCoordinate2D(latitude: 28.6259, longitude: 77.2385)

bharatMapView.startNavigation(destination: destination, simulation: true) { error in
    if let error = error {
        print("Navigation start error: \\(error.localizedDescription)")
    }
}
```

You can also pass explicit origin:

```swift
let origin = CLLocationCoordinate2D(latitude: 28.6129, longitude: 77.22958)
let destination = CLLocationCoordinate2D(latitude: 28.6259, longitude: 77.2385)

bharatMapView.startNavigation(origin: origin, destination: destination, simulation: true) { error in
    if let error = error {
        print("Navigation start error: \\(error.localizedDescription)")
    }
}
```

Stop and clear current navigation:

```swift
bharatMapView.stopNavigation()
```

`stopNavigation()` now also exits navigation camera mode automatically:
- resets camera bearing/pitch to neutral state
- if user location is available, recenters to user with default zoom and follow mode

To make the SDK-owned active navigation route vanish behind the navigation puck, enable it before starting navigation:

```swift
bharatMapView.setNavigationRouteVanishingEnabled(true)

bharatMapView.startNavigation(origin: origin, destination: destination, simulation: false) { error in
    if let error {
        print(error.localizedDescription)
    }
}
```

`setNavigationRouteVanishingEnabled(false)` is the default for backward compatibility. This affects only the SDK-owned active navigation route. It does not disable app-owned route polylines, route progress callbacks, maneuver callbacks, custom user puck, or navigation camera.

### Taxi simulation legs

Use simulation options when a driver flow has multiple simulated legs and the puck must stay at the simulated destination instead of jumping back to GPX/system location.

```swift
let options = BharatNavigationSimulationOptions(
    enabled: true,
    holdAtDestination: true,
    autoStopOnArrival: false,
    speedMultiplier: 1.0
)

bharatMapView.startNavigation(
    origin: driverCoordinate,
    destination: pickupCoordinate,
    simulationOptions: options
) { error in
    if let error {
        print(error.localizedDescription)
    }
}
```

When the first leg reaches pickup:

```swift
let nextOrigin = bharatMapView.currentNavigationLocation?.coordinate ?? pickupCoordinate

bharatMapView.startNavigation(
    origin: nextOrigin,
    destination: dropoffCoordinate,
    simulationOptions: options
) { error in
    if let error {
        print(error.localizedDescription)
    }
}
```

`holdAtDestination=true` keeps the native user-location puck at the last simulated coordinate. `autoStopOnArrival=false` prevents SDK from auto-stopping navigation at arrival. `stopNavigation()` keeps backward-compatible behavior and resets to real/system location. Use `stopNavigation(resetToRealLocation: false)` only when you need to close guidance while keeping the puck on the held simulated location.

Trip-end calibration line is enabled by default. Disable it when the app wants to keep the simulated puck at the destination without showing the red-dot calibration overlay:

```swift
bharatMapView.setNavigationCalibrationLineEnabled(false)
let enabled = bharatMapView.isNavigationCalibrationLineEnabled()
```

This only disables trip-end calibration dots/end marker/follow camera overlay. It does not disable route line, user puck, navigation progress callbacks, `currentNavigationLocation`, or `currentSimulatedNavigationLocation`.

Auto rerouting:
- while navigation is active, SDK detects off-route and automatically requests reroute to current destination
- reroute request includes current bearing as `bearings=<bearing>,90;` to avoid wrong U-turn-first routes
- reroute calls are debounced and require consecutive off-route detections to avoid GPS jitter

Manual reroute:

```swift
let origin = bharatMapView.currentUserLocation?.coordinate ?? CLLocationCoordinate2D(latitude: 28.6129, longitude: 77.22958)
let destination = CLLocationCoordinate2D(latitude: 28.6259, longitude: 77.2385)

bharatMapView.rerouteNavigation(origin: origin, destination: destination) { error in
    if let error = error {
        print("reroute error: \(error.localizedDescription)")
    }
}

bharatMapView.rerouteNavigation(origin: origin, destination: destination, simulation: true) { error in
    if let error = error {
        print("reroute(sim) error: \(error.localizedDescription)")
    }
}
```

Off-route simulation helper (for testing auto-reroute on real device):

```swift
_ = bharatMapView.simulateOffRouteDeviation()
_ = bharatMapView.simulateOffRouteDeviation(meters: 80)
```

Navigation-bound visibility binding:

```swift
// Visible only while navigation is active
bharatMapView.bindNavigationVisibility(navigationOnlyView, visibleWhenNavigationActive: true)

// Visible only while navigation is NOT active
bharatMapView.bindNavigationVisibility(mapOnlyView, visibleWhenNavigationActive: false)

// Unbind when no longer needed
bharatMapView.unbindNavigationVisibility(navigationOnlyView)
bharatMapView.unbindNavigationVisibility(mapOnlyView)
```

## 9A) Advanced annotations

Add custom view annotation anchored to map coordinate:

```swift
let content = UIStackView()
content.axis = .vertical
content.spacing = 6

let title = UILabel()
title.text = "Pinned place"
content.addArrangedSubview(title)

let options = BharatMapsAdvancedAnnotationOptions.defaultOptions()
options.backgroundColor = .white
options.borderColor = .systemBlue
options.borderWidth = 1
options.cornerRadius = 12
options.tailWidth = 21
options.tailHeight = 12
options.contentInsets = UIEdgeInsets(top: 12, left: 12, bottom: 12, right: 12)
options.maxWidth = 260
options.closeTapOutside = true

bharatMapView.addAdvancedAnnotation(
    id: "poi_bubble_1",
    location: CLLocationCoordinate2D(latitude: 28.6139, longitude: 77.2090),
    content: content,
    options: options
)
```

Update/remove:

```swift
bharatMapView.updateAdvancedAnnotation(
    id: "poi_bubble_1",
    location: CLLocationCoordinate2D(latitude: 28.6142, longitude: 77.2093)
)
bharatMapView.updateAdvancedAnnotationOptions(id: "poi_bubble_1", options: options)
bharatMapView.updateAdvancedAnnotationContent(id: "poi_bubble_1", content: content)
bharatMapView.removeAdvancedAnnotation(id: "poi_bubble_1")
bharatMapView.clearAdvancedAnnotations()
```

## 8) Route options + `BharatMapsRouteSelector`

If you want alternatives before navigation start:

1. call `requestRoutes(...)`
2. let user pick a route in `BharatMapsRouteSelector`
3. call `startSelectedNavigation(...)`

```swift
import UIKit
import BharatMaps

final class ViewController: UIViewController {

    private var bharatMapView: BharatMapView!
    private let selector = BharatMapsRouteSelector(frame: .zero)

    override func viewDidLoad() {
        super.viewDidLoad()

        bharatMapView = BharatMapView(frame: view.bounds)
        view.addSubview(bharatMapView)
        bharatMapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]

        selector.bharatMapView = bharatMapView
        selector.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(selector)

        NSLayoutConstraint.activate([
            selector.leadingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.leadingAnchor, constant: 16),
            selector.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16),
            selector.bottomAnchor.constraint(equalTo: view.safeAreaLayoutGuide.bottomAnchor, constant: -96),
            selector.heightAnchor.constraint(equalToConstant: 74),
        ])
    }

    func requestAndChooseRoute() {
        let destination = CLLocationCoordinate2D(latitude: 28.6259, longitude: 77.2385)
        bharatMapView.requestRoutes(destination: destination) { routes, error in
            if let error = error {
                print("requestRoutes error: \(error.localizedDescription)")
                return
            }
            print("routes: \(routes?.count ?? 0)")
        }
    }

    func startSelectedRoute() {
        bharatMapView.startSelectedNavigation(simulation: true) { error in
            if let error = error {
                print("startSelectedNavigation error: \(error.localizedDescription)")
            }
        }
    }
}
```

For non-navigation previews, for example driver-to-pickup route in a taxi app, use the controlled preview API:

```swift
bharatMapView.requestRoutePreview(
    origin: driverCoordinate,
    destination: pickupCoordinate,
    alternatives: false,
    autoFit: false
) { routes, error in
    if let routeId = routes?.first?.routeId {
        bharatMapView.selectRouteOption(routeId: routeId)
    }
}
```

`alternatives: false` requests and draws only the primary route. Preview route layers are inserted below symbol/user-location style layers; native annotation markers remain above style layers.

`autoFit: true` means SDK draws the route, may disable user follow for preview mode, and may fit the camera to the selected preview route.

`autoFit: false` means SDK draws the route only. Camera position, user tracking mode, follow state, map padding and content inset remain app-owned and unchanged.

### Backend-owned route geometry

Use this when your backend already returns OSRM-like route geometry and the app must draw exactly that route without SDK route requests, alternatives, camera fit, or follow/tracking changes.

```swift
bharatMapView.showRoutePolyline(
    encodedPolyline: trip.assignedDriverRouteGeometry,
    strokeColor: UIColor(red: 76/255, green: 125/255, blue: 246/255, alpha: 1),
    strokeWidth: 5,
    routeId: "assigned_driver"
)
```

Use `showRoutePolyline(encodedPolyline:precision:strokeColor:strokeWidth:routeId:)` when the backend returns a precision other than polyline6.

```swift
bharatMapView.clearRoutePolyline(routeId: "assigned_driver")
bharatMapView.clearRoutePolyline(routeId: nil) // clears all app-owned route polylines
```

To make the already travelled part of the backend-owned route disappear as the driver moves:

```swift
bharatMapView.updateRoutePolylineProgress(
    routeId: "assigned_driver",
    currentLocation: driverCoordinate
)
```

You can also trim by explicit progress:

```swift
bharatMapView.updateRoutePolylineProgress(routeId: "assigned_driver", progress: 0.45)
```

`progress` is clamped to `0...1`. `0` shows the full line, `1` hides it. Reusing `showRoutePolyline` with the same `routeId` replaces the original geometry and resets progress to `0`.

This API only draws/removes app-owned route layers. It does not call `requestRoutePreview`, does not move camera, does not change follow/tracking, and does not hide the user puck. Reusing the same `routeId` updates the existing line.

`BharatMapsRouteOption` also exposes `encodedPolyline`, `polylinePrecision`, `distanceMeters`, and `durationSeconds` for apps that still use SDK route preview responses.

Notes:

- `BharatMapsRouteSelector` is hidden when no route options are available.
- after navigation starts, preview routes are cleared and selector is hidden.
- route chips are always horizontal.
- you can customize selector with:
  - `buttonColor`, `activeButtonColor`
  - `textColor`, `activeTextColor`
  - `font` or `fontFamily`
  - `textSize`
  - `insets` (inner inset of selector content)
  - `buttonPadding`
  - `cornerRadius`
  - `gap`

## 9) Maneuver sign + voice instructions

`BharatMapView` now emits navigation instruction updates internally and speaks maneuver prompts automatically during active navigation.

- voice is enabled by default
- preferred TTS voice: `hi-IN` (fallback: `en-IN`)
- numeric values are normalized to spoken English before TTS (so distances are read in English words)
- bridge/underpass/lane custom instructions are supported via `bridge_instructions` codes in step data
- announcement timing follows Android SDK stages: `segment start`, `get ready`, `finish`

To render the next maneuver icon, add `BharatMapsManeuverSign` and bind it to your map:

```swift
import UIKit
import BharatMaps

final class ViewController: UIViewController {
    private var bharatMapView: BharatMapView!
    private let maneuverSign = BharatMapsManeuverSign(frame: .zero)

    override func viewDidLoad() {
        super.viewDidLoad()

        bharatMapView = BharatMapView(frame: view.bounds)
        view.addSubview(bharatMapView)
        bharatMapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]

        maneuverSign.bharatMapView = bharatMapView
        maneuverSign.translatesAutoresizingMaskIntoConstraints = false
        view.addSubview(maneuverSign)

        NSLayoutConstraint.activate([
            maneuverSign.topAnchor.constraint(equalTo: view.safeAreaLayoutGuide.topAnchor, constant: 16),
            maneuverSign.trailingAnchor.constraint(equalTo: view.safeAreaLayoutGuide.trailingAnchor, constant: -16),
            maneuverSign.widthAnchor.constraint(equalToConstant: 64),
            maneuverSign.heightAnchor.constraint(equalToConstant: 64),
        ])
    }
}
```

`BharatMapsManeuverSign` behavior:

- hidden when navigation is inactive
- shown automatically when the next maneuver is available
- updates icon automatically as steps change

Customizable properties:

- `iconColor`
- `signBackgroundColor`
- `cornerRadius`
- `insets`
- `orientation`
- `bharatMapView` or `bharatMapViewTag`

## 10) `BharatMapsLocationButton` (auto recenter)

`BharatMapsLocationButton` is a ready-to-use recenter control bound to `BharatMapView`.

Behavior:

- on tap:
  - normal map mode: calls `centerOnUserLocation(defaultZoom)`
  - active navigation mode: recenters navigation camera
- button is `disabled` while camera is already following user
- when disabled, icon alpha is `0.5`
- default icon in map mode: `icon_location`
- default icon in navigation mode: `icon_navigating`

Usage:

```swift
let locationButton = BharatMapsLocationButton(type: .custom)
locationButton.bharatMapView = bharatMapView
locationButton.cornerRadius = 14
locationButton.iconColor = .black
```

Customizable properties:

- `cornerRadius`
- `iconColor`
- `icon`
- `iconNavigation`
- `bharatMapView` or `bharatMapViewTag`

## 11) `BharatMapsZoomControl`

`BharatMapsZoomControl` is a ready-to-use zoom UI based on two buttons (`+` and `-`) inside a stack view.

Behavior:

- zoom-in button becomes disabled at max zoom
- zoom-out button becomes disabled at min zoom
- disabled button icon alpha is `0.5`
- default icons:
  - plus: `icon_plus`
  - minus: `icon_minus`

Usage:

```swift
let zoomControl = BharatMapsZoomControl(frame: .zero)
zoomControl.bharatMapView = bharatMapView
zoomControl.orientation = .vertical
zoomControl.cornerRadius = 12
zoomControl.iconColor = .black
zoomControl.backgroundColor = .white
```

Customizable properties:

- `cornerRadius` (button corner radius)
- `iconColor`
- `iconPlus`
- `iconMinus`
- `backgroundColor` (button background color)
- `orientation`
- `bharatMapView` or `bharatMapViewTag`

## 12) Navigation labels (auto-bound to nav state)

These labels work like Android SDK labels and auto-hide when navigation is inactive:

- `BharatMapsManeuverDistanceLabel`
- `BharatMapsTripTimeRemainingLabel`
- `BharatMapsTripTimeArrivalLabel`
- `BharatMapsTripDistanceLabel`
- `BharatMapsNextRoadNameLabel`
- `BharatMapsSpeedLabel`

Usage:

```swift
let tripDistanceLabel = BharatMapsTripDistanceLabel()
tripDistanceLabel.bharatMapView = bharatMapView
tripDistanceLabel.textColor = .white
tripDistanceLabel.font = .systemFont(ofSize: 14, weight: .semibold)
view.addSubview(tripDistanceLabel)
```

Or bind by tag:

```swift
bharatMapView.tag = 1001
tripDistanceLabel.bharatMapViewTag = 1001
```

Behavior:

- all labels are `hidden` when navigation is inactive
- `BharatMapsNextRoadNameLabel` is also `hidden` when next road name is empty
- values are pushed from live navigation trip progress updates

Style parameters (available on every navigation label):

- `textHexColor` (example: `#FFFFFF`)
- `backgroundHexColor` (example: `#66000000`)
- `fontFamily` (font name)
- `textSize` (default `15`)
- `cornerRadius`
- `horizontalPadding`
- `verticalPadding`
- plus all standard `UILabel` styling props (`textColor`, `font`, `textAlignment`, etc.)

## 13) Trip end flow + `BharatMapsTripEndView`

iOS SDK now mirrors Android trip-end behavior:

- when destination is reached, normal navigation state is closed
- if user is still farther than 10 meters from destination, calibration red-dot line is shown from current puck location to destination and camera keeps both points visible
- if distance is within 10 meters, no calibration line and simple arrival message
- `setNavigationCalibrationLineEnabled(false)` disables only the calibration overlay; trip-end state and progress callbacks still work
- if `BharatMapsTripEndView` is not present in UI, SDK auto-calls `stopNavigation()` after 3 seconds

`BharatMapsTripEndView` is auto-bound to map navigation state and appears only in trip-end state.

```swift
let tripEndView = BharatMapsTripEndView(frame: .zero)
tripEndView.bharatMapView = bharatMapView
view.addSubview(tripEndView)
```

Or by tag:

```swift
bharatMapView.tag = 1001
tripEndView.bharatMapViewTag = 1001
```

Customizable properties:

- `textColor`
- `buttonBackgroundColor`
- `buttonTextColor`
- `fontFamily`
- `borderRadius`
- `buttonBorderRadius`
- `buttonHeight`
- `textSize`
- `buttonTextSize`

Finish button inside `BharatMapsTripEndView` calls `stopNavigation()` automatically.

## 13) Map entity tap callbacks (POI / Building number / uPin)

Entity tap callbacks are delivered through `BharatMapsMapViewDelegate` (`BharatMapView.delegate`).

```swift
import UIKit
import BharatMaps

final class ViewController: UIViewController, BharatMapsMapViewDelegate {
    private var bharatMapView: BharatMapView!

    override func viewDidLoad() {
        super.viewDidLoad()
        bharatMapView = BharatMapView(frame: view.bounds)
        view.addSubview(bharatMapView)
        bharatMapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        bharatMapView.delegate = self
    }

    func bharatMapView(_ bharatMapView: BharatMapView, didTapPoi poi: BharatMapsPoiResult) {
        print("POI:", poi.name ?? "-", poi.address ?? "-", poi.category, poi.subcategory)
    }

    func bharatMapView(_ bharatMapView: BharatMapView, didTapBuildingNumber buildingNumber: BharatMapsBuildingNumberResult) {
        print("BUILDING:", buildingNumber.buildingNumber, buildingNumber.address ?? "-")
    }

    func bharatMapView(_ bharatMapView: BharatMapView, didTapUPin uPin: BharatMapsUPinResult) {
        print("UPIN:", uPin.uPin, uPin.address ?? "-")
    }
}
```

Tap hit priority is the same as Android:

`markers_layer` -> `house_number` -> `house_name` -> `building_names` -> `u_pin` -> `poi`.

## 14) U-Pin layer toggle

Use this to switch map into U-Pin mode:

```swift
bharatMapView.setUPinLayerEnabled(true)
```

Behavior (same as Android):
- enables `u_pin` layer
- hides `poi`, `house_name`, `house_number` layers

Disable U-Pin mode:

```swift
bharatMapView.setUPinLayerEnabled(false)
```

When disabled, regular `poi` / `house_name` / `house_number` layers are shown again.

## 15) Reverse geocoding callbacks (long press)

Reverse geocoding callbacks are also delivered through `BharatMapsMapViewDelegate`.

```swift
import UIKit
import BharatMaps

final class ViewController: UIViewController, BharatMapsMapViewDelegate {
    private var bharatMapView: BharatMapView!

    override func viewDidLoad() {
        super.viewDidLoad()
        bharatMapView = BharatMapView(frame: view.bounds)
        view.addSubview(bharatMapView)
        bharatMapView.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        bharatMapView.delegate = self
    }

    func bharatMapView(_ bharatMapView: BharatMapView, didReceiveReverseGeocoding result: BharatMapsReverseGeocodingResult) {
        print("address:", result.address ?? "-")
        print("name:", result.name ?? "-")
        print("ward:", result.wardNumber ?? "-")
        print("police phone:", result.policeStationPhone ?? "-")
        print("nearby POIs:", result.nearbyPois.count)
        print("nearby building numbers:", result.nearbyBuildingNumbers.count)
    }

    func bharatMapView(_ bharatMapView: BharatMapView,
                       didFailReverseGeocodingWithError message: String,
                       location: CLLocationCoordinate2D) {
        print("reverse geocoding error:", message, location.latitude, location.longitude)
    }
}
```

Full optional callback set on one delegate:

```swift
extension ViewController: BharatMapsMapViewDelegate {
    func bharatMapView(_ bharatMapView: BharatMapView, didTapPoi poi: BharatMapsPoiResult) {}
    func bharatMapView(_ bharatMapView: BharatMapView, didTapBuildingNumber buildingNumber: BharatMapsBuildingNumberResult) {}
    func bharatMapView(_ bharatMapView: BharatMapView, didTapUPin uPin: BharatMapsUPinResult) {}
    func bharatMapView(_ bharatMapView: BharatMapView, didReceiveReverseGeocoding result: BharatMapsReverseGeocodingResult) {}
    func bharatMapView(_ bharatMapView: BharatMapView,
                       didFailReverseGeocodingWithError message: String,
                       location: CLLocationCoordinate2D) {}
}
```

## 16) Trip progress callback (delegate)

Live navigation progress is also delivered through `BharatMapsMapViewDelegate`:

```swift
func bharatMapView(_ bharatMapView: BharatMapView, didUpdateTripProgress progress: BharatMapsTripProgress) {
    let maneuverDistance = progress.maneuverDistanceMeters
    let maneuverDuration = progress.maneuverDurationRemainingSeconds
    let tripDistance = progress.tripDistanceRemainingMeters
    let tripDuration = progress.tripDurationRemainingSeconds
    let arrivalTime = progress.arrivalTimeMillis
    let speed = progress.speedKmh
    let currentRoad = progress.currentRoadName
    let nextRoadLabel = progress.nextRoadName   // "Current  ➜  Next"
    let voiceText = progress.voiceInstructionText
}
```

`BharatMapsTripProgress` includes:

- `navigationActive`
- `maneuverDistanceMeters`
- `maneuverDurationRemainingSeconds`
- `tripDistanceRemainingMeters`
- `tripDurationRemainingSeconds`
- `arrivalTimeMillis`
- `speedKmh`
- `currentRoadName`
- `nextRoadName`
- `voiceInstructionText`

## 17) Simple map annotations (`BharatMapView`)

`BharatMapView` now provides high-level helpers for point/line/polygon/marker annotations.

### Point annotation

```swift
let point = bharatMapView.addPointAnnotation(
    location: CLLocationCoordinate2D(latitude: 26.8622, longitude: 75.7938),
    image: UIImage(named: "poi_pin"),
    title: "Pickup",
    subtitle: "Tonk Road"
)
```

### Line annotation

```swift
let line = bharatMapView.addLineAnnotation(
    locations: [
        CLLocation(latitude: 26.8622, longitude: 75.7938),
        CLLocation(latitude: 26.8642, longitude: 75.7956),
        CLLocation(latitude: 26.8670, longitude: 75.8000)
    ],
    strokeColor: UIColor.systemBlue,
    lineWidth: 4.0,
    alpha: 1.0
)
```

### Polygon annotation

```swift
let polygon = bharatMapView.addPolygonAnnotation(
    locations: [
        CLLocation(latitude: 26.8622, longitude: 75.7938),
        CLLocation(latitude: 26.8642, longitude: 75.7956),
        CLLocation(latitude: 26.8610, longitude: 75.7990)
    ],
    strokeColor: UIColor.systemBlue,
    fillColor: UIColor.systemBlue.withAlphaComponent(0.2),
    lineWidth: 3.0,
    alpha: 1.0
)
```

### Marker with popup (callout)

```swift
let marker = bharatMapView.addMarker(
    location: CLLocationCoordinate2D(latitude: 26.8650, longitude: 75.7980),
    title: "Drop-off",
    subtitle: "Tap marker",
    showCallout: true
)
```

If `showCallout == true` and marker has `title` or `subtitle`, standard map callout appears on tap.

### Dynamic custom markers

Use custom markers for moving objects such as taxis, couriers, drivers, or tracked assets.

```swift
let carId = "car_42"
let start = CLLocationCoordinate2D(latitude: 28.6129, longitude: 77.2295)
let carImage = UIImage(named: "ic_car_marker")!

bharatMapView.addCustomMarker(
    id: carId,
    location: start,
    image: carImage,
    bearing: 90
)
```

Update position instantly:

```swift
bharatMapView.updateCustomMarker(
    id: carId,
    location: CLLocationCoordinate2D(latitude: 28.6138, longitude: 77.2310),
    bearing: 120
)
```

Update position with animation:

```swift
bharatMapView.updateCustomMarker(
    id: carId,
    location: CLLocationCoordinate2D(latitude: 28.6144, longitude: 77.2320),
    bearing: 135,
    animated: true,
    duration: 1.0
)
```

`bearing` is clockwise degrees where `0` keeps the original image orientation.

When the vehicle must follow backend-owned route geometry instead of moving in a straight line between polling updates:

```swift
bharatMapView.updateCustomMarkerAlongRoute(
    id: "assigned_driver",
    routeId: "assigned_driver_route",
    currentLocation: driverCoordinate,
    animated: true,
    duration: 1.0
)
```

To move the marker along the route and update the vanishing route line in one call:

```swift
bharatMapView.updateCustomMarkerAlongRouteAndProgress(
    id: "assigned_driver",
    routeId: "assigned_driver_route",
    currentLocation: driverCoordinate,
    animated: true,
    duration: 1.0
)
```

`updateCustomMarkerAlongRouteAndProgress` synchronizes marker animation and vanishing route line frame-by-frame: the remaining route starts exactly at the currently rendered marker position during the animation. `updateRoutePolylineProgress(...)` remains an instant/manual trim API.

Remove markers:

```swift
bharatMapView.removeCustomMarker(id: carId)
bharatMapView.clearCustomMarkers()
```

Notes:
- marker ids are stable; calling `addCustomMarker` again with the same id replaces the old marker
- animated updates use linear interpolation between old and new coordinates
- `updateCustomMarkerAlongRoute` uses geometry previously set by `showRoutePolyline(... routeId:)`, projects current driver location to the route, and animates by route segments instead of a direct line
- for live vehicle tracking, push every new GPS fix through `updateCustomMarker(..., animated: true, duration: updateInterval)`

### Remove annotations

```swift
if let point {
    bharatMapView.removeMapAnnotation(point)
}

bharatMapView.clearMapAnnotations()
```
