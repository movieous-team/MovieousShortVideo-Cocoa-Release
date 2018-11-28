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

@protocol MovieousCameraConfiguration <NSObject>

@required
/*!
 * Number of maximum frames per seconds captured by the camera
 * Default to 30
 */
@property (nonatomic, assign) NSUInteger frameRate;

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
 * You may use an AVCaptureSessionPreset to set the resolution for camera output data
 * Default to AVCaptureSessionPresetHigh
 */
@property (nonatomic, strong) AVCaptureSessionPreset cameraResolution;

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

@property (assign, nonatomic) CGSize size;

@end

#endif
