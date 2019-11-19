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
 * Basic editor effect protocol.
 */
@protocol MSVEditorEffect
<
MovieousCaptureEffect
>

@required

/**
 * The time range to apply the effect.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
