//
//  MSVRecorder.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/26.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>
#import "MSVRecorderAudioConfiguration.h"
#import "MSVRecorderVideoConfiguration.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 开始采集完成回调。
 *
 * @param audioGranted 是否获取到音频采集权限。
 * @param audioError 音频组件初始化错误返回。
 * @param videoGranted 是否获取到视频采集权限。
 * @param videoError 视频组件初始化错误返回。
 */
typedef void(^MSVStartCapturingCompletionHandler)(BOOL audioGranted, NSError *_Nullable audioError, BOOL videoGranted, NSError *_Nullable videoError);

/**
 * 完成录制操作完成回调。
 *
 * @param path 录制过程中生成的视频文件地址。
 * @param error 如果发生错误返回错误对象。
 */
typedef void(^MSVFinishRecordingCompletionHandler)(NSString *_Nullable path, NSError *_Nullable error);

@class MSVRecorder;

/**
 * 录制器代理接口。
 */
@protocol MSVRecorderDelegate <NSObject>

@optional
/**
 * 当录制器发生错误时调用。
 *
 * @param recorder 产生事件的录制器对象。
 * @param error 产生的具体错误。
 */
- (void)recorder:(MSVRecorder *)recorder didErrorOccurred:(NSError *)error;

/**
 * 当前录制片段的时长发生更新的回调。
 *
 * @param recorder 产生事件的录制器对象。
 * @param duration 当前片段的时长。
 */
- (void)recorder:(MSVRecorder *)recorder durationDidUpdated:(MovieousTime)duration;

@end

/**
 * 录制器。
 */
@interface MSVRecorder : NSObject

/**
 * 视频参数配置对象。
 */
@property (nonatomic, strong) MSVRecorderVideoConfiguration *videoConfiguration;

/**
 * 音频参数配置对象。
 */
@property (nonatomic, strong) MSVRecorderAudioConfiguration *audioConfiguration;

/**
 * 已经录制的时长。
 */
@property (nonatomic, assign, readonly) MovieousTime duration;

/**
 * 预览视图。
 */
@property (nonatomic, strong, readonly) UIView *previewView;

/**
 * 代理对象，用于接收事件回调。
 */
@property (nonatomic, weak, nullable) id<MSVRecorderDelegate> delegate;

/**
 * 代理方法回调使用的队列，如果未指定将在主线程回调。
 */
@property (nonatomic, strong, null_resettable) dispatch_queue_t delegateQueue;

/**
 * 当前是否正在采集。
 */
@property (nonatomic, assign, readonly) BOOL capturing;

/**
 * 当前是否处于正在录制的状态。
 */
@property (nonatomic, assign, readonly) BOOL recording;

/**
 * 当前是否处于正在停止的状态。
 */
@property (nonatomic, assign, readonly) BOOL finishing;

/**
 * 录制文件地址，如果不赋值将使用内部自动生成的地址。
 */
@property (nonatomic, strong) NSString *path;

/**
 * 录制的文件类型。
 */
@property (nonatomic, assign) MSVFileType fileType;

/**
 * 待录制的视图。
 */
@property (nonatomic, strong) UIView *viewForRecording;

/**
 * 当前摄像头的手电筒模式。
 */
@property (nonatomic, assign, readonly) AVCaptureTorchMode torchMode;

/**
 * 当前摄像头的闪光灯模式。
 */
@property (nonatomic, assign, readonly) AVCaptureFlashMode flashMode;

/**
 * 指示当前摄像头支持的帧率范围。
 * videoSupportedFrameRateRanges 是一个 AVFrameRateRange 的数组，指示支持的帧率范围。
 */
@property(nonatomic, strong, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

/**
 * 当前摄像头的每秒最小帧率。
 */
@property (nonatomic, assign, readonly) Float64 minFrameRate;

/**
 * 当前摄像头的每秒最大帧率。
 */
@property (nonatomic, assign, readonly) Float64 maxFrameRate;

/**
 * 当前摄像头的位置。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition devicePosition;

/**
 * 最大可应用的缩放比例。
 */
@property (nonatomic, assign, readonly) CGFloat videoMaxZoomFactor;

/**
 * 当前的缩放比例。
 */
@property (nonatomic, assign, readonly) CGFloat videoZoomFactor;

/**
 * 当前是否开启持续自动对焦的配置。。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 *
 * @discussion 开启持续自动对焦即设备在需要的时候自动调节对焦参考点。
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoFocusEnable;

/**
 * 指示当前的对焦参考点。
 *
 * @discussion 此属性的值是一个决定对焦参考点的 CGPoint，(0,0) 点代表图片的左上角，(1,1)点代表图片的右下角。默认值为 (0.5,0.5)。
 */
@property (nonatomic, assign, readonly) CGPoint focusPointOfInterest;

/**
 * 当前的是否开启持续自动曝光状态
 *
 * @discussion 开启持续自动曝光即设备在需要的时候自动调节曝光参考点。
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoExposureEnable;

/*!
 * 指示当前的曝光参考点。
 *
 * @discussion 此属性的值是一个决定曝光参考点的 CGPoint，(0,0) 点代表图片的左上角，(1,1)点代表图片的右下角。默认值为 (0.5,0.5)。
 */
@property (nonatomic, assign, readonly) CGPoint exposurePointOfInterest;

/**
 * 以分贝为单位的当前音频采集设备采集到的音频平均能量级别。
 */
@property (nonatomic, readonly) float averagePowerLevel;

/**
 * 实例化一个 MSVRecorder 对象
 *
 * @param audioConfiguration 音频配置对象，传入 nil 使用默认配置。
 * @param videoConfiguration 视频配置对象，传入 nil 使用默认配置。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 实例化成功返回初始化后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)recorderWithAudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 初始化一个 MSVRecorder 对象
 *
 * @param audioConfiguration 音频配置对象，传入 nil 使用默认配置。
 * @param videoConfiguration 视频配置对象，传入 nil 使用默认配置。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 初始化成功返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithAudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 开始采集音视频，调用此方法将请求音视频的使用权限（如果指定音视频数据源为摄像头或麦克风的话）。
 *
 * @param completionHandler 调用完成的回调。
 */
- (void)startCapturingWithCompletion:(MSVStartCapturingCompletionHandler)completionHandler;

/**
 * 停止采集。
 */
- (void)stopCapturing;

/**
 * 使用默认配置开始录制。
 *
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)startRecordingWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * 完成录制。
 *
 * @param completionHandler 停止成功的回调。
 */
- (void)finishRecordingWithCompletionHandler:(MSVFinishRecordingCompletionHandler _Nullable)completionHandler;

/**
 * 取消当前录制。
 */
- (void)cancelRecording;

/**
 * 切换摄像头。
 */
- (void)switchCamera;

/**
 * 外部写入视频数据接口，使用该接口导入视频数据请保证配置 videoConfiguration.source = MSVVideoSourceExtern。
 *
 * @param videoData 待写入的视频数据。
 * @param presentationTime 视频数据的显示时间戳。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeVideoData:(CVPixelBufferRef)videoData presentationTime:(MovieousTime)presentationTime error:(NSError *_Nullable *_Nullable)outError;

/**
 * 外部写入视频数据接口，使用该接口导入视频数据请保证配置 videoConfiguration.source = MSVVideoSourceExtern。
 *
 * @param videoData 待写入的视频数据。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeVideoData:(CMSampleBufferRef)videoData error:(NSError *_Nullable *_Nullable)outError;

/**
 * 外部写入音频数据接口，使用该接口导入视频数据请保证配置 audioConfiguration.source = MSVAudioSourceExtern。
 *
 * @param audioData 待写入的视频数据。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeAudioData:(CMSampleBufferRef)audioData error:(NSError *_Nullable *_Nullable)outError;

/**
 * 获取视频快照。
 *
 * @param completionHandler 获取快照完成回调。
 */
- (void)snapshotWithCompletion:(MovieousSnapshotCompletionHandler)completionHandler;

@end

NS_ASSUME_NONNULL_END
