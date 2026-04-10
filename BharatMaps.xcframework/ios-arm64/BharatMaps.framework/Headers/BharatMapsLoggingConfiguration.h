#import <Foundation/Foundation.h>

#import "BharatMapsFoundation.h"

#ifndef BharatMaps_LOGGING_DISABLED
#ifndef BharatMaps_LOGGING_ENABLE_DEBUG
#ifndef NDEBUG
#define BharatMaps_LOGGING_ENABLE_DEBUG 1
#endif
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 Constants indicating the message's logging level.
 */
typedef NS_ENUM(NSInteger, BharatMapsLoggingLevel) {
  /**
   None-level won't print any messages.
   */
  BharatMapsLoggingLevelNone = 0,
  /**
   Fault-level messages contain system-level error information.
   */
  BharatMapsLoggingLevelFault,
  /**
   Error-level messages contain information that is intended to aid in process-level
   errors.
  */
  BharatMapsLoggingLevelError,
  /**
   Warning-level messages contain warning information for potential risks.
   */
  BharatMapsLoggingLevelWarning,
  /**
   Info-level messages contain information that may be helpful for flow tracing
   but is not essential.
   */
  BharatMapsLoggingLevelInfo,
/**
 Debug-level messages contain information that may be helpful for troubleshooting
 specific problems.
 */
#if BharatMaps_LOGGING_ENABLE_DEBUG
  BharatMapsLoggingLevelDebug,
#endif
  /**
   Verbose-level will print all messages.
   */
  BharatMapsLoggingLevelVerbose,
};

/**
 A block to be called once `loggingLevel` is set to a higher value than
 ``BharatMapsLoggingLevel/BharatMapsLoggingLevelNone``.

 @param loggingLevel The message logging level.
 @param filePath The description of the file and method for the calling message.
 @param line The line where the message is logged.
 @param message The logging message.
 */
typedef void (^BharatMapsLoggingBlockHandler)(BharatMapsLoggingLevel loggingLevel, NSString *filePath,
                                       NSUInteger line, NSString *message);

/**
 The ``BharatMapsLoggingConfiguration`` object provides a global way to set this SDK logging levels
 and logging handler.
 */
BharatMaps_EXPORT
@interface BharatMapsLoggingConfiguration : NSObject

/**
 The handler this SDK uses to log messages.

 If this property is set to nil or if no custom handler is provided this property
 is set to the default handler.

 The default handler uses `os_log` and `NSLog` for iOS 10+ and iOS < 10 respectively.
 */
@property (nonatomic, copy, null_resettable) BharatMapsLoggingBlockHandler handler;

/**
 The logging level.

 The default value is ``BharatMapsLoggingLevel/BharatMapsLoggingLevelNone``.

 Setting this property includes logging levels less than or equal to the setted value.
 */
@property (assign, nonatomic) BharatMapsLoggingLevel loggingLevel;

/**
 Returns the shared logging object.
 */
@property (class, nonatomic, readonly) BharatMapsLoggingConfiguration *sharedConfiguration;

- (BharatMapsLoggingBlockHandler)handler UNAVAILABLE_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
#endif
