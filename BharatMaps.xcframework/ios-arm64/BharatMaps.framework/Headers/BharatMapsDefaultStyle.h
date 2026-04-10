#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

/**
 The ``BharatMapsDefaultStyle`` defines the predefined vendor style
 */
BharatMaps_EXPORT
@interface BharatMapsDefaultStyle : NSObject

/**
The style URL
 */
@property (nonatomic, retain) NSURL* url;

/**
The style name
 */
@property (nonatomic, retain) NSString* name;

/**
The style version
 */
@property (nonatomic) int version;

@end

NS_ASSUME_NONNULL_END
