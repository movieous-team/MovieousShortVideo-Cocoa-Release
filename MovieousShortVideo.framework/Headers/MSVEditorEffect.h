//
//  MSVEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/2/22.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <MovieousCaptureBase/MovieousCaptureBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 基本编辑器特效类。
 */
@protocol MSVEditorEffect
<
MovieousCaptureEffect
>

@required

/**
 * 特效在主轨中持续的时间范围。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
