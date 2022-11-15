//
//  MovieousBeautifyFilterCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2019/4/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousCaptureBase/MovieousCaptureEffect.h>
#import <MovieousBase/MovieousObject.h>

/**
 * 美颜采集特效。
 */
@interface MovieousBeautifyFilterCaptureEffect : MovieousCaptureEffect

/**
 * 美颜强度，范围 0~1。
 */
@property (nonatomic, assign) CGFloat smoothLevel;

/**
 * 美白强度，范围 0~1。
 */
@property (nonatomic, assign) CGFloat whiteLevel;

/**
 * 红润强度，范围 0~1。
 */
@property (nonatomic, assign) CGFloat redLevel;

/**
 * 用另一个 MovieousBeautifyFilterCaptureEffect 对象初始化此 MovieousBeautifyFilterCaptureEffect。
 *
 * @param faceBeautyCaptureEffect 用于初始化的另一个 MovieousBeautifyFilterCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousBeautifyFilterCaptureEffect 对象。
 */
- (instancetype)initWithFaceBeautyCaptureEffect:(MovieousBeautifyFilterCaptureEffect *)faceBeautyCaptureEffect;

@end
