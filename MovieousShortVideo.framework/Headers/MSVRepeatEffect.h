//
//  MSVRepeatEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/11/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 反复特效
 */
@interface MSVRepeatEffect : NSObject

/**
 * @brief 用户自定义 ID 字段，业务使用用于区分对象
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief 在主轨当中应用反复效果的时间区间
 * @warning 需要注意的是如果插入多个跟时间有关的特效时（MSVRepeatEffect 及 MSVSpeedEffect），后插入的时间特效中 timeRangeAtMainTrack 应当以之前所有特效应用之后的时间轴为标准
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * @brief 反复次数
 */
@property (nonatomic, assign) NSUInteger count;

@end
