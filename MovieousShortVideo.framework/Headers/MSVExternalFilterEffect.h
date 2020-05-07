//
//  MSVExternalFilterEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2020/2/25.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVEffect.h"

NS_ASSUME_NONNULL_BEGIN

@class MSVExternalFilterEffect;
@protocol MSVExternalFilterEffectProcessor <NSObject>

/**
 * 外部滤镜处理器处理回调。
 *
 * @param externalFilterEffect 要处理的帧所关联的 MSVExternalFilterEffect 对象。
 * @param pixelBuffer 待处理的帧数据，在内部会被复用，请不要保留。返回的 pixelBuffer 请对要返回的 CVPixelBufferRef 对象依次调用 CFRetain 和 CFAutorelease 函数之后再返回，以便正确管理对象生命周期。
 * @param time 待处理的帧数据的时间戳。
 *
 * @return 处理完成的帧数据。
 */
- (CVPixelBufferRef)externalFilterEffect:(MSVExternalFilterEffect *)externalFilterEffect shouldProcessPixelBuffer:(CVPixelBufferRef)pixelBuffer time:(MovieousTime)time;

@end

@interface MSVExternalFilterEffect : MSVEffect

/**
 * 外部滤镜特效处理器对象。
 */
@property (nonatomic, weak) id<MSVExternalFilterEffectProcessor> processor;

@end

NS_ASSUME_NONNULL_END
