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

/**
 * 摄像头配置对象。
 */
@protocol MovieousCameraConfiguration
<
NSObject
>

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
 * 切换摄像头时是否进行模糊化过渡
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL blurSwitch;

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
 * 指定期望的摄像头闪光灯模式，需要注意的是 preferredFlashMode 的值不一定能够被成功应用，实际的闪光灯模式可以通过 MSVRecorder.flashMode 来获取。
 * 默认为 AVCaptureFlashModeAuto。
 */
@property (nonatomic, assign) AVCaptureFlashMode preferredFlashMode;

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

@end

#endif
