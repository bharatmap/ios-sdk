# 1.0.46

- Add updateNavigationRouteCongestion(levels:sessionId:revision:), its optional palette overload, and clearNavigationRouteCongestion(sessionId:revision:).
- Map one case-sensitive level to each adjacent coordinate pair in BharatMapsActiveRoute. Unknown/low retain accentColor; moderate/heavy/severe default to #F9A825/#EF6C00/#C62828 and support palette overrides.
- Reject invalid input and stale session/revision atomically, including same-count replacement routes. Stop and reroute clear old indices; late results cannot restore them.
- Preserve original segment color boundaries during vanishing-line trimming, update the source in place, and retain colors/remaining geometry through style/theme reload.
- Applying/clearing congestion does not request routes, restart guidance or change camera/padding/follow, puck, voice, progress or reroute state. Existing routing/search/reverse endpoints are unchanged.

Source revision: d855d7596af7fea45ebc270624ac902d4cb36173 in the SDK source repository.

Validation: XCFramework build, Swift interface typecheck, simulator runs at 1x/8x on the real two-leg fixture with repeated palette replacement and geometry/color-boundary inspection, mid-trip style reload, same-count reroute, stale/invalid input and stop/start checks. The initial full run inspected 686 geometry states and 70 crossed segments without failures. Cutover and trip-progress regression suites also pass. Both slices are stripped, signed and branding-checked.

Tests use an isolated simulator host with offline license bootstrap and test-only observation of source shapes, not application code or credentials. They do not validate production networking/licensing or physical-device GPU/GPS/background/acoustic/AR behavior. Required third-party licenses and external data formats are preserved.
