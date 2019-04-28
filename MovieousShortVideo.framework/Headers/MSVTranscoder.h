//
//  MSVTranscoder.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/1/28.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import "MSVTypeDefines.h"
#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Transcoder class used to transcode
 */
@interface MSVTranscoder : NSObject

/**
 * The URL of the media source file you would like to transcode.
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * The running status of the transcoder.
 */
@property (nonatomic, assign, readonly) BOOL running;

/**
 * The time range you would like to trim from the source media.
 * The default is kMovieousTimeRangeDefault
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * Whether to export the video to the album at the same time.
 * the default is NO.
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * The file type of the video export.
 * the default is MSVFileTypeMPEG4(.mp4).
 */
@property (nonatomic, assign) MSVFileType outputFileType;

/**
 * The path of the video export only supports the local file address.
 * The default is the automatically generated address.
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * The average bitrate of the output video.
 * The default is the automatically generated bitrate by encoder.
 */
@property (assign, nonatomic) NSUInteger averageBitrate;

/**
 * Whether set up the transmission in the network environment.
 * the default is YES.
 */
@property (assign, nonatomic) BOOL shouldOptimizeForNetworkUse;

/**
 * Export progress callback.
 */
@property (nonatomic, copy, nullable) void(^progressHandler)(float progress);

/**
 * Export failure callback.
 */
@property (nonatomic, copy, nullable) void(^failureHandler)(NSError *error);

/**
 * Export successful callback.
 */
@property (nonatomic, copy, nullable) void(^completionHandler)(NSURL *URL);

/**
 * Instantiate a MSVTranscoder object with video URL.
 *
 * @return The instantiated MSVTranscoder object
 */
+ (instancetype)transcoderWithURL:(NSURL *)URL;

/**
 * Initiate a MSVTranscoder object with video URL.
 *
 * @return The initiated MSVTranscoder object
 */
- (instancetype)initWithURL:(NSURL *)URL;

/**
 * Start exporting tasks.
 */
- (void)startExport;

/**
 * Cancel the export task.
 */
- (void)cancelExport;

@end

NS_ASSUME_NONNULL_END
