#import <UIKit/UIKit.h>

#import "BharatMapsFoundation.h"

@class BharatMapView;

NS_ASSUME_NONNULL_BEGIN

BharatMaps_EXPORT
IB_DESIGNABLE
@interface BharatMapsTripEndView : UIView

@property (nonatomic, weak, nullable) BharatMapView *bharatMapView;
@property (nonatomic, assign) IBInspectable NSInteger bharatMapViewTag;

@property (nonatomic, strong) IBInspectable UIColor *textColor;
@property (nonatomic, strong) IBInspectable UIColor *buttonBackgroundColor;
@property (nonatomic, strong) IBInspectable UIColor *buttonTextColor;
@property (nonatomic, copy, nullable) IBInspectable NSString *fontFamily;
@property (nonatomic, assign) IBInspectable CGFloat borderRadius;
@property (nonatomic, assign) IBInspectable CGFloat buttonBorderRadius;
@property (nonatomic, assign) IBInspectable CGFloat buttonHeight;
@property (nonatomic, assign) IBInspectable CGFloat textSize;
@property (nonatomic, assign) IBInspectable CGFloat buttonTextSize;

@end

NS_ASSUME_NONNULL_END

