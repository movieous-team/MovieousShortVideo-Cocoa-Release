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
 * The scope in which you want to place this time effect.
 */
@property (nonatomic, assign) MSVTimeEffectScope scope;

/**
 * The time interval for applying an basic effect on the main track.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
