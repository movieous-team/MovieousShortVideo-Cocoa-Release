//
//  MovieousCamera.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/9/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousCameraConfiguration.h>
#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>
#import "MovieousGPUImage.h"
#import <MovieousBase/MovieousCaptureEffect.h>

typedef void(^SnapshotCompletionHandler)(UIImage *image);

@class MovieousCamera;
@protocol MovieousCameraDelegate <NSObject>

@optional

- (void)camera:(MovieousCamera *)camera didFocusAtPoint:(CGPoint)point;
/// 必须同步获取 pixelBuffer 并且 lock 住 frameBuffer 直到使用完毕，不然 frameBuffer 会被 frameBuffer 池回收，导致图像结果出现问题
- (void)camera:(MovieousCamera *)camera didGetProcessedFramebuffer:(MovieousGPUImageFramebuffer *)frameBuffer sampleTimingInfo:(CMSampleTimingInfo)sampleTimingInfo;

@end

@interface MovieousCamera : NSObject

/**
 * @brief Effects applied to recorder.
 */
@property (nonatomic, weak) id<MovieousCameraDelegate> delegate;
@property (nonatomic, strong, readonly) UIView *previewView;
@property (nonatomic, assign, readonly) BOOL running;
@property (nonatomic, assign) CGSize size;
@property (nonatomic, copy) NSArray<id<MovieousCaptureEffect>> *captureEffects;
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;
@property (nonatomic, assign) BOOL mirrorFrontPreview;
@property (nonatomic, assign) BOOL mirrorBackPreview;
@property (nonatomic, assign) BOOL mirrorFrontEncoded;
@property (nonatomic, assign) BOOL mirrorBackEncoded;
@property (nonatomic, assign) BOOL touchToFocusExposureEnabled;
@property (nonatomic, assign) BOOL innerFocusViewEnabled;

@property (nonatomic, assign, readonly) AVCaptureTorchMode torchMode;
@property (nonatomic, assign) AVCaptureTorchMode preferredTorchMode;

@property(nonatomic, readonly) NSArray<AVFrameRateRange *> *videoSupportedFrameRateRanges;

@property (nonatomic, assign, readonly) Float64 minFrameRate;
@property (nonatomic, assign) Float64 preferredMinFrameRate;

@property (nonatomic, assign, readonly) Float64 maxFrameRate;
@property (nonatomic, assign) Float64 preferredMaxFrameRate;

@property (nonatomic, strong, readonly) AVCaptureSessionPreset sessionPreset;
@property (nonatomic, assign) AVCaptureSessionPreset preferredSessionPreset;

@property (nonatomic, assign, readonly) AVCaptureDevicePosition devicePosition;
@property (nonatomic, assign) AVCaptureDevicePosition preferredDevicePosition;

@property (nonatomic, assign, readonly) AVCaptureVideoOrientation videoOrientation;
@property (nonatomic, assign) AVCaptureVideoOrientation preferredVideoOrientation;

@property (nonatomic, assign, readonly) CGFloat videoMaxZoomFactor;
@property (nonatomic, assign, readonly) CGFloat videoZoomFactor;
@property (nonatomic, assign) CGFloat preferredVideoZoomFactor;

@property (nonatomic, assign, readonly) BOOL continuousAutoFocusEnable;
@property (nonatomic, assign) BOOL preferredContinuousAutoFocusEnable;
@property (nonatomic, assign, readonly) CGPoint focusPointOfInterest;
@property (nonatomic, assign) CGPoint preferredFocusPointOfInterest;

@property (nonatomic, assign, readonly) BOOL continuousAutoExposureEnable;
@property (nonatomic, assign) BOOL preferredContinuousAutoExposureEnable;
@property (nonatomic, assign, readonly) CGPoint exposurePointOfInterest;
@property (nonatomic, assign) CGPoint preferredExposurePointOfInterest;

- (instancetype)initWithCameraConfiguration:(id<MovieousCameraConfiguration>)cameraConfiguration error:(NSError **)outError;
- (instancetype)initWithCameraConfiguration:(id<MovieousCameraConfiguration>)cameraConfiguration eaglContext:(EAGLContext *)context error:(NSError **)outError;

- (void)startWithCompletion:(void(^)(BOOL granted, NSError *error))completion;
- (void)stop;

- (void)snapshotWithCompletion:(SnapshotCompletionHandler)completionHandler;
- (void)switchCamera;

@end

