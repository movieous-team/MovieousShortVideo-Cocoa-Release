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
 * Time editor effect.
 */
@protocol MSVTimeEditorEffect
<
NSObject,
NSCopying
>

@required

/**
 * User-defined ID field, business usage is used to distinguish objects.
 */
@property (nonatomic, strong) NSString *ID;

/**
 * The scope in which you want to place this time effect.
 */
@property (nonatomic, assign) MSVTimeEffectScope scope;

/**
 * The time interval for applying the time effect on the main track.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
