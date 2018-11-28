//
//  MSVClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/29.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 媒体片段
 */
@protocol MSVClip <NSObject>

/**
 * @brief 媒体片段的 URL，只支持本地文件
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief 媒体片段在主轨中的时间区间
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * @brief 验证草稿是否有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
