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
