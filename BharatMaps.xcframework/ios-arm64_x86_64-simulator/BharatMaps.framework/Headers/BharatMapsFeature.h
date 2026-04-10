#import <Foundation/Foundation.h>

#import "BharatMapsCluster.h"
#import "BharatMapsFoundation.h"
#import "BharatMapsPointAnnotation.h"
#import "BharatMapsPointCollection.h"
#import "BharatMapsPolygon.h"
#import "BharatMapsPolyline.h"
#import "BharatMapsShapeCollection.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The ``BharatMapsFeature``  protocol is used to provide details about geographic features
 contained in an ``BharatMapsShapeSource`` or ``BharatMapsVectorTileSource`` object. Each concrete
 subclass of ``BharatMapsShape`` in turn has a subclass that conforms to this protocol. A
 feature object associates a shape with an optional identifier and attributes.

 You can add custom data to display on the map by creating feature objects and
 adding them to an ``BharatMapsShapeSource`` using the
 ``BharatMapsShapeSource/initWithIdentifier:shape:options:`` method or
 ``BharatMapsShapeSource/shape`` property.

 In addition to adding data to the map, you can also extract data from the map:
 ``BharatMapsMapView/visibleFeaturesAtPoint:`` and related methods return feature
 objects that correspond to features in the source. This enables you to inspect
 the properties of features in vector tiles loaded by ``BharatMapsVectorTileSource``
 objects. You also reuse these feature objects as overlay annotations.

 While it is possible to add ``BharatMapsFeature``-conforming objects to the map as
 annotations using ``BharatMapsMapView/addAnnotations:`` and related methods, doing so
 has trade-offs:

 - Features added as annotations will not have ``identifier`` or ``attributes``
 properties when used with feature querying.

 - Features added as annotations become interactive. Taps and selection can be
 handled in ``BharatMapsMapViewDelegate/mapView:didSelectAnnotation:``.
 */
@protocol BharatMapsFeature <BharatMapsAnnotation>

/**
 An object that uniquely identifies the feature in its containing content
 source.

 You can configure an ``BharatMapsVectorStyleLayer`` object to include or exclude a
 specific feature in an ``BharatMapsShapeSource`` or ``BharatMapsVectorTileSource``. In the
 ``BharatMapsVectorStyleLayer/predicate`` property, compare the special `$id` attribute
 to the feature’s identifier.

 In vector tiles loaded by ``BharatMapsVectorTileSource`` objects, the identifier
 corresponds to the
 <a href="https://github.com/mapbox/vector-tile-spec/tree/master/2.1#42-features">feature
 identifier</a>
 (`id`). If the source does not specify the feature’s identifier, the value of
 this property is `nil`. If specified, the identifier may be an integer,
 floating-point number, or string. These data types are mapped to instances of
 the following Foundation classes:

 | In the tile source        | This property |
 |---------------------------|-------------------------------------------------------------------------------|
 | Integer                   | `NSNumber` (use the `unsignedLongLongValue` or `longLongValue`
 property)      | | Floating-point number      | `NSNumber` (use the `doubleValue` property) | |
 String                    | `NSString` |

 The identifier should be set before adding the feature to an ``BharatMapsShapeSource``
 object; setting it afterwards has no effect on the map’s contents. While it is
 possible to change this value on feature instances obtained from
 ``BharatMapsMapView/visibleFeaturesAtPoint:`` and related methods, doing so likewise
 has no effect on the map’s contents.
 */
@property (nonatomic, copy, nullable) id identifier;

/**
 A dictionary of attributes for this feature.

 You can configure an ``BharatMapsVectorStyleLayer`` object to include or exclude a
 specific feature in an ``BharatMapsShapeSource`` or ``BharatMapsVectorTileSource``. In the
 ``BharatMapsVectorStyleLayer/predicate`` property, compare a key of the attribute
 dictionary to the value you want to include. For example, if you want an
 ``BharatMapsLineStyleLayer`` object to display only important features, you might assign
 a value above 50 to the important features’ `importance` attribute, then set
 ``BharatMapsVectorStyleLayer/predicate`` to an
 [`NSPredicate`](https://developer.apple.com/documentation/foundation/nspredicate) with the format
 `importance > 50`.

 You can also configure many layout and paint attributes of an ``BharatMapsStyleLayer``
 object to match the value of an attribute in this dictionary whenever it
 renders this feature. For example, if you display features in an
 ``BharatMapsShapeSource`` using an ``BharatMapsCircleStyleLayer``, you can assign a `halfway`
 attribute to each of the source’s features, then set
 ``BharatMapsCircleStyleLayer/circleRadius`` to an expression for the key path `halfway`.

 The ``BharatMapsSymbolStyleLayer/text`` and ``BharatMapsSymbolStyleLayer/iconImageName``
 properties allow you to use attributes yet another way. For example, to label
 features in an ``BharatMapsShapeSource`` object by their names, you can assign a `name`
 attribute to each of the source’s features, then set
 ``BharatMapsSymbolStyleLayer/text`` to an expression for the constant string value
 `{name}`. See the
 <a href="../predicates-and-expressions.html">Predicates and Expressions</a>
 guide for more information about expressions.

 In vector tiles loaded by ``BharatMapsVectorTileSource`` objects, the keys and values of
 each feature’s attribute dictionary are determined by the source. Each
 attribute name is a string, while each attribute value may be a null value,
 Boolean value, integer, floating-point number, or string. These data types are
 mapped to instances of the following Foundation classes:

 | In the tile source        | In this dictionary |
 |---------------------------|-------------------------------------------------------------------------------|
 | Null                      | `NSNull` | | Boolean                   | `NSNumber` (use the
 `boolValue` property)                                     | | Integer                   |
 `NSNumber` (use the `unsignedLongLongValue` or `longLongValue` property)      | | Floating-point
 number      | `NSNumber` (use the `doubleValue` property)                                  | |
 String                    | `NSString` |

 When adding a feature to an ``BharatMapsShapeSource``, use the same Foundation types
 listed above for each attribute value. In addition to the Foundation types, you
 may also set an attribute to an `NSColor` (macOS) or `UIColor` (iOS), which
 will be converted into its
 <a href="https://maplibre.org/maplibre-style-spec/types/#color">CSS string representation</a>
 when the feature is added to an ``BharatMapsShapeSource``. This can be convenient when
 using the attribute to supply a value for a color-typed layout or paint
 attribute via a key path expression.

 Note that while it is possible to change this value on feature
 instances obtained from ``BharatMapsMapView/visibleFeaturesAtPoint:`` and related
 methods, there will be no effect on the map. Setting this value can be useful
 when the feature instance is used to initialize an ``BharatMapsShapeSource`` and that
 source is added to the map and styled.
 */
@property (nonatomic, copy) NSDictionary<NSString *, id> *attributes;

/**
 Returns the feature attribute for the given attribute name.

 See the ``attributes`` property’s documentation for details on keys and values
 associated with this method.
 */
- (nullable id)attributeForKey:(NSString *)key;

/**
 Returns a dictionary that can be serialized as a GeoJSON Feature representation
 of an instance of an ``BharatMapsFeature`` subclass.

 The dictionary includes a `geometry` key corresponding to the receiver’s
 underlying geometry data, a `properties` key corresponding to the receiver’s
 `attributes` property, and an `id` key corresponding to the receiver’s
 ``identifier` property.
 */
- (NSDictionary<NSString *, id> *)geoJSONDictionary;

@end

/**
 An ``BharatMapsEmptyFeature`` object associates an empty shape with an optional
 identifier and attributes.
 */
BharatMaps_EXPORT
@interface BharatMapsEmptyFeature : BharatMapsShape <BharatMapsFeature>
@end

/**
 An ``BharatMapsPointFeature`` object associates a point shape with an optional
 identifier and attributes.

 #### Related examples
 - <doc:WebAPIDataExample>
 */
BharatMaps_EXPORT
@interface BharatMapsPointFeature : BharatMapsPointAnnotation <BharatMapsFeature>
@end

/**
 An ``BharatMapsPointFeatureCluster`` object associates a point shape (with an optional
 identifier and attributes) and represents a point cluster.

 @see ``BharatMapsCluster``

 #### Related examples
 TODO: Clustering point data, learn how to initialize
 clusters and add them to your map.
 */
BharatMaps_EXPORT
@interface BharatMapsPointFeatureCluster : BharatMapsPointFeature <BharatMapsCluster>
@end

/**
 An ``BharatMapsPolylineFeature`` object associates a polyline shape with an optional
 identifier and attributes.

 A polyline feature is known as a
 <a href="https://tools.ietf.org/html/rfc7946#section-3.1.4">LineString</a>
 feature in GeoJSON.

 #### Related examples
 - <doc:AnimatedLineExample>
 */
BharatMaps_EXPORT
@interface BharatMapsPolylineFeature : BharatMapsPolyline <BharatMapsFeature>
@end

/**
 An ``BharatMapsPolygonFeature`` object associates a polygon shape with an optional
 identifier and attributes.
 */
BharatMaps_EXPORT
@interface BharatMapsPolygonFeature : BharatMapsPolygon <BharatMapsFeature>
@end

/**
 An ``BharatMapsPointCollectionFeature`` object associates a point collection with an
 optional identifier and attributes.

 A point collection feature is known as a
 <a href="https://tools.ietf.org/html/rfc7946#section-3.1.3">MultiPoint</a>
 feature in GeoJSON.
 */
BharatMaps_EXPORT
@interface BharatMapsPointCollectionFeature : BharatMapsPointCollection <BharatMapsFeature>
@end

// https://github.com/mapbox/mapbox-gl-native/issues/7473
@compatibility_alias BharatMapsMultiPointFeature BharatMapsPointCollectionFeature;

/**
 An ``BharatMapsMultiPolylineFeature`` object associates a multipolyline shape with an
 optional identifier and attributes.

 A multipolyline feature is known as a
 <a href="https://tools.ietf.org/html/rfc7946#section-3.1.5">MultiLineString</a>
 feature in GeoJSON.
 */
BharatMaps_EXPORT
@interface BharatMapsMultiPolylineFeature : BharatMapsMultiPolyline <BharatMapsFeature>
@end

/**
 An ``BharatMapsMultiPolygonFeature`` object associates a multipolygon shape with an
 optional identifier and attributes.
 */
BharatMaps_EXPORT
@interface BharatMapsMultiPolygonFeature : BharatMapsMultiPolygon <BharatMapsFeature>
@end

/**
 An ``BharatMapsShapeCollectionFeature`` object associates a shape collection with an
 optional identifier and attributes.

 ``BharatMapsShapeCollectionFeature`` is most commonly used to add multiple shapes to a
 single ``BharatMapsShapeSource``. Configure the appearance of an ``BharatMapsSource``’s shape
 collection collectively using an ``BharatMapsSymbolStyleLayer`` object, or use multiple
 instances of ``BharatMapsCircleStyleLayer``, ``BharatMapsFillStyleLayer``, and
 ``BharatMapsLineStyleLayer`` to configure the appearance of each kind of shape inside
 the collection.

 A shape collection feature is known as a
 <a href="https://tools.ietf.org/html/rfc7946#section-3.3">feature collection</a>
 in GeoJSON.

 #### Related examples
 TODO: Add multiple shapes from a single shape source, learn how to
 add shape data to your map using an ``BharatMapsShapeCollectionFeature`` object.
 */
BharatMaps_EXPORT
@interface BharatMapsShapeCollectionFeature : BharatMapsShapeCollection <BharatMapsFeature>

@property (nonatomic, copy, readonly) NSArray<BharatMapsShape<BharatMapsFeature> *> *shapes;

+ (instancetype)shapeCollectionWithShapes:(NSArray<BharatMapsShape<BharatMapsFeature> *> *)shapes;

@end

NS_ASSUME_NONNULL_END
