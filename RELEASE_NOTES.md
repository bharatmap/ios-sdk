# 1.0.40

- Add in-place tile URL updates for existing `BharatMapsVectorTileSource` instances.
- Add revision-scoped `pending`, `succeeded`, and `failed` source readiness events.
- Report success only after all required current-viewport tiles finish loading and parsing.
- Reject stale generation events and preserve normal map delegate forwarding.

Source revision: `816aec0` in the SDK source repository.

Required third-party licenses and external data formats are preserved.
