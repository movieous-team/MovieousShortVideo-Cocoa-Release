//
//  MLTypeDefines.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/// Scaling mode of MLController's preview content
typedef NS_ENUM(NSInteger, MovieousScalingMode) {
    /// Non-uniform scale. Both render dimensions will exactly match the visible bounds
    MovieousScalingModeFill,
    /// Uniform scale until one dimension fits
    MovieousScalingModeAspectFit,
    /// Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    MovieousScalingModeAspectFill
};

typedef struct {
    NSTimeInterval startTime;
    NSTimeInterval duration;
} MovieousTimeRange;

extern MovieousTimeRange kMovieousTimeRangeDefault;

MovieousTimeRange MovieousTimeRangeMake(NSTimeInterval startTime, NSTimeInterval duration);

BOOL MovieousTimeRangeIsEqual(MovieousTimeRange time1,MovieousTimeRange time2);

BOOL MovieousTimeRangeIsDefault(MovieousTimeRange timeRange);

CMTimeRange MovieousGetCMTimeRange(MovieousTimeRange timeRange, int32_t timeScale);

MovieousTimeRange MovieousGetMovieousTimeRange(CMTimeRange timeRange);
