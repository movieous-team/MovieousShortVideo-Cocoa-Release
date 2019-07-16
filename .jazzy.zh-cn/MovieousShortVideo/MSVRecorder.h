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
#import "MSVClipConfiguration.h"
#import "MSVClip.h"
#import "MSVMainTrackClip.h"
#import "MSVDraft.h"
#import "MSVRecorderBackgroundAudioConfiguration.h"

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
 * @param clip 录制过程中生成的 MSVMainTrackClip 对象，如果录制器已经结束了，此参数将返回上一个生成的 MSVMainTrackClip 对象。
 * @param error 如果发生错误返回错误对象。
 */
typedef void(^MSVFinishRecordingWithCompletionHandler)(MSVMainTrackClip *_Nullable clip, NSError *_Nullable error);

@class MSVRecorder;

/**
 * 录制器代理接口。
 */
@protocol MSVRecorderDelegate <NSObject>

@optional
/**
 * 当用户点击预览界面对焦时回调。
 * 
 * @param recorder 产生事件的录制器对象。
 * @param point 用户点击的位置。
 */
- (void)recorder:(MSVRecorder *)recorder didErrorOccurred:(NSError *)error;

/**
 * 当用户点击屏幕对焦成功时调用。
 *
 * @param recorder 产生事件的录制器对象。
 * @param point 用户点击的位置。
 */
- (void)recorder:(MSVRecorder *)recorder didFocusAtPoint:(CGPoint)point;

/**
 * 录制器播放背景音乐时发生错误。
 * 
 * @param recorder 产生事件的录制器对象。
 * @param error 产生的具体错误。
 */
- (void)recorder:(MSVRecorder *)recorder didPlayBackgroundAudioError:(NSError *)error;

/**
 * 当前录制片段的时长发生更新的回调，调用者可以在此回调当中更新 UI 反馈录制进度。
 * 
 * @param recorder 产生事件的录制器对象。
 * @param currentClipDuration 当前片段的时长。
 */
- (void)recorder:(MSVRecorder *)recorder currentClipDurationDidUpdated:(NSTimeInterval)currentClipDuration;

@end

/**
 * 录制器。
 */
@interface MSVRecorder : NSObject

/**
 * 自动生成的草稿对象，可以通过此属性获取草稿对象用于编辑或导出。
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * 视频参数配置对象。
 *
 * @warning 请不要修改获取到的 videoConfiguration 对象，否则会出现未定义的错误，更新参数请使用相关运行时属性更新接口或销毁当前 Recorder 重新生成。
 */
@property (nonatomic, strong, readonly) MSVRecorderVideoConfiguration *videoConfiguration;

/**
 * 音频参数配置对象。
 *
 * @warning 请不要修改获取到的 videoConfiguration 对象，否则会出现未定义的错误，更新参数请使用相关运行时属性更新接口或销毁当前 Recorder 重新生成。
 */
@property (nonatomic, strong, readonly) MSVRecorderAudioConfiguration *audioConfiguration;

/**
 * 当前片段已经录制的时间长度。
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentClipDuration;

/**
 * 所有已经保存的片段的时间长度(不考虑 speed 参数)。
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsOriginalDuration;

/**
 * 所有已经保存的片段的时间长度(考虑 speed 参数)。
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsRealDuration;

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
 * 采集时应用的特效组。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, copy) NSArray<id<MovieousCaptureEffect>> *captureEffects;

/**
 * 当 size（编码时的视频分辨率） 和 preview 的尺寸比例不一致时使用的填充模式。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * 当前是否正在采集。
 */
@property (nonatomic, assign, readonly) BOOL capturing;

/**
 * 当前是否处于正在录制的状态。
 */
@property (nonatomic, assign, readonly) BOOL recording;

/**
 * 是否对前置摄像头预览进行镜像处理。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/**
 * 是否对后置摄像头预览进行镜像处理。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/**
 * 是否对前置摄像头编码的视频进行镜像处理。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/**
 * 是否对后置摄像头编码的视频进行镜像处理。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * 切换摄像头时是否进行模糊化过渡
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL blurSwitch;

/**
 * 是否开启点击屏幕来设置对焦和曝光参考点。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL touchToFocusExposureEnabled;

/**
 * 是否开启内置的对焦视图。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL innerFocusViewEnabled;

/**
 * 当前摄像头的手电筒模式。
 */
@property (nonatomic, assign, readonly) AVCaptureTorchMode torchMode;

/**
 * 指定期望的摄像头手电筒模式，需要注意的是 preferredTorchMode 的值不一定能够被成功应用，实际的手电筒模式可以通过 MSVRecorder.torchMode 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

/**
 * 当前摄像头的闪光灯模式。
 */
@property (nonatomic, assign, readonly) AVCaptureFlashMode flashMode;

/**
 * 指定期望的摄像头闪光灯模式，需要注意的是 preferredFlashMode 的值不一定能够被成功应用，实际的手电筒模式可以通过 MSVRecorder.flashMode 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
+@property (nonatomic, assign) AVCaptureFlashMode preferredFlashMode;

/**
 * 指示当前摄像头支持的帧率范围。
 * videoSupportedFrameRateRanges 是一个 AVFrameRateRange 的数组，指示支持的帧率范围。
 */
@property(nonatomic, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

/**
 * 当前摄像头的每秒最小帧率。
 */
@property (nonatomic, assign, readonly) Float64 minFrameRate;

/**
 * 指定期望的最小采集帧率，需要注意的是 preferredMinFrameRate 的值不一定能够被成功应用，实际的最小采集帧率可以通过 MSVRecorder.minFrameRate 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) Float64 preferredMinFrameRate;

/**
 * 当前摄像头的每秒最大帧率。
 */
@property (nonatomic, assign, readonly) Float64 maxFrameRate;

/**
 * 指定期望的最大采集帧率，需要注意的是 preferredMaxFrameRate 的值不一定能够被成功应用，实际的最大采集帧率可以通过 MSVRecorder.maxFrameRate 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

/**
 * 当前摄像头的预设分辨率。
 */
@property (nonatomic, strong, readonly) AVCaptureSessionPreset sessionPreset;

/**
 * 指定期望的采集预设分辨率，需要注意的是 preferredSessionPreset 的值不一定能够被成功应用，实际的采集预设分辨率可以通过 MSVRecorder.sessionPreset 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureSessionPreset preferredSessionPreset;

/**
 * 当前摄像头的位置。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition devicePosition;

/**
 * 指定期望的摄像头位置，需要注意的是 preferredDevicePosition 的值不一定能够被成功应用，实际的摄像头位置可以通过 MSVRecorder.devicePosition 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

/**
 * 当前摄像头的方向。
 */
@property (nonatomic, assign, readonly) AVCaptureVideoOrientation videoOrientation;

/**
 * 指定期望的摄像头方向，需要注意的是 preferredVideoOrientation 的值不一定能够被成功应用，实际的摄像头方向可以通过 MSVRecorder.videoOrientation 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

/**
 * 最大可应用的缩放比例。
 */
@property (nonatomic, assign, readonly) CGFloat videoMaxZoomFactor;

/**
 * 当前的缩放比例。
 */
@property (nonatomic, assign, readonly) CGFloat videoZoomFactor;

/**
 * 指定期望的视频缩放比例，需要注意的是 preferredVideoZoomFactor 的值不一定能够被成功应用，实际的视频缩放比例可以通过 MSVRecorder.videoZoomFactor 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

/**
 * 当前是否开启持续自动对焦的配置。。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 *
 * @discussion 开启持续自动对焦即设备在需要的时候自动调节对焦参考点。
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoFocusEnable;

/**
 * 指定期望是否开启持续自动对焦，需要注意的是 preferredContinuousAutoFocusEnable 的值不一定能够被成功应用，实际是否开启持续自动对焦可以通过 MSVRecorder.continuousAutoFocusEnable 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;

/**
 * 指示当前的对焦参考点。
 *
 * @discussion 此属性的值是一个决定对焦参考点的 CGPoint，(0,0) 点代表图片的左上角，(1,1)点代表图片的右下角。默认值为 (0.5,0.5)。
 */
@property (nonatomic, assign, readonly) CGPoint focusPointOfInterest;

/**
 * 指定期望的对焦参考点，需要注意的是 preferredFocusPointOfInterest 的值不一定能够被成功应用，实际的对焦参考点可以通过 MSVRecorder.focusPointOfInterest 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

/**
 * 当前的是否开启持续自动曝光状态
 *
 * @discussion 开启持续自动曝光即设备在需要的时候自动调节曝光参考点。
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoExposureEnable;

/**
 * 指定期望是否开启持续自动曝光调节，需要注意的是 preferredContinuousAutoExposureEnable 的值不一定能够被成功应用，实际是否开启持续自动曝光调节可以通过 
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;

/*!
 * 指示当前的曝光参考点。
 *
 * @discussion 此属性的值是一个决定曝光参考点的 CGPoint，(0,0) 点代表图片的左上角，(1,1)点代表图片的右下角。默认值为 (0.5,0.5)。
 */
@property (nonatomic, assign, readonly) CGPoint exposurePointOfInterest;

/**
 * 指定期望的曝光参考点，需要注意的是 preferredExposurePointOfInterest 的值不一定能够被成功应用，实际的曝光参考点可以通过 MSVRecorder.exposurePointOfInterest 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

/**
 * 录制过程中是否静音，如果你想录制整段没有音频的视频，你可以在 audioConfiguration 中指定 source 为 MSVAudioSourceNone。
 * 默认和初始化录制器使用的 audioConfiguration 一致。
 */
@property (nonatomic, assign) BOOL mute;

/**
 * 录制目标文件的转向参数。
 */
@property (nonatomic, assign, readonly) CGAffineTransform encoderPreferredTransform;

/**
 * 是否开启自动检测设备方向以调整视频方向。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL autoOrientationAdaption;

/**
 * 当前设备的旋转方向，此属性当且仅当 autoOrientationAdaption 为 YES 时才有效。此属性支持 KVO。
 */
@property (nonatomic, assign, readonly) UIDeviceOrientation currentDeviceOrientation;

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
 * @brief 使用保存的草稿初始化一个录制器，使用此方法创建的录制器后续所有录制的片段和背景音乐都将添加到初始化使用的草稿对象中。
 *
 * @param draft 初始化使用的草稿对象。
 * @param audioConfiguration 音频配置，传入 nil 将使用默认配置。
 * @param videoConfiguration 视频配置，传入 nil 将使用默认配置。
 * @param outError 如果发生错误，返回发生的错误。
 * 
 * @return 初始化成功返回初始化后的对象，否则返回 nil。
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft AudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

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
 * 使用指定配置开始录制。
 *
 * @param clipConfiguration 录制使用的配置，传入 nil 将使用默认配置
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)startRecordingWithClipConfiguration:(MSVClipConfiguration *_Nullable)clipConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 完成录制。
 *
 * @param completionHandler 停止成功的回调。
 */
- (void)finishRecordingWithCompletionHandler:(MSVFinishRecordingWithCompletionHandler _Nullable)completionHandler;

/**
 * 取消当前录制。
 */
- (void)cancelRecording;

/**
 * 删除上一段录制的片段。
 *
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)discardLastClipWithError:(NSError *_Nullable *_Nullable )outError;

/**
 * 删除指定索引的片段。
 *
 * @param index 需要删除的片段的索引。
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)discardClipAtIndex:(NSUInteger)index error:(NSError *_Nullable *_Nullable)outError;

/**
 * 删除所有录制的片段。
 *
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)discardAllClipsWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * 切换摄像头。
 */
- (void)switchCamera;

/**
 * 背景音效配置对象。
 */
@property(nonatomic, strong, readonly, nullable) MSVRecorderBackgroundAudioConfiguration *backgroundAudioConfiguration;

/**
 * 只有在未开始录制或者已经删除所有已录制的片段之后才能设置或取消背景音乐，设置的背景音乐信息会体现在 draft.audioClips 中而不会直接编码到生成的录制文件当中，以便在编辑阶段可以随时替换背景音乐。
 *
 * @param configuration 背景音效配置对象，传入 nil 清空背景音效。
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
 (BOOL)setBackgroundAudioWithConfiguration:(MSVRecorderBackgroundAudioConfiguration *_Nullable)configuration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 外部写入视频数据接口，使用该接口导入视频数据请保证配置 videoConfiguration.source = MSVVideoSourceExtern。
 *
 * @param videoData 待写入的视频数据。
 * @param presentationTime 视频数据的显示时间戳。
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeVideoData:(CVPixelBufferRef)videoData presentationTime:(CMTime)presentationTime error:(NSError *_Nullable *_Nullable)outError;

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
 * 外部写入视频数据接口，使用该接口导入视频数据请保证配置 videoConfiguration.source = MSVVideoSourceExtern。
 *
 * @param videoData 待写入的视频数据。
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
