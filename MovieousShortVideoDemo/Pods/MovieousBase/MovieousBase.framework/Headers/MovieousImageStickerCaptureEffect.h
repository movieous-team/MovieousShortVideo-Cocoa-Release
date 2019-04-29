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
 * The image sticker filter effect.
 */
@interface MovieousImageStickerCaptureEffect : NSObject
<
MovieousCaptureEffect
>

/**
 * Image which used in image stickers.
 */
@property (nonatomic, strong) UIImage *image;

/**
 * Target location and size of the sticker.
 * @warning The sticker will be deformed when the aspect ratio and the aspect ratio of the sticker itself are inconsistent.
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * Rotation applied to the sticker in radian.
 */
@property (nonatomic, assign) CGFloat rotation;

/**
 * Initiate the MovieousImageStickerCaptureEffect with another MovieousImageStickerCaptureEffect object.
 *
 * @param imageStickerCaptureEffect Another MovieousImageStickerCaptureEffect used to initiate the instance.
 *
 * @return The initialized MovieousImageStickerCaptureEffect instance.
 */
- (instancetype)initWithImageStickerCaptureEffect:(MovieousImageStickerCaptureEffect *)imageStickerCaptureEffect;

@end

NS_ASSUME_NONNULL_END
