# 1.0.45

- Advance simulated navigation by traveled route distance, including skipped maneuvers and intermediate leg boundaries at accelerated speeds. No speed cap is introduced.
- Deliver final arrival exactly once directly from simulator completion, independently of native location-display filtering.
- Preserve holdAtDestination and autoStopOnArrival policy. Intermediate via points do not finish the trip.
- Prevent stopped/replaced simulation callbacks and old arrival auto-stop work from mutating a new session.
- Keep physical GPS proximity guidance and the 1.0.44 request cancellation contracts unchanged.

Source revision: 8d41b58f99a8ec38f83e2e46bb3046c90b2c50b4 in the SDK source repository.

Validation: XCFramework build and Swift interface typecheck; standalone simulator runs using a real imported two-leg, ten-step, polyline6 route at 1x, 8x and 100x; hold, auto-stop and stale-session checks; 43 cutover regression checks and 19 trip-progress checks. Both slices are stripped, signed and branding-checked. The 1.0.44 negative control reproduces missing arrival at 100x only; no normal-speed defect is inferred from an incomplete application test.

Tests bootstrap licensing offline without reading keys and use a local empty map style. They do not validate production networking/licensing, physical-iPhone GPS/background/audio, AR or existing application UI integration. The legacy aggregate XCTest target remains unavailable due to stale imports; standalone tests run independently.

Required third-party licenses and external data formats are preserved.
