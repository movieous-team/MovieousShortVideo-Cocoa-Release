//
//  MSVAudioConfiguration.h
//  MSVShortVideoKit
//
//  Created by Chris Wang on 18/3/1.
//  Copyright © 2018年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MSVTypeDefines.h"
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 音频录制配置类
 */
@interface MSVRecorderAudioConfiguration : NSObject
<
MovieousMicrophoneConfiguration
>

/**
 * @brief 音频输入源，默认为 MSVAudioSourceMicrophone
 */
@property (nonatomic, assign) MSVAudioSource source;

/**
 * @brief 采集音频数据的声道数，默认为 1
 * @warning 并非所有采集设备都支持多声道数据的采集
 */
@property (assign, nonatomic) NSUInteger numberOfChannels;

/**
 * @brief 音频采样率 sampleRate 默认为 MSVAudioSampleRate_44100Hz
 */
@property (assign, nonatomic) MSVAudioSampleRate sampleRate;

/**
 * @brief 音频编码码率 bitRate 默认为 MSVAudioBitRate_128Kbps
 */
@property (assign, nonatomic) MSVAudioBitRate bitRate;

/**
 * @brief 创建一个默认配置的 MSVAudioConfiguration 实例.
 * @return 创建的默认 MSVAudioConfiguration 对象
 */
+ (instancetype)defaultConfiguration;

/**
 * @brief 验证对象是否有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
