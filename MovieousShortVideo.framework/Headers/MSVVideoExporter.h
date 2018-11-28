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
 * @brief 草稿对象
 */
@property (nonatomic, strong, readonly, nullable) MSVDraft *draft;

/**
 * @brief 导出任务是否正在运行
 */
@property (nonatomic, assign) BOOL running;

/**
 * @brief 是否同时将视频导出到相册，默认为 NO
 */
@property (assign, nonatomic) BOOL saveToPhotosAlbum;

/**
 * @brief 视频导出的文件类型，默认为 MSVFileTypeMPEG4(.mp4)
 */
@property (assign, nonatomic) MSVFileType outputFileType;

/**
 * @brief 视频导出的路径，只支持本地文件地址，默认为自动生成的地址
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * @brief 视频的码率，默认为原视频的码率
 */
@property (assign, nonatomic) NSUInteger videoBitrate;

/**
 * @brief 导出视频的声道数量，默认使用原音频的声道数量
 */
@property (nonatomic, assign) UInt32 numberOfChannels;

/**
 * @brief 导出视频的音频采样率，默认使用原音频的采样率
 */
@property (nonatomic, assign) Float64 sampleRate;

/**
 * @brief 导出视频的音频码率，默认使用原视频的码率
 */
@property (nonatomic, assign) Float64 audioBitRate;

/**
 * @brief 是否设置便于网络环境下的传输，默认为 YES
 */
@property (assign, nonatomic) BOOL shouldOptimizeForNetworkUse;

/**
 * @brief 导出进度回调
 */
@property (nonatomic, copy, nullable) void(^progressHandler)(float progress);

/**
 * @brief 导出失败回调
 */
@property (nonatomic, copy, nullable) void(^failureHandler)(NSError *error);

/**
 * @brief 导出成功回调
 */
@property (nonatomic, copy, nullable) void(^completionHandler)(NSURL *URL);

/**
 * @brief 使用 draft 初始化导出对象
 * @param draft 需要导出的草稿对象
 * @param outError 如果发生错误，返回发生的具体错误
 * @return 如果初始化成功返回初始化后的对象，否则返回 nil
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft error:(NSError * _Nullable * _Nullable)outError;

/**
 * @brief 更新草稿
 * @param draft 新草稿
 * @param outError 如果发生错误，返回发生的具体错误
 * @return 更新成功返回 YES，否则返回 NO
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError * _Nullable * _Nullable)outError;

/**
 * @brief 开始导出任务
 */
- (void)startExport;

/**
 * @brief 取消导出任务
 */
- (void)cancelExport;

NS_ASSUME_NONNULL_END

@end
