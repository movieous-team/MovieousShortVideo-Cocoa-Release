//
//  MovieousExternalFilter.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/**
 * 外部滤镜协议，所有外部滤镜都需要实现该协议。
 */
@protocol MovieousExternalFilter
<
NSObject
>

@required
/**
 * 生成一个共享的外部滤镜对象。
 * 
 * @return 生成的外部滤镜对象。
 */
+ (instancetype)sharedInstance;

@optional
/**
 * 处理视频数据。
 * 
 * @param pixelBuffer 待处理的视频数据。
 * @param sampleTimingInfo 待处理视频数据的时间信息。
 *
 * @return 处理后的视频数据，也可以直接将未处理的原始数据返回。
 *
 * @warning 请不要直接修改 pixelBuffer 的内容，你需要返回一个与原 pixelBuffer 不同的 CVPixelBufferRef。
 */
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)pixelBuffer sampleTimingInfo:(CMSampleTimingInfo)sampleTimingInfo;

@end
