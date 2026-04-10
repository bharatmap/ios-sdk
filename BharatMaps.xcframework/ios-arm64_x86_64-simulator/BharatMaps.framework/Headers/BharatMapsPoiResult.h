#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
@interface BharatMapsPoiResult : NSObject

@property (nonatomic, assign, readonly) CLLocationCoordinate2D location;
@property (nonatomic, copy, nullable, readonly) NSString *name;
@property (nonatomic, copy, nullable, readonly) NSString *address;
@property (nonatomic, copy, nullable, readonly) NSString *phone;
@property (nonatomic, copy, nullable, readonly) NSString *website;
@property (nonatomic, copy, readonly) NSString *category;
@property (nonatomic, copy, readonly) NSString *subcategory;
@property (nonatomic, strong, nullable, readonly) NSNumber *distanceMeters;

- (instancetype)initWithLocation:(CLLocationCoordinate2D)location
                            name:(nullable NSString *)name
                         address:(nullable NSString *)address
                           phone:(nullable NSString *)phone
                         website:(nullable NSString *)website
                        category:(NSString *)category
                     subcategory:(NSString *)subcategory
                   distanceMeters:(nullable NSNumber *)distanceMeters;

@end

NS_ASSUME_NONNULL_END
