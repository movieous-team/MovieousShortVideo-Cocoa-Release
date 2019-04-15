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

@interface MovieousImageStickerCaptureEffect : NSObject
<
MovieousCaptureEffect
>

/**
 * @brief Image which used in image stickers
 */
@property (nonatomic, strong) UIImage *image;

/**
 * @brief Target location and size of the sticker
 * @warning The sticker will be deformed when the aspect ratio and the aspect ratio of the sticker itself are inconsistent.
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * @brief Rotation applied to the sticker in radian
 */
@property (nonatomic, assign) CGFloat rotation;

@end

NS_ASSUME_NONNULL_END
