//
//  MSVDSlider.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVDSlider : UIView

@property (nonatomic, strong, readonly) UISlider *slider;
@property (nonatomic, strong, readonly) UILabel *label;

- (void)setTarget:(nullable id)target action:(SEL)action;

@end

NS_ASSUME_NONNULL_END
