//
//  MSVDFrameView.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/24.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDFrameView.h"

@implementation MSVDFrameView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.backgroundColor = UIColor.clearColor;
        _frameColor = UIColor.whiteColor;
        _frameWidth = 1;
    }
    return self;
}

- (void)setFrameColor:(UIColor *)frameColor {
    _frameColor = frameColor;
    [self setNeedsDisplay];
}

- (void)setMargin:(CGFloat)margin {
    _margin = margin;
    [self setNeedsDisplay];
}

- (void)setFrameWidth:(CGFloat)frameWidth {
    _frameWidth = frameWidth;
    [self setNeedsDisplay];
}

- (void)setCornerRadius:(CGFloat)cornerRadius {
    _cornerRadius = cornerRadius;
    [self setNeedsDisplay];
}

- (void)layoutSubviews {
    [super layoutSubviews];
    [self setNeedsDisplay];
}

- (void)drawRect:(CGRect)rect {
    CGContextRef ctx = UIGraphicsGetCurrentContext();
    [_frameColor setStroke];
    CGContextSetLineWidth(ctx, _frameWidth);
    CGFloat halfFrameWidth = _frameWidth / 2;
    UIBezierPath *path = [UIBezierPath bezierPath];
    if (_hideTop) {
        [path moveToPoint:CGPointMake(self.bounds.size.width - _margin - halfFrameWidth, _margin + halfFrameWidth + _cornerRadius)];
    } else {
        [path moveToPoint:CGPointMake(_margin + halfFrameWidth + _cornerRadius, _margin + halfFrameWidth)];
        [path addLineToPoint:CGPointMake(self.bounds.size.width - _margin - halfFrameWidth - _cornerRadius, _margin + halfFrameWidth)];
        [path addArcWithCenter:CGPointMake(self.bounds.size.width - _margin - halfFrameWidth - _cornerRadius, _margin + halfFrameWidth + _cornerRadius) radius:_cornerRadius startAngle:1.5 * M_PI endAngle:2 * M_PI clockwise:YES];
    }
    [path addLineToPoint:CGPointMake(self.bounds.size.width - _margin - halfFrameWidth, self.bounds.size.height - _margin - halfFrameWidth - _cornerRadius)];
    [path addArcWithCenter:CGPointMake(self.bounds.size.width - _margin - halfFrameWidth - _cornerRadius, self.bounds.size.height - _margin - halfFrameWidth - _cornerRadius) radius:_cornerRadius startAngle:0 endAngle:0.5 * M_PI clockwise:YES];
    [path addLineToPoint:CGPointMake(_margin + halfFrameWidth + _cornerRadius, self.bounds.size.height - _margin - halfFrameWidth)];
    [path addArcWithCenter:CGPointMake(_margin + halfFrameWidth + _cornerRadius, self.bounds.size.height - _margin - halfFrameWidth - _cornerRadius) radius:_cornerRadius startAngle:0.5 * M_PI endAngle:M_PI clockwise:YES];
    [path addLineToPoint:CGPointMake(_margin + halfFrameWidth, _margin + halfFrameWidth + _cornerRadius)];
    if (!_hideTop) {
        [path addArcWithCenter:CGPointMake(_margin + halfFrameWidth + _cornerRadius, _margin + halfFrameWidth + _cornerRadius) radius:_cornerRadius startAngle:M_PI endAngle:1.5 * M_PI clockwise:YES];
    }
    CGContextAddPath(ctx, path.CGPath);
    CGContextSetBlendMode(ctx, kCGBlendModeCopy);
    CGContextStrokePath(ctx);
}

@end
