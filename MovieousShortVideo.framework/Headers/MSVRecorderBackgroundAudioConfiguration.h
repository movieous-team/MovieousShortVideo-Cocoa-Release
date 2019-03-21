//
//  MSVRecorderBackgroundAudioConfiguration.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/17.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief Background audio configuration class
 */
@interface MSVRecorderBackgroundAudioConfiguration : NSObject

/**
 * @brief Background audio source file URL
 * @warning Only local file URL is supported
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief The time range to use of the audio source
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief Volume of background audio, the default is the preferredVolume in the audio file
 */
@property (nonatomic, assign) float volume;

/**
 * @brief NO Loop audio play untill recording finishes
 */
@property (nonatomic, assign) BOOL loop;

/**
 * @brief Create a new MSVRecorderBackgroundAudioConfiguration instance
 * @param URL Audio source file URL, only local file is supported
 * @param outError Return error if any
 * @return Created instance if success or else nil
 */
+ (instancetype)backgroundAudioConfigurationWithURL:(NSURL *)URL error:(NSError **)outError;

@end
