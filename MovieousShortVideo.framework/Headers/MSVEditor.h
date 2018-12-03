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

extern NSString *kMSVEditorCurrentTimeUpdatedNotification;

@class MSVEditor;
@protocol MSVEditorDelegate <NSObject>

@optional
- (void)editor:(MSVEditor *)editor currentTimeDidUpdate:(NSTimeInterval)currentTime;

- (void)editor:(MSVEditor *)editor playStateChanged:(BOOL)playing;

@end

@interface MSVEditor : NSObject

/**
 * @brief 底层，草稿对象，相关编辑请通过该草稿对象进行操作
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * @brief 编辑预览视图
 */
@property (nonatomic, strong, readonly) UIView *preview;

/**
 * @brief 视频内容在 preview 中展示的区域
 */
@property (nonatomic, assign, readonly) CGRect contentFrame;

/**
 * @brief 预览视图的填充模式，默认为 MovieousScalingModeAspectFit
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * @brief 当前播放进度
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentTime;

/**
 * @brief 当前是否正在播放
 */
@property (nonatomic, assign, readonly) BOOL playing;

/**
 * @brief 是否循环播放
 */
@property (nonatomic, assign) BOOL loop;

/**
 * @brief 编辑器代理对象
 */
@property (nonatomic, weak) id<MSVEditorDelegate> delegate;

/**
 * @brief 代理方法回调的队列，默认为主队列
 */
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * @brief 通过音视频 URL 初始化一个 MSVEditor 对象
 * @param URL 音视频地址
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功则返回草稿对象，失败返回 nil
 */
- (instancetype)initWithAVURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 使用图片 URL 初始化一个 MSVEditor 对象
 * @param URL 图片地址
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功则返回草稿对象，失败返回 nil
 */
- (instancetype)initWithImageURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 使用一个草稿对象初始化一个 MSVEditor 对象
 * @param draft 草稿对象
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功则返回草稿对象，失败返回 nil
 */
- (instancetype)initWithDraft:(MSVDraft *)draft error:(NSError **)outError;

/**
 * @brief 开始预览
 */
- (void)play;

/**
 * @brief 暂停预览
 */
- (void)pause;

/**
 * @brief 播放器快进到相应的位置
 * @param time 目的位置
 * @param completionHandler 快进结束的回调，finished：快进是否完成。
 */
- (void)seekToTime:(NSTimeInterval)time completionHandler:(void (^)(BOOL finished))completionHandler;

@end
