#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"
#import "BharatMapsNetworkResponse.h"

NS_ASSUME_NONNULL_BEGIN

@class BharatMapsNetworkConfiguration;

@protocol BharatMapsNetworkConfigurationDelegate <NSObject>
@optional

/**
 :nodoc:
 Provides an `NSURLSession` object for the specified ``BharatMapsNetworkConfiguration``.
 This API should be considered experimental, likely to be removed or changed in
 future releases.

 This method is called from background threads, i.e. it is not called on the main
 thread.

 > Note: Background sessions (i.e. created with
 `-[NSURLSessionConfiguration backgroundSessionConfigurationWithIdentifier:]`)
 and sessions created with a delegate that conforms to `NSURLSessionDataDelegate`
 are not supported at this time.
 */
- (NSURLSession *)sessionForNetworkConfiguration:(BharatMapsNetworkConfiguration *)configuration;

- (NSMutableURLRequest *)willSendRequest:(NSMutableURLRequest *)request;

- (BharatMapsNetworkResponse *)didReceiveResponse:(BharatMapsNetworkResponse *)response;

@end

/**
 The ``BharatMapsNetworkConfiguration`` object provides a global way to set a base
 `NSURLSessionConfiguration`, and other resources.
 */
BharatMaps_EXPORT
@interface BharatMapsNetworkConfiguration : NSObject

/**
 :nodoc:
 Delegate for the ``BharatMapsNetworkConfiguration`` class.
 */
@property (nonatomic, weak) id<BharatMapsNetworkConfigurationDelegate> delegate;

/**
 Returns the shared instance of the ``BharatMapsNetworkConfiguration`` class.
 */
@property (class, nonatomic, readonly) BharatMapsNetworkConfiguration *sharedManager;

/**
 The session configuration object that is used by the `NSURLSession` objects
 in this SDK.

 If this property is set to nil or if no session configuration is provided this property
 is set to the default session configuration.

 Assign this object before instantiating any ``BharatMapsMapView`` object, or using
 ``BharatMapsOfflineStorage``

 > Note: `NSURLSession` objects store a copy of this configuration. Any further changes
 to mutable properties on this configuration object passed to a session’s initializer
 will not affect the behavior of that session.

 > Note: Background sessions are not currently supported.
 */
@property (atomic, strong, null_resettable) NSURLSessionConfiguration *sessionConfiguration;

@end

NS_ASSUME_NONNULL_END
