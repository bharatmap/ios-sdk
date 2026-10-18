# 1.0.73

- Add BharatMapsMartinAuthorization.state() and addListener(_:) with an immutable, sanitized status/error snapshot. Initial and subsequent delivery is asynchronous on the main queue; cancellation or subscription deallocation ends delivery.
- Observe the existing shared authorization operation. License acceptance alone is not ready. Preserve readiness while an existing token is usable during refresh; report session expiry, bounded preparation timeout, denial and temporary failure. Invalidation and identity changes discard queued old-state updates.
- Tile source 502/503 responses remain independent of authorization readiness. Observing state adds no network probes or retry loop.
- Host state and existing transport fixtures passed, including recovery, cancellation and tile 502/503 readiness. The public Swift device client compiled and linked against this XCFramework; arm64/x86_64 simulator API typechecks, exported classes, signatures, versions and all four styles passed. No simulator was launched. Physical iPhone runtime and production attestation were not verified for this release.

Source revision: 0853a3154ea0690920e17c7d1902482082035bde.

# 1.0.72

- Raise the signed data request limit to 1 MiB for complete route polygons. Method, URL and exact-body signature binding remain required.
- Document route search and server-authorized private UPIN access. Production remains restricted to enabled first-party apps with Apple/Google verification; Web and third-party access are disabled.
- Physical iPhone transport fixtures passed against the release framework, including signed bodies larger than 16 KiB. These fixtures do not establish production App Attest acceptance. Both XCFramework slices passed signature, version and style-resource checks.

Source revision: 997f94394417499830d2966b1301c23f51cfacda.

# 1.0.71

- Add the public BharatMapsDataClient for signed search, housing, nearby, reverse and public UPin requests, with cancellation and server quota responses.
- Automatically enroll licensed third-party applications using a per-installation signing key and short-lived sessions. Existing first-party Apple/Google verification remains required; this mode does not claim platform attestation.
- Bind request signatures to the exact method, URL and JSON bytes. Do not retry quota denials automatically.
- Route built-in reverse geocoding through the authenticated data client and remove its embedded Elasticsearch credentials.
- Server-side shared quotas and onboarding are deployed separately. Older published SDK versions and legacy application endpoints remain supported during migration.

Source revision: 5e4f0586d861c149eb6cbded16a2613582d68674.

# 1.0.70

- Load the dummy_sea layer from the existing Martin basemap source in all four bundled themes.
- Preserve dummy_sea_polygon, layer order, styling and zoom range 13..24. The vector source remains canonical 0..16 and supports overzoom above 16.
- No public API or application integration changes are required. POI data expansion uses the existing poi layer and requires no additional SDK changes.
- Verified all four themes at zoom 13/15/16 and overzoom 17 on a physical iPhone using captured coastal Mumbai MVT and the release framework. Existing Martin transport fixtures also passed on that device. Production attestation and authorized endpoint acceptance remain separate.

Source revision: b132de4d318c8d30b45dc66353e7e5c65d0a5b5e.

# 1.0.69

- Avoid duplicate flyover/underpass types in named navigation instructions. Recognize whole words case-insensitively, including Fly Over, Fly-over, Bridge, Under Pass and Under-pass.
- Preserve names, keep-left/right directions and generic unnamed instructions. Display text and voice share the same formatter; speech timing is unchanged.
- 44 shared Android/iOS formatting cases passed against the production Objective-C formatter on macOS Foundation. Device and simulator framework slices built; no simulator was launched and physical-device runtime validation is not claimed.

Source revision: a0f81762bd98ebc9f39e510930b4e5196b6a7e94.
# 1.0.68

- Fix the 1.0.67 regression that snapped navigation camera and puck bearing at route vertices. Keep position on the polyline; rotate over the shortest angular arc with a bounded rate, starting from the rendered angle on every retarget.
- Continue angular settling after the position animation finishes. Preserve free-camera ownership, north-up mode, navigation viewport/anchor, route trimming and arrival rendered-location observers.
- New frame-by-frame angular assertions reproduce approximately 90-degree jumps on both published 1.0.67 artifacts and pass on this fix. Pure tests cover wrap, 90/180-degree turns, retargets and delayed frames.
- Emulator/simulator checks are not physical-device driving or frame-pacing acceptance. Existing unrelated Android visual-anchor limitations remain outside this patch.

Source revision: 32338dd6cf19b7f5fe02ebb32e649ae6f7b991df.

# 1.0.67

- Animate SDK-owned navigation puck and attached camera along the original route segments, rather than cutting corners between sparse location updates. Match bearing, remaining route and live congestion to the rendered sample.
- Keep distant off-route fixes unsnapped; bound route intervals and use distance hints at repeated coordinates. Cancel the old route animation when rerouting.
- Add independent rendered user-location snapshot/observers for app-owned overlays. Subscription supplies the current snapshot and remains active after arrival for walking or simulation hold.
- Simulated hold retains the road-route endpoint. The original off-road destination remains the calibration target. Raw navigation progress/location semantics stay separate.
- Isolated native Android/iOS runtime fixtures, curved-path policy tests, release builds and public API compilation verified. Physical-device driving/walking smoothness is not claimed; prior Android visual-anchor limitations remain outside this change.

Source revision: d3781b1f0da3a8b1862c2de17e3c527445ee84f3.

# 1.0.66

- Synchronize active vanishing route and live congestion with the rendered puck sample on each animation frame, including free-camera mode.
- Preserve confirmed Android bridge instructions within the maneuver and route revision; reject stale results. iOS continues to use step-owned bridge metadata.
- Add follow-only adaptive navigation zoom with maneuver/speed hysteresis. Manual camera takeover is not undone by adaptive zoom.
- Add opt-in simulation variableSpeedEnabled, default false. Existing constant-speed simulation API remains compatible.
- Verified Android native fixture (361 frames, zero geographic separation), replay/zoom policy tests, iOS delegate/image fixtures (516/517 frames), iOS anchor fixture (963 frames), Swift API and release builds.
- Physical-device smoothness remains unverified. Existing Android visual-anchor fixture failures also reproduce on 1.0.65; these are not claimed as passing acceptance. iOS active-navigation programmatic camera ownership semantics are unchanged; gestures release follow and recenter restores it.

Source revision: 52281f7b069132ab5f532077720e19ffc0316656.

# 1.0.65

- Synchronize the navigation follow camera and native user puck using one interpolated geographic sample per display tick. Keep the puck projected on the map instead of positioning it as a fixed overlay.
- Animate navigation viewport changes on the same timeline. Coalesce identical mapPadding assignments that mirror an active navigation viewport transition.
- Preserve raw navigation locations/progress, custom image and delegate-provided puck views, free-camera takeover, and explicit recenter behavior. No new public API or application-owned timeout is introduced.
- Verified deterministic native simulator tests for per-frame motion, turns, speed/viewport changes, built-in simulation, mirrored padding, lifecycle/style reload, and navigation/session/reroute contracts. Physical-device driving and full long-route acceptance remain separate.

Source revision: a369c96b207cceac89200624b4c5e1b3eab0bb85.

# 1.0.64

- Apply a coherent navigation camera target so center, heading, pitch and zoom do not cancel each other. Restore the stored viewport on foreground entry and map resize without forcing free-camera follow.
- Stabilize small stationary real-navigation display jitter, including native/delegate custom puck location and course. Navigation calculations and currentNavigationLocation retain unfiltered provider input; simulation is unchanged.
- Preserve existing custom puck images and delegate views. No new public API or host integration changes are required.
- Local native regressions passed: 33 checks for delegate puck, 33 for image puck, and 43 navigation/session/reroute checks. Physical-device driving remains separate acceptance.

Source revision: 42e857de6257f6e32197cc3cbb286dff163e573b.
Fix revision: 4361656f358491f7a7795f3a5a25a6792ecedfe5.

# 1.0.63

- Restore continuous railway strokes in all four themes by removing two invalid single-element dash arrays. Sleepers and other styling remain unchanged.
- Verified with synthetic and real-tile native rendering on iOS and Android.

Source revision: b41e522a022f33e83e810b9e6eaac3b202f1bac3.

# 1.0.62

- Migrate eleven basemap datasets to one authenticated Martin vector source (water, waterways, India outline, state boundaries, railways, landuse, trees, country/state labels) in all four themes.
- Preserve all 52 existing style layer IDs, visual settings, filters, ordering and zoom ranges. Village polygons and unrelated legacy sources are excluded.
- Add independent basemap automatic/manual refresh with bounded persistent revisions at canonical zooms 0 through 16; no camera, tracking or whole-style reset.
- Existing approved app policies explicitly include basemap; other applications and default scopes are unchanged. Older SDK clients remain compatible with the expanded token claims.
- Both release builds, source protocol tests, Swift API typecheck and 28 real-MVT native render cases per platform passed. Physical-device production attestation is not claimed.

Source revision: 13679a96a0cebee7022686823dfcefaad640f27a.

# 1.0.61

- Fix four dormant tertiary/unclassified bridge layers to use the existing Martin road source in all themes, preserving their public layer IDs.
- Prevent duplicate bridge surfaces by excluding bridge=yes from the corresponding ordinary line bodies/casings; add the missing unclassified bridge casing.
- Keep labels, arrows, low-zoom roads, non-bridge roads and missing-bridge-property features unchanged. No new source scopes or server policies.
- Both native renderers passed 24 isolated cases across four themes and six zoom boundaries; both release builds and packaged styles verified. Physical-device/production-transport acceptance is not claimed by these fixtures.

Source revision: 566044a47a28920c6f01aa77c0a973aa4b1ba387.

# 1.0.60

- Migrate only sub-locality labels and building names to independent authenticated Martin sources in all four themes. Other administrative labels remain unchanged.
- Preserve existing layer IDs, styling, ordering and fractional visibility thresholds; building names remain hidden in simplified themes.
- Add independent automatic/manual refresh controls for administrative points and building names, with persistent multi-zoom tile revisions. No camera changes or unrelated cache purge.
- Existing approved application policies explicitly include the new scopes; default permissions for other applications are unchanged.
- Both platform builds, Swift interface, Android protocol suites, style compatibility and issuer tests passed. Physical-device production acceptance is not claimed.

Source revision: 019db91ff58a2b15175af3f9b8a2f7db44c6688b.

# 1.0.59

- All four styles use authenticated Martin POIs: one merged layer containing all 13 datasets, canonical zoom 16 with overzoom. Existing house-number Martin integration is preserved.
- Add POI layer registry and source-scoped automatic/manual refresh with persistent tile revisions and offline restart support.
- Preserve theme visibility and restore it after UPin; keep POI taps and route layering compatible.
- Category icons support exact codes, canonical fallback and a generic icon.
- Builds, native fixture/runtime and offline checks passed. Physical production authorization and CDN invalidation acceptance remain pending; no production-device acceptance is claimed.

Source revision: 0040b4f40996f611ab4c3495d4deb6fb95531b99.

# 1.0.58

- Adds opt-in installation-bound Martin session protection: App Attest and device-only Keychain, ES256 DPoP, SDK-owned refresh and bounded recovery.
- Existing licenses without Martin protection retain current behavior. Installing this release does not enable production enforcement. Server registration and real platform attestation validation are required before activation.
- Credentials stay in headers; roads/house-number URLs and revision/cache identity are preserved. Legacy production tiles and subtiles are unchanged.
- Binary artifact smoke and resource checks passed using provider fixtures; this does not claim real production attestation.

Source revision: 5fb9acf36f1bc57fb299e51a0e181e699c249151.

# 1.0.56

- Replaces unusable 1.0.55: its staging copy skipped same-size, same-timestamp style files, invalidating the signed resource manifest. Do not use 1.0.55.
- Packages the verified iOS restart persistence correction and house-number text-size 9.5 in all four styles.
- Checksum-based staging and strict codesign verification cover both complete framework slices.

Source revision: 7a09b98a.

# 1.0.55 (unusable; superseded by 1.0.56)

- Persist the full Martin house-number revision snapshot atomically, scoped to the tile source URL. Restore it before the first render after restart.
- Keep saved revision keys during initial feed failures/offline restart; no global tile-cache purge or map-startup delay. Cached tiles are still required offline.
- Increase only house-number text-size by 1 (8.5 to 9.5) in all four built-in styles.
- Native cold-restart, failed-feed, source-isolation, renderer regression and production Martin smoke checks passed. Physical-device smoothness remains unverified.

Source revision: 7a09b98a2cd94c97dcf89c402c9a966388180cf5.

# 1.0.54

- Automatically refresh Martin house numbers in all four styles while a licensed map is active.
- Refresh only changed canonical tiles; retain old content during loading/network errors, support deletion and fence stale responses.
- Add automatic-refresh toggle and manual refresh API; preserve camera, UPin and tap behavior.
- Native renderer, lifecycle and production Martin smoke checks passed on both platforms. Physical-device smoothness was not tested.

Source revision: 91ed74da0c084d1fb14db157607a13548e24a8f3.

# 1.0.53

- Load house numbers from Martin in all four built-in styles, including dark and simplified variants.
- Preserve each style's layer order, colors, layout and zoom thresholds. No camera, navigation or API changes.
- Packaged style parity checked on both platforms.

Source revision: 8575dc80aeeeff0bdb8ea7f58ae3c1c040a12ffc.

# 1.0.52

- Restore the original house_number symbol layer in default/light style, with its original placement, minzoom, layout and paint.
- Load it from martin_house_numbers: https://map.bharat-maps.com/martin/v1/house_number/{z}/{x}/{y}.pbf (MVT Point, source-layer house_number, z16 tiles with overzoom).
- Keep dark/simplified styles and other labels unchanged. Existing tap mapping accepts house_number and optional address; raw MVT feature ids retain gid.
- Server updates do not push automatic redraws of already-loaded tiles. No new API or application changes.
- Candidate iOS simulator verifies rendered features, id/properties, tap dispatch, UPin and reload. Android verification covers build/resources/network and 16 KB alignment, not runtime rendering. No physical-device test.

Source revision: 92d865e2d259f7f5e159aea8ab060342658b1ec2.

# 1.0.51

- Remove only the legacy house_number style layer from bundled default/light style.json.
- Dark and simplified styles, sources, other layers and public APIs are unchanged.
- No replacement source is added in this release; server/Martin migration is separate.

Source revision: 6011f17e6660d2afd30faad53b75620075e0d11e.

# 1.0.50

- Restore pre-migration English maneuver templates: ordinary road names use "onto", destination signposts retain "towards". Preserve distinct turn/U-turn, slight/sharp, continue, fork, merge, exit, name/ref and roundabout wording.
- Restore "Go straight for ..., Then ..." / "in ..." composition and original flyover/keep-left/keep-right bridge phrases. Keep punctuation in road names.
- Keep timing, distance thresholds, voice/rate, number normalization, mute/suspension, route selection and didStartNavigationSpeech unchanged.
- Validate 499 legacy formatter fixtures and all three phrase stages, bridge cases, speech-start lifecycle, actual simulator speech before/after reroute, navigation cutover and trip-progress regressions. Physical-device speaker/Bluetooth/background output is not verified.
- No application workaround or public API change. Android is unchanged.

Source revision: 41d09989d9cc20fd7312bf74af349bf39a6edc0e in the SDK source repository.

# 1.0.49

- Add optional `BharatMapsMapViewDelegate.bharatMapView(_:didStartNavigationSpeech:)` for each navigation utterance that actually starts in AVSpeechSynthesizer.
- Deliver final normalized text on main, once per utterance including repeated identical phrases. Do not emit for muted/suspended instructions or utterances cancelled before starting.
- Preserve queue, voice settings, cooldowns and app RoadEvents/ads coordination. Clear pending speech identities on stop/mute/suspension, isolate map instances and detach the synthesizer on teardown.
- The event indicates speech start, not completion or guaranteed audible output. Trip-progress voice text remains a snapshot, not a speech event.
- Add usage documentation, Swift interface verification and runtime coverage. Thirty speech checks passed, including real synthesizer events in simulated navigation and after public reroute; existing navigation-cutover and trip-progress suites passed. Cancellation/order/two-map edge cases use deterministic test injection; physical-device audio/Bluetooth/background coexistence remain unverified.

Source revision: a61e7916ff3b93d326bb1b29280cb5efeb68c2c1 in the SDK source repository.

# 1.0.48

- Fix live vector source refresh flicker in `updateTileURLTemplates`: keep rendered content while replacements load and parse; preserve unchanged symbol identity.
- Successful empty tiles remove old features. Failed tiles retain their previous content and a later refresh can recover. Updates are per tile, not a source-wide atomic transaction.
- Preserve revision readiness, supersession, source/style removal cancellation, callback release, and late-response rejection. Camera, insets, user location and navigation behavior are unchanged.
- Update the source refresh documentation. No application workaround or API migration is required.

Source revision: 5589ca82 in the SDK source repository.

Validation: three-architecture XCFramework build; isolated iOS simulator MVT fixture with 89 passing checks; 224 recorded refresh-phase frames with no missing/faded icons; existing trip-progress and navigation-cutover regressions passed. Xcode 27 build retained the existing deployment minimum; old-iOS-device and physical iPhone live-layer acceptance remain unverified. The public package contains binaries and public interfaces only.

# 1.0.47

- Add signed offline license restoration through the existing `validateLicense(apiKey:)` API. Applications do not need their own license cache or unlock logic.
- Persist the signed authorization in the application's device-only Keychain, bound to platform, API-key fingerprint, registered app ID and actual bundle ID.
- Allow restoration after transient network errors, HTTP 429 or HTTP 5xx for at most 24 hours after online validation, capped by key/subscription expiry. Offline restoration never extends expiry; there is no grace period.
- Reject missing, expired, mismatched or tampered authorizations. Explicit server denial invalidates saved authorization. Protect against stale validation responses and enforce expiry during a running session and on foreground entry.
- Return `validationSource` (online/offline) and online `offlineAvailable` in the existing callback. Existing servers without signing support remain online-compatible.
- Update the licensing guide. Available offline tiles/resources are unchanged; this release does not make REST APIs or uncached resources available offline.

Source revision: e60fa5f62d63171562b6ff491aa8c9a34a51b563 in the SDK source repository.

Validation: XCFramework build, native signature-verifier tests, isolated simulator online/offline process-relaunch scenarios using signed fixtures, and existing trip-progress/navigation-cutover regression suites. Device and simulator slices are stripped and signed; branding checks pass. The release package contains binaries and public interfaces, not SDK implementation source or private signing keys.

The production backend/signing key is deployed and its public key matches the SDK. Production API-key validation/revocation was not exercised: the owner explicitly excluded creation of production test organizations/keys. No customer keys were changed. Fixture tests are not a claim of physical-device behavior, real MBTiles coverage or complete network disconnection.
