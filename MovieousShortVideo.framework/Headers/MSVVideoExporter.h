//
//  MSVVideoExporter.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/18.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVDraft.h"
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface MSVVideoExporter : NSObject

/**
 * @brief Draft object
 */
@property (nonatomic, strong, readonly, nullable) MSVDraft *draft;

/**
 * @brief Whether the export task is running
 */
@property (nonatomic, assign) BOOL running;

/**
 * @brief Whether to export the video to the album at the same time, the default is NO
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * @brief The file type of the video export, the default is MSVFileTypeMPEG4(.mp4)
 */
@property (assign, nonatomic) MSVFileType outputFileType;

/**
 * @brief The path of the video export only supports the local file address. The default is the automatically generated address.
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * @brief The bitrate of the video, the default is the bitrate of the original video.
 */
@property (assign, nonatomic) NSUInteger videoBitrate;

/**
 * @brief The number of channels of the exported video, the default number of channels use the original audio
 */
@property (nonatomic, assign) UInt32 numberOfChannels;

/**
 * @brief The audio sample rate of the video that exported, using the original audio sample rate by default.
 */
@property (nonatomic, assign) Float64 sampleRate;

/**
 * @brief The audio bitrate of the video that exported, using the original video's bitrate by default.
 */
@property (nonatomic, assign) Float64 audioBitRate;

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
 * @brief Init and new are both not available, use other initialization method instead.
 */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * @brief Export objects with initialization draft
 * @param draft Draft object that needs to be exported
 * @param outError If an error occurs, return the error that occurred
 * @return It returns the initialized object if the initial succeeded, otherwise returns nil
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft error:(NSError * _Nullable * _Nullable)outError;

/**
 * @brief Update draft
 * @param draft New draft
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES if update successfully otherwise returns NO
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError * _Nullable * _Nullable)outError;

/**
 * @brief Start exporting tasks
 */
- (void)startExport;

/**
 * @brief Cancel the export task
 */
- (void)cancelExport;

NS_ASSUME_NONNULL_END

@end
