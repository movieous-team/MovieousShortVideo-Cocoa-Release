//
//  MSVBeautifyFilterEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2020/2/25.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <MovieousShortVideo/MovieousShortVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVBeautifyFilterEffect : MSVEffect

/**
 * 磨皮强度，取值范围为 0~1，默认为 0.5。
 */
@property (nonatomic, assign) CGFloat smoothLevel;

/**
 * 美白强度，取值范围为 0~1，默认为 0.5。
 */
@property (nonatomic, assign) CGFloat whiteLevel;

/**
 * 红润强度，取值范围为 0~1，默认为 0.5。
 */
@property (nonatomic, assign) CGFloat redLevel;

@end

NS_ASSUME_NONNULL_END
