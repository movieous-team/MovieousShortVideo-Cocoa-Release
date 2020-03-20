//
//  MovieousImageStickerCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousCaptureBase/MovieousCaptureEffect.h>
#import <MovieousBase/MovieousObject.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 图片贴纸特效。
 */
@interface MovieousImageStickerCaptureEffect : MovieousCaptureEffect

/**
 * 用作图片贴纸的图片
 */
@property (nonatomic, strong) UIImage *image;

/**
 * 取材的视频区域的中心点。
 * @warning 如果取材的视频区域超过源视频的范围，源视频以外的区域将显示为以源视频边缘的颜色向外延伸的栅格状图形。
 */
@property (nonatomic, assign) CGPoint sourceCenter;

/**
 * 取材的视频区域的大小。
 * @warning 如果取材的视频区域超过源视频的范围，源视频以外的区域将显示为以源视频边缘的颜色向外延伸的栅格状图形。
 */
@property (nonatomic, assign) CGSize sourceSize;

/**
 * 取材的视频区域的旋转弧度，以 sourceCenter 为中心。
 * @warning 如果取材的视频区域超过源视频的范围，源视频以外的区域将显示为以源视频边缘的颜色向外延伸的栅格状图形。
 */
@property (nonatomic, assign) float sourceRotation;

/**
 * 片段在目标视频当中的中心点。
 */
@property (nonatomic, assign) CGPoint destCenter;

/**
 * 片段在目标视频当中的大小。
 */
@property (nonatomic, assign) CGSize destSize;

/**
 * 片段在目标视频当中的旋转弧度。
 */
@property (nonatomic, assign) float destRotation;

/**
 * 片段在目标视频当中的透明度。
 */
@property (nonatomic, assign) float alpha;

/**
 * 用另一个 MovieousImageStickerCaptureEffect 对象初始化此 MovieousImageStickerCaptureEffect
 *
 * @param imageStickerCaptureEffect 用于初始化的另一个 MovieousImageStickerCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousImageStickerCaptureEffect 对象。
 */
- (instancetype)initWithImageStickerCaptureEffect:(MovieousImageStickerCaptureEffect *)imageStickerCaptureEffect;

@end

NS_ASSUME_NONNULL_END
