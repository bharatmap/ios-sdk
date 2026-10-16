#import <Foundation/Foundation.h>
#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BharatMapsDataOperation) {
    BharatMapsDataOperationSearch,
    BharatMapsDataOperationHousing,
    BharatMapsDataOperationNearby,
    BharatMapsDataOperationReverse,
    BharatMapsDataOperationUPin
};

/** Authenticated data requests using the initialized SDK's existing Martin authorization. */
BharatMaps_EXPORT
@interface BharatMapsDataClient : NSObject
/**
 Creates a suspended task. Call resume to start or cancel to stop it.
 The server validates operation parameters and must have data access enabled for the organization.
 Search and housing take q/lat/lon; reverse takes lat/lon; nearby takes category/lat/lon and optional limit.
 Route search and UPin authorization parameters are documented in GETTING_STARTED.md. Maximum body size is 1 MiB.
 Completion runs on the session's background queue; HTTP errors and Retry-After remain in the response.
 */
+ (NSURLSessionDataTask *)taskForOperation:(BharatMapsDataOperation)operation
                              parameters:(NSDictionary<NSString *, id> *)parameters
                              completion:(void (^)(NSData * _Nullable data, NSHTTPURLResponse * _Nullable response,
                                                   NSError * _Nullable error))completion;
@end

NS_ASSUME_NONNULL_END
