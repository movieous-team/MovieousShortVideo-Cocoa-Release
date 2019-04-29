//
//  MLTypeDefines.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/// Scaling mode to
typedef NS_ENUM(NSInteger, MovieousScalingMode) {
    /// Non-uniform scale. Both render dimensions will exactly match the visible bounds
    MovieousScalingModeFill,
    /// Uniform scale until one dimension fits
    MovieousScalingModeAspectFit,
    /// Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    MovieousScalingModeAspectFill
};

/// Time range
typedef struct {
    /// The start time of the time range
    NSTimeInterval startTime;
    /// The duration of the time range
    NSTimeInterval duration;
} MovieousTimeRange;

/// The default time range
extern MovieousTimeRange kMovieousTimeRangeDefault;

/// Make a time range with start time and duration
MovieousTimeRange MovieousTimeRangeMake(NSTimeInterval startTime, NSTimeInterval duration);

/// Decide whether two time range are equal
BOOL MovieousTimeRangeIsEqual(MovieousTimeRange timeRange1,MovieousTimeRange timeRange2);

/// Decide whether a time range is default time range
BOOL MovieousTimeRangeIsDefault(MovieousTimeRange timeRange);

/// Make a CMTimeRange with MovieousTimeRange
CMTimeRange CMTimeRangeMakeMovieousTimeRange(MovieousTimeRange timeRange, int32_t timeScale);

/// Make a MovieousTimeRange with CMTimeRange
MovieousTimeRange MovieousTimeRangeMakeWithCMTimeRange(CMTimeRange timeRange);

/**
 * Snapshot completion callback handler.
 *
 * @param image The captured image.
 * @param error The specific error if any.
 */
typedef void(^MovieousSnapshotCompletionHandler)(UIImage *_Nullable image, NSError *_Nullable error);
