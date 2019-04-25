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
 * @brief LUT(look up table) image
 */
@property (nonatomic, strong) UIImage *image;

- (instancetype)initWithLUTFilterCaptureEffect:(MovieousLUTFilterCaptureEffect *)LUTFilterCaptureEffect;

@end
