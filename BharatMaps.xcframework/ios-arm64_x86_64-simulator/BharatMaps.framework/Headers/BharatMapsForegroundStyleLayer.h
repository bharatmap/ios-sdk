#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsStyleLayer.h"

NS_ASSUME_NONNULL_BEGIN

@class BharatMapsSource;

/**
 ``BharatMapsForegroundStyleLayer`` is an abstract superclass for style layers whose
 content is defined by an ``BharatMapsSource`` object.

 Create instances of ``BharatMapsRasterStyleLayer``, ``BharatMapsRasterStyleLayer``, and the
 concrete subclasses of ``BharatMapsVectorStyleLayer`` in order to use
 ``BharatMapsForegroundStyleLayer``'s methods. Do not create instances of
 ``BharatMapsForegroundStyleLayer`` directly, and do not create your own subclasses of
 this class.
 */
BharatMaps_EXPORT
@interface BharatMapsForegroundStyleLayer : BharatMapsStyleLayer

// MARK: Initializing a Style Layer

- (instancetype)init
    __attribute__((unavailable("Use -init methods of concrete subclasses instead.")));

// MARK: Specifying a Style Layer’s Content

/**
 Identifier of the source from which the receiver obtains the data to style.
 */
@property (nonatomic, readonly, nullable) NSString *sourceIdentifier;

@end

NS_ASSUME_NONNULL_END
