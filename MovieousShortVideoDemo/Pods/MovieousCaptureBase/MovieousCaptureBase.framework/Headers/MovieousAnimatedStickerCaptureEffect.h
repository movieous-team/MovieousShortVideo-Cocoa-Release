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

@interface MovieousAnimatedStickerCaptureEffect : MovieousObject
<
MovieousCaptureEffect
>

/**
 * gif 文件的数据。
 */
@property (nonatomic, strong, readonly) NSData *gifData;

@property (nonatomic, assign, readonly) float interval;

@property (nonatomic, strong, readonly) NSArray<NSString *> *imagePaths;

/**
 * gif 的大小。
 */
@property (nonatomic, assign, readonly) CGSize size;

/**
 * 动画贴纸循环播放的次数，
 */
@property (nonatomic, assign) NSInteger loopCount;

/**
 * 贴纸的目标位置和大小。
 * @warning 当贴纸的比例和 destRect 的比例不一致时贴纸会变形。
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * 应用在贴纸上的旋转角度。
 */
@property (nonatomic, assign) CGFloat rotation;

/**
 * 用 gif 文件的 data 初始化此 MovieousAnimatedStickerCaptureEffect。
 *
 * @param gifData 用于初始化的 gif 文件的 data。
 *
 * @return 初始化完成的 MovieousAnimatedStickerCaptureEffect 对象。
 */
- (instancetype)initWithGifData:(NSData *)gifData;

- (instancetype)initWithImagePaths:(NSArray<NSString *> *)imagePaths interval:(float)interval;

/**
 * 用另一个 MovieousAnimatedStickerCaptureEffect 对象初始化此 MovieousAnimatedStickerCaptureEffect。
 *
 * @param animatedStickerCaptureEffect 用于初始化的另一个 MovieousAnimatedStickerCaptureEffect 对象。
 *
 * @return 初始化完成的 MovieousAnimatedStickerCaptureEffect 对象。
 */
- (instancetype)initWithAnimatedStickerCaptureEffect:(MovieousAnimatedStickerCaptureEffect *)animatedStickerCaptureEffect;

@end

NS_ASSUME_NONNULL_END
