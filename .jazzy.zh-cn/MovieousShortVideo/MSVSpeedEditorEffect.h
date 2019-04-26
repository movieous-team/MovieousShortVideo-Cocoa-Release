//
//  MSVSpeedEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/11/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVTimeEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Speed effects.
 */
@interface MSVSpeedEditorEffect : NSObject
<
MSVTimeEditorEffect
>

/**
 * 自定义 ID 字段，供用户使用来区分不同的对象类型。
 */
@property (nonatomic, strong) NSString *ID;

/**
 * The scope in which you want to place this time effect.
 */
@property (nonatomic, assign) MSVTimeEffectScope scope;

/**
 * 在主轨当中需要应用速度效果的时间区间，这个时间区间是指未应用速度效果前的时间区间。
 *
 * @warning 需要注意的是如果插入多个跟时间有关的特效时（MSVRepeatEffect 及 MSVSpeedEffect），后插入的时间特效中 timeRangeAtMainTrack 应当以之前所有特效应用之后的时间轴为标准。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 速度，添加速度特效后在相应特效时间区间内的实际速度将变为区间内各 MSVMainTrackClip 对象的 speed 乘以特效 speed
 */
@property (nonatomic, assign) float speed;

@end

NS_ASSUME_NONNULL_END
