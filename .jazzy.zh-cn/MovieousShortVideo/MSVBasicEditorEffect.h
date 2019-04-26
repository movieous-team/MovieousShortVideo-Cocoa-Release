//
//  MSVBasicEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/2/22.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 基本编辑器特效类。
 */
@protocol MSVBasicEditorEffect
<
MovieousCaptureEffect
>

@required

/**
 * 自定义 ID 字段，供用户使用来区分不同的对象类型。
 */
@property (nonatomic, strong) NSString *ID;

/**
 * 特效在主轨中持续的时间范围。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
