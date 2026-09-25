# BharatMaps iOS SDK (Binary via SPM)

This repository distributes `BharatMaps` as a binary Swift Package.

Current release: **1.0.63**. See [Getting Started](GETTING_STARTED.md) for the public API.

**Do not use 1.0.55:** it has a packaging regression (stale style resources and invalid resource signatures). Use 1.0.56 or later.

## Install

In Xcode:

1. `File` -> `Add Package Dependencies...`
2. Use URL: `https://github.com/bharatmap/ios-sdk.git`
3. Select a version tag
4. Add product `BharatMaps`

## Notes

- Binary only (`BharatMaps.xcframework`)
- No SDK source code is distributed through this package
- Minimum iOS version: 13.0
