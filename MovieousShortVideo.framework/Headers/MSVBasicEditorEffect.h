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
 * Basic effects class.
 */
@protocol MSVBasicEditorEffect
<
MovieousCaptureEffect
>

@required

/**
 * User-defined ID field, business usage is used to distinguish objects.
 */
@property (nonatomic, strong) NSString *ID;

/**
 * The time interval for applying an basic effect on the main track.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
