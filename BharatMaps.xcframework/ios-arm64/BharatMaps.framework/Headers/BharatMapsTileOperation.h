#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, BharatMapsTileOperation) {
  BharatMapsTileOperationRequestedFromCache,    ///< A read request from the cache
  BharatMapsTileOperationRequestedFromNetwork,  ///< A read request from the online source
  BharatMapsTileOperationLoadFromNetwork,       ///< Tile data from the network has been retrieved
  BharatMapsTileOperationLoadFromCache,         ///< Tile data from the cache has been retrieved
  BharatMapsTileOperationStartParse,            ///< Background processing of tile data has been initiated
  BharatMapsTileOperationEndParse,              ///< Background processing of tile data has been completed
  BharatMapsTileOperationError,                 ///< An error occurred while loading the tile
  BharatMapsTileOperationCancelled,             ///< Loading of a tile was cancelled
  BharatMapsTileOperationNullOp,                ///< No operation has taken place
};
