//
//  MSVMainTrackTransition.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2020/1/13.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "MSVTypeDefines.h"
#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

@class MSVExternalMainTrackTransition;

/**
 * 外部转场协议，所有外部转场都需要实现该协议。
 */
@protocol MSVExternalMainTrackTransitionProcessor
<
NSObject
>

/**
 * 处理视频数据。
 *
 * @param disappearingPixelBuffer 消失中的片段对应的帧。
 * @param appearingPixelBuffer 出现中的片段对应的帧。
 * @param time 帧时间戳。
 *
 * @return 处理后的视频数据。
 * @warning pixelBuffer 在内部会被复用，请不要保留。返回的 pixelBuffer 请对要返回的 CVPixelBufferRef 对象依次调用 CFRetain 和 CFAutorelease 函数之后再返回，一遍正确管理对象生命周期。
 */
- (CVPixelBufferRef)transition:(MSVExternalMainTrackTransition *)transition shouldProcessDisappearingPixelBuffer:(CVPixelBufferRef)disappearingPixelBuffer appearingPixelBuffer:(CVPixelBufferRef)appearingPixelBuffer time:(MovieousTime)time;

@end

/**
 * 主轨转场抽象类，请不要直接使用该类初始化对象，应使用它的子类。
 */
@interface MSVMainTrackTransition : NSObject

/**
 * 转场在主轨中实际应用的时间区间。
 */
@property (nonatomic, assign, readonly) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 转场在主轨中实际应用的开始时间。
 */
@property (nonatomic, assign, readonly) MovieousTime startTimeAtMainTrack;

/**
 * 转场在主轨中实际应用的时长。
 */
@property (nonatomic, assign) MovieousTime durationAtMainTrack;

@end

/**
 * 基础转场类。
 */
@interface MSVBasicMainTrackTransition : MSVMainTrackTransition

/**
 * 基础转场类型。
 */
@property (nonatomic, assign) MSVVideoTransitionType transitionType;

@end

/**
 * 外部转场类。
 */
@interface MSVExternalMainTrackTransition : MSVMainTrackTransition

/**
 * 用于外部转场处理的类。
 */
@property (nonatomic, weak) id<MSVExternalMainTrackTransitionProcessor> processor;

@end

NS_ASSUME_NONNULL_END
