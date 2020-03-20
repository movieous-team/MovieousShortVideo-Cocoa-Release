//
//  MovieousExternalFilterCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousCaptureBase/MovieousCaptureEffect.h>
#import <MovieousBase/MovieousObject.h>

@class MovieousExternalFilterCaptureEffect;
/**
 * 外部滤镜协议，所有外部滤镜都需要实现该协议。
 */
@protocol MovieousExternalFilterCaptureEffectProcessor
<
NSObject
>

/**
 * 处理视频数据。
 *
 * @param externalFilterCaptureEffect 特效对象
 * @param pixelBuffer 待处理的视频数据。
 * @param time 待处理视频时间戳。
 *
 * @return 处理后的视频数据，请对要返回的 CVPixelBufferRef 对象依次调用 CFRetain 和 CFAutorelease 函数之后再返回，以便正确管理对象生命周期。
 *
 * @warning 请不要直接修改 pixelBuffer 的内容，你需要返回一个与原 pixelBuffer 不同的 CVPixelBufferRef。
 */
- (CVPixelBufferRef)externalFilterCaptureEffect:(MovieousExternalFilterCaptureEffect *)externalFilterCaptureEffect shouldProcessPixelBuffer:(CVPixelBufferRef)pixelBuffer time:(MovieousTime)time;

@end

/**
 * 外部滤镜采集特效。
 */
@interface MovieousExternalFilterCaptureEffect : MovieousCaptureEffect

/**
 * 处理器对象。
 */
@property (nonatomic, weak) id<MovieousExternalFilterCaptureEffectProcessor> processor;

/**
 * 用另一个 MovieousExternalFilterCaptureEffect 对象初始化此 MovieousExternalFilterCaptureEffect。
 *
 * @param externalFilterCaptureEffect 用于初始化的另一个 MovieousExternalFilterCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousExternalFilterCaptureEffect 对象。
 */
- (instancetype)initWithExternalFilterCaptureEffect:(MovieousExternalFilterCaptureEffect *)externalFilterCaptureEffect;

@end
