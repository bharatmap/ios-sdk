#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface BharatMapsAdvancedAnnotationOptions : NSObject <NSCopying>

@property (nonatomic, strong) UIColor *backgroundColor;
@property (nonatomic, strong) UIColor *borderColor;
@property (nonatomic, assign) CGFloat borderWidth;
@property (nonatomic, assign) CGFloat cornerRadius;
@property (nonatomic, assign) CGFloat tailWidth;
@property (nonatomic, assign) CGFloat tailHeight;
@property (nonatomic, assign) CGFloat tailOffsetX;
@property (nonatomic, assign) UIEdgeInsets contentInsets;
@property (nonatomic, assign) CGFloat anchorOffsetY;
@property (nonatomic, assign) CGFloat maxWidth;
@property (nonatomic, assign) BOOL closeTapOutside;
@property (nonatomic, assign) BOOL persistent;

+ (instancetype)defaultOptions;

@end

NS_ASSUME_NONNULL_END
