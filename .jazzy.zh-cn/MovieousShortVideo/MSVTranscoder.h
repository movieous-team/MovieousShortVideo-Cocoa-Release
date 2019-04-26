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
 * 转码器类。
 */
@interface MSVTranscoder : NSObject

/**
 * 转码源文件地址。
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * 转码器当前是否在运行中。
 */
@property (nonatomic, assign, readonly) BOOL running;

/**
 * 源文件中你希望裁剪的时间区间。
 * 默认为 kMovieousTimeRangeDefault
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * 是否同时将视频导出到相册。
 * 默认为 NO。
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * 视频导出的文件类型。
 * 默认为 MSVFileTypeMPEG4(.mp4)。
 */
@property (nonatomic, assign) MSVFileType outputFileType;

/**
 * 视频导出的路径，只支持本地文件地址。
 * 默认为自动生成的地址。
 * 
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * 视频的码率。
 * 默认为原视频的码率。
 */
@property (assign, nonatomic) NSUInteger averageBitrate;

/**
 * 是否针对网络环境优化编码的文件。
 * 默认为 YES.
 */
@property (assign, nonatomic) BOOL shouldOptimizeForNetworkUse;

/**
 * Export 导出进度回调。
 */
@property (nonatomic, copy, nullable) void(^progressHandler)(float progress);

/**
 * Export 导出失败回调。
 */
@property (nonatomic, copy, nullable) void(^failureHandler)(NSError *error);

/**
 * Export 导出成功回调。
 */
@property (nonatomic, copy, nullable) void(^completionHandler)(NSURL *URL);

/**
 * 使用 URL 来创建一个 MSVTranscoder 对象。
 *
 * @return 创建完成的 MSVTranscoder 对象。
 */
+ (instancetype)transcoderWithURL:(NSURL *)URL;

/**
 * 使用 URL 来初始化一个 MSVTranscoder 对象。
 *
 * @return 初始化完成的 MSVTranscoder 对象。
 */
- (instancetype)initWithURL:(NSURL *)URL;

/**
 * 开始导出任务。
 */
- (void)startExport;

/**
 * 取消导出任务。
 */
- (void)cancelExport;

@end

NS_ASSUME_NONNULL_END
