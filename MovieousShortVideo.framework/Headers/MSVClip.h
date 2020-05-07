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
#import "MSVEffect.h"

NS_ASSUME_NONNULL_BEGIN

@class MSVClip;
@protocol MSVClipProcessor <NSObject>

/**
 * 外置片段处理回调，你需要在此回调中处理 clip 的帧并返回。
 *
 * @param clip 处理的帧来源的 MSVClip 对象。
 * @param pixelBuffer 待处理的原始帧。
 * @param time 待处理的帧时间戳。
 *
 * @return 处理完成的帧，请对要返回的 CVPixelBufferRef 对象依次调用 CFRetain 和 CFAutorelease 函数之后再返回，以便正确管理对象生命周期。
 */
- (CVPixelBufferRef)clip:(MSVClip *)clip shouldProcessPixelBuffer:(CVPixelBufferRef)pixelBuffer time:(MovieousTime)time;

@end

/**
 * 媒体片段的基类。
 */
@interface MSVClip : MovieousObject
<
NSCopying,
MSVClipOrEffect
>

/**
 * 用媒体文件路径来初始化一个 MSVClipTypeAV 类型的 MSVClip 对象。
 *
 * @param path 源文件路径，仅支持本地文件，支持 iOS 系统原生支持的所有音视频文件格式。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAVPath:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 对象来初始化一个 MSVClipTypeAV 类型的 MSVClip 对象。
 *
 * @param asset 用于初始化的 AVAsset 对象。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAsset:(AVAsset *)asset error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 对象来初始化一个 MSVClipTypeStillImage 类型的 MSVClip 对象。
 *
 * @param path 源文件路径，仅支持本地文件，支持 iOS 系统原生支持的所有图片文件格式。
 * @param duration 图片在视频中持续的时长，单位为微秒。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithStillImagePath:(NSString *)path duration:(MovieousTime)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 UIImage 对象来初始化一个图片类型的 MSVClip 对象。
 *
 * @param image 用来创建 MSVClip 对象的 UIImage 对象。
 * @param duration 图片在视频中持续的时长，单位为微秒。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithStillImage:(UIImage *)image duration:(MovieousTime)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片路径来初始化一个图片类型的 MSVClip 对象。
 *
 * @param path 源文件路径，仅支持本地文件，支持 iOS 系统原生支持的所有动态图片文件格式（gif 等）。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAnimatedImagePath:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 NSData 对象来初始化一个图片类型的 MSVClip 对象。
 *
 * @param data 用来创建 MSVClip 对象的 NSData 对象，支持 iOS 系统原生支持的所有动态图片文件格式（gif 等）。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype)initWithAnimatedImageData:(NSData *)data error:(NSError **)outError;

/**
 * 使用 UIImage 对象来初始化一个图片类型的 MSVClip 对象。
 *
 * @param image 用来创建 MSVClip 对象的 UIImage 对象，请确保 image.images 不为空。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAnimatedImage:(UIImage *)image error:(NSError *_Nullable *_Nullable)outError;

- (instancetype _Nullable)initWithStillText:(NSAttributedString *)text duration:(MovieousTime)duration error:(NSError *_Nullable *_Nullable)outError;

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
 * 媒体文件地址，当使用 asset 或 image 来初始化 MSVClip 时 path 的值为 nil。
 */
@property (nonatomic, strong, readonly) NSString *path;

/**
 * 初始化时使用的 UIImage对象。
 */
@property (nonatomic, strong, readonly) UIImage *image;

/**
 * 初始化时使用的 AVAsset 对象。
 * @warning 不适用于 MSVClipTypeStillImage 类型的 MSVClip。
 */
@property (nonatomic, strong, readonly) AVAsset *asset;

@property (nonatomic, strong) NSAttributedString *text;

/**
 * 片段的自然尺寸（将源文件默认的旋转考虑在内）。
 */
@property (nonatomic, assign, readonly) CGSize defaultSize;

/**
 * 片段的默认旋转方向。
 */
@property (nonatomic, assign, readonly) MovieousVideoOrientation defaultOrientation;

/**
 * 片段的默认镜像情况。
 */
@property (nonatomic, assign, readonly) BOOL defaultMirrored;

/**
 * 背景颜色。
 */
@property (nonatomic, strong) UIColor *backgroundColor;

/**
 * 取材的视频区域的中心点。
 * @warning 如果取材的视频区域超过源视频的范围，源视频以外的区域将显示为以源视频边缘的颜色向外延伸的栅格状图形。
 */
@property (nonatomic, assign) CGPoint sourceCenter;

/**
 * 取材的视频区域的大小。
 * @warning 如果取材的视频区域超过源视频的范围，源视频以外的区域将显示为以源视频边缘的颜色向外延伸的栅格状图形。
 */
@property (nonatomic, assign) CGSize sourceSize;

/**
 * 取材的视频区域的旋转弧度，以 sourceCenter 为中心。
 * @warning 如果取材的视频区域超过源视频的范围，源视频以外的区域将显示为以源视频边缘的颜色向外延伸的栅格状图形。
 */
@property (nonatomic, assign) float sourceRotation;

/**
 * 片段在目标视频当中的中心点。
 */
@property (nonatomic, assign) CGPoint destCenter;

/**
 * 片段在目标视频当中的大小。
 */
@property (nonatomic, assign) CGSize destSize;

/**
 * 片段在目标视频当中的旋转弧度。
 */
@property (nonatomic, assign) float destRotation;

/**
 * 重置视频的位置，大小和转向，使用该方法将会调整 sourceCenter，sourceSize，sourceRotation 以取材视频的所有内容，然后调整 destCenter，destSize 和 destRotation 以将素材按照 scalingMode 指定的填充方式填充到以 videoSize 为大小的目标视频当中。
 *
 * @param videoSize 目标视频大小。
 * @param scalingMode 填充模式。
 */
- (void)resetGeometryWithVideoSize:(CGSize)videoSize scalingMode:(MovieousScalingMode)scalingMode;

/**
 * 片段在目标视频当中的透明度。
 */
@property (nonatomic, assign) float alpha;

/**
 * 给片段应用的 LUT filter，您可以传入一张颜色查找图来应用滤镜。
 */
@property (nonatomic, strong, nullable) UIImage *LUTFilterImage;

/**
 * LUT 滤镜的强度。
 */
@property (nonatomic, assign) float LUTFilterIntensity;

/**
 * 片段帧数据处理器。
 */
@property (nonatomic, weak) id<MSVClipProcessor> processor;

/**
 * 片段实际在主轨中实际展示的时间区间。
 */
@property (nonatomic, assign, readonly) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 片段实际在主轨中实际展示的开始时间，当片段加入 MSVDraft 之后才能获取到该值。
 */
@property (nonatomic, assign, readonly) MovieousTime startTimeAtMainTrack;

/**
 * 片段实际在主轨中的时间长度，当片段类型是音视频时，durationAtMainTrack 参数和 speed 参数互相影响，调整 durationAtMainTrack 将会影响 speed，具体为：speed = timeRange.duration / durationAtMainTrack.
 * 默认为根据 timeRange 和 speed 自动计算出来的数据。
 */
@property (nonatomic, assign) MovieousTime durationAtMainTrack;

/**
 * 片段是否包含视觉内容（视频或图片）。
 */
@property (nonatomic, assign, readonly) BOOL hasVisualContent;

/**
 * 是否忽略片段中的视觉内容。
 * @warning 如果设置该值为 YES 后会导致片段既没有音频也没有视频，那么该设置会抛出 exception。
 */
@property (nonatomic, assign) BOOL ignoreVisualContent;

/**
 * 片段是否包含听觉内容（音乐）。
 */
@property (nonatomic, assign, readonly) BOOL hasAuditoryContent;

/**
 * 是否忽略片段中的听觉内容。
 * @warning 如果设置该值为 YES 后会导致片段既没有音频也没有视频，那么该设置会抛出 exception。
 */
@property (nonatomic, assign) BOOL ignoreAuditoryContent;

/**
 * 获取用于生成快照的图片生成器对象。
 *
 * @return 生成的 MSVSnapshotGenerator 对象。
 */
@property (nonatomic, strong, readonly) MSVSnapshotGenerator *snapshotGenerator;

/**
 * 当 `AVAudioSessionMediaServicesWereResetNotification` 通知发生时重置内部的音频相关服务。
 */
- (void)refreshAsset;

#pragma mark - 如下参数不适用于 MSVClipTypeStillImage 类型的 MSVClip。

/**
 * 视频片段的初始总时长。
 * @warning 不适用于 MSVClipTypeStillImage 类型的 MSVClip。
 */
@property (nonatomic, assign, readonly) MovieousTime originalDuration;

/**
 * 视频片段在主轨中（目标视频中）的总时长（考虑 speed 的因素）
 * @warning 不适用于 MSVClipTypeStillImage 类型的 MSVClip。
 */
@property (nonatomic, assign, readonly) MovieousTime originalDurationAtMainTrack;

/**
 * 片段的视频部分的帧率。
 * @warning 不适用于 MSVClipTypeStillImage 类型的 MSVClip。
 */
@property (nonatomic, assign, readonly) float frameRate;

/**
 * 源视频中用于填充目标视频的有效的时间区间。
 * 默认为整个视频区间。
 *
 * @warning 不适用于 MSVClipTypeStillImage 类型的 MSVClip。另外需要注意的是此处的 timeRange 不将快慢速考虑在内，另外超出整个媒体区间的部分将被忽略。
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * 录制视频片段的速度。
 * 默认为 1.0。
 *
 * @discussion
 * 推荐配置：非常快：2.0，快：1.5，正常：1.0，慢：0.75，非常慢：0.5。
 */
@property (nonatomic, assign) float speed;

/**
 * 文件自带的默认媒体音频的音量。
 */
@property (nonatomic, assign, readonly) float preferredVolume;

/**
 * 音量调节参数，体现在目标视频中的实际音量值为 preferredVolume * volumeMultiplier。
 */
@property (nonatomic, assign) float volumeMultiplier;

@end

NS_ASSUME_NONNULL_END
