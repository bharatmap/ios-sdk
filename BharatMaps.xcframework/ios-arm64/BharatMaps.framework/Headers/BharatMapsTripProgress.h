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

@end

NS_ASSUME_NONNULL_END
