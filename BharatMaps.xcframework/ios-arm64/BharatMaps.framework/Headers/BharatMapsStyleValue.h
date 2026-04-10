#import <CoreGraphics/CoreGraphics.h>
#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

typedef NSString *BharatMapsStyleFunctionOption NS_STRING_ENUM NS_UNAVAILABLE;

FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsStyleFunctionOption BharatMapsStyleFunctionOptionInterpolationBase
    __attribute__((unavailable(
        "Use NSExpression instead, applying the mgl_interpolate:withCurveType:parameters:stops: "
        "function with a curve type of “exponential” and a non-nil parameter.")));

FOUNDATION_EXTERN BharatMaps_EXPORT const BharatMapsStyleFunctionOption BharatMapsStyleFunctionOptionDefaultValue
    __attribute__((unavailable(
        "Use +[NSExpression expressionForConditional:trueExpression:falseExpression:] instead.")));

typedef NS_ENUM(NSUInteger, BharatMapsInterpolationMode) {
  BharatMapsInterpolationModeExponential __attribute__((unavailable(
      "Use NSExpression instead, applying the mgl_interpolate:withCurveType:parameters:stops: "
      "function with a curve type of “exponential”."))) = 0,
  BharatMapsInterpolationModeInterval __attribute__((
      unavailable("Use NSExpression instead, calling the mgl_step:from:stops: function."))),
  BharatMapsInterpolationModeCategorical __attribute__((unavailable("Use NSExpression instead."))),
  BharatMapsInterpolationModeIdentity
  __attribute__((unavailable("Use +[NSExpression expressionForKeyPath:] instead.")))
} __attribute__((unavailable("Use NSExpression instead.")));

BharatMaps_EXPORT __attribute__((unavailable("Use NSExpression instead.")))
@interface BharatMapsStyleValue<T> : NSObject
@end

BharatMaps_EXPORT __attribute__((unavailable("Use +[NSExpression expressionForConstantValue:] instead.")))
@interface BharatMapsConstantStyleValue<T> : BharatMapsStyleValue<T>
@end

@compatibility_alias BharatMapsStyleConstantValue BharatMapsConstantStyleValue;

BharatMaps_EXPORT
__attribute__((unavailable("Use NSExpression instead, calling the mgl_step:from:stops: or "
                           "mgl_interpolate:withCurveType:parameters:stops: function.")))
@interface BharatMapsStyleFunction<T> : BharatMapsStyleValue<T>
@end

BharatMaps_EXPORT __attribute__((unavailable(
    "Use NSExpression instead, applying the mgl_step:from:stops: or "
    "mgl_interpolate:withCurveType:parameters:stops: function to the $zoomLevel variable.")))
@interface BharatMapsCameraStyleFunction<T> : BharatMapsStyleFunction<T>
@end

BharatMaps_EXPORT __attribute__((unavailable(
    "Use NSExpression instead, applying the mgl_step:from:stops: or "
    "mgl_interpolate:withCurveType:parameters:stops: function to a key path expression.")))
@interface BharatMapsSourceStyleFunction<T> : BharatMapsStyleFunction<T>
@end

BharatMaps_EXPORT
__attribute__((unavailable("Use a NSExpression instead with nested mgl_step:from:stops: or "
                           "mgl_interpolate:withCurveType:parameters:stops: function calls.")))
@interface BharatMapsCompositeStyleFunction<T> : BharatMapsStyleFunction<T>
@end

NS_ASSUME_NONNULL_END
