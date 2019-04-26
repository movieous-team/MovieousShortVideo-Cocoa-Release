//
//  MSVImageGenerator.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/31.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

@class MSVImageGeneratorResult;
/**
 * 图片生成完成代码块。
 *
 * @param results 生成的结果。
 * @param result 生成的结果状态。
 * @param error 如果错误发生，返回具体的错误对象。
 */
typedef void (^MSVImageGeneratorCompletionHandler)(NSArray<MSVImageGeneratorResult *> *_Nullable results, AVAssetImageGeneratorResult result, NSError *_Nullable error);

/**
 * 生成图片的结果。
 */
@interface MSVImageGeneratorResult : NSObject

/**
 * 请求图片的时间。
 */
@property (nonatomic, assign) NSTimeInterval requestedTime;

/**
 * 实际产生的图片的时间。
 */
@property (nonatomic, assign) NSTimeInterval actualTime;

/**
 * 生成的图片。
 */
@property (nonatomic, strong) UIImage *image;

@end

/**
 * 用于生成快照的图片生成器。
 */
@interface MSVImageGenerator : NSObject

/**
 * 生成快照的时间范围。
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * 快照数量。
 */
@property (nonatomic, assign) NSUInteger imageCount;

/**
 * 生成快照的时间间隔。
 */
@property (nonatomic, assign, readonly) NSTimeInterval timeInterval;

/**
 * 底层的 AVAsset 对象。
 */
@property (nonatomic, strong) AVAsset *innerAsset;

/**
 * 底层的 AVAssetImageGenerator 对象，你能用这个对象来进行你自己的图片生成动作。
 */
@property (nonatomic, strong, readonly) AVAssetImageGenerator *innerImageGenerator;

/**
 * 用生成器的参数来生成截图。
 *
 * @param handler 当生成完成时调用改 block。
 */
- (void)generateImagesWithCompletionHandler:(MSVImageGeneratorCompletionHandler)handler;

@end

NS_ASSUME_NONNULL_END
