#import <UIKit/UIKit.h>

#import "BharatMapsTypes.h"

NS_ASSUME_NONNULL_BEGIN

/**
 A specialized view that displays the current compass heading for its associated map.
 */
BharatMaps_EXPORT
@interface BharatMapsCompassButton : UIImageView

/**
 The visibility of the compass button.

 You can configure a compass button to be visible all the time or only when the compass heading
 changes.
 */
@property (nonatomic, assign) BharatMapsOrnamentVisibility compassVisibility;

@end

NS_ASSUME_NONNULL_END
