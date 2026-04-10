#import <UIKit/UIKit.h>

#import "BharatMapsFoundation.h"

@class BharatMapView;

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
IB_DESIGNABLE
@interface BharatMapsRouteSelector : UIView

@property (nonatomic, weak, nullable) BharatMapView *bharatMapView;

/// Optional lookup by tag when view is attached and bharatMapView is nil.
@property (nonatomic, assign) IBInspectable NSInteger bharatMapViewTag;

@property (nonatomic, strong) IBInspectable UIColor *buttonColor;
@property (nonatomic, strong) IBInspectable UIColor *activeButtonColor;
@property (nonatomic, strong) IBInspectable UIColor *textColor;
@property (nonatomic, strong) IBInspectable UIColor *activeTextColor;
@property (nonatomic, strong, nullable) UIFont *font;
@property (nonatomic, copy, nullable) IBInspectable NSString *fontFamily;
@property (nonatomic, assign) IBInspectable CGFloat textSize;
@property (nonatomic, assign) IBInspectable CGFloat buttonPadding;
@property (nonatomic, assign) IBInspectable CGFloat gap;
@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;
@property (nonatomic, assign) UIEdgeInsets insets;
@property (nonatomic, assign) IBInspectable BOOL ibProbeFlag;

@end

NS_ASSUME_NONNULL_END
