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
 * Brush configuration for MSVGraffitiView.
 */
@interface MSVBrush : NSObject

/**
 * Line color of the brush.
 */
@property (nonatomic, strong) UIColor *lineColor;


/**
 * Line width of the brush.
 */
@property (nonatomic, assign) CGFloat lineWidth;

/**
 * The default brush.
 * Default brush width is 10 and color is black.
 *
 * @return The generated brush object.
 */
+ (instancetype)defaultBrush;

/**
 * Instantiate a brush with line width and line color.
 *
 * @param lineWidth Line width of the brush.
 * @param lineColor Line color of the brush.
 *
 * @return The instantiated brush instance.
 */
+ (instancetype)brushWithLineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

/**
 * Initiate a brush with line width and line color.
 *
 * @param lineWidth Line width of the brush.
 * @param lineColor Line color of the brush.
 *
 * @return The initiated brush instance.
 */
- (instancetype)initWithLineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

@end

NS_ASSUME_NONNULL_END
