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
 * MSVGraffitiView 的笔刷相关配置。
 */
@interface MSVBrush : NSObject

/**
 * 笔刷的颜色。
 */
@property (nonatomic, strong) UIColor *lineColor;


/**
 * 笔刷的线宽。
 */
@property (nonatomic, assign) CGFloat lineWidth;

/**
 * 默认的笔刷。
 * 默认笔刷的宽度为 10，颜色为黑色。
 *
 * @return 生成的笔刷对象。
 */
+ (instancetype)defaultBrush;

/**
 * 使用线宽和颜色生成一个笔刷对象。
 *
 * @param lineWidth 笔刷线宽。
 * @param lineColor 笔刷颜色。
 *
 * @return 生成的笔刷对象。
 */
+ (instancetype)brushWithLineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

/**
 * 使用线宽和颜色初始化一个笔刷对象。
 *
 * @param lineWidth 笔刷线宽。
 * @param lineColor 笔刷颜色。
 *
 * @return 初始化的笔刷对象。
 */
- (instancetype)initWithLineWidth:(CGFloat)lineWidth lineColor:(UIColor *)lineColor;

@end

NS_ASSUME_NONNULL_END
