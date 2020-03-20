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
 * LUT(颜色查找表)采集特效。
 */
@interface MovieousLUTFilterCaptureEffect : MovieousCaptureEffect

/**
 * 颜色查找表(look up table) 图片。
 */
@property (nonatomic, strong) UIImage *image;

/**
 * 滤镜的强度。
 */
@property(nonatomic, assign) CGFloat intensity;

/**
 * 用另一个 MovieousLUTFilterCaptureEffect 对象初始化此 MovieousLUTFilterCaptureEffect。
 *
 * @param LUTFilterCaptureEffect 用于初始化的另一个 MovieousLUTFilterCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousLUTFilterCaptureEffect 对象。
 */
- (instancetype)initWithLUTFilterCaptureEffect:(MovieousLUTFilterCaptureEffect *)LUTFilterCaptureEffect;

@end
