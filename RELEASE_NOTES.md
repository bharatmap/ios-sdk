# 1.0.44

- Invalidate pending preview/start/reroute requests on clear, stop, supersession and teardown. Ignore late/duplicate responses and complete cancellations exactly once.
- Import existing OSRM/polyline6/GeoJSON route responses, preserve alternative selection and diversions, and start the selected route with simulation/arrival options without another request.
- Add an app-owned reroute handler preserving existing retry/bearing relaxation/candidate policy and ordered remaining waypoints. Imported routes never silently use an origin/destination-only SDK fallback.
- Publish active route geometry with session/revision identity, reroute lifecycle events, and maneuver/bridge instruction snapshots with their map coordinates.
- Add persistent navigation voice mute and independent temporary speech suspension for app-owned RoadEvents/ads speech.
- Fix stale initial simulated-location use during repeated starts and initialize reroute steps before the replacement provider can emit locations.

Source revision: 7be5a0b11054a4bd022002ac0aa70849049ad238 in the SDK source repository.

Validation: XCFramework build, Swift interface typecheck, 43 cutover checks using delayed local HTTP fixtures and native simulation, plus 19 progress-ring regression checks. Both slices are stripped, signed and branding-checked. The tests bootstrap licensing offline without reading keys; they do not validate production networking/licensing. Speech checks verify scheduling/interruption using a spy, not audible output. Physical-iPhone GPS/background/audio, AR, and existing application UI integration remain unverified. Ordered waypoint projection can reject ambiguous looped routes rather than silently losing a diversion. The legacy aggregate XCTest target remains unavailable due to stale imports; standalone tests run independently.

Required third-party licenses and external data formats are preserved.
