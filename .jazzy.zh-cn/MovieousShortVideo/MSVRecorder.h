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
 * The real duration of all the saved clips(take speed into account)。
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
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

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
 * The current torchMode being used on the camera。
 */
@property (nonatomic, assign, readonly) AVCaptureTorchMode torchMode;

/**
 * 指定期望的摄像头手电筒模式，需要注意的是 preferredTorchMode 的值不一定能够被成功应用，实际的手电筒模式可以通过 MSVRecorder.torchMode 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

/**
 * A property indicating the format's supported frame rate ranges。 videoSupportedFrameRateRanges is an array of AVFrameRateRange objects, one for each of the format's supported video frame rate ranges。
 */
@property(nonatomic, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

/**
 * The current minimum frames per second on camera。
 */
@property (nonatomic, assign, readonly) Float64 minFrameRate;

/**
 * 指定期望的最小采集帧率，需要注意的是 preferredMinFrameRate 的值不一定能够被成功应用，实际的最小采集帧率可以通过 MSVRecorder.minFrameRate 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) Float64 preferredMinFrameRate;

/**
 * The current maximum frames per second on camera。
 */
@property (nonatomic, assign, readonly) Float64 maxFrameRate;

/**
 * 指定期望的最大采集帧率，需要注意的是 preferredMaxFrameRate 的值不一定能够被成功应用，实际的最大采集帧率可以通过 MSVRecorder.maxFrameRate 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

/**
 * The current sessionPreset of the camera。
 */
@property (nonatomic, strong, readonly) AVCaptureSessionPreset sessionPreset;

/**
 * 指定期望的采集预设分辨率，需要注意的是 preferredSessionPreset 的值不一定能够被成功应用，实际的采集预设分辨率可以通过 MSVRecorder.sessionPreset 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureSessionPreset preferredSessionPreset;

/**
 * The current position of the camera。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition devicePosition;

/**
 * 指定期望的摄像头位置，需要注意的是 preferredDevicePosition 的值不一定能够被成功应用，实际的摄像头位置可以通过 MSVRecorder.devicePosition 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

/**
 * The current orientation of the camera。
 */
@property (nonatomic, assign, readonly) AVCaptureVideoOrientation videoOrientation;

/**
 * 指定期望的摄像头方向，需要注意的是 preferredVideoOrientation 的值不一定能够被成功应用，实际的摄像头方向可以通过 MSVRecorder.videoOrientation 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

/**
 * The maximum video zoom factor that can be applied。
 */
@property (nonatomic, assign, readonly) CGFloat videoMaxZoomFactor;

/**
 * The current video zoom factor。
 */
@property (nonatomic, assign, readonly) CGFloat videoZoomFactor;

/**
 * 指定期望的视频缩放比例，需要注意的是 preferredVideoZoomFactor 的值不一定能够被成功应用，实际的视频缩放比例可以通过 MSVRecorder.videoZoomFactor 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

/**
 * The current continuousAutoFocusEnable status。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 *
 * @discussion ContinuousAutoFocus indicates that the device should automatically focus when needed。
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoFocusEnable;

/**
 * 指定期望是否开启持续自动对焦，需要注意的是 preferredContinuousAutoFocusEnable 的值不一定能够被成功应用，实际是否开启持续自动对焦可以通过 MSVRecorder.continuousAutoFocusEnable 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;

/**
 * Indicates current focus point of interest of the receiver, if it has one。
 *
 * @discussion The value of this property is a CGPoint that determines the receiver's focus point of interest, if it has one. A value of (0,0) indicates that the camera should focus on the top left corner of the image, while a value of (1,1) indicates that it should focus on the bottom right. The default value is (0.5,0.5)。
 */
@property (nonatomic, assign, readonly) CGPoint focusPointOfInterest;

/**
 * 指定期望的对焦参考点，需要注意的是 preferredFocusPointOfInterest 的值不一定能够被成功应用，实际的对焦参考点可以通过 MSVRecorder.focusPointOfInterest 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

/**
 * The current continuousAutoExposureEnable status
 *
 * @discussion Indicates that the device should automatically adjust exposure when needed
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoExposureEnable;

/**
 * 指定期望是否开启持续自动曝光调节，需要注意的是 preferredContinuousAutoExposureEnable 的值不一定能够被成功应用，实际是否开启持续自动曝光调节可以通过 
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;

/*!
 * Indicates current exposure point of interest of the receiver, if it has one。
 *
 * @discussion The value of this property is a CGPoint that determines the receiver's exposure point of interest, if it has adjustable exposure。 A value of (0,0) indicates that the camera should adjust exposure based on the top left corner of the image, while a value of (1,1) indicates that it should adjust exposure based on the bottom right corner. The default value is (0.5,0.5)。
 */
@property (nonatomic, assign, readonly) CGPoint exposurePointOfInterest;

/**
 * 指定期望的曝光参考点，需要注意的是 preferredExposurePointOfInterest 的值不一定能够被成功应用，实际的曝光参考点可以通过 MSVRecorder.exposurePointOfInterest 来获取。
 * 默认和初始化录制器使用的 videoConfiguration 一致。
 */
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

/**
 * Mute sound while recording, if you want to record a movie with no sound, you can specify source property in audioConfiguration to MSVAudioSourceNone。
 * 默认和初始化录制器使用的 audioConfiguration 一致。
 */
@property (nonatomic, assign) BOOL mute;

/**
 * The preferred Transform used for the recorded file。
 */
@property (nonatomic, assign, readonly) CGAffineTransform encoderPreferredTransform;

/**
 * Turn on device orientation to auto detection。
 * The default is NO。
 */
@property (nonatomic, assign) BOOL autoOrientationAdaption;

/**
 * The current device orientation, this property will only valid if autoOrientationAdaption is YES。 This property is also key-value Observable, you can observe this value use KVO。
 */
@property (nonatomic, assign, readonly) UIDeviceOrientation currentDeviceOrientation;

/**
 * Initialize an empty recorder。
 *
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration。
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration。
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return It returns YES when the initialization is successful, otherwise, it returns NO。
 */
- (instancetype _Nullable)initWithAudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a recorder with a saved draft, from the time on the recorder created with this method, all recorded clips and background music will be added to the draft object used for initialization。
 *
 * @param draft Initialize the used draft object。
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration。
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration。
 * @param outError 如果发生错误，返回错误对象。
 * 
 * @return It returns YES when the initialization is successful, otherwise, it returns NO。
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft AudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Start collecting audio and video, call this method will request the usage permission of audio and video (if the specified audio and video data source is the camera or microphone)。
 *
 * @param completionHandler Callback is completed, audioGranted：Whether to obtain audio rights, audioError：Error in audio component initialization, videoGranted：Whether you have obtained the captured permissions of the video,videoError：Error in video component initialization。
 */
- (void)startCapturingWithCompletion:(void(^)(BOOL audioGranted, NSError *_Nullable audioError, BOOL videoGranted, NSError *_Nullable videoError))completionHandler;

/**
 * Stop capturing。
 */
- (void)stopCapturing;

/**
 * Start recording with the default configuration。
 
 *
 * @param outError 如果发生错误，返回错误对象。
 * @return It returns YES when the setting is successful, otherwise, it returns NO。
 */
- (BOOL)startRecordingWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * Start recording with the specified configuration, if recorder has already started, returns YES。
 *
 * @param clipConfiguration Record the used configuration, the default configuration will be used after passing nil。
 * @param outError 如果发生错误，返回错误对象。
 * @return It returns YES when the setting is successful, otherwise, it returns NO。
 */
- (BOOL)startRecordingWithClipConfiguration:(MSVClipConfiguration *_Nullable)clipConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Complete the record。
 *
 * @param completionHandler Stop the successful callback, clip: record the generated main track clip object, if recorder has already stopped, completion, this is the last main track clip, error: error occurred。
 */
- (void)finishRecordingWithCompletionHandler:(void(^)(MSVMainTrackClip *_Nullable clip, NSError *_Nullable error))completionHandler;

/**
 * Cancel the current recording progress。
 */
- (void)cancelRecording;

/**
 * Delete the last recorded clip。
 *
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)discardLastClipWithError:(NSError *_Nullable *_Nullable )outError;

/**
 * Delete the segment of the specified index。
 *
 * @param index The index of the segment that needs to be deleted。
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)discardClipAtIndex:(NSUInteger)index error:(NSError *_Nullable *_Nullable)outError;

/**
 * Delete all recorded clips。
 *
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)discardAllClipsWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * Switch camera。
 */
- (void)switchCamera;

/**
 * Background audio configuration object。
 */
@property(nonatomic, strong, readonly, nullable) MSVRecorderBackgroundAudioConfiguration *backgroundAudioConfiguration;

/**
 * The background music can be set or canceled only after the recording has not started or all the recorded clips have been deleted, the background music information after set will be reflected in the draft.audioClips and will not be encoded into the generated recording file directly,  so that the background music can be replaced at any time during the editing phase。
 *
 * @param configuration The background audio configuration object after nil passed will clear the background audio。
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)setBackgroundAudioWithConfiguration:(MSVRecorderBackgroundAudioConfiguration *)configuration error:(NSError *_Nullable *_Nullable)outError;

/**
 * The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern。
 *
 * @param videoData Video data to be written。
 * @param presentationTime The presentationTime of the video data。
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeVideoData:(CVPixelBufferRef)videoData presentationTime:(CMTime)presentationTime error:(NSError *_Nullable *_Nullable)outError;

/**
 * The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern。
 *
 * @param videoData Video data to be written。
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeVideoData:(CMSampleBufferRef)videoData error:(NSError *_Nullable *_Nullable)outError;

/**
 * The interface of externally write the video data, please ensure the configuration if this interface will be used. audioConfiguration.source = MSVAudioSourceExtern。
 *
 * @param audioData Audio data to be written。
 * @param outError 如果发生错误，返回错误对象。
 * @return 如果操作成功返回 YES，否则返回 NO。
 */
- (BOOL)writeAudioData:(CMSampleBufferRef)audioData error:(NSError *_Nullable *_Nullable)outError;

/**
 * Obtain a screenshot。
 */
- (void)snapshotWithCompletion:(void(^)(UIImage *image))completionHandler;

@end

NS_ASSUME_NONNULL_END
