//
//  MovieousImageStickerCaptureEffect.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/4/4.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousBase/MovieousCaptureEffect.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 图片贴纸特效。
 */
@interface MovieousImageStickerCaptureEffect : NSObject
<
MovieousCaptureEffect
>

/**
 * 用作图片贴纸的图片
 */
@property (nonatomic, strong) UIImage *image;

/**
 * 贴纸的目标位置和大小
 * 
 * @warning 当图片的比例和贴纸目标大小的比例不一致时贴纸会被拉伸变形。
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * 图片贴纸的旋转弧度
 */
@property (nonatomic, assign) CGFloat rotation;

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
