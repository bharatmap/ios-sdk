#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

/** Options for ``BharatMapsAttributedExpression/attributes``. */
typedef NSString *BharatMapsAttributedExpressionKey NS_TYPED_ENUM;

/** The font name string array expression used to format the text. */
FOUNDATION_EXTERN BharatMaps_EXPORT BharatMapsAttributedExpressionKey const BharatMapsFontNamesAttribute;

/** The font scale number expression relative to ``BharatMapsSymbolStyleLayer/textFontSize`` used to format
 * the text. */
FOUNDATION_EXTERN BharatMaps_EXPORT BharatMapsAttributedExpressionKey const BharatMapsFontScaleAttribute;

/** The font color expression used to format the text. */
FOUNDATION_EXTERN BharatMaps_EXPORT BharatMapsAttributedExpressionKey const BharatMapsFontColorAttribute;

/**
 An ``BharatMapsAttributedExpression`` object associates text formatting attibutes (such as font size or
 font names) to an `NSExpression`.

 ### Example
 ```swift
 let redColor = UIColor.red
 let expression = NSExpression(forConstantValue: "Foo")
 let attributes: [BharatMapsAttributedExpressionKey: NSExpression] = [.fontNamesAttribute :
 NSExpression(forConstantValue: ["DIN Offc Pro Italic", "Arial Unicode MS Regular"]),
                                                               .fontScaleAttribute:
 NSExpression(forConstantValue: 1.2), .fontColorAttribute: NSExpression(forConstantValue: redColor)]
 let attributedExpression = BharatMapsAttributedExpression(expression, attributes:attributes)
 ```

 */
BharatMaps_EXPORT
@interface BharatMapsAttributedExpression : NSObject

/**
 The expression content of the receiver as `NSExpression`.
 */
@property (strong, nonatomic) NSExpression *expression;

#if TARGET_OS_IPHONE
/**
 The formatting attributes dictionary.
 Key | Value Type
 --- | ---
 ``BharatMapsFontNamesAttribute`` | An `NSExpression` evaluating to an `NSString` array.
 ``BharatMapsFontScaleAttribute`` | An `NSExpression` evaluating to an `NSNumber` value.
 ``BharatMapsFontColorAttribute`` | An `NSExpression` evaluating to an `UIColor`.

 */
@property (strong, nonatomic, readonly)
    NSDictionary<BharatMapsAttributedExpressionKey, NSExpression *> *attributes;
#else
/**
 The formatting attributes dictionary.
 Key | Value Type
 --- | ---
 ``BharatMapsFontNamesAttribute`` | An `NSExpression` evaluating to an `NSString` array.
 ``BharatMapsFontScaleAttribute`` | An `NSExpression` evaluating to an `NSNumber` value.
 ``BharatMapsFontColorAttribute`` | An `NSExpression` evaluating to an `NSColor` on macos.
 */
@property (strong, nonatomic, readonly)
    NSDictionary<BharatMapsAttributedExpressionKey, NSExpression *> *attributes;
#endif

/**
 Returns an ``BharatMapsAttributedExpression`` object initialized with an expression and no attribute
 information.
 */
- (instancetype)initWithExpression:(NSExpression *)expression;

/**
 Returns an ``BharatMapsAttributedExpression`` object initialized with an expression and text format
 attributes.
 */
- (instancetype)
    initWithExpression:(NSExpression *)expression
            attributes:(nonnull NSDictionary<BharatMapsAttributedExpressionKey, NSExpression *> *)attrs;

/**
 Creates an ``BharatMapsAttributedExpression`` object initialized with an expression and the format
 attributes for font names and font size.
 */
+ (instancetype)attributedExpression:(NSExpression *)expression
                           fontNames:(nullable NSArray<NSString *> *)fontNames
                           fontScale:(nullable NSNumber *)fontScale;

/**
 Creates an ``BharatMapsAttributedExpression`` object initialized with an expression and the format
 attributes dictionary.
 */
+ (instancetype)
    attributedExpression:(NSExpression *)expression
              attributes:(nonnull NSDictionary<BharatMapsAttributedExpressionKey, NSExpression *> *)attrs;

@end

NS_ASSUME_NONNULL_END
