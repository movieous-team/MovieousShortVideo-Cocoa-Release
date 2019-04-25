//
//  MovieousExternalFilterCaptureEffect.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousExternalFilter.h>
#import <MovieousBase/MovieousCaptureEffect.h>

@interface MovieousExternalFilterCaptureEffect : NSObject
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
