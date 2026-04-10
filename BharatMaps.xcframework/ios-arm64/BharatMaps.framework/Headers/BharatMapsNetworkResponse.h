#import <Foundation/Foundation.h>
#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
@interface BharatMapsNetworkResponse : NSObject

@property (retain, nullable) NSError *error;
@property (retain, nullable) NSData *data;
@property (retain, nullable) NSURLResponse *response;

+ (BharatMapsNetworkResponse *)responseWithData:(NSData *)data
                             urlResponse:(NSURLResponse *)response
                                   error:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
