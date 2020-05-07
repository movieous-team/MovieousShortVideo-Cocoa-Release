//
//  MSVDSlider.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDSlider.h"
#import "UIImage+MSVD.h"

@implementation MSVDSlider {
    id _target;
    SEL _action;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        _slider = [UISlider new];
        [_slider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
        [_slider addTarget:self action:@selector(sliderTouchedUp:) forControlEvents:UIControlEventTouchUpInside];
        [_slider addTarget:self action:@selector(sliderTouchedUp:) forControlEvents:UIControlEventTouchUpOutside];
        [_slider addTarget:self action:@selector(sliderTouchedUp:) forControlEvents:UIControlEventTouchCancel];
        _slider.minimumTrackTintColor = [UIColor colorWithRed:0.4039 green:0.8745 blue:0.8078 alpha:1];
        _slider.maximumTrackTintColor = UIColor.lightGrayColor;
        UIImage *thumbImage = [UIImage rectangleImageWithSize:CGSizeMake(6, 20) color:UIColor.whiteColor];
        [_slider setThumbImage:thumbImage forState:UIControlStateNormal];
        [_slider setThumbImage:thumbImage forState:UIControlStateHighlighted];
        [self addSubview:_slider];
        [_slider mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(@0);
            make.left.equalTo(@5);
            make.right.equalTo(@-5);
        }];
        
        _label = [UILabel new];
        _label.hidden = YES;
        _label.font = [UIFont systemFontOfSize:15];
        _label.textColor = UIColor.whiteColor;
        _label.text = [NSString stringWithFormat:@"%d", (int)(_slider.value * 100)];
        [self addSubview:_label];
        [_label mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@5);
            make.bottom.equalTo(_slider.mas_top).offset(-5);
            make.centerX.equalTo(_slider.mas_left);
        }];
    }
    return self;
}

- (void)setTarget:(nullable id)target action:(SEL)action {
    _target = target;
    _action = action;
}

- (void)sliderTouchedUp:(UISlider *)sender {
    _label.hidden = YES;
}

- (void)sliderValueChanged:(UISlider *)sender {
    IMP imp = [_target methodForSelector:_action];
    void (*func)(id, SEL, UIView *) = (void *)imp;
    func(_target, _action, self);
    _label.text = [NSString stringWithFormat:@"%d", (int)(_slider.value * 100)];
    [_label mas_updateConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_slider.mas_left).offset((_slider.frame.size.width - 6) * (_slider.value - _slider.minimumValue) / (_slider.maximumValue - _slider.minimumValue));
    }];
    _label.hidden = NO;
}

@end
