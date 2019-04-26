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

NS_ASSUME_NONNULL_BEGIN

/**
 * 录制视频配置对象
 */
@interface MSVRecorderVideoConfiguration : NSObject
<
MovieousCameraConfiguration
>

/**
 * 视频输入源类型。
 * 默认为 MSVAudioSourceMicrophone。
 */
@property (nonatomic, assign) MSVVideoSource source;

#pragma mark - camera configurations
/**
 * Video 编码时的视频分辨率，默认 (1280, 720)。
 *
 * @discussion 需要注意的是，这个参数影响的是视频编码时的分辨率，而非摄像头采集到数据的预览大小，传递给编码器的图像尺寸与此尺寸不同时，会按照保持比例并填充的方式生成最终的视频，从而确保图像不会出现压缩的现象（但编码视频的比例与采集视频的比例不同时会出现裁剪的现象）。
 */
@property (nonatomic, assign) CGSize size;

/**
 * 采集时应用的特效组。
 */
@property (nonatomic, strong) NSArray<id<MovieousCaptureEffect>> *captureEffects;

/**
 * 当 size（编码时的视频分辨率） 和 preview 的尺寸比例不一致时使用的填充模式。
 * 默认为 MovieousScalingModeAspectFill。
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/*!
 * 是否对前置摄像头预览进行镜像处理。
 * 默认为 YES。
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/*!
 * 是否对后置摄像头预览进行镜像处理。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/*!
 * 是否对前置摄像头编码的视频进行镜像处理。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/*!
 * 是否对后置摄像头编码的视频进行镜像处理。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * 是否开启点击屏幕来设置对焦和曝光参考点。
 * 默认为 YES。
 */
@property (nonatomic, assign) BOOL touchToFocusExposureEnabled;

/**
 * 是否开启内置的对焦视图。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL innerFocusViewEnabled;

/**
 * 指定期望的摄像头手电筒模式，需要注意的是 preferredTorchMode 的值不一定能够被成功应用，实际的手电筒模式可以通过 MSVRecorder.torchMode 来获取。
 * 默认为 AVCaptureTorchModeAuto。
 */
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

/**
 * 指定期望的最小采集帧率，需要注意的是 preferredMinFrameRate 的值不一定能够被成功应用，实际的最小采集帧率可以通过 MSVRecorder.minFrameRate 来获取。
 * 默认为 24。
 */
@property (nonatomic, assign) Float64 preferredMinFrameRate;

/**
 * 指定期望的最大采集帧率，需要注意的是 preferredMaxFrameRate 的值不一定能够被成功应用，实际的最大采集帧率可以通过 MSVRecorder.maxFrameRate 来获取。
 * 默认为 30。
 */
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

/**
 * 指定期望的采集预设分辨率，需要注意的是 preferredSessionPreset 的值不一定能够被成功应用，实际的采集预设分辨率可以通过 MSVRecorder.sessionPreset 来获取。
 * 默认为 AVCaptureSessionPresetHigh。
 */
@property (nonatomic, strong) AVCaptureSessionPreset preferredSessionPreset;

/**
 * 指定期望的摄像头位置，需要注意的是 preferredDevicePosition 的值不一定能够被成功应用，实际的摄像头位置可以通过 MSVRecorder.devicePosition 来获取。
 * 默认为 AVCaptureDevicePositionFront。
 */
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

/**
 * 指定期望的摄像头方向，需要注意的是 preferredVideoOrientation 的值不一定能够被成功应用，实际的摄像头方向可以通过 MSVRecorder.videoOrientation 来获取。
 * 默认为 AVCaptureVideoOrientationPortrait。
 */
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

/**
 * 指定期望的视频缩放比例，需要注意的是 preferredVideoZoomFactor 的值不一定能够被成功应用，实际的视频缩放比例可以通过 MSVRecorder.videoZoomFactor 来获取。
 * 默认为 1。
 */
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

/**
 * 指定期望是否开启持续自动对焦，需要注意的是 preferredContinuousAutoFocusEnable 的值不一定能够被成功应用，实际是否开启持续自动对焦可以通过 MSVRecorder.continuousAutoFocusEnable 来获取。
 * 默认为 YES。
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;

/**
 * 指定期望的对焦参考点，需要注意的是 preferredFocusPointOfInterest 的值不一定能够被成功应用，实际的对焦参考点可以通过 MSVRecorder.focusPointOfInterest 来获取。
 * 默认为 CGPointMake(0。5, 0。5)。
 */
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

/**
 * 指定期望是否开启持续自动曝光调节，需要注意的是 preferredContinuousAutoExposureEnable 的值不一定能够被成功应用，实际是否开启持续自动曝光调节可以通过 MSVRecorder.continuousAutoExposureEnable 来获取。
 * 默认为 YES。
 */
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;

/**
 * 指定期望的曝光参考点，需要注意的是 preferredExposurePointOfInterest 的值不一定能够被成功应用，实际的曝光参考点可以通过 MSVRecorder.exposurePointOfInterest 来获取。
 * 默认为 CGPointMake(0.5, 0.5)。
 */
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

#pragma mark - encoder configurations
/**
 * Average video encoding rate.
 * The default is 1024 * 1024(1 mbps).
 *
 * @discussion unit is bps(Bits per Second). The parameters of the video encoding are not constant values in the actual process, so the average video encoding rate can be set only.
 */
@property (nonatomic, assign) NSUInteger averageVideoBitRate;

/**
 * The Maximum Interval of video encoding Keyframe. (GOP).
 * The default is 0 which means that the encoder decide what videoMaxKeyframeInterval to use.
 *
 * @discussion During h.264 encoding, The maximum number of frames between two keyframes typically is twice or three times than the fps. The default is 2*fps
 */
@property (nonatomic, assign) NSUInteger videoMaxKeyframeInterval;

/**
 * During H.264 encoding, the Profile Level will be used.
 * The default is AVVideoProfileLevelH264HighAutoLevel.
 *
 * @discussion By default, AVVideoProfileLevelH264HighAutoLevel is used, if you have additional requirements for video encoding, you can change it yourself if understanding that the impacts  from this parameter.
 *
 * @warning When you are not sure about the impact of this parameter change on resolution requirements, code rate, etc., please do not change it.
 */
@property (nonatomic, copy) NSString *videoProfileLevel;

/**
 * Enables or disables frame reordering.
 * The default is NO.
 *
 * @discussion In order to achieve the best compression while maintaining image quality, some video encoders can reorder frames.  This means that the order in which the frames will be emitted and stored (the decode order) will be different from the order in which they are presented to the video encoder (the display order). Encoding using frame reordering requires more system resources than encoding without frame reordering, so encoding performance should be taken into account when deciding whether to enable frame reordering.  This is especially important when encoding video data from a real-time source, such as AVCaptureVideoDataOutput.  In this situation, using a value of NO may yield the best results.
*/
@property (nonatomic, assign) BOOL allowFrameReordering;

/**
 * Create a default configuration of the MSVVideoConfiguration instance.
 *
 * @return The created default MSVVideoConfiguration object
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
