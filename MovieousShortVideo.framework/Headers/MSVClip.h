//
//  MSVClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/4/13.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVTypeDefines.h"
#import <MovieousBase/MovieousBase.h>
#import "MSVSnapshotGenerator.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 媒体片段的基类。
 */
@interface MSVClip : MovieousObject
<
NSCopying
>

/**
 * 初始化一个 MSVClip 对象。
 *
 * @param type 片段的类型。
 * @param path 媒体文件的 path。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithType:(MSVClipType)type path:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 对象来初始化一个音视频类型的 MSVClip 对象。
 *
 * @param asset 用于初始化的 AVAsset 对象。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAsset:(AVAsset *)asset error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 UIImage 对象来初始化一个图片类型的 MSVClip 对象。
 *
 * @param image 用来创建 MSVClip 的 UIImage 对象
 * @param duration 图片时长。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithImage:(UIImage *)image duration:(NSTimeInterval)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用另一个 MSVClip 对象来初始化一个 MSVClip 对象。
 *
 * @param clip 用于初始化的另一个 MSVClip 对象。
 *
 * @return 初始化完成的对象。
 */
- (instancetype)initWithClip:(MSVClip *)clip;

/**
 * 片段类型。
 */
@property (nonatomic, assign, readonly) MSVClipType type;

/**
 * 媒体文件地址。
 */
@property (nonatomic, strong, readonly) NSString *path;

/**
 * 源视频空间中用于填充目标视频的区域位置和大小。
 * 默认为 CGRectInfinite，也就是整个源视频区域都用于填充。
 */
@property (nonatomic, assign) CGRect sourceDisplayFrame;

/**
 * 将源视频中的内容填充到目标视频中的区域位置和大小。
 * 默认为 CGRectNull，也就是整个目标视频区域都用于填充源视频。
 */
@property (nonatomic, assign) CGRect destDisplayFrame;

/**
 * 源视频在目标视频中的旋转弧度，旋转操作会在源视频在目标区域填充完成之后进行，锚点在目标区域的中心位置。
 * 默认为 0。
 */
@property (nonatomic, assign) float rotateAngle;

/**
 * 当源视频有效区域的比例和目标填充区域比例不一致时使用的填充模式。
 * 默认为 MovieousScalingModeAspectFit
 */
@property (nonatomic, assign) MovieousScalingMode scalingMode;

/**
 * 片段实际在主轨中的时间长度，当片段类型是音视频时，durationAtMainTrack 参数和 speed 参数互相影响，调整 durationAtMainTrack 将会影响 speed，具体为：speed = timeRange.duration / durationAtMainTrack.
 * 默认为根据 timeRange 和 speed 自动计算出来的数据。
 */
@property (nonatomic, assign) NSTimeInterval durationAtMainTrack;

/**
 * 视频片段的初始总时长。
 */
@property (nonatomic, assign, readonly) NSTimeInterval originalDuration;

/**
 *  视频片段的总时长（考虑 speed 的因素）
 */
@property (nonatomic, assign, readonly) NSTimeInterval originalDurationAtMainTrack;

/**
 * 片段的自然尺寸（将旋转考虑在内）。
 */
@property (nonatomic, assign, readonly) CGSize size;


// 如下参数仅在 MSVClipTypeAV 类型的片段中有效。
#pragma mark - video properties
/**
 * 初始化时使用的 AVAsset 对象。
 */
@property (nonatomic, strong, readonly) AVAsset *asset;

/**
 * 源视频中用于填充目标视频的有效的时间区间。
 * 默认为 kMovieousTimeRangeDefault，也就是整个视频区间。
 *
 * @warning 需要注意的是此处的 timeRange 不将快慢速考虑在内， 另外超出整个媒体区间的部分将被忽略。
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * 片段的视频部分的帧率。
 */
@property (nonatomic, assign, readonly) float frameRate;

/**
 * 获取用于生成快照的图片生成器对象。
 *
 * @return 生成的 MSVSnapshotGenerator 对象。
 */
@property (nonatomic, strong, readonly) MSVSnapshotGenerator *imageGenerator;

/**
 * 录制视频片段的速度。
 * 默认为 1.0。
 *
 * @discussion
 * 推荐配置：
 * 非常快：2.0。
 * 快：1.5。
 * 正常：1.0。
 * 慢：0.75。
 * 非常慢：0.5。
 */
@property (nonatomic, assign) float speed;

/**
 * 媒体音频的音量。
 * 默认为媒体文件的 preferredVolume 属性。
 */
@property (nonatomic, assign) float volume;

// 以下参数仅对 MSVClipTypeImage 类型的媒体片段有效。
#pragma mark - image properties
/**
 * 初始化时使用的 UIImage对象。
 */
@property (nonatomic, assign, readonly) UIImage *image;

/**
 * 当 `AVAudioSessionMediaServicesWereResetNotification` 通知发生时重置内部的音频相关服务。
 */
- (void)refreshAsset;

@end

NS_ASSUME_NONNULL_END
