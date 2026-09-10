# 1.0.43

- Add nullable `maneuverRemainingFraction` and `tripRemainingFraction` to `BharatMapsTripProgress` for progress rings.
- Calculate maneuver progress from the complete approach geometry, including when the UI attaches midway. Replace the distance bases on step changes and reroute.
- Return nil for unavailable, zero-length, inactive and trip-end states. Preserve existing distance fields and the older initializer.
- Correct the Swift delegate example to `bharatMapView(_:didUpdate:)`.

Source revision: 8df457c911a027b04c952daf3793a03c8353fe0a in the SDK source repository.

Validation: XCFramework build, Swift public interface typecheck, and standalone iOS 26.5 simulator binary regression with 19 checks and 29 delegate snapshots. Coverage includes mid-step attachment, different step lengths, bends, reroute, clipped geometry fallback, and undefined states. This uses deterministic injected route fixtures, not a live-server or physical-device GPS test. The legacy aggregate XCTest target remains unavailable because of stale test imports; the standalone binary test runs independently. Both XCFramework slices are stripped, signed and branding-checked.

Required third-party licenses and external data formats are preserved.
