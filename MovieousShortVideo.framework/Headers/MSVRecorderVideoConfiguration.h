//
//  MSVRecorderVideoConfiguration.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 18/3/1.
//  Copyright © 2018年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "MSVTypeDefines.h"
#import <MovieousCaptureBase/MovieousCaptureBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 录制视频配置对象
 */
@interface MSVRecorderVideoConfiguration : MovieousCameraConfiguration

/**
 * 视频输入源类型。
 * 默认为 MSVVideoSourceCamera。
 */
@property (nonatomic, assign) MSVVideoSource source;

/**
 * 创建一个默认配置的 MSVVideoConfiguration 实例。
 *
 * @return 创建的默认 MSVVideoConfiguration 对象。
 */
+ (instancetype)defaultConfiguration;

@end

@interface MSVRecorderAVVideoConfiguration : MSVRecorderVideoConfiguration

#pragma mark - encoder configurations
/**
 * 平均视频编码码率。默认为 1024*1000
 *
 * @discussion 单位为 bps(Bits per Second)。该参数的视频编码实际过程中，并不是恒定的数值，所以只能设定平均视频编码码率。
 */
@property (nonatomic, assign) NSUInteger averageVideoBitRate;

/**
 * 视频编码关键帧最大间隔（GOP）。
 *
 * @discussion h.264 编码时，两个关键帧之间间隔的最多的帧数，一般为 fps 的两倍或者三倍。默认为 2*fps
 */
@property (nonatomic, assign) NSUInteger videoMaxKeyframeInterval;

/**
 * H.264 编码时使用的 Profile Level。
 *
 * @discussion 默认情况下使用 AVVideoProfileLevelH264HighAutoLevel，如果对于视频编码有额外的需求并且知晓该参数带来的影响可以自行更改。
 *
 * @warning 当你不清楚该参数更改对分辨率要求，码率等影响时，请不要随意更改。
 */
@property (nonatomic, copy) NSString *videoProfileLevel;

/**
 * 是否允许帧重排序
 * 默认为 NO.
 *
 * @discussion 当允许帧排序时会生成 B 帧，否则不会生成 B 帧。
*/
@property (nonatomic, assign) BOOL allowFrameReordering;

@end

NS_ASSUME_NONNULL_END
