#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsSource.h"
#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

@class BharatMapsAttributionInfo;

/**
 Options for ``BharatMapsTileSource`` objects.
 */
typedef NSString *BharatMapsTileSourceOption NS_STRING_ENUM;

/**
 An `NSNumber` object containing an unsigned integer that specifies the minimum
 zoom level at which to display tiles from the source.

 The value should be between 0 and 22, inclusive, and less than
 ``BharatMapsTileSourceOptionMaximumZoomLevel``, if specified. The default value for this
 option is 0.

 This option corresponds to the `minzoom` key in the
 <a href="https://github.com/mapbox/tilejson-spec/tree/master/2.1.0">TileJSON</a>
 specification.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionMinimumZoomLevel;

/**
 An `NSNumber` object containing an unsigned integer that specifies the maximum
 zoom level at which to display tiles from the source.

 The value should be between 0 and 22, inclusive, and less than
 ``BharatMapsTileSourceOptionMinimumZoomLevel``, if specified. The default value for this
 option is 22.

 This option corresponds to the `maxzoom` key in the
 <a href="https://github.com/mapbox/tilejson-spec/tree/master/2.1.0">TileJSON</a>
 specification.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionMaximumZoomLevel;

/**
 An `NSValue` object containing an ``BharatMapsCoordinateBounds`` struct that specifies
 the geographic extent of the source.

 If this option is specified, the SDK avoids requesting any tile that falls
 outside of the coordinate bounds. Otherwise, the SDK requests any tile needed
 to cover the viewport, as it does by default.

 This option corresponds to the `bounds` key in the
 <a href="https://github.com/mapbox/tilejson-spec/tree/master/2.1.0">TileJSON</a>
 specification.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionCoordinateBounds;

#if TARGET_OS_IPHONE
/**
 An HTML string defining the buttons to be displayed in an action sheet when the
 source is part of a map view’s style and the map view’s attribution button is
 pressed.

 By default, no attribution statements are displayed. If the
 ``BharatMapsTileSourceOptionAttributionInfos`` option is specified, this option is
 ignored.

 This option corresponds to the `attribution` key in the
 <a href="https://github.com/mapbox/tilejson-spec/tree/master/2.1.0">TileJSON</a>
 specification.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionAttributionHTMLString;

/**
 An array of ``BharatMapsAttributionInfo`` objects defining the buttons to be displayed
 in an action sheet when the source is part of a map view’s style and the map
 view’s attribution button is pressed.

 By default, no attribution statements are displayed.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionAttributionInfos;
#else
/**
 An HTML string defining the buttons to be displayed in the map view’s
 attribution view when the source is part of the map view’s style.

 By default, no attribution statements are displayed. If the
 ``BharatMapsTileSourceOptionAttributionInfos`` option is specified, this option is
 ignored.

 This option corresponds to the `attribution` key in the
 <a href="https://github.com/mapbox/tilejson-spec/tree/master/2.1.0">TileJSON</a>
 specification.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionAttributionHTMLString;

/**
 An array of ``BharatMapsAttributionInfo`` objects defining the buttons to be displayed
 in the map view’s attribution view when the source is part of the map view’s
 style.

 By default, no attribution statements are displayed.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionAttributionInfos;
#endif

/**
 An `NSNumber` object containing an unsigned integer that specifies the tile
 coordinate system for the source’s tile URLs. The integer corresponds to one of
 the constants described in ``BharatMapsTileCoordinateSystem``.

 The default value for this option is ``BharatMapsTileCoordinateSystem/BharatMapsTileCoordinateSystemXYZ``.

 This option corresponds to the `scheme` key in the
 <a href="https://github.com/mapbox/tilejson-spec/tree/master/2.1.0">TileJSON</a>
 specification.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionTileCoordinateSystem;

/**
 Tile coordinate systems that determine how tile coordinates in tile URLs are
 interpreted.
 */
typedef NS_ENUM(NSUInteger, BharatMapsTileCoordinateSystem) {
  /**
   The origin is at the top-left (northwest), and `y` values increase
   southwards.

   This tile coordinate system is used by Mapbox and OpenStreetMap tile
   servers.
   */
  BharatMapsTileCoordinateSystemXYZ = 0,

  /**
   The origin is at the bottom-left (southwest), and `y` values increase
   northwards.

   This tile coordinate system is used by tile servers that conform to the
   <a href="http://wiki.osgeo.org/wiki/Tile_Map_Service_Specification">Tile Map Service
   Specification</a>.
   */
  BharatMapsTileCoordinateSystemTMS
};

/**
 ``BharatMapsTileSource`` is a map content source that supplies map tiles to be shown on
 the map. The location of and metadata about the tiles are defined either by an
 option dictionary or by an external file that conforms to the
 <a href="https://github.com/mapbox/tilejson-spec/">TileJSON specification</a>.
 A tile source is added to an ``BharatMapsStyle`` object along with one or more
 ``BharatMapsRasterStyleLayer`` or ``BharatMapsRasterStyleLayer`` objects. Use a style layer to
 control the appearance of content supplied by the tile source.

 A tile source is also known as a tile set. To learn about the structure of a
 Mapbox-hosted tile set, view it in
 <a href="https://www.mapbox.com/studio/tilesets/">Mapbox Studio’s Tilesets editor</a>.

 Create instances of ``BharatMapsRasterTileSource`` and ``BharatMapsRasterTileSource`` in order
 to use ``BharatMapsTileSource``'s properties and methods. Do not create instances of
 ``BharatMapsTileSource`` directly, and do not create your own subclasses of this class.
 */
BharatMaps_EXPORT
@interface BharatMapsTileSource : BharatMapsSource

// MARK: Accessing a Source’s Content

/**
 The URL to the TileJSON configuration file that specifies the contents of the
 source.

 If the receiver was initialized using
 `-initWithIdentifier:tileURLTemplates:options`, this property is set to `nil`.
 */
@property (nonatomic, copy, nullable, readonly) NSURL *configurationURL;

// MARK: Accessing Attribution Strings

/**
 An array of ``BharatMapsAttributionInfo`` objects that define the attribution
 statements to be displayed when the map is shown to the user.

 By default, this array is empty. If the source is initialized with a
 configuration URL, this array is also empty until the configuration JSON file
 is loaded.
 */
@property (nonatomic, copy, readonly) NSArray<BharatMapsAttributionInfo *> *attributionInfos;

/**
 The attribution HTML string associated with this source.

 By default, this is nil. If the source is initialized with a
 configuration URL, this is nil until the configuration JSON file
 is loaded.
 */
@property (nonatomic, copy, nullable, readonly) NSString *attributionHTMLString;

@end

NS_ASSUME_NONNULL_END
