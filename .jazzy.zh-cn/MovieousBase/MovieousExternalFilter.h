//
//  MovieousExternalFilter.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/**
 * @brief The external filter effect protocol, which should be followed by all of the external filters.
 */
@protocol MovieousExternalFilter
<
NSObject
>

@required
/**
 * @brief Generate a shared external filter object
 * @return Generated external filter object
 */
+ (instancetype)sharedInstance;
@optional

/**
 * @brief Process video data
 * @param pixelBuffer Pending video data
 * @param sampleTimingInfo Timestamp of pending video data
 * @return Video data after processing, can feedback the pending video data directly, which is, without any processing.
 * @warning Do not modify pixelBuffer content directly, you must return a pixel buffer different from the original one
 */
- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)pixelBuffer sampleTimingInfo:(CMSampleTimingInfo)sampleTimingInfo;

@end
