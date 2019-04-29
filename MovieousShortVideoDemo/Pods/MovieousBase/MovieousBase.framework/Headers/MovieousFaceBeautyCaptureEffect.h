//
//  MovieousFaceBeautyCaptureEffect.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/4/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousBase/MovieousCaptureEffect.h>

/**
 * The face beautification filter effect.
 */
@interface MovieousFaceBeautyCaptureEffect : NSObject
<
MovieousCaptureEffect
>

/**
 * The beauty level to use, which ranges between 0 and 1.
 */
@property (nonatomic, assign) CGFloat beautyLevel;

/**
 * The bright level to use, which ranges between 0 and 1.
 */
@property (nonatomic, assign) CGFloat brightLevel;

/**
 * The tone level to use, which ranges between 0 and 1.
 */
@property (nonatomic, assign) CGFloat toneLevel;

/**
 * Initiate the MovieousFaceBeautyCaptureEffect with another MovieousFaceBeautyCaptureEffect object.
 *
 * @param faceBeautyCaptureEffect Another MovieousFaceBeautyCaptureEffect used to initiate the instance.
 *
 * @return The initialized MovieousFaceBeautyCaptureEffect instance.
 */
- (instancetype)initWithFaceBeautyCaptureEffect:(MovieousFaceBeautyCaptureEffect *)faceBeautyCaptureEffect;

@end
