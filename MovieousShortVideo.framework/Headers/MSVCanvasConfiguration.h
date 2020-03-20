//
//  MSVCanvasConfiguration.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2020/2/14.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * 画布配置类，该类为一个抽象类，实际使用请使用它的子类。
 */
@protocol MSVCanvasConfiguration <NSObject>

@end

/**
 * 纯色画布配置类。
 */
@interface MSVPureColorCanvasConfiguration : NSObject
<
MSVCanvasConfiguration
>

/**
 * 使用 UIColor 初始化 MSVPureColorCanvasConfiguration 对象。
 *
 * @param color 纯色。
 *
 * @return 返回初始化成功的 MSVPureColorCanvasConfiguration 对象。
 */
- (instancetype)initWithColor:(UIColor *)color;

/**
 * 纯色配置颜色。
 */
@property (nonatomic, strong) UIColor *color;

@end

/**
 * 模糊画布配置类。
 */
@interface MSVBlurCanvasConfiguration : NSObject
<
MSVCanvasConfiguration
>

@end
