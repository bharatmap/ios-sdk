#import "BharatMapsFoundation.h"

#import "BharatMapsRasterTileSource.h"

/**
 An `NSNumber` object containing an unsigned integer that specifies the encoding
 formula for raster-dem tilesets. The integer corresponds to one of
 the constants described in ``BharatMapsDEMEncoding``.

 The default value for this option is ``BharatMapsDEMEncoding/BharatMapsDEMEncodingMapbox``.

 This option cannot be represented in a TileJSON or style JSON file. It is used
 with the ``BharatMapsRasterDEMSource`` class and is ignored when creating a
 ``BharatMapsRasterTileSource`` or ``BharatMapsRasterTileSource`` object.
 */
FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsTileSourceOption BharatMapsTileSourceOptionDEMEncoding;

/**
 The encoding formula used to generate the raster tileset
*/

typedef NS_ENUM(NSUInteger, BharatMapsDEMEncoding) {

  /**
     Raster tiles generated with the [Mapbox encoding
     formula](https://docs.mapbox.com/help/troubleshooting/access-elevation-data/#mapbox-terrain-rgb)
  */
  BharatMapsDEMEncodingMapbox = 0,

  /**
   Raster tiles generated with the [Mapzen Terrarium encoding
   formula](https://aws.amazon.com/public-datasets/terrain/).
  */
  BharatMapsDEMEncodingTerrarium = 1,
};

/**
 ``BharatMapsRasterDEMSource`` is a map content source that supplies rasterized
 <a href="https://en.wikipedia.org/wiki/Digital_elevation_model">digital elevation model</a>
 (DEM) tiles to be shown on the map. The location of and metadata about the
 tiles are defined either by an option dictionary or by an external file that
 conforms to the
 <a href="https://github.com/mapbox/tilejson-spec/">TileJSON specification</a>.
 A raster DEM source is added to an ``BharatMapsStyle`` object along with one or more
 ``BharatMapsHillshadeStyleLayer`` objects. Use a hillshade style layer to control the
 appearance of content supplied by the raster DEM source.

 Each
 <a href="https://maplibre.org/maplibre-style-spec/#sources-raster-dem"><code>raster-dem</code></a>
 source defined by the style JSON file is represented at runtime by an
 ``BharatMapsRasterDEMSource`` object that you can use to initialize new style layers.
 You can also add and remove sources dynamically using methods such as
 ``BharatMapsStyle/addSource:`` and ``BharatMapsStyle/sourceWithIdentifier:``.

 Currently, raster DEM sources only support the format used by
 <a
 href="https://docs.mapbox.com/help/troubleshooting/access-elevation-data/#mapbox-terrain-rgb">Mapbox
 Terrain-RGB</a>.

 ### Example

 ```swift
 let terrainRGBURL = URL(string: "maptiler://sources/terrain-rgb")!
 let source = BharatMapsRasterDEMSource(identifier: "hills", configurationURL: terrainRGBURL)
 mapView.style?.addSource(source)
 ```
 */
BharatMaps_EXPORT
@interface BharatMapsRasterDEMSource : BharatMapsRasterTileSource

@end
