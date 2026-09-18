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
