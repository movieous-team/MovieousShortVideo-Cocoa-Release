//
//  MSVLUTFilterEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2020/2/25.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Look up table 滤镜特效。
 */
@interface MSVLUTFilterEffect : MSVEffect

/**
 * Look up table 滤镜图片。
 */
@property (nonatomic, strong) UIImage *image;

/**
 * Look up table 滤镜强度。
 */
@property (nonatomic, assign) float intensity;

@end

NS_ASSUME_NONNULL_END
