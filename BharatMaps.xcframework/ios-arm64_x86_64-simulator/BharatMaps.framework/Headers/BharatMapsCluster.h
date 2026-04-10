#import "BharatMapsFoundation.h"

@protocol BharatMapsFeature;

NS_ASSUME_NONNULL_BEGIN

/**
 An `NSUInteger` constant used to indicate an invalid cluster identifier.
 This indicates a missing cluster feature.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const NSUInteger BharatMapsClusterIdentifierInvalid;

/**
 A protocol that feature subclasses (i.e. those already conforming to
 the ``BharatMapsFeature`` protocol) conform to if they represent clusters.

 Currently the only class that conforms to ``BharatMapsCluster`` is
 ``BharatMapsPointFeatureCluster`` (a subclass of ``BharatMapsPointFeatureCluster``).

 To check if a feature is a cluster, check conformity to ``BharatMapsCluster``, for
 example:

 ```swift
 let shape = try! BharatMapsShape(data: clusterShapeData, encoding: String.Encoding.utf8.rawValue)

 guard let pointFeature = shape as? BharatMapsPointFeature else {
     throw ExampleError.unexpectedFeatureType
 }

 // Check for cluster conformance
 guard let cluster = pointFeature as? BharatMapsCluster else {
     throw ExampleError.featureIsNotACluster
 }

 // Currently the only supported class that conforms to ``BharatMapsCluster`` is
 // ``BharatMapsPointFeatureCluster``
 guard cluster is BharatMapsPointFeatureCluster else {
     throw ExampleError.unexpectedFeatureType
 }
 ```
 */
BharatMaps_EXPORT
@protocol BharatMapsCluster <BharatMapsFeature>

/** The identifier for the cluster. */
@property (nonatomic, readonly) NSUInteger clusterIdentifier;

/** The number of points within this cluster */
@property (nonatomic, readonly) NSUInteger clusterPointCount;

@end

NS_ASSUME_NONNULL_END
