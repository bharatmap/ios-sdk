#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
@interface BharatMapsActiveRoute : NSObject
@property (nonatomic, copy, readonly) NSString *sessionId;
@property (nonatomic, assign, readonly) NSUInteger revision;
/// WGS84 coordinates of the geometry actually used by guidance, in travel order.
@property (nonatomic, copy, readonly) NSArray<CLLocation *> *locations;
@property (nonatomic, assign, readonly) double distanceMeters;
@property (nonatomic, assign, readonly) double durationSeconds;
@end

BharatMaps_EXPORT
@interface BharatMapsNavigationInstruction : NSObject
@property (nonatomic, copy, readonly) NSString *sessionId;
@property (nonatomic, assign, readonly) NSUInteger routeRevision;
@property (nonatomic, assign, readonly) NSUInteger stepIndex;
@property (nonatomic, strong, readonly) CLLocation *location;
@property (nonatomic, copy, readonly, nullable) NSString *text;
@property (nonatomic, copy, readonly, nullable) NSString *iconName;
@end

typedef NS_ENUM(NSInteger, BharatMapsRerouteState) {
    BharatMapsRerouteStateStarted,
    BharatMapsRerouteStateSucceeded,
    BharatMapsRerouteStateFailed,
    BharatMapsRerouteStateCancelled
};

BharatMaps_EXPORT
@interface BharatMapsRerouteEvent : NSObject
@property (nonatomic, copy, readonly) NSString *sessionId;
@property (nonatomic, copy, readonly) NSString *requestId;
@property (nonatomic, assign, readonly) BharatMapsRerouteState state;
@property (nonatomic, strong, readonly, nullable) BharatMapsActiveRoute *route;
@property (nonatomic, strong, readonly, nullable) NSError *error;
@end

BharatMaps_EXPORT
@interface BharatMapsRerouteRequest : NSObject
@property (nonatomic, copy, readonly) NSString *requestId;
@property (nonatomic, strong, readonly) BharatMapsActiveRoute *activeRoute;
@property (nonatomic, strong, readonly) CLLocation *origin;
/// Unvisited intermediate waypoints followed by the destination, in travel order.
@property (nonatomic, copy, readonly) NSArray<CLLocation *> *remainingWaypoints;
@property (nonatomic, assign, readonly) CLLocationDirection bearing;
@end

/// Return exactly one selected route in an OSRM routes/data.routes response.
/// Encoded geometry uses polyline6; GeoJSON LineString is also accepted.
typedef void (^BharatMapsRerouteCompletion)(NSData *_Nullable responseData, NSError *_Nullable error);
typedef void (^BharatMapsRerouteHandler)(BharatMapsRerouteRequest *request, BharatMapsRerouteCompletion completion);

NS_ASSUME_NONNULL_END
