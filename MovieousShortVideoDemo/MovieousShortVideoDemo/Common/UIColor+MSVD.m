//
//  UIColor+MSVD.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "UIColor+MSVD.h"

@implementation UIColor(MSVD)

+ (instancetype)colorWithR:(CGFloat)R G:(CGFloat)G B:(CGFloat)B A:(CGFloat)A {
    return [self colorWithRed:R / 255 green:G / 255 blue:B / 255 alpha:A];
}

@end
