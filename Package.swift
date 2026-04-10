// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "BharatMaps",
    platforms: [
        .iOS(.v13)
    ],
    products: [
        .library(
            name: "BharatMaps",
            targets: ["BharatMaps"]
        )
    ],
    targets: [
        .binaryTarget(
            name: "BharatMaps",
            path: "BharatMaps.xcframework"
        )
    ]
)
