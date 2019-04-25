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
 * @brief
 * 编码时的视频分辨率，默认 (1280, 720)
 * 
 * @discussion 
 * 需要注意的是，这个参数影响的是视频编码时的分辨率，而非摄像头采集到数据的预览大小，传递给编码器的图像尺寸与此尺寸不同时，会按照保持比例并填充的方式生成最终的视频，从而确保图像不会出现压缩的现象（但编码视频的比例与采集视频的比例不同时会出现裁剪的现象）。
 */
@property (nonatomic, assign) CGSize size;

/**
 * @brief
 * 应用到 MSVRecorder 的特效
 */
@property (nonatomic, strong) NSArray<id<MovieousCaptureEffect>> *captureEffects;

/**
 * @brief 
 * 当你设置的 size 和预览的 UIView 的比例不一致时填充视频的模式
 * 默认为 MovieousScalingModeAspectFill
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/*!
 * 是否对前置摄像头的预览画面做镜像处理
 * 默认值为 YES
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/*!
 * 是否对后置摄像头的预览画面做镜像处理
 * 默认值为 NO
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/*!
 * 是否对前置摄像头编码后的图像做镜像处理
 * 默认为 NO
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/*!
 * 是否对后置摄像头编码后的图像做镜像处理
 * 默认为 NO
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * 是否开启点击屏幕调整对焦和曝光参考点的功能
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
