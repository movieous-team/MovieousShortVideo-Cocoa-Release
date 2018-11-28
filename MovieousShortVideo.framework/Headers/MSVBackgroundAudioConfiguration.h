//
//  MSVBackgroundAudioConfiguration.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/17.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 背景音效的配置类
 */
@interface MSVBackgroundAudioConfiguration : NSObject

/**
 * @brief 背景音效源文件路径
 * @warning 当前仅支持本地文件
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief URL 指向的音频当中截取使用的区间，默认全部使用
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief 背景音效的音量，默认为音频文件中自带的 preferredVolume
 */
@property (nonatomic, assign) float volume;

/**
 * @brief 是否循环播放背景音效直到录制结束，默认为 NO
 */
@property (nonatomic, assign) BOOL loop;

/**
 * @brief 初始化背景音效对象
 * @param URL 背景音效源文件路径，当前仅支持本地文件
 * @param outError 如发生错误，返回具体的错误对象
 * @return 生成成功返回初始化的对象，发生错误返回 nil
 */
+ (instancetype)backgroundAudioConfigurationWithURL:(NSURL *)URL error:(NSError **)outError;

@end
