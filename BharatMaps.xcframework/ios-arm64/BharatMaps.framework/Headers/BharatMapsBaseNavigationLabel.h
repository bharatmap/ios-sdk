#import <UIKit/UIKit.h>

@class BharatMapView;

NS_ASSUME_NONNULL_BEGIN

@interface BharatMapsBaseNavigationLabel : UILabel

@property (nonatomic, weak, nullable) BharatMapView *bharatMapView;
@property (nonatomic, assign) NSInteger bharatMapViewTag;
@property (nonatomic, copy, nullable) IBInspectable NSString *textHexColor;
@property (nonatomic, copy, nullable) IBInspectable NSString *backgroundHexColor;
@property (nonatomic, copy, nullable) IBInspectable NSString *fontFamily;
@property (nonatomic, assign) IBInspectable CGFloat textSize;
@property (nonatomic, assign) IBInspectable CGFloat cornerRadius;
@property (nonatomic, assign) IBInspectable CGFloat horizontalPadding;
@property (nonatomic, assign) IBInspectable CGFloat verticalPadding;

- (void)renderWithTripProgressUserInfo:(NSDictionary *)userInfo;
- (void)resetLabel;
- (NSString *)formatDistance:(double)meters;
- (NSString *)formatDuration:(double)seconds;
- (NSString *)formatArrivalMillis:(double)arrivalMillis;

@end

NS_ASSUME_NONNULL_END
