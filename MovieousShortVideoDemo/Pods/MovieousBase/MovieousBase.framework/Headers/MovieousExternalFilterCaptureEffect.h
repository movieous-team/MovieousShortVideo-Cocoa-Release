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
 * @brief  The external filter class
 */
@property (nonatomic, assign) Class<MovieousExternalFilter> externalFilterClass;

@end
