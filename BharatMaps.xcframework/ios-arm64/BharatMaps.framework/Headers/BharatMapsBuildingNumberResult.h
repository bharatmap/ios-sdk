#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
@interface BharatMapsBuildingNumberResult : NSObject

@property (nonatomic, assign, readonly) CLLocationCoordinate2D location;
@property (nonatomic, copy, readonly) NSString *buildingNumber;
@property (nonatomic, copy, readonly) NSString *title;
@property (nonatomic, copy, nullable, readonly) NSString *address;
@property (nonatomic, strong, nullable, readonly) NSNumber *distanceMeters;

- (instancetype)initWithLocation:(CLLocationCoordinate2D)location
                  buildingNumber:(NSString *)buildingNumber
                           title:(NSString *)title
                         address:(nullable NSString *)address
                   distanceMeters:(nullable NSNumber *)distanceMeters;

@end

NS_ASSUME_NONNULL_END
