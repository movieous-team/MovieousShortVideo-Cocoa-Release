//
//  MovieousTypeDefines.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/// Scaling mode type.
typedef NS_ENUM(NSInteger, MovieousScalingMode) {
    /// Non-uniform scale. Both render dimensions will exactly match the visible bounds
    MovieousScalingModeFill,
    /// Uniform scale until one dimension fits
    MovieousScalingModeAspectFit,
    /// Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    MovieousScalingModeAspectFill
};

/// Action to take when view is tapped.
typedef NS_ENUM(NSInteger, MovieousRecorderTapPreviewAction) {
    /// Take no action.
    MovieousRecorderTapPreviewActionNone = 0,
    /// Focus on the point tapped.
    MovieousRecorderTapPreviewActionFocus = 1 << 0,
    /// Exposure to the point tapped.
    MovieousRecorderTapPreviewActionExposure = 1 << 1,
    /// Show indicator on the point tapped.
    MovieousRecorderTapPreviewActionShowIndicator = 1 << 2,
    /// Focus on and exposure to the point tapped.
    MovieousRecorderTapPreviewActionFocusExposure = MovieousRecorderTapPreviewActionFocus | MovieousRecorderTapPreviewActionExposure,
    /// Focus on and show indicator on the point tapped.
    MovieousRecorderTapPreviewActionFocusShowIndicator = MovieousRecorderTapPreviewActionFocus | MovieousRecorderTapPreviewActionShowIndicator,
    /// Exposure to and show indicator on the point tapped.
    MovieousRecorderTapPreviewActionExposureShowIndicator = MovieousRecorderTapPreviewActionExposure | MovieousRecorderTapPreviewActionShowIndicator,
    /// Focus on, exposure to and show indicator on the point tapped.
    MovieousRecorderTapPreviewActionFocusExposureShowIndicator = MovieousRecorderTapPreviewActionFocus | MovieousRecorderTapPreviewActionExposure | MovieousRecorderTapPreviewActionShowIndicator
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
