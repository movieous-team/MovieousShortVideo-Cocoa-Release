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

NS_ASSUME_NONNULL_BEGIN

/**
 * 音频配置类
 */
@interface MSVRecorderAudioConfiguration : NSObject
<
MovieousMicrophoneConfiguration
>

/**
 * 音频输入源类型。
 * 默认为 MSVAudioSourceMicrophone。
 */
@property (nonatomic, assign) MSVAudioSource source;

#pragma mark - microphone configurations

/**
 * 录制时是否静音。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL mute;

#pragma mark - encoder configurations

/**
 * 音频编码码率。
 * 默认为 128 * 1024。
 */
@property (assign, nonatomic) UInt32 bitrate;

/**
 * 创建一个默认的 MSVAudioConfiguration 对象。
 *
 * @return 创建完成的对象。
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
