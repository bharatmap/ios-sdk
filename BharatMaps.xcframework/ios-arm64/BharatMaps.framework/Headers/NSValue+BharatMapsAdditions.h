#import <Foundation/Foundation.h>

#import "BharatMapsGeometry.h"
#import "BharatMapsLight.h"
#import "BharatMapsOfflinePack.h"
#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 Methods for round-tripping values for Mapbox-defined types.
 */
@interface NSValue (BharatMapsAdditions)

// MARK: Working with Geographic Coordinate Values

/**
 Creates a new value object containing the specified Core Location geographic
 coordinate structure.

 @param coordinate The value for the new object.
 @return A new value object that contains the geographic coordinate information.
 */
+ (instancetype)valueWithBharatMapsCoordinate:(CLLocationCoordinate2D)coordinate;

/**
 The Core Location geographic coordinate structure representation of the value.
 */
@property (readonly) CLLocationCoordinate2D BharatMapsCoordinateValue;

/**
 Creates a new value object containing the specified Mapbox map point structure.

 @param point The value for the new object.
 @return A new value object that contains the coordinate and zoom level information.
 */
+ (instancetype)valueWithBharatMapsMapPoint:(BharatMapsMapPoint)point;

/**
 The Mapbox map point structure representation of the value.
 */
@property (readonly) BharatMapsMapPoint BharatMapsMapPointValue;

/**
 Creates a new value object containing the specified Mapbox coordinate span
 structure.

 @param span The value for the new object.
 @return A new value object that contains the coordinate span information.
 */
+ (instancetype)valueWithBharatMapsCoordinateSpan:(BharatMapsCoordinateSpan)span;

/**
 The Mapbox coordinate span structure representation of the value.
 */
@property (readonly) BharatMapsCoordinateSpan BharatMapsCoordinateSpanValue;

/**
 Creates a new value object containing the specified Mapbox coordinate bounds
 structure.

 @param bounds The value for the new object.
 @return A new value object that contains the coordinate bounds information.
 */
+ (instancetype)valueWithBharatMapsCoordinateBounds:(BharatMapsCoordinateBounds)bounds;

/**
 The Mapbox coordinate bounds structure representation of the value.
 */
@property (readonly) BharatMapsCoordinateBounds BharatMapsCoordinateBoundsValue;

/**
 Creates a new value object containing the specified Mapbox coordinate
 quad structure.

 @param quad The value for the new object.
 @return A new value object that contains the coordinate quad information.
 */
+ (instancetype)valueWithBharatMapsCoordinateQuad:(BharatMapsCoordinateQuad)quad;

/**
 The Mapbox coordinate quad structure representation of the value.
 */
- (BharatMapsCoordinateQuad)BharatMapsCoordinateQuadValue;

// MARK: Working with Offline Map Values

/**
 Creates a new value object containing the given ``BharatMapsOfflinePackProgress``
 structure.

 @param progress The value for the new object.
 @return A new value object that contains the offline pack progress information.
 */
+ (NSValue *)valueWithBharatMapsOfflinePackProgress:(BharatMapsOfflinePackProgress)progress;

/**
 The ``BharatMapsOfflinePackProgress`` structure representation of the value.
 */
@property (readonly) BharatMapsOfflinePackProgress BharatMapsOfflinePackProgressValue;

// MARK: Working with Transition Values

/**
 Creates a new value object containing the given ``BharatMapsTransition``
 structure.

 @param transition The value for the new object.
 @return A new value object that contains the transition information.
 */
+ (NSValue *)valueWithBharatMapsTransition:(BharatMapsTransition)transition;

/**
 The ``BharatMapsTransition`` structure representation of the value.
 */
@property (readonly) BharatMapsTransition BharatMapsTransitionValue;

/**
 Creates a new value object containing the given ``BharatMapsSphericalPosition``
 structure.

 @param lightPosition The value for the new object.
 @return A new value object that contains the light position information.
 */
+ (instancetype)valueWithBharatMapsSphericalPosition:(BharatMapsSphericalPosition)lightPosition;

/**
 The ``BharatMapsSphericalPosition`` structure representation of the value.
 */
@property (readonly) BharatMapsSphericalPosition BharatMapsSphericalPositionValue;

/**
 Creates a new value object containing the given ``BharatMapsLightAnchor``
 enum.

 @param lightAnchor The value for the new object.
 @return A new value object that contains the light anchor information.
 */
+ (NSValue *)valueWithBharatMapsLightAnchor:(BharatMapsLightAnchor)lightAnchor;

/**
 The ``BharatMapsLightAnchor`` enum representation of the value.
 */
@property (readonly) BharatMapsLightAnchor BharatMapsLightAnchorValue;

@end

NS_ASSUME_NONNULL_END
