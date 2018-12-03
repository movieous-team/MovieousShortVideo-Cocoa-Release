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
#import "MSVAudioClip.h"
#import "MSVLUTFilterEffect.h"
#import "MSVExternalFilterEffect.h"
#import "MSVImagePasterEffect.h"

/**
 * @brief 视频草稿，调用者可以自行生成草稿或直接草稿进行任意编辑，然后使用 MSVEditor 实时生成草稿的预览，也可以使用 MSVExporter 对草稿进行导出
 */
@interface MSVDraft : NSObject

/**
 * @brief 主轨道片段集合，主轨道片段按照其 durationAtMainTrack 所指定的时长顺序排列组成视频的主轨道，草稿的长度由主轨道时长决定
 */
@property (nonatomic, strong, readonly) NSArray<MSVMainTrackClip *> *mainTrackClips;

/**
 * @brief 音频片段集合，草稿的音频为由 mainTrackClips 中的音频与 audioClips 按照各自的音量进行混合产生
 */
@property (nonatomic, strong, readonly) NSArray<MSVAudioClip *> *audioClips;

/**
 * @brief 特效集合，当前支持 MSVExternalFilterEffect、MSVLUTFilterEffect、MSVImageEffect、MSVRepeatEffect、MSVSpeedEffect，这些效果均只应用到主轨上
 */
@property (nonatomic, strong, readonly) NSArray *effects;

/**
 * @brief 草稿原始总时长（不考虑时间特效，不考虑 timeRange）
 */
@property (nonatomic, assign, readonly) NSTimeInterval originalDuration;

/**
 * @brief 草稿总时长（考虑时间特效，不考虑 timeRange）
 */
@property (nonatomic, assign, readonly) NSTimeInterval duration;

/**
 * @brief 视频的大小，预览时如果窗口的大小与 videoSize 的大小不一致，将按照 editor.previewScalingMode 指定的缩放方式进行缩放
 */
@property (nonatomic, assign) CGSize videoSize;

/**
 * @brief 有效的时间区域，其他部分将被忽略
 * @warning 这里的时间区间是以应用完时间特效之后的区间，调用者如果设置了 timeRange，对主轨进行相关增删改或更新时间特效之后要配合调整 timeRange，以保证应用正确的 timeRange
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief 使用音视频文件地址来创建一份草稿，创建的草稿将包含一个 MSVMainTrackClip 指向该文件的地址
 * @param URL 音视频文件的地址
 * @param outError 如果发生错误，返回发生的错误
 * @return 创建成功则返回草稿对象，失败返回 nil
 */
+ (instancetype)draftWithAVURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 使用图片文件地址来创建一个草稿对象，创建的草稿将包含一个 MSVMainTrackClip 指向该文件的地址
 * @param URL 图片文件的地址
 * @param outError 如果发生错误，返回发生的错误
 * @return 创建成功则返回草稿对象，失败返回 nil
 */
+ (instancetype)draftWithImageURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 初始化草稿对象
 * @param mainTrackClipType 主轨道片段类型
 * @param URL 主轨道片段的地址
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功则返回草稿对象，失败返回 nil
 */
- (instancetype)initWithMainTrackClipType:(MSVMainTrackClipType)mainTrackClipType URL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 生成草稿的预览截屏
 * @param count 预览截屏的数量
 * @param withinTimeRange 是否只生成 timeRange 范围内的截图
 * @param handler 完成后的回调，timestamp：截屏时间戳，snapshot：截屏，error：如发生错误即所发生的错误
 */
- (void)generateSnapshotsWithCount:(NSUInteger)count withinTimeRange:(BOOL)withinTimeRange completionHanler:(void (^)(NSTimeInterval timestamp, UIImage *snapshot, NSError *error))handler;

/**
 * @brief 更新主轨片段集，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新
 * @param mainTrackClips 新的主轨片段集
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)updateMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips error:(NSError **)outError;

/**
 * @brief 更新音频片段集，非 readonly 的参数可以直接在相关对象中调整，其他操作（增、删、替换等）需要使用该接口进行刷新
 * @param audioClips 新的音频片段集合
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)updateAudioClips:(NSArray<MSVAudioClip *> *)audioClips error:(NSError **)outError;

/**
 * @brief 更新特效集合
 * @param effects 新的特效集合
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)updateEffects:(NSArray *)effects error:(NSError **)outError;

/**
 * @brief 验证当前草稿是否能够有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateForRecorderWithError:(NSError **)outError;

/**
 * @brief 验证草稿是否有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateForWithError:(NSError **)outError;

/**
 * @brief 更新音量的操作是实时进行了，当你需要批量修改很多片段的音量时为了提高操作的效率请先调用该方法，然后进行相关音量修改，最后调用 -commitVolumeChange 方法提交修改。如果不按照这种范式进行调用那每次修改音量都会触发更新操作，这将会导致
 */
- (void)beginVolumeChangeTransaction;

/**
 * @brief 提交音量更新
 */
- (BOOL)commitVolumeChangeWithError:(NSError **)outError;

/**
 * @brief 除了更新音量以外的其他操作，当你需要批量对相关属性进行操作时可以调用该方法开始一个 transaction，然后再完成所有操作之后再调用 -commitChangeWithError: 方法提交所有修改
 */
- (void)beginChangeTransaction;

/**
 * @brief 取消当前批量更新 transaction
 */
- (void)cancelChangeTransaction;

/**
 * @brief 提交一般属性的更新
 */
- (BOOL)commitChangeWithError:(NSError **)outError;

/**
 * @brief 工具方法，对原始时间点应用时间特效，映射为应用时间特效后的时间点
 * @param time 未应用时间特效的时间点
 * @return 应用时间特效后的时间点
 */
- (NSTimeInterval)applyEffectToTime:(NSTimeInterval)time;

/**
 * @brief 工具方法，将已应用时间特效的时间点映射到去掉时间特效的时间点
 * @param time 已应用时间特效的时间点
 * @return 去掉时间特效后的时间点
 */
- (NSTimeInterval)removeEffectFromTime:(NSTimeInterval)time;

/**
 * @brief 工具方法，对原始时间区间应用时间特效，映射为应用时间特效后的时间区间
 * @param timeRange 未应用时间特效的时间区间
 * @return 应用时间特效后的时间区间
 */
- (MovieousTimeRange)applyEffectToTimeRange:(MovieousTimeRange)timeRange;

/**
 * @brief 工具方法，将已应用时间特效的时间区间映射到去掉时间特效的时间区间
 * @param timeRange 已应用时间特效的时间区间
 * @return 去掉时间特效后的时间区间
 */
- (MovieousTimeRange)removeEffectFromTimeRange:(MovieousTimeRange)timeRange;

@end
