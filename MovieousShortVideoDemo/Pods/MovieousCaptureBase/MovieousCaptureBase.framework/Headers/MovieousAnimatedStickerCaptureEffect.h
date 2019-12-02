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
 * 动态贴纸采集特效对象
 * 支持使用 gif 文件初始化或使用图片路径序列进行初始化。
 */
@interface MovieousAnimatedStickerCaptureEffect : MovieousObject
<
MovieousCaptureEffect
>

/**
 * gif 文件的数据。
 */
@property (nonatomic, strong, readonly) NSData *gifData;

/**
 * 图片地址序列。
 */
@property (nonatomic, strong, readonly) NSArray<NSString *> *imagePaths;

/**
 * 图片地址序列播放的帧间隔。
 */
@property (nonatomic, assign, readonly) float interval;

/**
 * gif 的大小。
 */
@property (nonatomic, assign, readonly) CGSize size;

/**
 * 动画贴纸循环播放的次数，传入 0 代表动画贴纸无限重复。
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
 * 用 gif 文件的 data 初始化此 MovieousAnimatedStickerCaptureEffect 对象。
 *
 * @param gifData 用于初始化的 gif 文件的 data。
 *
 * @return 初始化完成的 MovieousAnimatedStickerCaptureEffect 对象。
 */
- (instancetype)initWithGifData:(NSData *)gifData;

/**
 * 用图片地址序列及帧间隔初始化此 MovieousAnimatedStickerCaptureEffect 对象。
 *
 * @param imagePaths 用于初始化的图片地址序列。
 * @param interval 动画帧间隔。
 *
 * @return 初始化完成的 MovieousAnimatedStickerCaptureEffect 对象。
 */
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
