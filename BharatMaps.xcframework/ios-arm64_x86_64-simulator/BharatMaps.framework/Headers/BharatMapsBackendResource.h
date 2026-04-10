#if BharatMaps_RENDER_BACKEND_METAL

#import <MetalKit/MetalKit.h>

@interface BharatMapsBackendResource : NSObject

@property (nonatomic, strong) MTKView *mtkView;
@property (nonatomic, strong) id<MTLDevice> device;
@property (nonatomic, strong) MTLRenderPassDescriptor *renderPassDescriptor;
@property (nonatomic, strong) id<MTLCommandBuffer> commandBuffer;

- (instancetype)initWithMTKView:(MTKView *)mtkView
                         device:(id<MTLDevice>)device
           renderPassDescriptor:(MTLRenderPassDescriptor *)renderPassDescriptor
                  commandBuffer:(id<MTLCommandBuffer>)commandBuffer;

@end

#else

#import <Foundation/Foundation.h>
#import "BharatMapsFoundation.h"

BharatMaps_EXPORT
@interface BharatMapsBackendResource : NSObject

- (instancetype)initWithMTKView:(id)mtkView
                         device:(id)device
           renderPassDescriptor:(id)renderPassDescriptor
                  commandBuffer:(id)commandBuffer;

@end

#endif
