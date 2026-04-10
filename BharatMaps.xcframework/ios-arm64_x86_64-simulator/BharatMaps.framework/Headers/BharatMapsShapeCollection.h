#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsShape.h"

#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 An ``BharatMapsShapeCollection`` object represents a shape consisting of zero or more
 distinct but related shapes that are instances of ``BharatMapsShape``. The constituent
 shapes can be a mixture of different kinds of shapes.

 ``BharatMapsShapeCollection`` is most commonly used to add multiple shapes to a single
 ``BharatMapsShapeSource``. Configure the appearance of an ``BharatMapsShapeSource``’s or
 ``BharatMapsVectorTileSource``’s shape collection collectively using an
 ``BharatMapsSymbolStyleLayer`` object, or use multiple instances of
 ``BharatMapsCircleStyleLayer``, ``BharatMapsCircleStyleLayer``, and ``BharatMapsCircleStyleLayer`` to
 configure the appearance of each kind of shape inside the collection.

 You cannot add an ``BharatMapsShapeCollection`` object directly to a map view as an
 annotation. However, you can create individual ``BharatMapsPointAnnotation``,
 ``BharatMapsPolyline``, and ``BharatMapsPolyline`` objects from the `shapes` array and add those
 annotation objects to the map view using the ``BharatMapsMapView/addAnnotations:``
 method.

 To represent a collection of point, polyline, or polygon shapes, it may be more
 convenient to use an ``BharatMapsPointCollection``, ``BharatMapsPointCollection``, or
 ``BharatMapsMultiPolygon`` object, respectively. To access a shape collection’s
 attributes, use the corresponding ``BharatMapsFeature`` object.

 A shape collection is known as a
 <a href="https://tools.ietf.org/html/rfc7946#section-3.1.8">GeometryCollection</a>
 geometry in GeoJSON.
 */
BharatMaps_EXPORT
@interface BharatMapsShapeCollection : BharatMapsShape

/**
 An array of shapes forming the shape collection.
 */
@property (nonatomic, copy, readonly) NSArray<BharatMapsShape *> *shapes;

/**
 Creates and returns a shape collection consisting of the given shapes.

 @param shapes The array of shapes defining the shape collection. The data in
    this array is copied to the new object.
 @return A new shape collection object.
 */
+ (instancetype)shapeCollectionWithShapes:(NSArray<BharatMapsShape *> *)shapes;

@end

NS_ASSUME_NONNULL_END
