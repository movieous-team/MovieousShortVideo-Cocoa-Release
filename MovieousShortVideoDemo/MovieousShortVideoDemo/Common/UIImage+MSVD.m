//
//  UIImage+MSVD.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/23.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "UIImage+MSVD.h"

@implementation UIImage(MSVD)

+ (UIImage *)circleImageWithSize:(CGSize)size color:(UIColor *)color {
    UIGraphicsBeginImageContextWithOptions(size, NO, 0);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect rect = CGRectMake(0, 0, size.width, size.height);
    CGContextAddEllipseInRect(context, rect);
    CGContextSetFillColorWithColor(context, color.CGColor);
    CGContextDrawPath(context, kCGPathFill);
    UIImage *image =  UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

+ (UIImage *)rectangleImageWithSize:(CGSize)size color:(UIColor *)color {
    UIGraphicsBeginImageContextWithOptions(size, NO, 0);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGRect rect = CGRectMake(0, 0, size.width, size.height);
    CGContextAddRect(context, rect);
    CGContextSetFillColorWithColor(context, color.CGColor);
    CGContextDrawPath(context, kCGPathFill);
    UIImage *image =  UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return image;
}

@end
