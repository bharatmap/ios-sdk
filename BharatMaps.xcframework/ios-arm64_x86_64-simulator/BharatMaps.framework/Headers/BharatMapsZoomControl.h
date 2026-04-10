#import <UIKit/UIKit.h>

#import "BharatMapsFoundation.h"

@class BharatMapView;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BharatMapsZoomControlOrientation) {
    BharatMapsZoomControlOrientationHorizontal = 0,
    BharatMapsZoomControlOrientationVertical = 1
};

BharatMaps_EXPORT
IB_DESIGNABLE
@interface BharatMapsZoomControl : UIView

@property (nonatomic, weak, nullable) BharatMapView *bharatMapView;
@property (nonatomic, assign) IBInspectable NSInteger bharatMapViewTag;

@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;
@property (nonatomic, strong) IBInspectable UIColor *iconColor;

/// Uses view backgroundColor as button background color.
@property (nonatomic, strong, nullable) UIImage *iconPlus;
@property (nonatomic, strong, nullable) UIImage *iconMinus;

@property (nonatomic, assign) BharatMapsZoomControlOrientation orientation;
/// Interface Builder support: 0 = horizontal, 1 = vertical.
@property (nonatomic, assign) IBInspectable NSInteger orientationValue;

@end

NS_ASSUME_NONNULL_END
