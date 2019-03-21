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
 * @brief Audio configuration class
 */
@interface MSVRecorderAudioConfiguration : NSObject
<
MovieousMicrophoneConfiguration
>

/**
 * @brief Audio input source, the default is MSVAudioSourceMicrophone
 */
@property (nonatomic, assign) MSVAudioSource source;

#pragma mark - microphone configurations
/*!
 * Whether to allow to compromise some parameters which are not supported by the current device to ensure component initialization's success. The default is YES
 */
@property (nonatomic, assign) BOOL compromise;

#pragma mark - encoder configurations
/**
 * @brief Audio sample rate sampleRate The default is MSVAudioSampleRate_44100Hz
 */
@property (assign, nonatomic) MSVAudioSampleRate sampleRate;

/**
 * @brief Audio encoding rate bitRate The default is MSVAudioBitRate_128Kbps
 */
@property (assign, nonatomic) MSVAudioBitRate bitRate;

/**
 * @brief Create a default configuration of the MSVAudioConfiguration instance
 * @return Create a default object of MSVAudioConfiguration
 */
+ (instancetype)defaultConfiguration;

/**
 * @brief Verify the object is valid or not
 * @param outError If an error occurs, return the error that occurred
 * @return Valid operation return YES, invalid operation return NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
