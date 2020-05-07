//
//  MSVDMixDragView.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/24.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDMixDragView.h"

@implementation MSVDMixDragView {
    UIImageView *_imageView;
}

- (instancetype)initWithImage:(UIImage *)image {
    if (self = [self init]) {
        _imageView = [UIImageView new];
        [self addSubview:_imageView];
        [_imageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            make.size.equalTo(@0);
        }];
        _imageView.image = image;
    }
    return self;
}

@end
