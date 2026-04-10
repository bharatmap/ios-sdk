#import "BharatMapsFoundation.h"

/**
 Bitmask values that describe why a camera move occurred.

 Values of this type are passed to the ``BharatMapsMapView``'s delegate in the following methods:

 - ``BharatMapsMapViewDelegate/mapView:shouldChangeFromCamera:toCamera:reason:``
 - ``BharatMapsMapViewDelegate/mapView:regionWillChangeWithReason:animated:``
 - ``BharatMapsMapViewDelegate/mapView:regionIsChangingWithReason:``
 - ``BharatMapsMapViewDelegate/mapView:regionDidChangeWithReason:animated:``

 It's important to note that it's almost impossible to perform a rotate without zooming (in or out),
 so if you'll often find ``BharatMapsCameraChangeReasonGesturePinch`` set alongside
 ``BharatMapsCameraChangeReasonGestureRotate``.

 Since there are several reasons why a zoom or rotation has occurred, it is worth considering
 creating a combined constant, for example:

 ```objc
 static const BharatMapsCameraChangeReason anyZoom = BharatMapsCameraChangeReasonGesturePinch |
                                                BharatMapsCameraChangeReasonGestureZoomIn |
                                                BharatMapsCameraChangeReasonGestureZoomOut |
                                                BharatMapsCameraChangeReasonGestureOneFingerZoom;

 static const BharatMapsCameraChangeReason anyRotation = BharatMapsCameraChangeReasonResetNorth |
 BharatMapsCameraChangeReasonGestureRotate;
 ```
 */
typedef NS_OPTIONS(NSUInteger, BharatMapsCameraChangeReason) {
  /// The reason for the camera change has not be specified.
  BharatMapsCameraChangeReasonNone = 0,

  /// Set when a public API that moves the camera is called. This may be set for some
  /// gestures, for example BharatMapsCameraChangeReasonResetNorth.
  BharatMapsCameraChangeReasonProgrammatic = 1 << 0,

  /// The user tapped the compass to reset the map orientation so North is up.
  BharatMapsCameraChangeReasonResetNorth = 1 << 1,

  /// The user panned the map.
  BharatMapsCameraChangeReasonGesturePan = 1 << 2,

  /// The user pinched to zoom in/out.
  BharatMapsCameraChangeReasonGesturePinch = 1 << 3,

  // :nodoc: The user rotated the map.
  BharatMapsCameraChangeReasonGestureRotate = 1 << 4,

  /// The user zoomed the map in (one finger double tap).
  BharatMapsCameraChangeReasonGestureZoomIn = 1 << 5,

  /// The user zoomed the map out (two finger single tap).
  BharatMapsCameraChangeReasonGestureZoomOut = 1 << 6,

  /// The user long pressed on the map for a quick zoom (single tap, then long press and
  /// drag up/down).
  BharatMapsCameraChangeReasonGestureOneFingerZoom = 1 << 7,

  // The user panned with two fingers to tilt the map (two finger drag).
  BharatMapsCameraChangeReasonGestureTilt = 1 << 8,

  // Cancelled
  BharatMapsCameraChangeReasonTransitionCancelled = 1 << 16

};
