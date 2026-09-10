# 1.0.42

- Fix switching back to the light style by resolving its bundled JSON consistently.
- Include UPin, ads, RoadEvents and static overlay definitions in all four styles, preserving source IDs, layer ordering, predicates and sprite references.
- Preserve camera, padding, user location and follow state during switching and reloads.
- Document restoring app-owned endpoints, images and overlays after style loading.

Source revision: b9b9b430a36b1bc2fba5f3a07b33ee59e57b4c22 in the SDK source repository.

Validation: standalone iOS 26.5 simulator regression, 20 style loads including reloads; bundled overlay contract checks; XCFramework build and branding verification. The legacy aggregate XCTest target remains unavailable because of stale test imports; the standalone binary test runs independently.

Required third-party licenses and external data formats are preserved.
