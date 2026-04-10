#import <UIKit/UIKit.h>
#import "BharatMapsAdvancedAnnotationOptions.h"

NS_ASSUME_NONNULL_BEGIN

@interface BharatMapsAdvancedAnnotation : UIView

@property (nonatomic, strong, readonly) UIView *contentContainer;
@property (nonatomic, strong, readonly) BharatMapsAdvancedAnnotationOptions *options;

- (instancetype)initWithOptions:(BharatMapsAdvancedAnnotationOptions *)options;
- (void)setContentView:(UIView *)content;
- (void)applyOptions:(BharatMapsAdvancedAnnotationOptions *)options;
- (void)setRuntimeTailOffsetX:(CGFloat)offsetX;
- (CGFloat)anchorOffsetY;
- (CGFloat)tailWidth;

@end

NS_ASSUME_NONNULL_END
