# 1.0.35

- Fix `centerOnUserLocation` being interrupted by location updates at an intermediate zoom.
- Keep location and puck updates active while a coherent recenter transition completes.
- Coalesce location updates received during recenter and smoothly finish at the latest coordinate and requested zoom.
- Prevent stale transition completions from restoring follow or resetting camera state after a gesture, app-owned camera movement, location disable, or newer recenter.

Source revision: `8b9b0e0` in the SDK source repository.

Required third-party licenses and external data formats are preserved.
