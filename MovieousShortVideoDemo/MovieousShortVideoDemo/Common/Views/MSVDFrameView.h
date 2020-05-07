//
//  MSVDFrameView.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/24.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVDFrameView : UIView

@property (nonatomic, strong) UIColor *frameColor;
@property (nonatomic, assign) CGFloat margin;
@property (nonatomic, assign) CGFloat frameWidth;
@property (nonatomic, assign) CGFloat cornerRadius;
@property (nonatomic, assign) BOOL hideTop;

@end

NS_ASSUME_NONNULL_END
