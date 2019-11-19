//
//  MovieousExternalFilterCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousCaptureBase/MovieousExternalFilter.h>
#import <MovieousCaptureBase/MovieousCaptureEffect.h>
#import <MovieousBase/MovieousObject.h>

/**
 * The external filter effect.
 */
@interface MovieousExternalFilterCaptureEffect : MovieousObject
<
MovieousCaptureEffect
>

/**
 *  The external filter class.
 */
@property (nonatomic, assign) Class<MovieousExternalFilter> externalFilterClass;

/**
 * Initiate the MovieousExternalFilterCaptureEffect with another MovieousExternalFilterCaptureEffect object.
 *
 * @param externalFilterCaptureEffect Another MovieousExternalFilterCaptureEffect used to initiate the instance.
 *
 * @return The initialized MovieousExternalFilterCaptureEffect instance.
 */
- (instancetype)initWithExternalFilterCaptureEffect:(MovieousExternalFilterCaptureEffect *)externalFilterCaptureEffect;

@end
