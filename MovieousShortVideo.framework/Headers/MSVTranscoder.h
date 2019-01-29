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

@interface MSVTranscoder : NSObject

@property (nonatomic, strong, readonly) NSURL *URL;

@property (nonatomic, assign, readonly) BOOL running;


@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief Whether to export the video to the album at the same time, the default is NO
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * @brief The file type of the video export, the default is MSVFileTypeMPEG4(.mp4)
 */
@property (nonatomic, assign) MSVFileType outputFileType;

/**
 * @brief The path of the video export only supports the local file address. The default is the automatically generated address.
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * @brief The average bitrate of the output video.
 */
@property (assign, nonatomic) NSUInteger averageBitrate;

/**
 * @brief Whether set up the transmission in the network environment, the default is YES
 */
@property (assign, nonatomic) BOOL shouldOptimizeForNetworkUse;

/**
 * @brief Export progress callback
 */
@property (nonatomic, copy, nullable) void(^progressHandler)(float progress);

/**
 * @brief Export failure callback
 */
@property (nonatomic, copy, nullable) void(^failureHandler)(NSError *error);

/**
 * @brief Export successful callback
 */
@property (nonatomic, copy, nullable) void(^completionHandler)(NSURL *URL);

/**
 * @brief instantiate a MSVTranscoder object with video URL
 */
+ (instancetype)transcoderWithURL:(NSURL *)URL;

/**
 * @brief init a MSVTranscoder object with video URL
 */
- (instancetype)initWithURL:(NSURL *)URL;

/**
 * @brief Start exporting tasks
 */
- (void)startExport;

/**
 * @brief Cancel the export task
 */
- (void)cancelExport;

@end

NS_ASSUME_NONNULL_END
