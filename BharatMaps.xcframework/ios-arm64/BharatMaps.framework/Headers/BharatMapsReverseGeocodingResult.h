#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsPoiResult.h"
#import "BharatMapsBuildingNumberResult.h"

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
@interface BharatMapsReverseGeocodingResult : NSObject

@property (nonatomic, assign, readonly) CLLocationCoordinate2D location;
@property (nonatomic, copy, nullable, readonly) NSString *name;
@property (nonatomic, copy, nullable, readonly) NSString *address;
@property (nonatomic, copy, nullable, readonly) NSString *wardNumber;
@property (nonatomic, copy, nullable, readonly) NSString *policeStationPhone;
@property (nonatomic, strong, nullable, readonly) NSNumber *nearestAddressDistanceMeters;
@property (nonatomic, copy, readonly) NSArray<BharatMapsPoiResult *> *nearbyPois;
@property (nonatomic, copy, readonly) NSArray<BharatMapsBuildingNumberResult *> *nearbyBuildingNumbers;

- (instancetype)initWithLocation:(CLLocationCoordinate2D)location
                            name:(nullable NSString *)name
                         address:(nullable NSString *)address
                      wardNumber:(nullable NSString *)wardNumber
               policeStationPhone:(nullable NSString *)policeStationPhone
       nearestAddressDistanceMeters:(nullable NSNumber *)nearestAddressDistanceMeters
                       nearbyPois:(nullable NSArray<BharatMapsPoiResult *> *)nearbyPois
             nearbyBuildingNumbers:(nullable NSArray<BharatMapsBuildingNumberResult *> *)nearbyBuildingNumbers;

@end

NS_ASSUME_NONNULL_END
