//
//  MovieousFaceBeautyCaptureEffect.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/4/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousBase/MovieousCaptureEffect.h>

@interface MovieousFaceBeautyCaptureEffect : NSObject
<
MovieousCaptureEffect
>

@property (nonatomic, assign) CGFloat beautyLevel;
@property (nonatomic, assign) CGFloat brightLevel;
@property (nonatomic, assign) CGFloat toneLevel;

@end
