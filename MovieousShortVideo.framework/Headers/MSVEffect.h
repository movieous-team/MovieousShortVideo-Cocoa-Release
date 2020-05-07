//
//  MSVEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2020/2/25.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>
#import "MSVClipOrEffect.h"

NS_ASSUME_NONNULL_BEGIN

@interface MSVEffect : MovieousObject
<
MSVMutableClipOrEffect,
NSCopying
>

/**
 * 特效在主轨中应用的时间区间。
 * 单位为 us。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 特效在主轨中开始时间，与 timeRangeAtMainTrack.start 相同。
 * 单位为 us。
 */
@property (nonatomic, assign) MovieousTime startTimeAtMainTrack;

/**
 * 特效在主轨中开始时间，与 timeRangeAtMainTrack.duration 相同。
 * 单位为 us。
 */
@property (nonatomic, assign) MovieousTime durationAtMainTrack;

/**
 * 用已经存在的一个 MSVEffect 对象初始化一个 MSVEffect 对象。
 *
 * @param effect 用于初始化的 MSVEffect 的对象。
 *
 * @return 返回初始化后的 MSVEffect 对象。
 */
- (instancetype)initWithEffect:(MSVEffect *)effect;

@end

NS_ASSUME_NONNULL_END
