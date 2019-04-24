//
//  MovieousCameraConfiguration.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/9/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#ifndef MovieousCameraConfiguration_h
#define MovieousCameraConfiguration_h

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousTypeDefines.h>
#import <MovieousBase/MovieousCaptureEffect.h>

@protocol MovieousCameraConfiguration
<
NSObject
>

/**
 * @brief   Video resolution when encoding. The default is (1280, 720)
 * @discussion It should be noted that this parameter affects the resolution of the video encoding, rather than the preview size of the data captured by the camera. When the image size passed to the encoder is different from this size, it will be generated in the same way The video ensures that the image does not appear to be compressed (but the cropping phenomenon occurs when the ratio of the encoded video is different from the ratio of the captured video).
 */
@property (nonatomic, assign) CGSize size;

/**
 * @brief Effects applied to recorder.
 */
@property (nonatomic, strong) NSArray<id<MovieousCaptureEffect>> *captureEffects;

/**
 * The scaling mode you want to use if the aspect ratio of cameraResolution and size are not equal
 * The default is MovieousScalingModeAspectFill
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/*!
 * Turn mirrorFrontPreview means preview for front camera will be mirrored
 * The default is YES
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/*!
 * Turn mirrorBackPreview means preview for back camera will be mirrored
 * The default is NO
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/*!
 * Turn mirrorFrontStream means stream broadcasted for front camera will be mirrored
 * The default is NO
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/*!
 * Turn mirrorBackStream means stream broadcasted for back camera will be mirrored
 * The default is NO
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
 * @brief Specify the preferred torch mode to use on camera, what needs to note is that the preferredTorchMode is not guaranteed to be applied succesfully, the actual torch mode can be accessed by the property torchMode
 */
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

/**
 * @brief Specify the preferred minimum frames per second on camera, what needs to note is that the preferredMinFrameRate is not guaranteed to be applied succesfully, the actual minimum frames per second can be accessed by the property minFrameRate
 */
@property (nonatomic, assign) Float64 preferredMinFrameRate;

/**
 * @brief Specify the preferred maximum frames per second on camera, what needs to note is that the preferredMaxFrameRate is not guaranteed to be applied succesfully, the actual maximum frames per second can be accessed by the property maxFrameRate
 */
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

/**
 * @brief Specify the resolution for capturing, what needs to note is that the preferredSessionPreset is not guaranteed to be applied succesfully, the actual resolution can be accessed by the property sessionPreset
 */
@property (nonatomic, strong) AVCaptureSessionPreset preferredSessionPreset;

/**
 * @brief Specify the Camera position for capturing, what needs to note is that the preferredDevicePosition is not guaranteed to be applied succesfully, the actual Camera position can be accessed by the property devicePosition
 */
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

/**
 * @brief Specify the orientation of the camera, what needs to note is that the preferredVideoOrientation is not guaranteed to be applied succesfully, the actual Camera orientation can be accessed by the property videoOrientation
 */
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

/**
 * @brief Specify the video zoom factor of the camera, what needs to note is that the preferredVideoZoomFactor is not guaranteed to be applied succesfully, the actual video zoom factor can be accessed by the property videoZoomFactor
 */
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

/**
 * @brief Specify the continuousAutoFocusEnable status of the camera, what needs to note is that the preferredContinuousAutoFocusEnable is not guaranteed to be applied succesfully, the actual continuousAutoFocusEnable can be accessed by the property continuousAutoFocusEnable
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;

/**
 * @brief Specify the preferredFocusPointOfInterest status of the camera, what needs to note is that the preferredFocusPointOfInterest is not guaranteed to be applied succesfully, the actual focusPointOfInterest can be accessed by the property focusPointOfInterest
 */
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

/**
 * @brief Specify the preferredContinuousAutoExposureEnable of the camera, what needs to note is that the preferredContinuousAutoExposureEnable is not guaranteed to be applied succesfully, the actual continuousAutoExposureEnable can be accessed by the property continuousAutoExposureEnable
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;

/**
 * @brief Specify the preferredExposurePointOfInterest of the camera, what needs to note is that the preferredExposurePointOfInterest is not guaranteed to be applied succesfully, the actual exposurePointOfInterest can be accessed by the property exposurePointOfInterest
 */
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

@end

#endif
