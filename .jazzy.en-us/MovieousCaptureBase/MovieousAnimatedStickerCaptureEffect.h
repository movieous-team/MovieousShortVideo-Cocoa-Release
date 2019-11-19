//
//  MovieousAnimatedStickerCaptureEffect.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2019/8/14.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousCaptureBase/MovieousCaptureEffect.h>
#import <MovieousBase/MovieousObject.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The animated sticker effect object for capturing.
 * Initializing with gif file or file path array are both supported.
 */
@interface MovieousAnimatedStickerCaptureEffect : MovieousObject
<
MovieousCaptureEffect
>

/**
 * Gif file data.
 */
@property (nonatomic, strong, readonly) NSData *gifData;

/**
 * Image path array.
 */
@property (nonatomic, strong, readonly) NSArray<NSString *> *imagePaths;

/**
 * Frame interval when play image path array.
 */
@property (nonatomic, assign, readonly) float interval;

/**
 * The size of gif.
 */
@property (nonatomic, assign, readonly) CGSize size;

/**
 * Loop count for Animated sticker, pass 0 indicates loop indefinitely
 */
@property (nonatomic, assign) NSInteger loopCount;

/**
 * The destination position and size for the sticker.
 * @warning Sticker may be distorted when their aspect ratio  are not equal.
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * The rotation angle applied in the sticker.
 */
@property (nonatomic, assign) CGFloat rotation;

/**
 * Initialize MovieousAnimatedStickerCaptureEffect object with gif file data.
 *
 * @param gifData Data used for initialization
 * 
 * @return The initialized MovieousAnimatedStickerCaptureEffect object.
 */
- (instancetype)initWithGifData:(NSData *)gifData;

/**
 * Initialize MovieousAnimatedStickerCaptureEffect object with image path array and frame interval.
 * 
 * @param imagePaths The image path array.
 * @param interval Animated image sticker frame interval in second.
 *
 * @return The initialized MovieousAnimatedStickerCaptureEffect object.
 */
- (instancetype)initWithImagePaths:(NSArray<NSString *> *)imagePaths interval:(float)interval;

/**
 * Initialize MovieousAnimatedStickerCaptureEffect object with another MovieousAnimatedStickerCaptureEffect object.
 *
 * @param animatedStickerCaptureEffect The MovieousAnimatedStickerCaptureEffect object used to initialized the MovieousAnimatedStickerCaptureEffect object.
 *
 * @return The initialized MovieousAnimatedStickerCaptureEffect object.
 */
- (instancetype)initWithAnimatedStickerCaptureEffect:(MovieousAnimatedStickerCaptureEffect *)animatedStickerCaptureEffect;

@end

NS_ASSUME_NONNULL_END
