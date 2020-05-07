//
//  MSVEditor.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/5.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MSVDraft.h"
#import "MSVClip.h"

NS_ASSUME_NONNULL_BEGIN

@interface MSVEditorPreview : UIView

/**
 * 预览视图的填充模式。
 * 默认为 MovieousScalingModeAspectFit。
 */
@property (nonatomic, assign) MovieousScalingMode scalingMode;

@end

/**
 * 编辑器对象。
 */
@interface MSVEditor : NSObject

/**
 * 底层草稿对象，相关编辑请通过该草稿对象进行操作。
 */
@property (nonatomic, strong) MSVDraft *draft;

/**
 * 编辑预览视图。
 */
@property (nonatomic, strong, readonly) MSVEditorPreview *preview;

/**
 * 视频内容在 preview 中展示的区域。
 */
@property (nonatomic, assign, readonly) CGRect contentFrame;

/**
 * 展示在画面。
 */
@property (nonatomic, assign, readonly) CGRect displayingRect;

/**
 * 编辑器错误。
 * 支持 KVO
 */
@property (nonatomic, strong, readonly) NSError *error;

/**
 * 编辑器的状态。
 * 支持 KVO
 */
@property (nonatomic, assign, readonly) MSVEditorStatus status;

/**
 * 当前播放进度。
 * 支持 KVO
 */
@property (nonatomic, assign, readonly) MovieousTime currentTime;

/**
 *是否循环播放。
 */
@property (nonatomic, assign) BOOL loop;

/**
 * 编辑器的预览播放器音量。
 */
@property (nonatomic, assign) float volume;

/**
 * 代理方法回调的队列。
 * 默认为主队列。
 */
@property (nonatomic, strong, null_resettable) dispatch_queue_t delegateQueue;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

/**
 * 使用一个草稿对象创建一个 MSVEditor 对象。
 *
 * @param draft 草稿对象。
 * @param outError 如果发生错误，返回发生的错误。
 *
 * @return 创建成功则返回草稿对象，失败返回 nil。
 */
+ (instancetype _Nullable)editorWithDraft:(MSVDraft *_Nullable)draft error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用一个草稿对象初始化一个 MSVEditor 对象。
 * 
 * @param draft 草稿对象。
 * @param outError 如果发生错误，返回发生的错误。
 * 
 * @return 初始化成功则返回草稿对象，失败返回 nil。
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft error:(NSError *_Nullable *_Nullable)outError NS_DESIGNATED_INITIALIZER;

/**
 * 开始预览草稿。
 */
- (void)play;

/**
 * 暂停预览草稿。
 */
- (void)pause;

/**
 * 快进到对应时间点。
 *
 * @param time 目标时间点。
 * @param accurate 是否是精确的快进，精确的快进将消耗更多的时间。
 */
- (void)seekToTime:(MovieousTime)time accurate:(BOOL)accurate;

@end

NS_ASSUME_NONNULL_END
