//
//  MSVDraft.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/5.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>
#import "MSVTypeDefines.h"
#import "MSVMainTrackClip.h"
#import "MSVClip.h"
#import "MSVMixTrackClip.h"
#import "MSVSnapshotGenerator.h"
#import "MSVMainTrackTransition.h"
#import "MSVClipOrEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 视频草稿，调用者可以自行生成草稿或直接草稿进行任意编辑，然后使用 MSVEditor 实时生成草稿的预览，也可以使用 MSVExporter 对草稿进行导出
 */
@interface MSVDraft : MovieousObject
<
NSCopying
>

/**
 * 使用主轨片段数组实例化一个 MSVDraft 对象。
 *
 * @param mainTrackClips 新的主轨片段集。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
+ (instancetype)draftWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips error:(NSError **)outError;

/**
 * 使用主轨片段数组初始化一个 MSVDraft 对象。
 *
 * @param mainTrackClips 新的主轨片段集。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (instancetype)initWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips error:(NSError **)outError;

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
- (BOOL)updateMainTrackClips:(NSArray<MSVMainTrackClip *> *_Nullable)mainTrackClips error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(mainTrackClips:));

/**
 * @brief 主轨转场 dictionary，key 为应用转场的两个相邻 MSVMainTrackClip 对象中前一个的 index
 * 例如 mainTrackClips 由 [mainTrackClip1, mainTrackClip2, mainTrackClip3] 组成，那么 mainTrackClip2 和 mainTrackClip3 之间的转场 key 值为 1（即 mainTrackClip2 的 index ）
 */
@property (nonatomic, strong, readonly) NSDictionary<NSNumber *, MSVMainTrackTransition *> *mainTrackTransitions;

/**
 * 更新主轨转场集，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新。
 *
 * @param mainTrackTransitions 新的主轨转场集。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateMainTrackTransitions:(NSDictionary<NSNumber *, MSVMainTrackTransition *> *_Nullable)mainTrackTransitions error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(mainTrackTransitions:));

/**
 * 合成轨片段或特效数组，合成轨片段的视频叠加顺序和特效应用的顺序与该数组的顺序保持一致。
 * 例如 mixTrackClipsOrEffects 的构成为 [mixTrackClip1, mixTrackClip2, effect1, mixTrackClip3, effect2]，mixTrackClip1，mixTrackClip2，mixTrackClip3，则任意一帧的生成将是按照如下方式：在画布上绘制 mixTrackClip1，在画布上绘制 mixTrackClip2，应用 effect1 特效，在画布上绘制 mixTrackClip3，应用 effect2 特效。
 */
@property (nonatomic, strong, readonly) NSArray<id<MSVMutableClipOrEffect>> *mixTrackClipsOrEffects;

/**
 * 更新合成轨片段或特效数组，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新。
 * 例如 mixTrackClipsOrEffects 的构成为 [mixTrackClip1, mixTrackClip2, effect1, mixTrackClip3, effect2]，mixTrackClip1，mixTrackClip2，mixTrackClip3，则任意一帧的生成将是按照如下方式：在画布上绘制 mixTrackClip1，在画布上绘制 mixTrackClip2，应用 effect1 特效，在画布上绘制 mixTrackClip3，应用 effect2 特效。
 *
 * @param mixTrackClipsOrEffects 新的合成轨片段集。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateMixTrackClipsOrEffects:(NSArray<id<MSVMutableClipOrEffect>> *_Nullable)mixTrackClipsOrEffects error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(mixTrackClipsOrEffects:));

/**
 * 草稿的在应用 timeRange 之前的总时长。
 */
@property (nonatomic, assign, readonly) MovieousTime originalDuration;

/**
 * 视频分辨率，该分辨率由 maximumSize 和 aspectRatio 经过计算得到，分辨率在 maximumSize 形成的矩形区域之内，比例近似为 aspectRatio 且满足宽高均为 8 的整数倍的要求（编码视频的硬性要求）。
 */
@property (nonatomic, assign, readonly) CGSize videoSize;

/**
 * 视频的横纵比，最终的视频分辨率会尽量保证此横纵比。
 */
@property (nonatomic, assign) CGSize aspectRatio;

/**
 * 视频的最大分辨率。
 */
@property (nonatomic, assign) CGSize maximumSize;

/**
 * 目标视频的帧率。
 */
@property (nonatomic, assign) float frameRate;

/**
 * 有效的时间区间，其他部分将在预览和导出时被忽略。
 * 默认为 (0, draft.duration)，即 draft 的原始长度，传入 kMovieousTimeRangeDefault 可重置到默认时间区间。
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * 获取图片生成器以生成草稿的快照。
 *
 * @return 生成的图片生成器对象。
 */
@property (nonatomic, strong, readonly) MSVSnapshotGenerator *imageGenerator;

/**
 * 当你需要批量对相关属性进行操作时可以调用该方法开始一个 transaction，然后再完成所有操作之后再调用 -commitChangeWithError: 方法提交所有修改。
 */
- (void)beginChangeTransaction;

/**
 * 提交批量属性的更新。
 *
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)commitChangeWithError:(NSError *_Nullable *_Nullable)outError;

@end

NS_ASSUME_NONNULL_END
