//
//  MSVImageStickerEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/24.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief Image sticker effects
 */
@interface MSVImageStickerEffect : NSObject

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief Image which used in image stickers
 */
@property (nonatomic, strong, readonly) UIImage *image;

/**
 * @brief Target location and size of the sticker
 * @warning The sticker will be deformed when the aspect ratio and the aspect ratio of the sticker itself are inconsistent.
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * @brief The time interval for applying an external filter in the main track
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

- (instancetype)initWithImage:(UIImage *)image;

+ (instancetype)stickerEffectWithImage:(UIImage *)image;

@end

