#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
@interface BharatMapsRouteOption : NSObject

@property (nonatomic, copy, readonly) NSString *routeId;
@property (nonatomic, assign, readonly) CLLocationDistance distanceMeters;
@property (nonatomic, assign, readonly) NSTimeInterval durationSeconds;
@property (nonatomic, assign, readonly, getter=isSelected) BOOL selected;

- (instancetype)initWithRouteId:(NSString *)routeId
                  distanceMeters:(CLLocationDistance)distanceMeters
                 durationSeconds:(NSTimeInterval)durationSeconds
                        selected:(BOOL)selected NS_DESIGNATED_INITIALIZER;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
