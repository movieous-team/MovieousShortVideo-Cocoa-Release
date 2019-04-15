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

#pragma mark - encoder configurations

/**
 * @brief Audio encoding rate bitRate The default is 128 * 1024
 */
@property (assign, nonatomic) UInt32 bitrate;

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
