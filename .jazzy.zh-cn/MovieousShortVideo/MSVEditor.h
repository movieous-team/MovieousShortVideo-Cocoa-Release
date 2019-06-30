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

/**
 * 通知编辑器的当前播放时间已更新，userInfo 的 kMSVEditorCurrentTimeKey 中将携带当前的时间值。
 */
extern NSString *kMSVEditorCurrentTimeUpdatedNotification;

/**
 * 获取当前时间值的 key
 */
extern NSString *kMSVEditorCurrentTimeKey;

@class MSVEditor;
/**
 * 编辑器的代理对象，接受编辑器事件回调。
 */
@protocol MSVEditorDelegate <NSObject>

@optional
/**
 * 当前播放时间已更新的回调。
 *
 * @param editor 事件发送者。
 * @param currentTime 当前播放时间。
 */
- (void)editor:(MSVEditor *)editor currentTimeDidUpdate:(NSTimeInterval)currentTime;

/**
 * 当前播放状态已改变的回调。
 *
 * @param editor 事件发送者。
 * @param playing 当前是否正在播放的状态。
 */
- (void)editor:(MSVEditor *)editor playStateChanged:(BOOL)playing;

@end

/**
 * 编辑器对象。
 */
@interface MSVEditor : NSObject

/**
 * 底层草稿对象，相关编辑请通过该草稿对象进行操作。
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * 编辑预览视图。
 */
@property (nonatomic, strong, readonly) UIView *preview;

/**
 * 视频内容在 preview 中展示的区域。
 */
@property (nonatomic, assign, readonly) CGRect contentFrame;

/**
 * 预览视图的填充模式。
 * 默认为 MovieousScalingModeAspectFit。
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * 当前播放进度。
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentTime;

/**
 * 当前是否正在播放。
 */
@property (nonatomic, assign, readonly) BOOL playing;

/**
 *是否循环播放。
 */
@property (nonatomic, assign) BOOL loop;

/**
 * 编辑器的预览播放器音量。
 */
@property (nonatomic, assign) float volume;

/**
 * 编辑器代理对象。
 */
@property (nonatomic, weak) id<MSVEditorDelegate> delegate;

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
 * 更新底层 MSVDraft 对象。
 *
 * @param draft 新的 MSVDraft 对象。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError **)outError;

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
- (void)seekToTime:(NSTimeInterval)time accurate:(BOOL)accurate;

@end

NS_ASSUME_NONNULL_END
