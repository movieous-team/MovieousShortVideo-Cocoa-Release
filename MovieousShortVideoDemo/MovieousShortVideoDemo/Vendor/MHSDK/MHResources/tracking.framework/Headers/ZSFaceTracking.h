//
//  ZSFaceTracking.h
//  zeuseefacenet
//
//  Created by flora on 2019/4/9.
//  Copyright © 2019 zeusee. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class ZSFace, UIImage;

@interface ZSFaceTracking : NSObject

- (instancetype)initWithAuthorizationKey:(NSString *)authorizationKey;

/**
 *  初始化第一帧，主要用于捕捉场景,一些追踪前的初始化工作，初始帧检测等工作。
 *  @param byteArray    RGB 格式的视频流，通常来自 - (void)captureOutput: didOutputSampleBuffer: fromConnection: 方法
 *  @param width   [in]预览视频流的宽度
 *  @param height  [in]预览视频流的高度
 */
- (void)faceTrackingInit:(unsigned char *)byteArray width:(int)width height:(int)height;

/**
 *  在初始化后第一帧的后，跟踪新的帧。在调用完 -(void)faceTrackingInit:width:height: 后每次调用此方法即可。
 *  @param byteArray    RGB 格式的视频流，通常来自 - (void)captureOutput: didOutputSampleBuffer: fromConnection: 方法
 *  @param width   [in]预览视频流的宽度
 *  @param height  [in]预览视频流的高度
 */
- (void)update:(unsigned char *)byteArray width:(int)width height:(int)height;

/**
 *  返回跟踪后的人脸列表，在调用完-(void)update:width:height 之后，会更新类内的 NSMutableArray<ZSFace *>，调用此方法可以获取在跟踪中的人脸列表。一般在调用完 -(void)update:width:height 之后，调用此方法来获取数据。
 *  @return 人脸实例列表
 */
- (NSMutableArray<ZSFace *>*)getTrackingInfo;

@end

NS_ASSUME_NONNULL_END
