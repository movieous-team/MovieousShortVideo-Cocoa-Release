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
#import "MSVRecorderAudioConfiguration.h"
#import "MSVRecorderVideoConfiguration.h"
#import "MSVClipConfiguration.h"
#import "MSVClip.h"
#import "MSVMainTrackClip.h"
#import "MSVDraft.h"
#import "MSVBackgroundAudioConfiguration.h"
#import "MSVExternalFilter.h"

@class MSVRecorder;

/**
 * @brief Recorder proxy interface
 */
@protocol MSVRecorderDelegate <NSObject>

@optional
/**
 * @brief Callback when the user clicks on the preview interface to focus
 * @param recorder Recorder object that generated the event
 * @param point User clicked location
 */
- (void)recorder:(MSVRecorder *)recorder didFocusAtPoint:(CGPoint)point;

/**
 * @brief The maximum time that the recorder reaches the configuration
 * @param recorder Recorder object that generated the event
 */
- (void)recorderDidReachMaxDuration:(MSVRecorder *)recorder;

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

/**
 * @brief The camera obtains the callback of the video data, and the caller can customize and process the video data by using the method, and the processed data will be feedback to the preview image and encoded into the generated segment.
 * @param recorder Recorder object that generated the event
 * @param pixelBuffer The pending video data
 * @return Processed video data
 */
- (CVPixelBufferRef)recorder:(MSVRecorder *)recorder didGetPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

/**
 * @brief Recorder
 */
@interface MSVRecorder : NSObject

/**
 * @brief Recorder Automatically generated draft object that can be used to obtain draft objects for editing or exporting.
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

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
 * @brief The duration of all the saved clips
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsDuration;

/**
 * @brief The maximum recording duration,  the recording duration here refers to the sum of the duration of all the clips, when the recording duration reaches the maximum value, the delegate's `recorderDidReachMaxDuration` method will be called, when the value is less than or equal to 0, there is no maximum duration limit.
 */
@property (nonatomic, assign) NSTimeInterval maxDuration;

/**
 * @brief Preview view
 */
@property (nonatomic, strong, readonly) UIView *preview;

/**
 * @brief Proxy object for receiving event callbacks
 */
@property (nonatomic, weak) id<MSVRecorderDelegate> delegate;

/**
 * @brief  The queue used by the proxy method callback, if not specified, will be called back in the main thread.
 */
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

/**
 * @brief The fill mode used when the preview window does not match the configured videoSize ratio, the default is MovieousScalingModeAspectFit.
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * @brief whether it is in the status of recording or not
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
 * @brief Whether to open the internal focus view, the default is NO
 */
@property (nonatomic, assign) BOOL innerFocusView;

/**
 * @brief Obtain a screenshot
 */
@property (nonatomic, strong, readonly) UIImage *snapshot;

/**
 * @brief The action is taken automatically during recording operation runs from the background. If the operation is not automatic, the caller needs to perform the appropriate processing (complete or cancel the recording of the current clip). The default is MSVBackgroundActionContinue.
 */
@property (nonatomic, assign) MSVBackgroundAction backgroundAction;

/**
 * @brief Whether the flashlight is turned on, the default is NO
 */
@property (nonatomic, assign, readonly) BOOL torchOn;

/**
 * @brief  the interface of switching flashlight
 * @param torchOn Turn it on or off
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setTorchOn:(BOOL)torchOn error:(NSError **)outError;

/**
 * @brief The frame rate of capturing video
 */
@property (nonatomic, assign, readonly) NSUInteger frameRate;

/**
 * @brief Setup the frame rate of capturing video
 * @param frameRate New frame rate
 * @param outError If an error occurs, return the error that occurred
 * @return  It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setFrameRate:(NSUInteger)frameRate error:(NSError **)outError;

/**
 * @brief The resolution captured by the camera, the default is AVCaptureSessionPresetHigh
 */
@property (nonatomic, strong, readonly) AVCaptureSessionPreset cameraResolution;

/**
 * @brief Setup the resolution captured by the camera
 * @param cameraResolution New resolution rate
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setCameraResolution:(AVCaptureSessionPreset)cameraResolution error:(NSError **)outError;

/**
 * @brief Camera position, the default is AVCaptureDevicePositionBack
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition cameraPosition;

/**
 * @brief Set the position of the camera
 * @param cameraPosition New camera position
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setCameraPosition:(AVCaptureDevicePosition)cameraPosition error:(NSError **)outError;

/**
 * @brief The direction of the camera rotation, the default is AVCaptureVideoOrientationPortrait
 */
@property (nonatomic, assign, readonly) AVCaptureVideoOrientation cameraOrientation;

/**
 * @brief Setup the camera orientation
 * @param cameraOrientation New camera orientation
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setCameraOrientation:(AVCaptureVideoOrientation)cameraOrientation error:(NSError **)outError;

/**
 * @brief Camera zoom factor, default is 1
 */
@property (nonatomic, assign, readonly) CGFloat cameraZoomFactor;

/**
 * @brief Setup camera zoom factor
 * @param cameraZoomFactor New camera zoom factor
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setCameraZoomFactor:(CGFloat)cameraZoomFactor error:(NSError **)outError;

/**
 * @brief Focus and exposure reference points (the position of the point is referenced by the acquisition resolution specified by cameraResolution, the upper left corner is the origin, and the right and down orientations are the orientation in which the x value and the y value increase respectively)
 */
@property (nonatomic, assign, readonly) CGPoint pointOfInterest;

/**
 * @brief Set the reference point for focus and exposure
 * @param pointOfInterest New reference point for focus and exposure
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setPointOfInterest:(CGPoint)pointOfInterest error:(NSError **)outError;

/**
 * @brief Initialize an empty recorder
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the initialization is successful, otherwise, it returns NO
 */
- (instancetype)initWithAudioConfiguration:(MSVRecorderAudioConfiguration *)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *)videoConfiguration error:(NSError **)outError;

/**
 * @brief Initialize a recorder with a saved draft, from the time on the recorder created with this method, all recorded clips and background music will be added to the draft object used for initialization.
 * @param draft Initialize the used draft object
 * @param audioConfiguration Audio configuration that introducing nil will use the default configuration
 * @param videoConfiguration Video configuration that introducing nil will use the default configuration
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the initialization is successful, otherwise, it returns NO
 */
- (instancetype)initWithDraft:(MSVDraft *)draft AudioConfiguration:(MSVRecorderAudioConfiguration *)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *)videoConfiguration error:(NSError **)outError;

/**
 * @brief Start collecting audio and video, call this method will request the usage permission of audio and video (if the specified audio and video data source is the camera or microphone)
 * @param completionHandler Callback is completed, audioGranted：Whether to obtain audio rights, audioError：Error in audio component initialization, videoGranted：Whether you have obtained the captured permissions of the video,videoError：Error in video component initialization
 */
- (void)startCapturingWithCompletionHandler:(void(^)(BOOL audioGranted, NSError *audioError, BOOL videoGranted, NSError *videoError))completionHandler;

/**
 * @brief Start collecting audio and video, call this method will request the usage permission of audio and video (if the specified audio and video data source is the camera or microphone)
 * @param compromise Whether to allow to compromise some parameters which are not supported by the current device to ensure component initialization is successful.
 * @param completionHandler Callback is completed, audioGranted：Whether to obtain audio rights, audioError：Error in audio component initialization, videoGranted：Whether you have obtained the captured permissions of the video,videoError：Error in video component initialization
 */
- (void)startCapturingWithCompromise:(BOOL)compromise completionHandler:(void(^)(BOOL audioGranted, NSError *audioError, BOOL videoGranted, NSError *videoError))completionHandler;

/**
 * @brief Stop capturing
 */
- (void)stopCapturing;

/**
 * @brief Start recording with the default configuration
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)startRecordingWithError:(NSError **)outError;

/**
 * @brief Start recording with the specified configuration
 * @param clipConfiguration Record the used configuration, the default configuration will be used after passing nil
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)startRecordingWithClipConfiguration:(MSVClipConfiguration *)clipConfiguration error:(NSError **)outError;

/**
 * @brief Complete the record
 * @param completionHandler Stop the successful callback, clip: record the generated main track segment object, error: error occurred
 */
- (void)finishRecordingWithCompletionHandler:(void(^)(MSVMainTrackClip *clip, NSError *error))completionHandler;

/**
 * @brief Delete the last recorded clip
 */
- (void)discardLastClip;

/**
 * @brief Delete the segment of the specified index
 * @param index The index of the segment that needs to be deleted
 */
- (void)discardClipAtIndex:(NSUInteger)index;

/**
 * @brief Delete all recorded clips
 */
- (void)discardAllClips;

/**
 * @brief Switch camera
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)switchCameraWithError:(NSError **)outError;

/**
 * @brief Setup watermark
 * @param waterMark Watermark image
 * @param position Watermark position
 */
- (void)setWaterMark:(UIImage *)waterMark position:(CGPoint)position;

/**
 * @brief Clear watermark
 */
- (void)clearWaterMark;

/**
 * @brief Turn on device orientation to auto detection
 * @param orientationUpdatedBlock The callback when the rotated orientation of the device changes
 */
- (void)enableAutoOrientationAdaptionWithOrientationUpdatedBlock:(void(^)(UIDeviceOrientation))orientationUpdatedBlock;

/**
 * @brief Turn off device orientation to auto detection
 */
- (void)disableAutoOrientationAdaption;

/**
 * @brief Update the draft object used by the recorder
 * @param draft New draft object
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError **)outError;

/**
 * @brief Background audio configuration object
 */
@property(nonatomic, strong, readonly) MSVBackgroundAudioConfiguration *backgroundAudioConfiguration;

/**
 * @brief The background music can be set or canceled only after the recording has not started or all the recorded clips have been deleted, the background music information after set will be reflected in the draft.audioClips and will not be encoded into the generated recording file directly,  so that the background music can be replaced at any time during the editing phase.
 * @param configuration The background audio configuration object after nil passed will clear the background audio
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)setBackgroundAudioWithConfiguration:(MSVBackgroundAudioConfiguration *)configuration error:(NSError **)outError;

/**
 * @brief The interface of externally write the video data, please ensure the configuration if this interface will be used.  videoConfiguration.source = MSVVideoSourceExtern
 * @param videoData Video data to be written
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)writeVideoData:(CMSampleBufferRef)videoData error:(NSError **)outError;

/**
 * @brief The interface of externally write the video data, please ensure the configuration if this interface will be used. audioConfiguration.source = MSVAudioSourceExtern
 * @param audioData Audio data to be written
 * @param outError If an error occurs, return the error that occurred
 * @return It returns YES when the setting is successful, otherwise, it returns NO
 */
- (BOOL)writeAudioData:(CMSampleBufferRef)audioData error:(NSError **)outError;

@end

