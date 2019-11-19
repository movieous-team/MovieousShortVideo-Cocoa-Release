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
#import <MovieousCaptureBase/MovieousCaptureBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Audio configuration class
 */
@interface MSVRecorderAudioConfiguration : NSObject
<
MovieousMicrophoneConfiguration
>

/**
 * Audio input source.
 * The default is MSVAudioSourceMicrophone.
 */
@property (nonatomic, assign) MSVAudioSource source;

#pragma mark - microphone configurations

/**
 * Mute sound while recording, if you want to record a movie with no sound, you can specify source property in audioConfiguration to MSVAudioSourceNone.
 * The default is NO.
 */
@property (nonatomic, assign) BOOL mute;

#pragma mark - encoder configurations

/**
 * Audio encoding rate bitRate.
 * The default is 128 * 1024.
 */
@property (assign, nonatomic) UInt32 bitrate;

/**
 * Create a default configuration of the MSVAudioConfiguration instance.
 *
 * @return Create a default object of MSVAudioConfiguration.
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
