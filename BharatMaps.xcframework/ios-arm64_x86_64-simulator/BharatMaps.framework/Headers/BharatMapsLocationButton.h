#import <UIKit/UIKit.h>

#import "BharatMapsFoundation.h"

@class BharatMapView;

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
IB_DESIGNABLE
@interface BharatMapsLocationButton : UIButton

@property (nonatomic, weak, nullable) BharatMapView *bharatMapView;
@property (nonatomic, assign) IBInspectable NSInteger bharatMapViewTag;

@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;
@property (nonatomic, strong) IBInspectable UIColor *iconColor;

/// Custom icon for normal map mode. Defaults to "icon_location".
@property (nonatomic, strong, nullable) UIImage *icon;
/// Custom icon for active navigation mode. Defaults to "icon_navigating".
@property (nonatomic, strong, nullable) UIImage *iconNavigation;

@end

NS_ASSUME_NONNULL_END
