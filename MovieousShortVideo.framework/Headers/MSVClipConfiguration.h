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
 * 录制片段的配置类，用于进行当前录制片段的配置
 */
@interface MSVClipConfiguration : NSObject

/**
 * @brief 片段录制的文件地址，默认为自动生成的地址
 */
@property (nonatomic, strong) NSURL *URL;

/**
 * @brief 片段录制的媒体文件类型，默认为 MSVFileTypeMPEG4
 */
@property (nonatomic, assign) MSVFileType fileType;

/**
 * @brief 将要录制的片段的速度，默认值为：1.0
 * 一般来说可以进行如下配置：
 * 极快：2.0
 * 快：1.5
 * 正常：1.0
 * 慢：0.75
 * 极慢：0.5
 */
@property (nonatomic, assign) CGFloat speed;

/**
 * @brief 所录制的片段的原声音量，默认为 1.0
 */
@property (nonatomic, assign) float volume;

/**
 * @brief 用于录制的 view，当且仅当 videoConfiguration.source = MSVVideoSourceUIView 时有效
 * 默认为 nil
 */
@property (nonatomic, strong) UIView *viewForRecording;

/**
 * @brief 生成默认配置对象
 * @return 返回生成的默认配置对象
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
