//
//  MSVVideoConfiguration.h
//  MSVShortVideoKit
//
//  Created by Chris Wang on 18/3/1.
//  Copyright © 2018年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "MSVTypeDefines.h"
#import <MovieousBase/MovieousBase.h>

/**
 * @brief Video configuration class
 */
@interface MSVRecorderVideoConfiguration : NSObject
<
MovieousCameraConfiguration
>

/**
 * @brief Video input source, the default is MSVAudioSourceMicrophone
 */
@property (nonatomic, assign) MSVVideoSource source;

#pragma mark - camera configurations
/**
 * @brief The frame rate of the video data captured when using MSVVideoSourceCamera, the default is 30
 */
@property (nonatomic, assign) NSUInteger frameRate;

/**
 * @brief The resolution of the video captured when using MSVVideoSourceCamera, the default is AVCaptureSessionPresetHigh
 */
@property (nonatomic, strong) AVCaptureSessionPreset cameraResolution;

/**
 * @brief   Video resolution when encoding, default (1280, 720)
 * @discussion It should be noted that this parameter affects the resolution of the video encoding, rather than the preview size of the data captured by the camera. When the image size passed to the encoder is different from this size, it will be generated in the same way The video ensures that the image does not appear to be compressed (but the cropping phenomenon occurs when the ratio of the encoded video is different from the ratio of the captured video).
 */
@property (nonatomic, assign) CGSize size;

/**
 * The scaling mode you want to use if the aspect ratio of cameraResolution and size are not equal.
 * The default is MovieousScalingModeAspectFill
 */
@property (nonatomic, assign) MovieousScalingMode scalingMode;

/**
 * @brief Front preview mirror is enabled or not when using MSVVideoSourceCamera. The default is YES.
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/**
 * @brief Rear preview mirror is enabled or not when using MSVVideoSourceCamera, the default is NO
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/**
 * @brief When using MSVVideoSourceCamera, Whether the recorded stream is enable to mirror in the front camera,  the default is NO
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/**
 * @brief When using MSVVideoSourceCamera, whether the recorded stream is enabled to mirror in the rear camera, the default NO
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * @brief The captured camera position when using MSVVideoSourceCamera, the default is AVCaptureDevicePositionBack
 */
@property (nonatomic, assign) AVCaptureDevicePosition cameraPosition;

/**
 * @brief The camera rotation orientation captured when using MSVVideoSourceCamera, the default is AVCaptureVideoOrientationPortrait
 */
@property (nonatomic, assign) AVCaptureVideoOrientation cameraOrientation;

/*!
 * Whether to allow to compromise some parameters which are not supported by the current device to ensure component initialization's success. The default is YES
 */
@property (nonatomic, assign) BOOL compromise;

#pragma mark - encoder configurations
/**
 * @brief Average video encoding rate. The default is 1024*1000
 * @discussion unit is bps(Bits per Second). The parameters of the video encoding are not constant values in the actual process, so the average video encoding rate can be set only.
 */
@property (nonatomic, assign) NSUInteger averageVideoBitRate;

/**
 * @brief The Maximum Interval of video encoding Keyframe. (GOP)
 * @discussion During h.264 encoding, The maximum number of frames between two keyframes typically is twice or three times than the fps. The default is 2*fps
 */
@property (nonatomic, assign) NSUInteger videoMaxKeyframeInterval;

/**
 * @brief During H.264 encoding, the Profile Level will be used.
 * @discussion By default, AVVideoProfileLevelH264HighAutoLevel is used, if you have additional requirements for video encoding, you can change it yourself if understanding that the impacts  from this parameter.
 * @warning When you are not sure about the impact of this parameter change on resolution requirements, code rate, etc., please do not change it.
 */
@property (nonatomic, copy) NSString *videoProfileLevel;

/*!
@abstract
Enables or disables frame reordering.
@discussion
In order to achieve the best compression while maintaining image quality, some video encoders can reorder frames.  This means that the order in which the frames will be emitted and stored (the decode order) will be different from the order in which they are presented to the video encoder (the display order).

Encoding using frame reordering requires more system resources than encoding without frame reordering, so encoding performance should be taken into account when deciding whether to enable frame reordering.  This is especially important when encoding video data from a real-time source, such as AVCaptureVideoDataOutput.  In this situation, using a value of NO may yield the best results.

The default is NO.
*/
@property (nonatomic, assign) BOOL allowFrameReordering;

/**
 * @brief Create a default configuration of the MSVVideoConfiguration instance.
 * @return The created default MSVVideoConfiguration object
 */
+ (instancetype)defaultConfiguration;

/**
 * @brief Verify the object is valid or not
 * @param outError If an error occurs, return the error that occurred
 * @return Valid operation return YES, invalid operation return NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
