#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsTileServerOptions.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Well-known tile servers
 */
typedef NS_ENUM(NSUInteger, BharatMapsWellKnownTileServer) {
  /**
   Maptiler
   */
  BharatMapsMapTiler,
  /**
   MapLibre
   */
  BharatMapsMapLibre,
  /**
   Mapbox
   */
  BharatMapsMapbox
};

/**
 The ``BharatMapsSettings`` object provides a global way to set SDK properties such
 as apiKey, backend URL, etc.
 */
BharatMaps_EXPORT
@interface BharatMapsSettings : NSObject

// MARK: Tile Server Configuration

/**
 Tile server options
 */
@property (class, copy, nullable) BharatMapsTileServerOptions* tileServerOptions;

// MARK: Authorizing Access

/**
 The API Key used by all instances of ``BharatMapsMapView`` in the current application.
 Setting this property to a value of `nil` has no effect.

 > Note: You must set the API key before attempting to load any style which
    requires the token. Therefore, you should generally set it before creating an instance of
    ``BharatMapsMapView``. The recommended way to set an api key is to add an entry
    to your application’s Info.plist file with the key `BharatMapsApiKey``
    and the type `String`. Alternatively, you may call this method from your
    application delegate’s `-applicationDidFinishLaunching:` method.
 */
@property (class, copy, nullable) NSString* apiKey;

/**
 Instructs the SDk to use the give tile server
 */
+ (void)useWellKnownTileServer:(BharatMapsWellKnownTileServer)tileServer;

@end

NS_ASSUME_NONNULL_END
