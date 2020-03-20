//
//  MSVTimeDomainObject.h
//  MovieousShortVideo
//
//  Created by WangSiyu on 2020/3/6.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MSVTimeDomainObject <NSObject>

/**
 * 片段实际在主轨中实际展示的时间区间。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 片段实际在主轨中实际展示的开始时间，当片段加入 MSVDraft 之后才能获取到该值。
 */
@property (nonatomic, assign) MovieousTime startTimeAtMainTrack;

/**
 * 片段实际在主轨中的时间长度，当片段类型是音视频时，durationAtMainTrack 参数和 speed 参数互相影响，调整 durationAtMainTrack 将会影响 speed，具体为：speed = timeRange.duration / durationAtMainTrack.
 * 默认为根据 timeRange 和 speed 自动计算出来的数据。
 */
@property (nonatomic, assign) MovieousTime durationAtMainTrack;

@end

NS_ASSUME_NONNULL_END
