//
//  MSVAudioClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/17.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import "MSVClip.h"

/**
 * @brief 音频片段
 */
@interface MSVAudioClip<MSVClip> : NSObject

/**
 * @brief 用户自定义 ID 字段，业务使用用于区分对象
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief 音频片段的 URL，只支持本地文件
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief 底层使用的 AVAsset 对象，可以获取 duration 等媒体参数
 */
@property (nonatomic, strong, readonly) AVAsset *asset;

/**
 * @brief 音频片段在主轨中开始的时间，音频片段在主轨中实际的时长为 timeRange.duration / speed
 */
@property (nonatomic, assign) NSTimeInterval startTimeAtMainTrack;

/**
 * @brief 在音频片段当中截取使用的时间范围，这个时间范围是指没有经过快慢速处理之前的时间范围，请注意，timeRange.startTime + timeRange.duration <= 媒体总时长
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief 音频片段的速度，此参数和 timeRangeAtMainTrack.duration 互相影响，具体的运算关系为 speed = timeRange.duration / timeRangeAtMainTrack.duration
 * 一般来说可以进行如下配置：
 * 极快：2.0
 * 快：1.5
 * 正常：1.0
 * 慢：0.75
 * 极慢：0.5
 */
@property (nonatomic, assign) float speed;

/**
 * @brief 音频片段的音量，默认为媒体自带的
 */
@property (nonatomic, assign) float volume;

/**
 * @brief 使用媒体地址来创建音频片段
 * @param URL 音频片段的地址，只支持本地文件
 * @param outError 如果发生错误，返回发生的错误
 * @return 创建成功返回初始化后的对象，否则返回 nil
 */
+ (instancetype)audioClipWithURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 使用媒体地址来初始化音频片段
 * @param URL 音频片段的地址，只支持本地文件
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功返回初始化后的对象，否则返回 nil
 */
- (instancetype)initWithURL:(NSURL *)URL error:(NSError **)outError;

- (void)refreshAsset;

/**
 * @brief 验证草稿是否有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
