# 1.0.36

- Prevent startup and explicit recenter from being interrupted by `mapPadding` updates.
- Preserve the target user coordinate, requested zoom, follow state and camera reset while padding changes.
- Defer repeated padding updates during recenter and resume active padding animation with its remaining duration afterward.
- Preserve gesture and app-owned camera cancellation semantics while applying requested padding.

Source revision: `15cd17d` in the SDK source repository.

Required third-party licenses and external data formats are preserved.
