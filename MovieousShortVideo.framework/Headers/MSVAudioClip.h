//
//  MSVAudioClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/17.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import "MSVClip.h"

/**
 * @brief Audio clip
 */
@interface MSVAudioClip<MSVClip> : NSObject

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief The URL of the audio clip supports local files only
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief The underlying AVAsset object can get media parameters such as duration
 */
@property (nonatomic, strong, readonly) AVAsset *asset;

/**
 * @brief The time when the audio clip starts in the main track,the actual duration of the audio clip in the main track is timeRange.duration / speed
 */
@property (nonatomic, assign) NSTimeInterval startTimeAtMainTrack;

/**
 * @brief Intercepting the time range used in the audio clip, this time range refers to the time range without the fast and slow processing, please be note: timeRange.startTime + timeRange.duration <= total media duration
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief This time range refers to the time range without the fast and slow processing and reverses processing,Also, if timeRange.startTime + timeRange.duration > total media duration,  the excess part will be ignored.
 * Generally, the following configuration can be performed：
 * Extremely fast：2.0
 * Fast：1.5
 * Standard：1.0
 * Slow：0.75
 * Extremely slow：0.5
 */
@property (nonatomic, assign) float speed;

/**
 * @brief The volume of the audio clip defaults to the value comes with media
 */
@property (nonatomic, assign) float volume;

/**
 * @brief Create audio clips through using media addresses
 * @param URL The address of the audio clip supports local files only
 * @param outError If an error occurs, return the error that occurred
 * @return The initialized object will be returned if creation is successfully, otherwise returns nil
 */
+ (instancetype)audioClipWithURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief Use media address to initialize the audio clip
 * @param URL The address of the audio clip supports local files only
 * @param outError If an error occurs, return the error that occurred
 * @return The initialized object will be returned if initialization is successfully, otherwise returns nil
 */
- (instancetype)initWithURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief Verify that the draft is valid or not
 * @param outError If an error occurs, return the error that occurred
 * @return Valid operation return YES, invalid operation return NO
 */
- (BOOL)validateWithError:(NSError **)outError;

/**
 * @brief Refresh inner Asset objects，need to be called when received `AVAudioSessionMediaServicesWereResetNotification` notification
 */
- (void)refreshAsset;

@end
