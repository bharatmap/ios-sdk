#import <UIKit/UIKit.h>

#import "BharatMapsFoundation.h"

@class BharatMapView;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BharatMapsManeuverSignOrientation) {
    BharatMapsManeuverSignOrientationHorizontal = 0,
    BharatMapsManeuverSignOrientationVertical = 1
};

BharatMaps_EXPORT
IB_DESIGNABLE
@interface BharatMapsManeuverSign : UIView

@property (nonatomic, weak, nullable) BharatMapView *bharatMapView;

/// Optional lookup by tag when view is attached and bharatMapView is nil.
@property (nonatomic, assign) IBInspectable NSInteger bharatMapViewTag;

@property (nonatomic, strong) IBInspectable UIColor *iconColor;
@property (nonatomic, strong) IBInspectable UIColor *signBackgroundColor;
@property (nonatomic, assign) BharatMapsManeuverSignOrientation orientation;
@property (nonatomic, assign) UIEdgeInsets insets;

@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;

/// Interface Builder support: 0 = horizontal, 1 = vertical.
@property (nonatomic, assign) IBInspectable NSInteger orientationValue;
@property (nonatomic, assign) IBInspectable CGFloat insetTop;
@property (nonatomic, assign) IBInspectable CGFloat insetLeft;
@property (nonatomic, assign) IBInspectable CGFloat insetBottom;
@property (nonatomic, assign) IBInspectable CGFloat insetRight;
@property (nonatomic, assign) IBInspectable BOOL ibProbeFlag;

@end

NS_ASSUME_NONNULL_END
