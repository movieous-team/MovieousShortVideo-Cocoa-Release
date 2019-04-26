//
//  MovieousLUTFilterCaptureEffect.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousBase/MovieousCaptureEffect.h>

/**
 * LUT(颜色查找表)采集特效。
 */
@interface MovieousLUTFilterCaptureEffect : NSObject
<
MovieousCaptureEffect
>

/**
 * 颜色查找表(look up table) 图片。
 */
@property (nonatomic, strong) UIImage *image;

/**
 * 用另一个 MovieousLUTFilterCaptureEffect 对象初始化此 MovieousLUTFilterCaptureEffect。
 *
 * @param LUTFilterCaptureEffect 用于初始化的另一个 MovieousLUTFilterCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousLUTFilterCaptureEffect 对象。
 */
- (instancetype)initWithLUTFilterCaptureEffect:(MovieousLUTFilterCaptureEffect *)LUTFilterCaptureEffect;

@end
