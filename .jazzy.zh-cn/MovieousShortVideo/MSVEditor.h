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
 * Notify the current play time of the editor has updated。
 */
extern NSString *kMSVEditorCurrentTimeUpdatedNotification;

/**
 * The current time key of kMSVEditorCurrentTimeUpdatedNotification。
 */
extern NSString *kMSVEditorCurrentTimeKey;

@class MSVEditor;
@protocol MSVEditorDelegate <NSObject>

@optional
/**
 * Notify the delegate that current play time has updated。
 *
 * @param editor The editor that send the event。
 * @param currentTime The current play time of the editor。
 */
- (void)editor:(MSVEditor *)editor currentTimeDidUpdate:(NSTimeInterval)currentTime;

/**
 * Notify the delegate that current play state has changed。
 *
 * @param editor The editor that send the event。
 * @param playing The current play state of the editor。
 */
- (void)editor:(MSVEditor *)editor playStateChanged:(BOOL)playing;

@end

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
 * 编辑器代理对象。
 */
@property (nonatomic, weak) id<MSVEditorDelegate> delegate;

/**
 * 代理方法回调的队列。
 * 默认为主队列。
 */
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

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
 * Update the underlying MSVDraft object。
 *
 * @param draft Draft object。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return It returns YES if the update is successful, returns NO if it fails。
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError **)outError;

/**
 * Start previewing。
 */
- (void)play;

/**
 * Pause previewing。
 */
- (void)pause;

/**
 * The player fast forwards to the appropriate position。
 *
 * @param time Target position。
 */
- (void)seekToTime:(NSTimeInterval)time accurate:(BOOL)accurate;

@end

NS_ASSUME_NONNULL_END
