//
//  MSVMixTrackClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/1.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVClip.h"
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 用来合成视频的片段对象。
 */
@interface MSVMixTrackClip : MSVClip

/**
 * 创建一个 MSVMixTrackClip 对象。
 *
 * @param type MSVMixTrackClip 的类型。
 * @param path 媒体文件的地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithType:(MSVClipType)type path:(NSString *)path startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 来创建一个 MSVMixTrackClip 对象。
 *
 * @param asset 用来创建合成轨片段的 AVAsset 对象。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mixTrackClipWithAsset:(AVAsset *)asset  startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

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
+ (instancetype _Nullable)mixTrackClipWithImage:(UIImage *)image duration:(NSTimeInterval)duration startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 初始化一个 MSVMixTrackClip 对象。
 *
 * @param type MSVMixTrackClip 的类型。
 * @param path 媒体文件的地址。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithType:(MSVClipType)type path:(NSString *)path startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 AVAsset 来初始化一个 MSVMixTrackClip 对象。
 *
 * @param asset 用来创建合成轨片段的 AVAsset 对象。
 * @param startTimeAtMainTrack 合成轨片段在主轨中的开始时间。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果初始化成功，返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAsset:(AVAsset *)asset startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

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
- (instancetype _Nullable)initWithImage:(UIImage *)image duration:(NSTimeInterval)duration startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

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
@property (nonatomic, assign) NSTimeInterval startTimeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
