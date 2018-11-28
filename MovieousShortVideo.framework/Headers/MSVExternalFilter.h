//
//  MSVExternalFilter.h
//  Movieous
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/**
 * @brief 外部滤镜效果协议，所有外部滤镜都需要遵守此协议
 */
@protocol MSVExternalFilter <NSObject>

@required
/**
 * @brief 生成一个共享的外部滤镜对象
 * @return 生成的外部滤镜对象
 */
+ (instancetype)sharedInstance;
@optional

/**
 * @brief 处理视频数据
 * @param pixelBuffer 待处理的视频数据
 * @param sampleTimingInfo 待处理视频数据的时间戳
 * @return 处理完成的视频数据，可以直接返回待处理的视频数据，即不进行任何处理
 */
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)pixelBuffer sampleTimingInfo:(CMSampleTimingInfo)sampleTimingInfo;

@end
