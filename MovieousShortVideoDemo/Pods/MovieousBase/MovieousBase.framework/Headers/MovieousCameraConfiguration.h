//
//  MovieousCameraConfiguration.h
//  MovieousLive
//
//  Created by Chris Wang on 2018/9/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#ifndef MovieousCameraConfiguration_h
#define MovieousCameraConfiguration_h

#import <AVFoundation/AVFoundation.h>
#import "MovieousTypeDefines.h"

@protocol MovieousCameraConfiguration <NSObject>

@required
/*!
 * Number of maximum frames per seconds captured by the camera
 * Default to 30
 */
@property (nonatomic, assign) NSUInteger frameRate;

/*!
 * You may use an AVCaptureSessionPreset to set the resolution for camera output data
 * Default to AVCaptureSessionPresetHigh
 */
@property (nonatomic, strong) AVCaptureSessionPreset cameraResolution;

/**
 * @brief   Video resolution when encoding. Default to (1280, 720)
 * @discussion It should be noted that this parameter affects the resolution of the video encoding, rather than the preview size of the data captured by the camera. When the image size passed to the encoder is different from this size, it will be generated in the same way The video ensures that the image does not appear to be compressed (but the cropping phenomenon occurs when the ratio of the encoded video is different from the ratio of the captured video).
 */
@property (nonatomic, assign) CGSize size;

/**
 * The scaling mode you want to use if the aspect ratio of cameraResolution and size are not equal
 * Default to MovieousScalingModeAspectFill
 */
@property (nonatomic, assign) MovieousScalingMode scalingMode;

/*!
 * Turn mirrorFrontPreview means preview for front camera will be mirrored
 * Default to YES
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/*!
 * Turn mirrorBackPreview means preview for back camera will be mirrored
 * Default to NO
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/*!
 * Turn mirrorFrontStream means stream broadcasted for front camera will be mirrored
 * Default to NO
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/*!
 * Turn mirrorBackStream means stream broadcasted for back camera will be mirrored
 * Default to NO
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/*!
 * Indicates the physical position of camera on the system.
 * Default to AVCaptureDevicePositionFront
 */
@property (nonatomic, assign) AVCaptureDevicePosition cameraPosition;

/*!
 * Indicates the orientation of out put video.
 * Default to AVCaptureVideoOrientationPortrait
 */
@property (nonatomic, assign) AVCaptureVideoOrientation cameraOrientation;

/*!
 * Whether to allow to compromise some parameters which are not supported by the current device to ensure component initialization's success. Default to YES
 */
@property (nonatomic, assign) BOOL compromise;

@end

#endif
