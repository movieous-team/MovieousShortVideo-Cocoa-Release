//
//  MovieousLUTFilterCaptureEffect.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousBase/MovieousCaptureEffect.h>

@interface MovieousLUTFilterCaptureEffect : NSObject
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
