//
//  MSVExporter.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/18.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVDraft.h"
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

@interface MSVExporter : NSObject

/**
 * 草稿对象。
 */
@property (nonatomic, strong, nullable) MSVDraft *draft;

/**
 * 导出任务是否正在运行.
 */
@property (nonatomic, assign) BOOL running;

/**
 * 是否同时将视频导出到相册。
 * 默认为 NO。
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * 视频导出的文件类型。
 * 默认为 MSVFileTypeMPEG4(.mp4)。
 */
@property (assign, nonatomic) MSVFileType outputFileType;

/**
 * 视频导出的路径，只支持本地文件地址。
 * 默认为自动生成的地址。
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * The 视频的码率。
 * The 默认为原视频的码率。
 */
@property (assign, nonatomic) NSUInteger videoBitrate;

/**
 * 导出视频的声道数量。
 * 默认使用原音频的声道数量。
 */
@property (nonatomic, assign) UInt32 numberOfChannels;

/**
 * The audio sample rate of the video that exported.
 * The default is the original audio sample rate.
 */
@property (nonatomic, assign) Float64 sampleRate;

/**
 * 导出视频的音频采样率。
 * 默认使用原音频的采样率。
 */
@property (nonatomic, assign) Float64 audioBitRate;

/**
 * 导出视频的音频码率。
 * 默认使用原视频的码率。
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

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * 使用 draft 初始化导出对象。
 * 
 * @param draft 需要导出的草稿对象。
 * @param outError 如果发生错误，返回发生的具体错误。
 * 
 * @return 如果初始化成功返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft;

/**
 * 使用 draft 创建导出对象。
 * 
 * @param draft 需要导出的草稿对象。
 * @param outError 如果发生错误，返回发生的具体错误。
 * 
 * @return 如果创建成功返回初始化后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)exporterWithDraft:(MSVDraft *_Nullable)draft;

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
