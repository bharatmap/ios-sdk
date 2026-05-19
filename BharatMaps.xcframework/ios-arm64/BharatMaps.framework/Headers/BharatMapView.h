#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsMapView.h"
#import "BharatMapsMapViewDelegate.h"
#import "BharatMapsAdvancedAnnotation.h"
#import "BharatMapsAdvancedAnnotationOptions.h"
#import "BharatMapsRouteOption.h"
#import "BharatMapsPointAnnotation.h"
#import "BharatMapsPolyline.h"
#import "BharatMapsPolygon.h"

NS_ASSUME_NONNULL_BEGIN

typedef void (^BharatNavigationCallback)(NSError *_Nullable error);
typedef void (^BharatRoutesCallback)(NSArray<BharatMapsRouteOption *> *_Nullable routes, NSError *_Nullable error);
typedef void (^BharatLicenseValidationCallback)(NSDictionary<NSString *, id> *_Nullable result, NSError *_Nullable error);

typedef NS_ENUM(NSInteger, BharatMapStyle) {
    BharatMapStyleLight = 0,
    BharatMapStyleDark = 1,
    BharatMapStyleLightSimplified = 2,
    BharatMapStyleDarkSimplified = 3
};

BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewRouteSelectionDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewRouteSelectionRoutesKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewRouteSelectionSelectedRouteIdKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationStateDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationStateIsActiveKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationInstructionDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationInstructionIconNameKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationInstructionTextKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationInstructionDistanceKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressManeuverDistanceKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressManeuverDurationRemainingKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressDistanceKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressDurationRemainingKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressArrivalTimeMillisKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressNextRoadNameKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressCurrentRoadNameKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressVoiceInstructionTextKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewNavigationTripProgressSpeedKmhKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewTripEndStateDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewTripEndStateIsActiveKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewTripEndStateDistanceMetersKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewTripEndStateShowCalibrationLineKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewCameraFollowStateDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewCameraFollowStateIsFollowingKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewCameraStateDidChangeNotification;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewCameraStateZoomLevelKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewCameraStateMinimumZoomLevelKey;
BharatMaps_EXPORT FOUNDATION_EXTERN NSString *const BharatMapViewCameraStateMaximumZoomLevelKey;

/**
 A simplified high-level map view API for SDK consumers.
 */
BharatMaps_EXPORT
@interface BharatMapView : UIView

/// The underlying map view instance.
@property (nonatomic, strong, readonly) BharatMapsMapView *mapView;

/// Forwarded delegate for map callbacks.
@property (nonatomic, weak, nullable) IBOutlet id delegate;

/// Last known user location.
@property (nonatomic, strong, readonly, nullable) CLLocation *currentUserLocation;
/// Whether navigation session is currently active.
@property (nonatomic, assign, readonly, getter=isNavigationActive) BOOL navigationActive;
/// Whether camera is currently following user location.
@property (nonatomic, assign, readonly) BOOL cameraFollowingUser;

/// Latest preview route options from requestRoutes.
@property (nonatomic, copy, readonly) NSArray<BharatMapsRouteOption *> *routeOptions;

/// Default zoom used by centerOnUserLocation() and first auto-center after user location becomes available.
@property (nonatomic, assign) double defaultZoom;

/// Default location used before first GPS fix and as a fallback for centerOnUserLocation().
@property (nonatomic, assign) CLLocationCoordinate2D defaultLocation;

/// Current built-in map style.
@property (nonatomic, assign) BharatMapStyle mapStyle;
/// Current map viewport padding.
@property (nonatomic, assign) UIEdgeInsets mapPadding;

/// Last validated license token returned by licensing backend.
@property (nonatomic, copy, readonly, nullable) NSString *licenseToken;
/// YES only after successful license validation with a non-empty token.
@property (nonatomic, assign, readonly, getter=isLicenseValidated) BOOL licenseValidated;

- (instancetype)initWithFrame:(CGRect)frame;

- (instancetype)initWithFrame:(CGRect)frame
                      styleURL:(nullable NSURL *)styleURL;

- (instancetype)initWithFrame:(CGRect)frame
                     mapStyle:(BharatMapStyle)mapStyle;

// MARK: License

/**
 Validates SDK API key against Bharat licensing backend using current app bundle id.
 */
- (void)validateLicense:(NSString *)apiKey
             completion:(nullable BharatLicenseValidationCallback)completion NS_SWIFT_NAME(validateLicense(apiKey:completion:));

/**
 Validates SDK API key against Bharat licensing backend with explicit app id override.
 */
- (void)validateLicense:(NSString *)apiKey
                  appId:(nullable NSString *)appId
             completion:(nullable BharatLicenseValidationCallback)completion NS_SWIFT_NAME(validateLicense(apiKey:appId:completion:));

// MARK: Style

- (void)setMapStyle:(BharatMapStyle)mapStyle NS_SWIFT_NAME(setMapStyle(_:));

// MARK: Camera

- (void)setMapPadding:(UIEdgeInsets)padding NS_SWIFT_NAME(setMapPadding(_:));
- (void)animateMapPadding:(UIEdgeInsets)padding
                 duration:(NSTimeInterval)duration NS_SWIFT_NAME(animateMapPadding(_:duration:));

- (void)setLogoMargins:(UIEdgeInsets)margins NS_SWIFT_NAME(setLogoMargins(_:));

- (void)animateCameraTo:(CLLocationCoordinate2D)location
                   zoom:(double)zoom NS_SWIFT_NAME(animateCameraTo(location:zoom:));

- (void)animateCameraTo:(CLLocationCoordinate2D)location
                   zoom:(double)zoom
                bearing:(CLLocationDirection)bearing
                  pitch:(CGFloat)pitch NS_SWIFT_NAME(animateCameraTo(location:zoom:bearing:pitch:));

- (void)moveCameraTo:(CLLocationCoordinate2D)location
                zoom:(double)zoom NS_SWIFT_NAME(moveCameraTo(location:zoom:));

- (void)moveCameraTo:(CLLocationCoordinate2D)location
                zoom:(double)zoom
             bearing:(CLLocationDirection)bearing
               pitch:(CGFloat)pitch NS_SWIFT_NAME(moveCameraTo(location:zoom:bearing:pitch:));

- (void)easeCameraTo:(CLLocationCoordinate2D)location
                zoom:(double)zoom
            duration:(NSTimeInterval)duration NS_SWIFT_NAME(easeCameraTo(location:zoom:duration:));

- (void)easeCameraTo:(CLLocationCoordinate2D)location
                zoom:(double)zoom
             bearing:(CLLocationDirection)bearing
               pitch:(CGFloat)pitch
            duration:(NSTimeInterval)duration NS_SWIFT_NAME(easeCameraTo(location:zoom:bearing:pitch:duration:));

/**
 Fits camera to all provided locations with viewport padding in screen points.
 Returns NO when locations is empty.
 */
- (BOOL)fitCameraToLocations:(NSArray<CLLocation *> *)locations
                 edgePadding:(UIEdgeInsets)edgePadding
                    animated:(BOOL)animated
                    duration:(NSTimeInterval)duration NS_SWIFT_NAME(fitCamera(to:edgePadding:animated:duration:));

// MARK: Map annotations

/**
 Adds a point annotation on map.
 Optionally sets image/title/subtitle.
 */
- (BharatMapsPointAnnotation *)addPointAnnotationAt:(CLLocationCoordinate2D)location
                                               image:(nullable UIImage *)image
                                               title:(nullable NSString *)title
                                            subtitle:(nullable NSString *)subtitle NS_SWIFT_NAME(addPointAnnotation(location:image:title:subtitle:));

/**
 Adds a line annotation from a list of locations.
 Returns nil when there are fewer than 2 points.
 */
- (nullable BharatMapsPolyline *)addLineAnnotationWithLocations:(NSArray<CLLocation *> *)locations
                                                    strokeColor:(UIColor *)strokeColor
                                                      lineWidth:(CGFloat)lineWidth
                                                          alpha:(CGFloat)alpha NS_SWIFT_NAME(addLineAnnotation(locations:strokeColor:lineWidth:alpha:));

/**
 Adds a polygon annotation from a list of locations.
 Returns nil when there are fewer than 3 points.
 Polygon is auto-closed if first and last points differ.
 */
- (nullable BharatMapsPolygon *)addPolygonAnnotationWithLocations:(NSArray<CLLocation *> *)locations
                                                      strokeColor:(UIColor *)strokeColor
                                                        fillColor:(UIColor *)fillColor
                                                        lineWidth:(CGFloat)lineWidth
                                                            alpha:(CGFloat)alpha NS_SWIFT_NAME(addPolygonAnnotation(locations:strokeColor:fillColor:lineWidth:alpha:));

/**
 Adds a regular marker annotation.
 If showCallout is YES and marker has title/subtitle, default callout is shown on tap.
 */
- (BharatMapsPointAnnotation *)addMarkerAt:(CLLocationCoordinate2D)location
                                      title:(nullable NSString *)title
                                   subtitle:(nullable NSString *)subtitle
                                showCallout:(BOOL)showCallout NS_SWIFT_NAME(addMarker(location:title:subtitle:showCallout:));

/**
 Removes a previously added map annotation.
 */
- (void)removeMapAnnotation:(id<BharatMapsAnnotation>)annotation NS_SWIFT_NAME(removeMapAnnotation(_:));

/**
 Clears all map annotations.
 */
- (void)clearMapAnnotations;

// MARK: Custom Markers

/**
 Adds or replaces a lightweight custom marker.
 Use this for dynamic objects such as cars, couriers, drivers, or moving assets.
 */
- (BharatMapsPointAnnotation *)addCustomMarkerWithId:(NSString *)identifier
                                            location:(CLLocationCoordinate2D)location
                                               image:(UIImage *)image NS_SWIFT_NAME(addCustomMarker(id:location:image:));

/**
 Adds or replaces a lightweight custom marker with bearing.
 */
- (BharatMapsPointAnnotation *)addCustomMarkerWithId:(NSString *)identifier
                                            location:(CLLocationCoordinate2D)location
                                               image:(UIImage *)image
                                             bearing:(CLLocationDirection)bearing NS_SWIFT_NAME(addCustomMarker(id:location:image:bearing:));

/**
 Updates custom marker position.
 */
- (BOOL)updateCustomMarkerWithId:(NSString *)identifier
                         location:(CLLocationCoordinate2D)location NS_SWIFT_NAME(updateCustomMarker(id:location:));

/**
 Updates custom marker position and bearing.
 */
- (BOOL)updateCustomMarkerWithId:(NSString *)identifier
                         location:(CLLocationCoordinate2D)location
                          bearing:(CLLocationDirection)bearing NS_SWIFT_NAME(updateCustomMarker(id:location:bearing:));

/**
 Updates custom marker position with optional linear animation.
 */
- (BOOL)updateCustomMarkerWithId:(NSString *)identifier
                         location:(CLLocationCoordinate2D)location
                         animated:(BOOL)animated
                         duration:(NSTimeInterval)duration NS_SWIFT_NAME(updateCustomMarker(id:location:animated:duration:));

/**
 Updates custom marker position and bearing with optional linear animation.
 */
- (BOOL)updateCustomMarkerWithId:(NSString *)identifier
                         location:(CLLocationCoordinate2D)location
                          bearing:(CLLocationDirection)bearing
                         animated:(BOOL)animated
                         duration:(NSTimeInterval)duration NS_SWIFT_NAME(updateCustomMarker(id:location:bearing:animated:duration:));

/**
 Removes a custom marker by id.
 */
- (BOOL)removeCustomMarkerWithId:(NSString *)identifier NS_SWIFT_NAME(removeCustomMarker(id:));

/**
 Removes all custom markers.
 */
- (void)clearCustomMarkers;

// MARK: Advanced Annotations

- (BharatMapsAdvancedAnnotation *)addAdvancedAnnotationWithId:(NSString *)identifier
                                                      location:(CLLocationCoordinate2D)location
                                                       content:(UIView *)content NS_SWIFT_NAME(addAdvancedAnnotation(id:location:content:));

- (BharatMapsAdvancedAnnotation *)addAdvancedAnnotationWithId:(NSString *)identifier
                                                      location:(CLLocationCoordinate2D)location
                                                       content:(UIView *)content
                                                       options:(BharatMapsAdvancedAnnotationOptions *)options NS_SWIFT_NAME(addAdvancedAnnotation(id:location:content:options:));

- (nullable BharatMapsAdvancedAnnotation *)advancedAnnotationForId:(NSString *)identifier NS_SWIFT_NAME(advancedAnnotation(id:));

- (BOOL)updateAdvancedAnnotationWithId:(NSString *)identifier
                              location:(CLLocationCoordinate2D)location NS_SWIFT_NAME(updateAdvancedAnnotation(id:location:));

- (BOOL)updateAdvancedAnnotationOptionsWithId:(NSString *)identifier
                                      options:(BharatMapsAdvancedAnnotationOptions *)options NS_SWIFT_NAME(updateAdvancedAnnotationOptions(id:options:));

- (BOOL)updateAdvancedAnnotationContentWithId:(NSString *)identifier
                                      content:(UIView *)content NS_SWIFT_NAME(updateAdvancedAnnotationContent(id:content:));

- (BOOL)removeAdvancedAnnotationWithId:(NSString *)identifier NS_SWIFT_NAME(removeAdvancedAnnotation(id:));

- (void)clearAdvancedAnnotations;

// MARK: User location

- (void)enableUserLocation;
- (void)disableUserLocation;

/**
 Centers camera on current user location, resets bearing/pitch to 0 and re-enables follow mode.
 */
- (void)centerOnUserLocation:(double)zoom NS_SWIFT_NAME(centerOnUserLocation(zoom:));

/**
 Centers camera on current user location using defaultZoom.
 */
- (void)centerOnUserLocation NS_SWIFT_NAME(centerOnUserLocation());

/**
 Recenters camera to user location using mode-aware behavior.
 In normal map mode it calls centerOnUserLocation(defaultZoom).
 In navigation mode it recenters navigation camera without leaving navigation state.
 */
- (void)recenterCamera NS_SWIFT_NAME(recenterCamera());

/// Returns YES when any user-follow mode is active.
- (BOOL)isUserLocationFollowEnabled;

// MARK: Navigation

/**
 Requests routes (including alternatives) and previews them on map.
 */
- (void)requestRoutesFrom:(CLLocationCoordinate2D)origin
              destination:(CLLocationCoordinate2D)destination
               completion:(nullable BharatRoutesCallback)completion NS_SWIFT_NAME(requestRoutes(origin:destination:completion:));

/**
 Requests routes (including alternatives) from current location and previews them on map.
 */
- (void)requestRoutesTo:(CLLocationCoordinate2D)destination
             completion:(nullable BharatRoutesCallback)completion NS_SWIFT_NAME(requestRoutes(destination:completion:));

/**
 Selects one preview route by id and updates preview styling.
 Returns YES if route exists.
 */
- (BOOL)selectRouteOption:(NSString *)routeId NS_SWIFT_NAME(selectRouteOption(routeId:));

/**
 Starts navigation from the currently selected preview route.
 */
- (void)startSelectedNavigationWithSimulation:(BOOL)simulation
                                    completion:(nullable BharatNavigationCallback)completion NS_SWIFT_NAME(startSelectedNavigation(simulation:completion:));

/**
 Clears preview routes and route selection state without starting navigation.
 */
- (void)clearRoutePreview NS_SWIFT_NAME(clearRoutePreview());

/**
 Starts navigation immediately from origin to destination and draws route on map.
 */
- (void)startNavigationFrom:(CLLocationCoordinate2D)origin
                destination:(CLLocationCoordinate2D)destination
                 simulation:(BOOL)simulation
                 completion:(nullable BharatNavigationCallback)completion NS_SWIFT_NAME(startNavigation(origin:destination:simulation:completion:));

/**
 Convenience overload. Uses current user location as origin.
 */
- (void)startNavigationTo:(CLLocationCoordinate2D)destination
               simulation:(BOOL)simulation
               completion:(nullable BharatNavigationCallback)completion NS_SWIFT_NAME(startNavigation(destination:simulation:completion:));

/**
 Manually requests a reroute while navigation is active.
 */
- (void)rerouteNavigationFrom:(CLLocationCoordinate2D)origin
                  destination:(CLLocationCoordinate2D)destination
                   completion:(nullable BharatNavigationCallback)completion NS_SWIFT_NAME(rerouteNavigation(origin:destination:completion:));

/**
 Manually requests a reroute while navigation is active.
 */
- (void)rerouteNavigationFrom:(CLLocationCoordinate2D)origin
                  destination:(CLLocationCoordinate2D)destination
                   simulation:(BOOL)simulation
                   completion:(nullable BharatNavigationCallback)completion NS_SWIFT_NAME(rerouteNavigation(origin:destination:simulation:completion:));

/**
 Stops active navigation and clears route from map.
 */
- (void)stopNavigation;

/**
 Test helper: when simulated navigation is active, injects an off-route deviation to trigger auto reroute.
 */
- (BOOL)simulateOffRouteDeviation;

/**
 Test helper: when simulated navigation is active, injects an off-route deviation in meters to trigger auto reroute.
 */
- (BOOL)simulateOffRouteDeviation:(double)meters NS_SWIFT_NAME(simulateOffRouteDeviation(meters:));

/**
 Binds an arbitrary view visibility to embedded navigation state.

 @param view The view to bind.
 @param visibleWhenNavigationActive
 `YES`  -> view is visible while navigation is active.
 `NO`   -> view is hidden while navigation is active.
 */
- (void)bindNavigationVisibility:(UIView *)view
      visibleWhenNavigationActive:(BOOL)visibleWhenNavigationActive NS_SWIFT_NAME(bindNavigationVisibility(_:visibleWhenNavigationActive:));

/**
 Removes a previously bound view from navigation visibility handling.
 */
- (void)unbindNavigationVisibility:(UIView *)view NS_SWIFT_NAME(unbindNavigationVisibility(_:));

/**
 Toggles U-Pin map layer visibility.
 When enabled, regular POI/building labels are hidden.
 */
- (void)setUPinLayerEnabled:(BOOL)enabled NS_SWIFT_NAME(setUPinLayerEnabled(_:));

@end

NS_ASSUME_NONNULL_END
