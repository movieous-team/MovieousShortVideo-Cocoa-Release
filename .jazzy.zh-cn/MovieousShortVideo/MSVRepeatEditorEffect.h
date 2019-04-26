//
//  MSVRepeatEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/11/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVTimeEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 反复特效。
 */
@interface MSVRepeatEditorEffect : NSObject
<
MSVTimeEditorEffect
>

/**
 * 自定义 ID 字段，供用户使用来区分不同的对象类型。
 */
@property (nonatomic, strong) NSString *ID;

/**
 * 你希望应用反复特效的范围。
 */
@property (nonatomic, assign) MSVTimeEffectScope scope;

/**
 * 在主轨当中需要应用速度效果的时间区间，这个时间区间是指未应用速度效果前的时间区间。
 *
 * @warning 需要注意的是如果插入多个跟时间有关的特效时（MSVRepeatEffect 及 MSVSpeedEffect），后插入的时间特效中 timeRangeAtMainTrack 应当以之前所有特效应用之后的时间轴为标准
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 反复次数。
 */
@property (nonatomic, assign) NSUInteger count;

@end

NS_ASSUME_NONNULL_END
