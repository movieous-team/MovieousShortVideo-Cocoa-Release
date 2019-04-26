//
//  MSVDraft.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/5.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "MSVTypeDefines.h"
#import "MSVMainTrackClip.h"
#import "MSVClip.h"
#import "MSVLUTFilterEditorEffect.h"
#import "MSVBasicEditorEffect.h"
#import "MSVTimeEditorEffect.h"
#import "MSVMixTrackClip.h"
#import "MSVImageGenerator.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 视频草稿，调用者可以自行生成草稿或直接草稿进行任意编辑，然后使用 MSVEditor 实时生成草稿的预览，也可以使用 MSVExporter 对草稿进行导出
 */
@interface MSVDraft : NSObject
<
NSCopying
>

/**
 * 使用音视频文件地址来初始化一份草稿，初始化后的草稿将包含一个 MSVMainTrackClip 指向该文件的地址。
 * 
 * @param URL 音视频文件的地址。
 * @param outError 如果发生错误，返回发生的错误。
 * 
 * @return 初始化成功的草稿对象。
 */
+ (instancetype)draftWithAVURL:(NSURL *)URL error:(NSError **)outError;

/**
 * 使用图片文件地址来创建一个草稿对象，初始化后的草稿将包含一个 MSVMainTrackClip 指向该文件的地址。
 * 
 * @param URL 图片文件的地址。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 创建成功则返回草稿对象，失败返回 nil。
 */
+ (instancetype)draftWithImageURL:(NSURL *)URL error:(NSError **)outError;

/**
 * 初始化草稿对象。
 * 
 * @param mainTrackClipType 主轨道片段类型。
 * @param URL 主轨道片段的地址。
 * @param outError 如果发生错误，返回发生的错误。
 * 
 * @return 初始化成功则返回草稿对象，失败返回 nil。
 */
- (instancetype)initWithMainTrackClipType:(MSVClipType)mainTrackClipType URL:(NSURL *)URL error:(NSError **)outError;

/**
 * 视频容器的背景颜色。
 */
@property (nonatomic, strong, readonly) UIColor *backgroundColor;

/**
 * 更新视频容器的背景颜色。
 *
 * @param backgroundColor 新背景颜色。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateBackgroundColor:(UIColor *)backgroundColor error:(NSError **)outError;

/**
 * @brief 主轨道片段数组，主轨道片段按照其 durationAtMainTrack 所指定的时长顺序排列组成视频的主轨道，草稿的长度由主轨道时长决定
 */
@property (nonatomic, strong, readonly) NSArray<MSVMainTrackClip *> *mainTrackClips;

/**
 * 更新主轨片段集，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新。
 * 
 * @param mainTrackClips 新的主轨片段集。
 * @param outError 如果发生错误，返回发生的错误。
 * 
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips error:(NSError **)outError;

/**
 * 合成轨片段数组，最终生成的视频的可视部分由 mainTrackClips 和 mixTrackClips 根据各自的位置和大小合成得到
 */
@property (nonatomic, strong, readonly) NSArray<MSVMixTrackClip *> *mixTrackClips;

/**
 * 更新合成轨片段集，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新。
 *
 * @param mainTrackClips 新的合成轨片段集。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateMixTrackClips:(NSArray<MSVMixTrackClip *> *)mixTrackClips error:(NSError **)outError;

/**
 * 基础特效数组，当前支持 MSVExternalFilterEditorEffect, MSVLUTFilterEditorEffect, MSVImageEffect，所有特效均被应用于整个目标视频。
 */
@property (nonatomic, strong, readonly) NSArray<id<MSVBasicEditorEffect>> *basicEffects;

/**
 * 更新基础特效数组。
 *
 * @param basicEffects 新的基础特效数组。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateBasicEffects:(NSArray<id<MSVBasicEditorEffect>> *)basicEffects error:(NSError **)outError;

/**
 * 时间特效数组，当前支持 MSVRepeatEditorEffect, MSVSpeedEditorEffect
 */
@property (nonatomic, strong, readonly) NSArray<id<MSVTimeEditorEffect>> *timeEffects;

/**
 * 更新时间特效数组。
 *
 * @param timeEffects 新的时间特效数组.
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateTimeEffects:(NSArray<id<MSVTimeEditorEffect>> *)timeEffects error:(NSError **)outError;

/**
 * 草稿原始总时长（不考虑时间特效，不考虑 timeRange）
 */
@property (nonatomic, assign, readonly) NSTimeInterval originalDuration;

/**
 * 草稿总时长（考虑时间特效，不考虑 timeRange）
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;

/**
 * Whether to reverse video part of the draft, audio part will never be reversed.
 */
@property (nonatomic, assign) BOOL reverseVideo;

/**
 * 视频的大小，预览时如果窗口的大小与 videoSize 的大小不一致，将按照 editor.previewScalingMode 指定的缩放方式进行缩放
 */
@property (nonatomic, assign, readonly) CGSize videoSize;

/**
 * 设置视频的大小，预览时如果窗口的大小与 videoSize 的大小不一致，将按照 editor.previewScalingMode 指定的缩放方式进行缩放。
 *
 * @param videoSize 新的视频大小。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)setVideoSize:(CGSize)videoSize error:(NSError **)outError;

/**
 * 有效的时间区域，其他部分将被忽略
 * 
 * @warning 这里的时间区间是以应用完时间特效之后的区间，调用者如果设置了 timeRange，对主轨进行相关增删改或更新时间特效之后要配合调整 timeRange，以保证应用正确的 timeRange
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * Get the image generator object used for generating snapshots.
 *
 * @return The instantiated MSVImageGenerator object.
 */
@property (nonatomic, strong) MSVImageGenerator *imageGenerator;

/**
 * 更新音量的操作是实时进行了，当你需要批量修改很多片段的音量时为了提高操作的效率请先调用该方法，然后进行相关音量修改，最后调用 -commitVolumeChange 方法提交修改。如果不按照这种范式进行调用那每次修改音量都会触发更新操作，这将会导致性能问题。
 */
- (void)beginVolumeChangeTransaction;

/**
 * 提交音量更新。
 * 
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)commitVolumeChangeWithError:(NSError **)outError;

/**
 * 除了更新音量以外的其他操作，当你需要批量对相关属性进行操作时可以调用该方法开始一个 transaction，然后再完成所有操作之后再调用 -commitChangeWithError: 方法提交所有修改。
 */
- (void)beginChangeTransaction;

/**
 * 取消当前批量更新 transaction。
 */
- (void)cancelChangeTransaction;

/**
 * 提交一般属性的更新。
 * 
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)commitChangeWithError:(NSError **)outError;

/**
 * 工具方法，对原始时间点应用时间特效，映射为应用时间特效后的时间点。
 * 
 * @param originalTime 未应用时间特效的时间点。
 * 
 * @return 应用时间特效后的时间点。
 */
- (NSTimeInterval)getEffectedTimeFromOriginalTime:(NSTimeInterval)originalTime;

/**
 * 工具方法，将已应用时间特效的时间点映射到去掉时间特效的时间点。
 * 
 * @param time 已应用时间特效的时间点。
 * 
 * @return 去掉时间特效后的时间点。
 */
- (NSTimeInterval)getOriginalTimeFromEffectedTime:(NSTimeInterval)effectedTime;

/**
 * 工具方法，对原始时间区间应用时间特效，映射为应用时间特效后的时间区间。
 * 
 * @param timeRange 未应用时间特效的时间区间。
 * 
 * @return 应用时间特效后的时间区间。
 */
- (MovieousTimeRange)getEffectedRangeTimeFromOriginalTimeRange:(MovieousTimeRange)originalTimeRange;

/**
 * 工具方法，将已应用时间特效的时间区间映射到去掉时间特效的时间区间。
 * 
 * @param timeRange 已应用时间特效的时间区间。
 * 
 * @return 去掉时间特效后的时间区间。
 */
- (MovieousTimeRange)getOriginalTimeRangeFromEffectedTimeRange:(MovieousTimeRange)effectedTimeRange;

@end

NS_ASSUME_NONNULL_END
