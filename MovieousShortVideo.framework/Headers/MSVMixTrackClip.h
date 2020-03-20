//
//  MSVMixTrackClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/1.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVClip.h"
#import "MSVTypeDefines.h"
#import "MSVTimeDomainObject.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 用来合成视频的片段对象。
 */
@interface MSVMixTrackClip : MSVClip
<
MSVTimeDomainObject
>

/**
 * 使用音视频文件地址来创建一个 MSVMixTrackClip 对象。
 *
 * @param path 媒体文件的地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithAVPath:(NSString *)path startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用音视频文件地址来初始化一个 MSVMixTrackClip 对象。
 *
 * @param path 媒体文件的地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAVPath:(NSString *)path startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 来创建一个 MSVMixTrackClip 对象。
 *
 * @param asset 用来创建合成轨片段的 AVAsset 对象。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithAsset:(AVAsset *)asset  startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 来初始化一个 MSVMixTrackClip 对象。
 *
 * @param asset 用来创建合成轨片段的 AVAsset 对象。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAsset:(AVAsset *)asset startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用静态图片地址来创建一个 MSVMixTrackClip 对象。
 *
 * @param path 静态图片地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithStillImagePath:(NSString *)path duration:(MovieousTime)duration startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用静态图片地址来初始化一个 MSVMixTrackClip 对象。
 *
 * @param path 静态图片地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithStillImagePath:(NSString *)path duration:(MovieousTime)duration startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 UIImage 来创建一个 MSVMixTrackClip 对象。
 *
 * @param image 用来初始化的 UIImage 对象。
 * @param duration 图片时长。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithStillImage:(UIImage *)image duration:(MovieousTime)duration startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 UIImage 来初始化一个 MSVMixTrackClip 对象。
 *
 * @param image 用来初始化的 UIImage 对象。
 * @param duration 图片时长。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithStillImage:(UIImage *)image duration:(MovieousTime)duration startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片地址来创建一个 MSVMixTrackClip 对象。
 *
 * @param path 动态图片地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithAnimatedImagePath:(NSString *)path startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片地址来初始化一个 MSVMixTrackClip 对象。
 *
 * @param path 动态图片地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回创建后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAnimatedImagePath:(NSString *)path startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片数据来创建一个 MSVMixTrackClip 对象。
 *
 * @param data 动态图片数据。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithAnimatedImageData:(NSData *)data startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片数据来初始化一个 MSVMixTrackClip 对象。
 *
 * @param data 动态图片数据。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回创建后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAnimatedImageData:(NSData *)data startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片对象来创建一个 MSVMixTrackClip 对象。
 *
 * @param image 动态图片对象，image 对象需要包含 images 属性（即为动态图片对象）。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithAnimatedImage:(UIImage *)image startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片对象来初始化一个 MSVMixTrackClip 对象。
 *
 * @param image 动态图片对象，image 对象需要包含 images 属性（即为动态图片对象）。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回创建后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAnimatedImage:(UIImage *)image startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;


/**
 * 使用其他 MSVMixTrackClip 来初始化一个 MSVMixTrackClip 对象。
 *
 * @param mixTrackClip 用于初始化的的 MSVMixTrackClip 对象。
 *
 * @return 返回初始化后的对象。
 */
- (instancetype)initWithMixTrackClip:(MSVMixTrackClip *)mixTrackClip;

/**
 * 合成轨片段在主轨中的开始时间。
 */
@property (nonatomic, assign) MovieousTime startTimeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
