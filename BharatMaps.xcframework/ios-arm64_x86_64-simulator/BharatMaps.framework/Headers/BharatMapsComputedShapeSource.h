#import "BharatMapsFoundation.h"
#import "BharatMapsGeometry.h"
#import "BharatMapsShapeSource.h"
#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

@protocol BharatMapsFeature;

/**
 An `NSNumber` object containing a Boolean value; specifies whether the shape of
 an ``BharatMapsComputedShapeSource`` should be wrapped to accomodate coordinates with
 longitudes beyond −180 and 180. The default value is `NO`.

 Setting this option to `YES` affects rendering performance.

 This option is used with the ``BharatMapsComputedShapeSource`` class; it is ignored when
 creating an ``BharatMapsShapeSource`` object.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsShapeSourceOption BharatMapsShapeSourceOptionWrapsCoordinates;

/**
 An `NSNumber` object containing a Boolean value; specifies whether the shape of
 an ``BharatMapsComputedShapeSource`` should be clipped at the edge of each tile. The
 default value is `NO`.

 Setting this option to `YES` affects rendering performance. Use this option to
 clip ``BharatMapsPolyline``s and ``BharatMapsPolyline``s at tile boundaries without artifacts.

 This option is used with the ``BharatMapsComputedShapeSource`` class; it is ignored when
 creating an ``BharatMapsShapeSource`` object.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsShapeSourceOption BharatMapsShapeSourceOptionClipsCoordinates;

FOUNDATION_EXTERN BharatMaps_EXPORT BharatMapsExceptionName const BharatMapsInvalidDatasourceException;

/**
 Data source for ``BharatMapsComputedShapeSource``. This protocol defines two optional methods for fetching
 data, one based on tile coordinates, and one based on a bounding box. Classes that implement this
 protocol must implement one, and only one of the methods. Methods on this protocol will not be
 called on main thread, they will be called on the caller's `requestQueue`.
 */
@protocol BharatMapsComputedShapeSourceDataSource <NSObject>

@optional
/**
 Fetch features for a tile. This method will not be invoked on the main queue, it
 will be invoked on the caller's `requestQueue`.
 @param x Tile X coordinate.
 @param y Tile Y coordinate.
 @param zoomLevel Tile zoom level.
 */
- (NSArray<BharatMapsShape<BharatMapsFeature> *> *)featuresInTileAtX:(NSUInteger)x
                                                     y:(NSUInteger)y
                                             zoomLevel:(NSUInteger)zoomLevel;

/**
 Fetch features for a tile. This method will not be invoked on the main queue, it
 will be invoked on the caller's `requestQueue`.
 @param bounds The bounds to fetch data for.
 @param zoomLevel Tile zoom level.
 */
- (NSArray<BharatMapsShape<BharatMapsFeature> *> *)featuresInCoordinateBounds:(BharatMapsCoordinateBounds)bounds
                                                      zoomLevel:(NSUInteger)zoomLevel;

@end

/**
 ``BharatMapsComputedShapeSource`` is a map content source that supplies vector shapes,
 one tile at a time, to be shown on the map on demand. You implement a class
 conforming to the ``BharatMapsComputedShapeSourceDataSource`` protocol that returns
 instances of ``BharatMapsShape`` or ``BharatMapsShape``, then add a computed shape source to an
 ``BharatMapsStyle`` object along with an ``BharatMapsStyle`` object. The vector style
 layer defines the appearance of any content supplied by the computed shape
 source.

 ``BharatMapsComputedShapeSource`` is similar to ``BharatMapsComputedShapeSource`` but is optimized for
 data sets that change dynamically or are too large to fit completely in memory.
 It is also useful for data that is divided into tiles in a format other than
 <a href="https://www.mapbox.com/vector-tiles/">Mapbox Vector Tiles</a>. For
 <a href="http://geojson.org/">GeoJSON</a> data, use the ``BharatMapsShapeSource`` class.
 For static tiles or Mapbox Vector Tiles, use the ``BharatMapsVectorTileSource`` class.

 You can add and remove sources dynamically using methods such as
 ``BharatMapsStyle/addSource:`` and ``BharatMapsStyle/sourceWithIdentifier:``. This class
 cannot be represented in a style JSON file; you must add it ot the style at
 runtime.
 */
BharatMaps_EXPORT
@interface BharatMapsComputedShapeSource : BharatMapsSource

/**
 Returns a custom shape data source initialized with an identifier, and a
 dictionary of options for the source according to the
 <a href="https://maplibre.org/maplibre-style-spec/#sources-geojson">style
 specification</a>.

 This class supports the following options:
 ``BharatMapsShapeSourceOptionMinimumZoomLevel``, ``BharatMapsShapeSourceOptionMinimumZoomLevel``,
 ``BharatMapsShapeSourceOptionBuffer``,
 ``BharatMapsShapeSourceOptionSimplificationTolerance``,
 ``BharatMapsShapeSourceOptionWrapsCoordinates``, and
 ``BharatMapsShapeSourceOptionClipsCoordinates``. Shapes provided by a computed
 shape source cannot be clustered.

 @param identifier A string that uniquely identifies the source.
 @param options An `NSDictionary` of options for this source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                           options:(nullable NSDictionary<BharatMapsShapeSourceOption, id> *)options
    NS_DESIGNATED_INITIALIZER;

/**
 Returns a custom shape data source initialized with an identifier, data source, and a
 dictionary of options for the source according to the
 <a href="https://maplibre.org/maplibre-style-spec/#sources-geojson">style
 specification</a>.

 This class supports the following options:
 ``BharatMapsShapeSourceOptionMinimumZoomLevel``, ``BharatMapsShapeSourceOptionMinimumZoomLevel``,
 ``BharatMapsShapeSourceOptionBuffer``,
 ``BharatMapsShapeSourceOptionSimplificationTolerance``,
 ``BharatMapsShapeSourceOptionWrapsCoordinates``, and
 ``BharatMapsShapeSourceOptionClipsCoordinates``. Shapes provided by a computed shape
 source cannot be clustered.

 @param identifier A string that uniquely identifies the source.
 @param dataSource An object conforming to BharatMapsComputedShapeSourceDataSource protocol that will
 provide the shape data.
 @param options An `NSDictionary` of options for this source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier
                        dataSource:(id<BharatMapsComputedShapeSourceDataSource>)dataSource
                           options:(nullable NSDictionary<BharatMapsShapeSourceOption, id> *)options;
/**
 Invalidates all the features and properties intersecting with or contained in
 the specified bounds. New fetch requests will immediately be invoked on the
 ``BharatMapsComputedShapeSourceDataSource``.
 @param bounds  Coordinate bounds to invalidate.
 */
- (void)invalidateBounds:(BharatMapsCoordinateBounds)bounds;

/**
 Invalidates all the feautres and properties of a given tile. A new fetch request
 will immediately be invoked on the ``BharatMapsComputedShapeSourceDataSource``.
 @param x Tile X coordinate.
 @param y Tile Y coordinate.
 @param zoomLevel Tile zoom level.
 */
- (void)invalidateTileAtX:(NSUInteger)x y:(NSUInteger)y zoomLevel:(NSUInteger)zoomLevel;

/**
 Set a new set of features for a tile. This method can be invkoed from background threads.
 For best performance, use this method only to update tiles that have already been requested
 through ``BharatMapsComputedShapeSourceDataSource/``
 @param features  Features for the tile.
 @param x         Tile X coordinate.
 @param y         Tile Y coordinate.
 @param zoomLevel Tile zoom level.
 */
- (void)setFeatures:(NSArray<BharatMapsShape<BharatMapsFeature> *> *)features
          inTileAtX:(NSUInteger)x
                  y:(NSUInteger)y
          zoomLevel:(NSUInteger)zoomLevel;

/**
 An object that implements the ``BharatMapsComputedShapeSourceDataSource`` protocol that will be queried
 for tile data.
 */
@property (nonatomic, weak, nullable) id<BharatMapsComputedShapeSourceDataSource> dataSource;

/**
 A queue that calls to the data source will be made on.
 */
@property (nonatomic, readonly) NSOperationQueue *requestQueue;

@end

NS_ASSUME_NONNULL_END
