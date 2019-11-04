//
//  MSVRecordingConfiguration.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/29.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 录制的片段配置类，用于配置录制的片段。
 */
@interface MSVClipConfiguration : NSObject

/**
 * 片段文件地址。
 * 默认为自动生成的地址。
 */
@property (nonatomic, strong, null_resettable) NSString *path;

/**
 * 媒体文件类型。
 * 默认为 MSVFileTypeMPEG4。
 */
@property (nonatomic, assign) MSVFileType fileType;

/**
 * 录制视频片段的速度。
 * 默认为 1.0。
 *
 * @discussion
 * 推荐配置：
 * 非常快：2.0。
 * 快：1.5。
 * 正常：1.0。
 * 慢：0.75。
 * 非常慢：0.5。
 */
@property (nonatomic, assign) CGFloat speed;

/**
 * 原始视频的音量。
 * 默认为1。
 */
@property (nonatomic, assign) float volume;

/**
 * 用来录制的 UIView，只有当 videoConfiguration.source = MSVVideoSourceUIView 时才有效。
 * 默认为 nil。
 */
@property (nonatomic, strong) UIView *viewForRecording;

/**
 * 创建一个默认配置对象。
 * 
 * @return 创建完成的对象。
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
