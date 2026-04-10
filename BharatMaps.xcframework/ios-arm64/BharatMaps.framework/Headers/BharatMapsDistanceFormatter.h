#import <CoreLocation/CoreLocation.h>
#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

/**
 ``BharatMapsDistanceFormatter`` implements a formatter object meant to be used for
 geographic distances. The user’s current locale will be used by default
 but it can be overriden by changing the locale property of the numberFormatter.
 */
BharatMaps_EXPORT
@interface BharatMapsDistanceFormatter : NSLengthFormatter

/**
 Returns a localized formatted string for the provided distance.

 @param distance The distance, measured in meters.
 @return A localized formatted distance string including units.
 */
- (NSString *)stringFromDistance:(CLLocationDistance)distance;

@end

NS_ASSUME_NONNULL_END
