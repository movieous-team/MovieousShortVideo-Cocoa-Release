//
//  UIImage+MSVD.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/23.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UIImage(MSVD)

/**
 绘制生成圆形图片

 @param size 指定大小
 @param color 颜色
 @return UIImage 对象
 */
+ (UIImage *)circleImageWithSize:(CGSize)size color:(UIColor *)color;

/**
 绘制生成圆形图片

 @param size 指定大小
 @param color 颜色
 @return UIImage 对象
 */
+ (UIImage *)rectangleImageWithSize:(CGSize)size color:(UIColor *)color;


@end
