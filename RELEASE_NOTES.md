# 1.0.41

- Finish a pending vector tile source refresh with `failed` when its source is removed.
- Release the pending handler and source record immediately after removal.
- Ignore late tile events from the removed revision and isolate a replacement source with the same identifier.

Source revision: `b7b0dc7` in the SDK source repository.

Required third-party licenses and external data formats are preserved.
