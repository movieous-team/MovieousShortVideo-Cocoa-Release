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
 * @brief 视频录制配置类
 */
@interface MSVRecorderVideoConfiguration : NSObject
<
MovieousCameraConfiguration
>

/**
 * @brief 视频输入源，默认为 MSVAudioSourceMicrophone
 */
@property (nonatomic, assign) MSVVideoSource source;

/**
 * @brief 使用 MSVVideoSourceCamera 时采集的视频数据的帧率，默认为 30
 */
@property (assign, nonatomic) NSUInteger frameRate;

/**
 * @brief 使用 MSVVideoSourceCamera 时采集的视频的分辨率，默认为 AVCaptureSessionPresetHigh
 */
@property (strong, nonatomic) AVCaptureSessionPreset cameraResolution;

/**
 * @brief 使用 MSVVideoSourceCamera 时前置预览是否开启镜像，默认为 YES
 */
@property (assign, nonatomic) BOOL mirrorFrontPreview;

/**
 * @brief 使用 MSVVideoSourceCamera 时后置预览是否开启镜像，默认为 NO
 */
@property (assign, nonatomic) BOOL mirrorBackPreview;

/**
 * @brief 使用 MSVVideoSourceCamera 时前置摄像头，录制的流是否开启镜像，默认 NO
 */
@property (assign, nonatomic) BOOL mirrorFrontEncoded;

/**
 * @brief 使用 MSVVideoSourceCamera 时后置摄像头，录制的流是否开启镜像，默认 NO
 */
@property (assign, nonatomic) BOOL mirrorBackEncoded;

/**
 * @brief 使用 MSVVideoSourceCamera 时采集摄像头位置，默认为 AVCaptureDevicePositionBack
 */
@property (assign, nonatomic) AVCaptureDevicePosition cameraPosition;

/**
 * @brief 使用 MSVVideoSourceCamera 时的采集摄像头的旋转方向，默认为 AVCaptureVideoOrientationPortrait
 */
@property (assign, nonatomic) AVCaptureVideoOrientation cameraOrientation;

/**
 * @brief   编码时的视频分辨率，默认 (1280, 720)
 * @discussion 需要注意的是，这个参数影响的是视频编码时的分辨率，而非摄像头采集到数据的预览大小，传递给编码器的图像尺寸与此尺寸不同时，会按照保持比例并填充的方式生成最终的视频，从而确保图像不会出现压缩的现象（但编码视频的比例与采集视频的比例不同时会出现裁剪的现象）。
 */
@property (assign, nonatomic) CGSize size;

/**
 * @brief 平均视频编码码率。默认为 1024*1000
 * @discussion 单位为 bps(Bits per Second)。该参数的视频编码实际过程中，并不是恒定的数值，所以只能设定平均视频编码码率。
 */
@property (nonatomic, assign) NSUInteger averageVideoBitRate;

/**
 * @brief 视频编码关键帧最大间隔（GOP）。
 * @discussion h.264 编码时，两个关键帧之间间隔的最多的帧数，一般为 fps 的两倍或者三倍。默认为 2*fps
 */
@property (nonatomic, assign) NSUInteger videoMaxKeyframeInterval;

/**
 * @brief H.264 编码时使用的 Profile Level。
 * @discussion 默认情况下使用 AVVideoProfileLevelH264HighAutoLevel，如果对于视频编码有额外的需求并且知晓该参数带来的影响可以自行更改。
 * @warning 当你不清楚该参数更改对分辨率要求，码率等影响时，请不要随意更改。
 */
@property (nonatomic, copy) NSString *videoProfileLevel;

/**
 * @brief 创建一个默认配置的 MSVVideoConfiguration 实例.
 * @return 创建的默认 MSVVideoConfiguration 对象
 */
+ (instancetype)defaultConfiguration;

/**
 * @brief 验证对象是否有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
