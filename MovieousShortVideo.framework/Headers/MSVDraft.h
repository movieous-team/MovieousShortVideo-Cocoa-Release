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
#import "MSVLUTFilterEditorEffect.h"
#import "MSVEditorEffect.h"
#import "MSVMixTrackClip.h"
#import "MSVSnapshotGenerator.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 视频草稿，调用者可以自行生成草稿或直接草稿进行任意编辑，然后使用 MSVEditor 实时生成草稿的预览，也可以使用 MSVExporter 对草稿进行导出
 */
@interface MSVDraft : MovieousObject
<
NSCopying
>

/**
 * 使用音视频文件地址来初始化一份草稿，初始化后的草稿将包含一个 MSVMainTrackClip 指向该文件的地址。
 *
 * @param path 音视频文件的地址。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 初始化成功的草稿对象。
 */
+ (instancetype _Nullable)draftWithAVPath:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用图片文件地址来创建一个草稿对象，初始化后的草稿将包含一个 MSVMainTrackClip 指向该文件的地址。
 *
 * @param path 图片文件的地址。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 创建成功则返回草稿对象，失败返回 nil。
 */
+ (instancetype _Nullable)draftWithImagePath:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 初始化草稿对象。
 *
 * @param mainTrackClipType 主轨道片段类型。
 * @param path 主轨道片段的地址。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 初始化成功则返回草稿对象，失败返回 nil。
 */
- (instancetype _Nullable)initWithMainTrackClipType:(MSVClipType)mainTrackClipType path:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

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
- (BOOL)updateBackgroundColor:(UIColor *)backgroundColor error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(backgroundColor:));

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
 * 合成轨片段数组，最终生成的视频的可视部分由 mainTrackClips 和 mixTrackClips 根据各自的位置和大小合成得到
 */
@property (nonatomic, strong, readonly) NSArray<MSVMixTrackClip *> *mixTrackClips;

/**
 * 更新合成轨片段集，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新。
 *
 * @param mixTrackClips 新的合成轨片段集。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateMixTrackClips:(NSArray<MSVMixTrackClip *> *_Nullable)mixTrackClips error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(mixTrackClips:));

/**
 * 基础特效数组，当前支持 MSVExternalFilterEditorEffect, MSVLUTFilterEditorEffect, MSVImageEffect，所有特效均被应用于整个目标视频。
 */
@property (nonatomic, strong, readonly) NSArray<id<MSVEditorEffect>> *basicEffects;

/**
 * 更新基础特效数组。
 *
 * @param basicEffects 新的基础特效数组。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateBasicEffects:(NSArray<id<MSVEditorEffect>> *_Nullable)basicEffects error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(basicEffects:));

/**
 * 草稿总时长（不考虑 timeRange）
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;

/**
 * 视频的大小，预览时如果 preview 的比例与 videoSize 的比例不同，将按照 editor.previewScalingMode 指定的缩放方式进行缩放填充。
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
- (BOOL)updateVideoSize:(CGSize)videoSize error:(NSError *_Nullable *_Nullable)outError NS_SWIFT_NAME(update(videoSize:));

/**
 * 目标视频的帧率。
 */
@property (nonatomic, assign, readonly) float frameRate;

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
@property (nonatomic, strong) MSVSnapshotGenerator *imageGenerator;

/**
 * 除了更新音量以外的其他操作，当你需要批量对相关属性进行操作时可以调用该方法开始一个 transaction，然后再完成所有操作之后再调用 -commitChangeWithError: 方法提交所有修改。
 */
- (void)beginChangeTransaction;

/**
 * 提交一般属性的更新。
 *
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)commitChangeWithError:(NSError *_Nullable *_Nullable)outError;

@end

NS_ASSUME_NONNULL_END
