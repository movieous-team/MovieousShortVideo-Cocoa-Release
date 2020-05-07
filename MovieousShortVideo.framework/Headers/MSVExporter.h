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

/**
 * 导出器格式参数集。
 */
@protocol MSVExporterFormatParameters <NSObject>

@end

/**
 * 音视频导出器格式参数集。
 */
@interface MSVExporterAVFormatParameters : NSObject
<
MSVExporterFormatParameters
>

/**
 * 视频的码率。
 * 默认为原视频的码率，对 MSVFileTypeAppleM4A 类型导出对象无效。
 */
@property (nonatomic, assign) NSUInteger videoBitrate;

/**
 * 视频的最大关键帧间距，也就是最大的 GOP(Group Of Pictures) 大小，以帧为单位，该值为 0 代表编码器自主选择如何插入关键帧，该值为 1 代表视频所有帧都为关键帧。
 * 默认为 0。
 */
@property (nonatomic, assign) NSUInteger maxKeyFrameInterval;

/**
 * 导出视频的声道数量。
 * 默认使用原音频的声道数量。
 */
@property (nonatomic, assign) UInt32 numberOfChannels;

/**
 * 导出的视频中音频的采样率。
 * 默认采样率是音频的原始采样率。
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
 * 生成一个默认的音视频格式参数集对象。
 */
+ (instancetype)defaultFormatParameters;

@end

/**
 * 导出器对象。
 */
@interface MSVExporter : NSObject

/**
 * 草稿对象。
 */
@property (nonatomic, strong, nullable) MSVDraft *draft;

/**
 * 是否在导出时将视频部分倒放。
 */
@property (nonatomic, assign) BOOL reverseVideo;

/**
 * 导出任务是否正在运行。
 */
@property (nonatomic, assign, readonly) BOOL running;

/**
 * 导出进度。
 */
@property (nonatomic, assign, readonly) float progress;

/**
 * 视频导出的文件类型。
 * 默认为 MSVFileTypeMPEG4(.mp4)。
 */
@property (assign, nonatomic) MSVFileType outputFileType;

/**
 * 视频导出的路径，只支持本地文件地址。
 * 默认为自动生成的地址。
 */
@property (strong, nonatomic, nullable) NSString *outputPath;

/**
 * 是否同时将视频导出到相册。
 * 默认为 NO。
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * 格式参数集对象。
 * 默认为 [MSVExporterAVFormatParameters defaultFormatParameters]
 */
@property (nonatomic, strong) id<MSVExporterFormatParameters> formatParameters;

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
@property (nonatomic, copy, nullable) void(^completionHandler)(NSString *path);

/**
 * `-Init` 和 `-new` 方法都不可用，请使用其他方法来初始化
 */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * 使用 draft 初始化导出对象。
 *
 * @param draft 需要导出的草稿对象。
 *
 * @return 如果初始化成功返回初始化后的对象，否则返回 nil。
 */
- (instancetype)initWithDraft:(MSVDraft *_Nullable)draft;

/**
 * 使用 draft 创建导出对象。
 * 
 * @param draft 需要导出的草稿对象。
 *
 * @return 如果创建成功返回初始化后的对象，否则返回 nil。
 */
+ (instancetype)exporterWithDraft:(MSVDraft *_Nullable)draft;

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
