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
 * @brief Recorder proxy interface
 */
@protocol MSVRecorderDelegate <NSObject>

@optional
/**
 * @brief Callback when error occurred while recording
 * @param recorder Recorder object that generated the event
 * @param error The specific error occurred
 */
- (void)recorder:(MSVRecorder *)recorder didErrorOccurred:(NSError *)error;

/**
 * @brief Callback when the user clicks on the preview interface to focus
 * @param recorder Recorder object that generated the event
 * @param point User clicked location
 */
- (void)recorder:(MSVRecorder *)recorder didFocusAtPoint:(CGPoint)point;

/**
 * @brief An error occurred while the recorder was playing background music
 * @param recorder Recorder object that generated the event
 * @param error Specific error
 */
- (void)recorder:(MSVRecorder *)recorder didPlayBackgroundAudioError:(NSError *)error;

/**
 * @brief The callback of the duration of the current recorded clip has updated, the caller can update the UI feedback recording progress in this callback.
 * @param recorder Recorder object that generated the event
 * @param currentClipDuration The duration of current clip
 */
- (void)recorder:(MSVRecorder *)recorder currentClipDurationDidUpdated:(NSTimeInterval)currentClipDuration;

@end

/**
 * @brief Recorder
 */
@interface MSVRecorder : NSObject

/**
 * @brief Recorder Automatically generated draft object that can be used to obtain draft objects for editing or exporting.
 */
@property (nonatomic, strong, readonly, nullable) MSVDraft *draft;

/**
 * @brief Video parameter configuration object
 * @warning Please do not modify the obtained videoConfiguration object, otherwise, an undefined error will occur. If the parameters were modified, please use related running properties updating interface or destroy the current Recorder and re-generate.
 */
@property (nonatomic, strong, readonly) MSVRecorderVideoConfiguration *videoConfiguration;

/**
 * @brief Audio parameter configuration object
 * @warning Please do not modify the obtained videoConfiguration object, otherwise, an undefined error will occur. If the parameters were modified, please use related running properties updating interface or destroy the current Recorder and re-generate.
 */
@property (nonatomic, strong, readonly) MSVRecorderAudioConfiguration *audioConfiguration;

/**
 * @brief The duration has been recorded of the current clip
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentClipDuration;

/**
 * @brief The original duration of all the saved clips(without taking speed into account)
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsOriginalDuration;

/**
 * @brief The real duration of all the saved clips(take speed into account)
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsRealDuration;

/**
 * @brief Preview view
 */
@property (nonatomic, strong, readonly) UIView *previewView;

/**
 * @brief Delegate object for receiving event callbacks
 */
@property (nonatomic, weak, nullable) id<MSVRecorderDelegate> delegate;

/**
 * @brief  The queue used by the proxy method callback, if not specified, will be called back in the main thread.
 */
@property (nonatomic, strong, nullable) dispatch_queue_t delegateQueue;

/**
 * @brief Effects applied to recorder.
 */
@property (nonatomic, copy) NSArray<id<MovieousCaptureEffect>> *captureEffects;

/**
 * @brief The fill mode used when the preview window does not match the configured videoSize ratio, the default is MovieousScalingModeAspectFit.
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * @brief Whether it is in the status of recording or not
 */
@property (nonatomic, assign, readonly) BOOL recording;

/**
 * @brief Whether to mirror the front camera preview, the default is YES
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/**
 * @brief Whether to mirror the rear camera preview, the default is NO
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/**
 * @brief Whether to mirror the video encoded by the front camera, the default is NO
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/**
 * @brief Whether to mirror the video encoded by the rear camera, the default is NO
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * @brief Whether to enable touch to focus and exposure the specified point in the preview
 */
@property (nonatomic, assign) BOOL touchToFocusExposureEnabled;

/**
 * @brief Whether to open the internal focus view, the default is NO
 */
@property (nonatomic, assign) BOOL innerFocusViewEnabled;

/**
 * @brief The current torchMode being used on the camera
 */
@property (nonatomic, assign, readonly) AVCaptureTorchMode torchMode;

/**
 * @brief Specify the preferred torch mode to use on camera, what needs to note is that the preferredTorchMode is not guaranteed to be applied succesfully, the actual torch mode can be accessed by the property torchMode
 */
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

/**
 * @brief A property indicating the format's supported frame rate ranges. videoSupportedFrameRateRanges is an array of AVFrameRateRange objects, one for each of the format's supported video frame rate ranges
 */
@property(nonatomic, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

/**
 * @brief The current minimum frames per second on camera
 */
@property (nonatomic, assign, readonly) Float64 minFrameRate;

/**
 * @brief Specify the preferred minimum frames per second on camera, what needs to note is that the preferredMinFrameRate is not guaranteed to be applied succesfully, the actual minimum frames per second can be accessed by the property minFrameRate
 */
@property (nonatomic, assign) Float64 preferredMinFrameRate;

/**
 * @brief The current maximum frames per second on camera
 */
@property (nonatomic, assign, readonly) Float64 maxFrameRate;

/**
 * @brief Specify the preferred maximum frames per second on camera, what needs to note is that the preferredMaxFrameRate is not guaranteed to be applied succesfully, the actual maximum frames per second can be accessed by the property maxFrameRate
 */
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

/**
 * @brief The resolution captured by the camera, the default is AVCaptureSessionPresetHigh
 */
@property (nonatomic, strong, readonly) AVCaptureSessionPreset sessionPreset;

/**
 * @brief Specify the resolution for capturing, what needs to note is that the preferredSessionPreset is not guaranteed to be applied succesfully, the actual resolution can be accessed by the property sessionPreset
 */
@property (nonatomic, assign) AVCaptureSessionPreset preferredSessionPreset;

/**
 * @brief Camera position, the default is AVCaptureDevicePositionBack
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition devicePosition;

/**
 * @brief Specify the Camera position for capturing, what needs to note is that the preferredDevicePosition is not guaranteed to be applied succesfully, the actual Camera position can be accessed by the property devicePosition
 */
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

/**
 * @brief Set the orientation of the camera
 */
@property (nonatomic, assign, readonly) AVCaptureVideoOrientation videoOrientation;

/**
 * @brief Specify the orientation of the camera, what needs to note is that the preferredVideoOrientation is not guaranteed to be applied succesfully, the actual Camera orientation can be accessed by the property videoOrientation
 */
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

/**
 * @brief The maximum video zoom factor that can be applied
 */
@property (nonatomic, assign, readonly) CGFloat videoMaxZoomFactor;

/**
 * @brief The current video zoom factor
 */
@property (nonatomic, assign, readonly) CGFloat videoZoomFactor;

/**
 * @brief Specify the video zoom factor of the camera, what needs to note is that the preferredVideoZoomFactor is not guaranteed to be applied succesfully, the actual video zoom factor can be accessed by the property videoZoomFactor
 */
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

/**
 * @brief The current continuousAutoFocusEnable status
 * @discussion ContinuousAutoFocus indicates that the device should automatically focus when needed.
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoFocusEnable;

/**
 * @brief Specify the continuousAutoFocusEnable status of the camera, what needs to note is that the preferredContinuousAutoFocusEnable is not guaranteed to be applied succesfully, the actual continuousAutoFocusEnable can be accessed by the property continuousAutoFocusEnable
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;

/**
 @abstract
 Indicates current focus point of interest of the receiver, if it has one.
 
 @discussion
 The value of this property is a CGPoint that determines the receiver's focus point of interest, if it has one. A value of (0,0) indicates that the camera should focus on the top left corner of the image, while a value of (1,1) indicates that it should focus on the bottom right. The default value is (0.5,0.5).
 */
@property (nonatomic, assign, readonly) CGPoint focusPointOfInterest;

/**
 * @brief Specify the preferredFocusPointOfInterest status of the camera, what needs to note is that the preferredFocusPointOfInterest is not guaranteed to be applied succesfully, the actual focusPointOfInterest can be accessed by the property focusPointOfInterest
 */
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

/**
 @abstract
 The current continuousAutoExposureEnable status
 
 @discussion
 Indicates that the device should automatically adjust exposure when needed
 */
@property (nonatomic, assign, readonly) BOOL continuousAutoExposureEnable;

/**
 * @brief Specify the preferredContinuousAutoExposureEnable of the camera, what needs to note is that the preferredContinuousAutoExposureEnable is not guaranteed to be applied succesfully, the actual continuousAutoExposureEnable can be accessed by the property continuousAutoExposureEnable
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;

/*!
 @abstract
 Indicates current exposure point of interest of the receiver, if it has one.
 
 @discussion
 The value of this property is a CGPoint that determines the receiver's exposure point of interest, if it has adjustable exposure. A value of (0,0) indicates that the camera should adjust exposure based on the top left corner of the image, while a value of (1,1) indicates that it should adjust exposure based on the bottom right corner. The default value is (0.5,0.5).
 */
@property (nonatomic, assign, readonly) CGPoint exposurePointOfInterest;

/**
 * @brief Specify the preferredExposurePointOfInterest of the camera, what needs to note is that the preferredExposurePointOfInterest is not guaranteed to be applied succesfully, the actual exposurePointOfInterest can be accessed by the property exposurePointOfInterest
 */
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

/**
 * @brief Mute sound while recording, if you want to record a movie with no sound, you can specify source property in audioConfiguration to MSVAudioSourceNone
 */
@property (nonatomic, assign) BOOL mute;

/**
 * @brief The preferred Transform used for the recorded file
 */
@property (nonatomic, assign, readonly) CGAffineTransform encoderPreferredTransform;

/**
 * @brief Turn on device orientation to auto detection
 */
@property (nonatomic, assign) BOOL autoOrientationAdaption;

/**
 * @brief The current device orientation, this property will only valid if autoOrientationAdaption is YES. This property is also key-value Observable, you can observe this value use KVO.
 */
@property (nonatomic, assign) UIDeviceOrientation currentDeviceOrientation;

/**
 * @brief Initialize an empty recorder
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the initialization is successful, otherwise, it returns NO
 */
- (instancetype _Nullable)initWithAudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Initialize a recorder with a saved draft, from the time on the recorder created with this method, all recorded clips and background music will be added to the draft object used for initialization.
 * @param draft Initialize the used draft object
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the initialization is successful, otherwise, it returns NO
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *)draft AudioConfiguration:(MSVRecorderAudioConfiguration *_Nullable)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *_Nullable)videoConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Start collecting audio and video, call this method will request the usage permission of audio and video (if the specified audio and video data source is the camera or microphone)
 * @param completionHandler Callback is completed, audioGranted：Whether to obtain audio rights, audioError：Error in audio component initialization, videoGranted：Whether you have obtained the captured permissions of the video,videoError：Error in video component initialization
 */
- (void)startCapturingWithCompletion:(void(^)(BOOL audioGranted, NSError *_Nullable audioError, BOOL videoGranted, NSError *_Nullable videoError))completionHandler;

/**
 * @brief Stop capturing
 */
- (void)stopCapturing;

/**
 * @brief Start recording with the default configuration
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)startRecordingWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Start recording with the specified configuration, if recorder has already started, return YES;
 * @param clipConfiguration Record the used configuration, the default configuration will be used after passing nil
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)startRecordingWithClipConfiguration:(MSVClipConfiguration *_Nullable)clipConfiguration error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Complete the record
 * @param completionHandler Stop the successful callback, clip: record the generated main track clip object, if recorder has already stopped, completion, this is the last main track clip, error: error occurred
 */
- (void)finishRecordingWithCompletionHandler:(void(^)(MSVMainTrackClip *_Nullable clip, NSError *_Nullable error))completionHandler;

/**
 * @brief Cancel the current recording progress
 */
- (void)cancelRecording;

/**
 * @brief Delete the last recorded clip
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)discardLastClipWithError:(NSError *_Nullable *_Nullable )outError;

/**
 * @brief Delete the segment of the specified index
 * @param index The index of the segment that needs to be deleted
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)discardClipAtIndex:(NSUInteger)index error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Delete all recorded clips
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)discardAllClipsWithError:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Switch camera
 */
- (void)switchCamera;

/**
 * @brief Background audio configuration object
 */
@property(nonatomic, strong, readonly, nullable) MSVRecorderBackgroundAudioConfiguration *backgroundAudioConfiguration;

/**
 * @brief The background music can be set or canceled only after the recording has not started or all the recorded clips have been deleted, the background music information after set will be reflected in the draft.audioClips and will not be encoded into the generated recording file directly,  so that the background music can be replaced at any time during the editing phase.
 * @param configuration The background audio configuration object after nil passed will clear the background audio
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setBackgroundAudioWithConfiguration:(MSVRecorderBackgroundAudioConfiguration *)configuration error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern
 * @param videoData Video data to be written
 * @param presentationTime The presentationTime of the video data
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)writeVideoData:(CVPixelBufferRef)videoData presentationTime:(CMTime)presentationTime error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern
 * @param videoData Video data to be written
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)writeVideoData:(CMSampleBufferRef)videoData error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief The interface of externally write the video data, please ensure the configuration if this interface will be used. audioConfiguration.source = MSVAudioSourceExtern
 * @param audioData Audio data to be written
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)writeAudioData:(CMSampleBufferRef)audioData error:(NSError *_Nullable *_Nullable)outError;

/**
 * @brief Obtain a screenshot
 */
- (void)snapshotWithCompletion:(void(^)(UIImage *image))completionHandler;

@end

NS_ASSUME_NONNULL_END
