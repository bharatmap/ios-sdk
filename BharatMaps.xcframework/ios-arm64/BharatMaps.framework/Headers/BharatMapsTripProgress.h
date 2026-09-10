#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface BharatMapsTripProgress : NSObject

@property (nonatomic, assign, readonly) BOOL navigationActive;
@property (nonatomic, strong, readonly, nullable) NSNumber *maneuverDistanceMeters;
@property (nonatomic, strong, readonly, nullable) NSNumber *maneuverDurationRemainingSeconds;
@property (nonatomic, strong, readonly, nullable) NSNumber *tripDistanceRemainingMeters;
@property (nonatomic, strong, readonly, nullable) NSNumber *tripDurationRemainingSeconds;
@property (nonatomic, strong, readonly, nullable) NSNumber *arrivalTimeMillis;
@property (nonatomic, strong, readonly, nullable) NSNumber *speedKmh;
@property (nonatomic, copy, readonly, nullable) NSString *nextRoadName;
@property (nonatomic, copy, readonly, nullable) NSString *currentRoadName;
@property (nonatomic, copy, readonly, nullable) NSString *voiceInstructionText;

/** Remaining fraction (0...1) of the route section leading to the current maneuver.
 * Uses the complete section geometry, not the first observed location. Nil when
 * inactive, arrived, or no nonzero section geometry is available.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *maneuverRemainingFraction;
/** Remaining distance divided by the current active route's distance (0...1).
 * Nil when inactive, arrived, or the active route has no valid positive distance.
 */
@property (nonatomic, strong, readonly, nullable) NSNumber *tripRemainingFraction;

- (instancetype)initWithNavigationActive:(BOOL)navigationActive
                   maneuverDistanceMeters:(nullable NSNumber *)maneuverDistanceMeters
         maneuverDurationRemainingSeconds:(nullable NSNumber *)maneuverDurationRemainingSeconds
               tripDistanceRemainingMeters:(nullable NSNumber *)tripDistanceRemainingMeters
             tripDurationRemainingSeconds:(nullable NSNumber *)tripDurationRemainingSeconds
                         arrivalTimeMillis:(nullable NSNumber *)arrivalTimeMillis
                                  speedKmh:(nullable NSNumber *)speedKmh
                               nextRoadName:(nullable NSString *)nextRoadName
                            currentRoadName:(nullable NSString *)currentRoadName
                       voiceInstructionText:(nullable NSString *)voiceInstructionText;

- (instancetype)initWithNavigationActive:(BOOL)navigationActive
                   maneuverDistanceMeters:(nullable NSNumber *)maneuverDistanceMeters
         maneuverDurationRemainingSeconds:(nullable NSNumber *)maneuverDurationRemainingSeconds
               tripDistanceRemainingMeters:(nullable NSNumber *)tripDistanceRemainingMeters
             tripDurationRemainingSeconds:(nullable NSNumber *)tripDurationRemainingSeconds
                         arrivalTimeMillis:(nullable NSNumber *)arrivalTimeMillis
                                  speedKmh:(nullable NSNumber *)speedKmh
                               nextRoadName:(nullable NSString *)nextRoadName
                            currentRoadName:(nullable NSString *)currentRoadName
                       voiceInstructionText:(nullable NSString *)voiceInstructionText
                 maneuverRemainingFraction:(nullable NSNumber *)maneuverRemainingFraction
                     tripRemainingFraction:(nullable NSNumber *)tripRemainingFraction;

@end

NS_ASSUME_NONNULL_END
