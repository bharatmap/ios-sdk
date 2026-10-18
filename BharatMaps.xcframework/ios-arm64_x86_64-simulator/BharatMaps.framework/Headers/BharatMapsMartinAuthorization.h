#import <Foundation/Foundation.h>
#import "BharatMapsFoundation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BharatMapsMartinAuthorizationStatus) {
    BharatMapsMartinAuthorizationStatusLicenseUnavailable,
    BharatMapsMartinAuthorizationStatusDisabled,
    BharatMapsMartinAuthorizationStatusPreparing,
    BharatMapsMartinAuthorizationStatusReady,
    BharatMapsMartinAuthorizationStatusDenied,
    BharatMapsMartinAuthorizationStatusRetryableFailure
};

typedef NS_ENUM(NSInteger, BharatMapsMartinAuthorizationErrorCode) {
    BharatMapsMartinAuthorizationErrorCodeNone,
    BharatMapsMartinAuthorizationErrorCodeLicenseNotValidated,
    BharatMapsMartinAuthorizationErrorCodeConfigurationInvalid,
    BharatMapsMartinAuthorizationErrorCodeServerDenied,
    BharatMapsMartinAuthorizationErrorCodeUnavailable,
    BharatMapsMartinAuthorizationErrorCodeTimeout,
    BharatMapsMartinAuthorizationErrorCodeSessionExpired
};

/** Immutable, sanitized state of the SDK's shared Martin authorization. */
BharatMaps_EXPORT
@interface BharatMapsMartinAuthorizationSnapshot : NSObject
@property(nonatomic, readonly) BharatMapsMartinAuthorizationStatus status;
@property(nonatomic, readonly) BharatMapsMartinAuthorizationErrorCode errorCode;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

/** Retain this object to keep receiving updates. Releasing it also ends the subscription. */
BharatMaps_EXPORT
@interface BharatMapsMartinAuthorizationSubscription : NSObject
/** Suppresses queued updates and releases the listener. Does not cancel shared authorization. */
- (void)cancel;
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

BharatMaps_EXPORT
@interface BharatMapsMartinAuthorization : NSObject
/** Current state; license validation alone does not imply ready. Safe from any queue. */
+ (BharatMapsMartinAuthorizationSnapshot *)state NS_SWIFT_NAME(state());
/**
 Asynchronously delivers the current state and subsequent changes on the main queue.
 Superseded updates, including those from an invalidated identity, are coalesced to the latest state.
 Cancellation prevents further callbacks; a callback already executing may finish.
 Capture the owner weakly when it retains the subscription.
 */
+ (BharatMapsMartinAuthorizationSubscription *)addListener:
    (void (^)(BharatMapsMartinAuthorizationSnapshot *snapshot))listener NS_SWIFT_NAME(addListener(_:));
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

NS_ASSUME_NONNULL_END
