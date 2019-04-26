//
//  MSVTimeEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/2/22.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 时间特效类型。
 */
@protocol MSVTimeEditorEffect
<
NSObject,
NSCopying
>

@required

/**
 * 自定义 ID 字段，供用户使用来区分不同的对象类型。
 */
@property (nonatomic, strong) NSString *ID;

/**
 * 你希望应用事件特效的范围。
 */
@property (nonatomic, assign) MSVTimeEffectScope scope;

/**
 * 你希望应用事件特效的主轨时间区间。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
