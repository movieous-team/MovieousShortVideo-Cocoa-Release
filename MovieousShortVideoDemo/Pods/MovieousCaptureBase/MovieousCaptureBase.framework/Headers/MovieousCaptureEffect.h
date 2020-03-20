//
//  MovieousCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by WangSiyu on 2020/3/8.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

@interface MovieousCaptureEffect : MovieousObject

/**
 * 用另一个 MovieousCaptureEffect 对象初始化此 MovieousCaptureEffect。
 *
 * @param captureEffect 用于初始化的另一个 MovieousCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousCaptureEffect 对象。
 */
- (instancetype)initWithCaptureEffect:(MovieousCaptureEffect *)captureEffect;

@end

NS_ASSUME_NONNULL_END
