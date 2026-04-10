#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN BharatMaps_EXPORT BharatMapsExceptionName const BharatMapsInvalidStyleLayerException;

/**
 ``BharatMapsStyleLayer`` is an abstract base class for style layers. A style layer
 manages the layout and appearance of content at a specific z-index in a style.
 An ``BharatMapsStyle`` object consists of one or more ``BharatMapsStyle`` objects.

 Each style layer defined by the style JSON file is represented at runtime by an
 ``BharatMapsStyleLayer`` object, which you can use to refine the map’s appearance. You
 can also add and remove style layers dynamically.

 Create instances of ``BharatMapsBackgroundStyleLayer`` and the concrete subclasses of
 ``BharatMapsForegroundStyleLayer`` in order to use ``BharatMapsForegroundStyleLayer``'s properties and methods.
 You do not create instances of ``BharatMapsStyleLayer`` directly, and do not
 create your own subclasses of this class.

 Do not add ``BharatMapsStyleLayer`` objects to the `style` property of a ``BharatMapsStyleLayer`` before
 ``BharatMapsMapViewDelegate/mapView:didFinishLoadingStyle:`` is called.
 */
BharatMaps_EXPORT
@interface BharatMapsStyleLayer : NSObject

// MARK: Initializing a Style Layer

- (instancetype)init
    __attribute__((unavailable("Use -init methods of concrete subclasses instead.")));

// MARK: Identifying a Style Layer

/**
 A string that uniquely identifies the style layer in the style to which it is
 added.
 */
@property (nonatomic, copy, readonly) NSString *identifier;

// MARK: Configuring a Style Layer’s Visibility

/**
 Whether this layer is displayed. A value of `NO` hides the layer.

 #### Related examples
 TODO: Show and hide a layer, learn how to toggle an ``BharatMapsStyleLayer``
 object's visibility.
 */
@property (nonatomic, assign, getter=isVisible) BOOL visible;

/**
 The maximum zoom level at which the layer gets parsed and appears. This value is a floating-point
 number.
 */
@property (nonatomic, assign) float maximumZoomLevel;

/**
 The minimum zoom level at which the layer gets parsed and appears. This value is a floating-point
 number.
 */
@property (nonatomic, assign) float minimumZoomLevel;

@end

NS_ASSUME_NONNULL_END
