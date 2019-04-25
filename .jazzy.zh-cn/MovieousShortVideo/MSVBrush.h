//
//  MSVBrush.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/19.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief Brush configuration for MSVGraffitiView
 */
@interface MSVBrush : NSObject

/**
 * @brief Line color of the brush
 */
@property (nonatomic, strong) UIColor *lineColor;


/**
 * @brief Line width of the brush
 */
@property (nonatomic, assign) CGFloat lineWidth;

/**
 * @brief Instantiate a brush with line width and line color
 * @param lineWidth Line color of the brush
 * @param lineColor Line width of the brush
 * @return The instantiated brush instance
 */
+ (instancetype)brushWithLineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

/**
 * @brief Initiate a brush with line width and line color
 * @param lineWidth Line color of the brush
 * @param lineColor Line width of the brush
 * @return The initiated brush instance
 */
- (instancetype)initWithLineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

@end

NS_ASSUME_NONNULL_END
