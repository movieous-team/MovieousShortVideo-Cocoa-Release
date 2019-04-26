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
 *  外部滤镜类。
 */
@property (nonatomic, assign) Class<MovieousExternalFilter> externalFilterClass;

/**
 * 用另一个 MovieousExternalFilterCaptureEffect 对象初始化此 MovieousExternalFilterCaptureEffect。
 *
 * @param externalFilterCaptureEffect 用于初始化的另一个 MovieousExternalFilterCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousExternalFilterCaptureEffect 对象。
 */
- (instancetype)initWithExternalFilterCaptureEffect:(MovieousExternalFilterCaptureEffect *)externalFilterCaptureEffect;

@end
