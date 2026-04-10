#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN BharatMaps_EXPORT BharatMapsExceptionName const BharatMapsInvalidStyleSourceException;

/**
 ``BharatMapsSource`` is an abstract base class for map content sources. A map content
 source supplies content to be shown on the map. A source is added to an
 ``BharatMapsStyle`` object along with an ``BharatMapsStyle`` object. The
 foreground style layer defines the appearance of any content supplied by the
 source.

 Each source defined by the style JSON file is represented at runtime by an
 ``BharatMapsSource`` object that you can use to refine the map’s content. You can also
 add and remove sources dynamically using methods such as
 ``BharatMapsStyle/addSource:`` and ``BharatMapsStyle/sourceWithIdentifier:``.

 Create instances of ``BharatMapsShapeSource``, ``BharatMapsShapeSource``,
 ``BharatMapsImageSource``, and the concrete subclasses of ``BharatMapsImageSource``
 (``BharatMapsVectorTileSource`` and ``BharatMapsRasterTileSource``) in order to use ``BharatMapsRasterTileSource``’s
 properties and methods. Do not create instances of ``BharatMapsSource`` directly, and do
 not create your own subclasses of this class.
 */
BharatMaps_EXPORT
@interface BharatMapsSource : NSObject

// MARK: Initializing a Source

- (instancetype)init __attribute__((unavailable("Use -initWithIdentifier: instead.")));

/**
 Returns a source initialized with an identifier.

 After initializing and configuring the source, add it to a map view’s style
 using the ``BharatMapsStyle/addSource:`` method.

 @param identifier A string that uniquely identifies the source in the style to
    which it is added.
 @return An initialized source.
 */
- (instancetype)initWithIdentifier:(NSString *)identifier;

// MARK: Identifying a Source

/**
 A string that uniquely identifies the source in the style to which it is added.
 */
@property (nonatomic, copy) NSString *identifier;

@end

NS_ASSUME_NONNULL_END
