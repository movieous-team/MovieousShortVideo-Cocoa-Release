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
 * Recorder delegate interface.
 */
@protocol MSVRecorderDelegate <NSObject>

@optional
/**
 * Callback when error occurred while recording.
 *
 * @param recorder Recorder object that generated the event.
 * @param error The specific error occurred.
 */
- (void)recorder:(MSVRecorder *)recorder didErrorOccurred:(NSError *)error;

/**
 * Callback when the user clicks on the preview interface to focus.
 *
 * @param recorder Recorder object that generated the event.
 * @param point User clicked location.
 */
- (void)recorder:(MSVRecorder *)recorder didFocusAtPoint:(CGPoint)point;

/**
 * An error occurred while the recorder was playing background music.
 *
 * @param recorder Recorder object that generated the event.
 * @param error Specific error.
 */
- (void)recorder:(MSVRecorder *)recorder didPlayBackgroundAudioError:(NSError *)error;

/**
 * The callback of the duration of the current recorded clip has updated, the caller can update the UI feedback recording progress in this callback.
 *
 * @param recorder Recorder object that generated the event.
 * @param currentClipDuration The duration of current clip.
 */
- (void)recorder:(MSVRecorder *)recorder currentClipDurationDidUpdated:(NSTimeInterval)currentClipDuration;

@end

/**
 * Recorder class used to record video.
 */
@interface MSVRecorder : NSObject

/**
 * Recorder Automatically generated draft object that can be used to obtain draft objects for editing or exporting.
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * Video parameter configuration object.
 *
 * @warning Please do not modify the obtained videoConfiguration object, otherwise, an undefined error will occur. If the parameters were modified, please use related running properties updating interface or destroy the current Recorder and re-generate.
 */
@property (nonatomic, strong, readonly) MSVRecorderVideoConfiguration *videoConfiguration;

/**
 * Audio parameter configuration object.
 *
 * @warning Please do not modify the obtained videoConfiguration object, otherwise, an undefined error will occur. If the parameters were modified, please use related running properties updating interface or destroy the current Recorder and re-generate.
 */
@property (nonatomic, strong, readonly) MSVRecorderAudioConfiguration *audioConfiguration;

/**
 * The duration has been recorded of the current clip.
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentClipDuration;

/**
 * The original duration of all the saved clips(without taking speed into account).
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsOriginalDuration;

/**
 * The real duration of all the saved clips(take speed into account).
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsRealDuration;

/**
 * Preview view.
 */
@property (nonatomic, strong, readonly) UIView *previewView;

/**
 * Delegate object for receiving event callbacks.
 */
@property (nonatomic, weak, nullable) id<MSVRecorderDelegate> delegate;

/**
 * The queue used by the delegate method callback, if not specified, will be called back in the main thread.
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 * Effects applied to recorder.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, copy) NSArray<id<MovieousCaptureEffect>> *captureEffects;

/**
 * The fill mode used when the preview window does not match the configured videoSize ratiothe.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * Whether it is in the status of recording or not.
 */
@property (nonatomic, assign, readonly) BOOL recording;

/**
 * Whether to mirror the front camera preview.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/**
 * Whether to mirror the rear camera preview.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/**
 * Whether to mirror the video encoded by the front camera.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/**
 * Whether to mirror the video encoded by the rear camera.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * Whether to enable touch to focus and exposure the specified point in the preview.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL touchToFocusExposureEnabled;

/**
 * Whether to open the internal focus view.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL innerFocusViewEnabled;

/**
 * The current torchMode being used on the camera.
 */
@property (nonatomic, assign, readonly) AVCaptureTorchMode torchMode;

/**
 * Specify the preferred torch mode to use on camera, what needs to note is that the preferredTorchMode is not guaranteed to be applied succesfully, the actual torch mode can be accessed by the property torchMode.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

/**
 * The current flashMode being used on the camera.
 */
@property (nonatomic, assign, readonly) AVCaptureFlashMode flashMode;

/**
 * Specify the preferred flash mode to use on camera, what needs to note is that the preferredFlashMode is not guaranteed to be applied succesfully, the actual torch mode can be accessed by the property flashMode.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) AVCaptureFlashMode preferredFlashMode;

/**
 * A property indicating the format's supported frame rate ranges. videoSupportedFrameRateRanges is an array of AVFrameRateRange objects, one for each of the format's supported video frame rate ranges.
 */
@property(nonatomic, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

/**
 * The current minimum frames per second on camera.
 */
@property (nonatomic, assign, readonly) Float64 minFrameRate;

/**
 * Specify the preferred minimum frames per second on camera, what needs to note is that the preferredMinFrameRate is not guaranteed to be applied succesfully, the actual minimum frames per second can be accessed by the property minFrameRate.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) Float64 preferredMinFrameRate;

/**
 * The current maximum frames per second on camera.
 */
@property (nonatomic, assign, readonly) Float64 maxFrameRate;

/**
 * Specify the preferred maximum frames per second on camera, what needs to note is that the preferredMaxFrameRate is not guaranteed to be applied succesfully, the actual maximum frames per second can be accessed by the property maxFrameRate.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

/**
 * The current sessionPreset of the camera.
 */
@property (nonatomic, strong, readonly) AVCaptureSessionPreset sessionPreset;

/**
 * Specify the resolution for capturing, what needs to note is that the preferredSessionPreset is not guaranteed to be applied succesfully, the actual resolution can be accessed by the property sessionPreset.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, strong) AVCaptureSessionPreset preferredSessionPreset;

/**
 * The current position of the camera.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition devicePosition;

/**
 * Specify the Camera position for capturing, what needs to note is that the preferredDevicePosition is not guaranteed to be applied succesfully, the actual Camera position can be accessed by the property devicePosition.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

/**
 * The current orientation of the camera.
 */
@property (nonatomic, assign, readonly) AVCaptureVideoOrientation videoOrientation;

/**
 * Specify the orientation of the camera, what needs to note is that the preferredVideoOrientation is not guaranteed to be applied succesfully, the actual Camera orientation can be accessed by the property videoOrientation.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

/**
 * The maximum video zoom factor that can be applied.
 */
@property (nonatomic, assign, readonly) CGFloat videoMaxZoomFactor;

/**
 * The current video zoom factor.
 */
@property (nonatomic, assign, readonly) CGFloat videoZoomFactor;

/**
 * Specify the video zoom factor of the camera, what needs to note is that the preferredVideoZoomFactor is not guaranteed to be applied succesfully, the actual video zoom factor can be accessed by the property videoZoomFactor.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

/**
 * The current continuousAutoFocusEnable status.
 * The default is the same as the videoConfiguration initializing the recorder.
 *
 * @discussion ContinuousAutoFocus indicates that the device should automatically focus when needed.
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoFocusEnable;

/**
 * Specify the continuousAutoFocusEnable status of the camera, what needs to note is that the preferredContinuousAutoFocusEnable is not guaranteed to be applied succesfully, the actual continuousAutoFocusEnable can be accessed by the property continuousAutoFocusEnable
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;

/**
 * Indicates current focus point of interest of the receiver, if it has one.
 *
 * @discussion The value of this property is a CGPoint that determines the receiver's focus point of interest, if it has one. A value of (0,0) indicates that the camera should focus on the top left corner of the image, while a value of (1,1) indicates that it should focus on the bottom right. The default value is (0.5,0.5).
 */
@property (nonatomic, assign, readonly) CGPoint focusPointOfInterest;

/**
 * Specify the preferredFocusPointOfInterest status of the camera, what needs to note is that the preferredFocusPointOfInterest is not guaranteed to be applied succesfully, the actual focusPointOfInterest can be accessed by the property focusPointOfInterest
 * The default is the same as the videoConfiguration initializing the recorder..
 */
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

/**
 * The current continuousAutoExposureEnable status
 *
 * @discussion Indicates that the device should automatically adjust exposure when needed
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoExposureEnable;

/**
 * Specify the preferredContinuousAutoExposureEnable of the camera, what needs to note is that the preferredContinuousAutoExposureEnable is not guaranteed to be applied succesfully, the actual continuousAutoExposureEnable can be accessed by the property continuousAutoExposureEnable.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;

/*!
 * Indicates current exposure point of interest of the receiver, if it has one.
 *
 * @discussion The value of this property is a CGPoint that determines the receiver's exposure point of interest, if it has adjustable exposure. A value of (0,0) indicates that the camera should adjust exposure based on the top left corner of the image, while a value of (1,1) indicates that it should adjust exposure based on the bottom right corner. The default value is (0.5,0.5).
 */
@property (nonatomic, assign, readonly) CGPoint exposurePointOfInterest;

/**
 * Specify the preferredExposurePointOfInterest of the camera, what needs to note is that the preferredExposurePointOfInterest is not guaranteed to be applied succesfully, the actual exposurePointOfInterest can be accessed by the property exposurePointOfInterest.
 * The default is the same as the videoConfiguration initializing the recorder.
 */
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

/**
 * Mute sound while recording, if you want to record a movie with no sound, you can specify source property in audioConfiguration to MSVAudioSourceNone.
 * The default is the same as the audioConfiguration initializing the recorder.
 */
@property (nonatomic, assign) BOOL mute;

/**
 * The preferred Transform used for the recorded file.
 */
@property (nonatomic, assign, readonly) CGAffineTransform encoderPreferredTransform;

/**
 * Turn on device orientation to auto detection.
 * The default is NO.
 */
@property (nonatomic, assign) BOOL autoOrientationAdaption;

/**
 * The current device orientation, this property will only valid if autoOrientationAdaption is YES. This property is also key-value Observable, you can observe this value use KVO.
 */
@property (nonatomic, assign, readonly) UIDeviceOrientation currentDeviceOrientation;

/**
 * Initialize a MSVRecorder object.
 *
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration.
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the initialization is successful, otherwise, it returns NO.
 */
- (instancetype _Nullable)initWithAudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a recorder with a saved draft, from the time on the recorder created with this method, all recorded clips and background music will be added to the draft object used for initialization.
 *
 * @param draft Initialize the used draft object.
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration.
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the initialization is successful, otherwise, it returns NO.
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft AudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Start collecting audio and video, call this method will request the usage permission of audio and video (if the specified audio and video data source is the camera or microphone).
 *
 * @param completionHandler Callback is completed, audioGranted：Whether to obtain audio rights, audioError：Error in audio component initialization, videoGranted：Whether you have obtained the captured permissions of the video,videoError：Error in video component initialization.
 */
- (void)startCapturingWithCompletion:(void(^)(BOOL audioGranted, NSError *_Nullable audioError, BOOL videoGranted, NSError *_Nullable videoError))completionHandler;

/**
 * Stop capturing.
 */
- (void)stopCapturing;

/**
 * Start recording with the default configuration.
 
 *
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)startRecordingWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * Start recording with the specified configuration, if recorder has already started, returns YES.
 *
 * @param clipConfiguration Record the used configuration, the default configuration will be used after passing nil.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)startRecordingWithClipConfiguration:(MSVClipConfiguration *_Nullable)clipConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Complete the record.
 *
 * @param completionHandler Stop the successful callback, clip: record the generated main track clip object, if recorder has already stopped, completion, this is the last main track clip, error: error occurred.
 */
- (void)finishRecordingWithCompletionHandler:(void(^)(MSVMainTrackClip *_Nullable clip, NSError *_Nullable error))completionHandler;

/**
 * Cancel the current recording progress.
 */
- (void)cancelRecording;

/**
 * Delete the last recorded clip.
 *
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)discardLastClipWithError:(NSError *_Nullable *_Nullable )outError;

/**
 * Delete the segment of the specified index.
 *
 * @param index The index of the segment that needs to be deleted.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)discardClipAtIndex:(NSUInteger)index error:(NSError *_Nullable *_Nullable)outError;

/**
 * Delete all recorded clips.
 *
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)discardAllClipsWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * Switch camera.
 */
- (void)switchCamera;

/**
 * Background audio configuration object.
 */
@property(nonatomic, strong, readonly, nullable) MSVRecorderBackgroundAudioConfiguration *backgroundAudioConfiguration;

/**
 * The background music can be set or canceled only after the recording has not started or all the recorded clips have been deleted, the background music information after set will be reflected in the draft.audioClips and will not be encoded into the generated recording file directly,  so that the background music can be replaced at any time during the editing phase.
 *
 * @param configuration The background audio configuration object after nil passed will clear the background audio.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)setBackgroundAudioWithConfiguration:(MSVRecorderBackgroundAudioConfiguration *_Nullable)configuration error:(NSError *_Nullable *_Nullable)outError;

/**
 * The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern.
 *
 * @param videoData Video data to be written.
 * @param presentationTime The presentationTime of the video data.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)writeVideoData:(CVPixelBufferRef)videoData presentationTime:(CMTime)presentationTime error:(NSError *_Nullable *_Nullable)outError;

/**
 * The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern.
 *
 * @param videoData Video data to be written.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)writeVideoData:(CMSampleBufferRef)videoData error:(NSError *_Nullable *_Nullable)outError;

/**
 * The interface of externally write the video data, please ensure the configuration if this interface will be used. audioConfiguration.source = MSVAudioSourceExtern.
 *
 * @param audioData Audio data to be written.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES when the setting is successful, otherwise, it returns NO.
 */
- (BOOL)writeAudioData:(CMSampleBufferRef)audioData error:(NSError *_Nullable *_Nullable)outError;

/**
 * Obtain a screenshot.
 *
 * @param completionHandler Called when capture completes.
 */
- (void)snapshotWithCompletion:(MovieousSnapshotCompletionHandler)completionHandler;

@end

NS_ASSUME_NONNULL_END
