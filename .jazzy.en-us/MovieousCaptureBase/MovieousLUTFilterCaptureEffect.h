//
//  MovieousLUTFilterCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousCaptureBase/MovieousCaptureEffect.h>
#import <MovieousBase/MovieousObject.h>

/**
 * The LUT(look up table) filter effect.
 */
@interface MovieousLUTFilterCaptureEffect : MovieousObject
<
MovieousCaptureEffect
>

/**
 * LUT(look up table) image.
 */
@property (nonatomic, strong) UIImage *image;

/**
 * Initiate the MovieousLUTFilterCaptureEffect with another MovieousLUTFilterCaptureEffect object.
 *
 * @param LUTFilterCaptureEffect Another MovieousLUTFilterCaptureEffect used to initiate the instance.
 *
 * @return The initialized MovieousLUTFilterCaptureEffect instance.
 */
- (instancetype)initWithLUTFilterCaptureEffect:(MovieousLUTFilterCaptureEffect *)LUTFilterCaptureEffect;

@end
