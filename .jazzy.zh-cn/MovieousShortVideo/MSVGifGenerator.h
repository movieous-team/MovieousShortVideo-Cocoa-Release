//
//  MSVGifGenerator.h
//  MSVShortVideoKit
//
//  Created by Chris Wang on 2019/7/14.
//  Copyright © 2019年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVGifGenerator : NSObject

/**
 * GIF 文件输出地址，仅支持本地地址。
 * 默认为自动生成的地址。
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * 生成任务是否正在运行。
 */
@property (nonatomic, assign, readonly) BOOL running;

/**
 * 生成的 GIF 文件中各帧之间的间隔时长。
 * 默认为 0.1。
 */
@property (assign, nonatomic) float interval;

/**
 * gif 轮播次数，0 表示无限轮播。
 * 默认为 0。
 */
@property (assign, nonatomic) NSUInteger loopCount;

/**
 * 生成任务进度回调。
 */
@property (nonatomic, copy, nullable) void(^progressHandler)(float progress);

/**
 * 生成任务失败回调。
 */
@property (nonatomic, copy, nullable) void(^failureHandler)(NSError *error);

/**
 * 生成任务成功回调。
 */
@property (nonatomic, copy, nullable) void(^completionHandler)(NSURL *URL);

/**
 * 使用图片数组初始化 MSVGifGenerator 对象。
 *
 * @param images 用于生成 gif 的图片数组。
 *
 * @return 初始化完成的对象。
 */
- (instancetype)initWithImages:(NSArray<UIImage *> *)images;

/**
 * 开始生成任务。
 */
- (void)start;

/**
 * 取消生成任务。
 */
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
