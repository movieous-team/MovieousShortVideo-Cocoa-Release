//
//  MSVSnapshotGenerator.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/31.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 视频快照结果状态码。
 */
typedef NS_ENUM(NSInteger, MSVSnapshotGeneratorResult) {
    /**
     * 视频快照生成成功。
     */
    MSVSnapshotGeneratorResultSucceeded   = 0,
    /**
     * 视频快照生成失败。
     */
    MSVSnapshotGeneratorResultFailed      = 1,
    /**
     * 视频快照生成操作被取消。
     */
    MSVSnapshotGeneratorResultCancelled   = 2,
};

/**
 * 生成的快照的光圈模式。
 */
typedef NS_ENUM(NSInteger, MSVSnapshotGeneratorApertureMode) {
    /**
     * 视频快照生成成功。
     */
    MSVSnapshotGeneratorApertureModeCleanAperture       = 0,
    /**
     * 视频快照生成失败。
     */
    MSVSnapshotGeneratorApertureModeProductionAperture  = 1,
    /**
     * 视频快照生成操作被取消。
     */
    MSVSnapshotGeneratorApertureModeEncodedPixels       = 2,
};


/**
 * 用于接收生成的快照的回调代码块，你可以将此类型的代码块传递给 `-generateSnapshotsAsynchronouslyForTimes:completionHandler:`，然后使用该代码块来接收生成的图片，针对每个传入的时间戳，`-generateSnapshotsAsynchronouslyForTimes:completionHandler:`都会执行一次该代码块。
 *
 * @param requestedTime 你请求生成快照的时间戳。
 * @param image 生成的快照，如果快照无法生成，则返回 nil 。
 * @param actualTime 实际获取到的快照的时间戳。
 * @param result 指示快照生成过程是成功，失败还是被取消的状态码。
 * @param error 如果 `result` 为 MSVSnapshotGeneratorFailed，该错误对象将描述问题产生的具体原因。
 */
typedef void (^MSVSnapshotGeneratorCompletionHandler)(MovieousTime requestedTime, UIImage *_Nullable image, MovieousTime actualTime, MSVSnapshotGeneratorResult result, NSError * _Nullable error);

/**
 * 视频快照生成器。
 */
@interface MSVSnapshotGenerator : NSObject
<
NSCopying
>

/**
 * @abstract 指定生成的图片的最大尺寸
 *
 * @discussion 默认值为 CGSizeZero，即指定为视频未经缩放的尺寸。MSVSnapshotGenerator 会缩小快照的尺寸以便能够满足最大尺寸的要求，但是不会放大。
 */
@property (nonatomic, assign) CGSize maximumSize;

/**
 * 指定生成的快照的光圈模式。
 */
@property (nonatomic, assign) MSVSnapshotGeneratorApertureMode apertureMode;

/**
 * 生成快照的时间戳比请求时间戳小的最大允许的差值，该值越小时间越精确，但会让快照生成的速度越慢。
 * 默认为无穷大。
 */
@property (nonatomic, assign) MovieousTime requestedTimeToleranceBefore;

/**
 * 生成快照的时间戳比请求时间戳大的最大允许的差值，该值越小时间越精确，但会让快照生成的速度越慢。
 * 默认为无穷大。
 */
@property (nonatomic, assign) MovieousTime requestedTimeToleranceAfter;

/**
 * 生成指定时间点的单张快照。
 *
 * @param requestedTime 请求生成快照的时间。
 * @param actualTime 生成的快照的实际时间。
 * @param outError 如果发成错误，返回发生的具体错误对象。
 *
 * @return 生成的快照对象，生成失败返回 nil。
 */
- (UIImage *_Nullable)generateSnapshotAtTime:(MovieousTime)requestedTime actualTime:(nullable MovieousTime *)actualTime error:(NSError * _Nullable * _Nullable)outError;

/**
 * @abstract 生成一系列指定时间点或附近的快照对象。
 * @discussion 此方法使用高效的批处理模式来以时间顺序生成快照，每个请求的时间戳客户端都将收到唯一的一次回调。对生成器的属性（例如 apertureMode，maximumSize 等）的改变将不会影响之前的异步图片生成请求。
 *
 * @param requestedTimes 当生成完成时调用改 block。
 * @param handler 当生成完成时调用改 block。
 */
- (void)generateSnapshotsAsynchronouslyForTimes:(NSArray<NSNumber *> *)requestedTimes completionHandler:(MSVSnapshotGeneratorCompletionHandler)handler;

/**
 * 取消所有之前通过 `-generateSnapshotsAsynchronouslyForTimes:completionHandler:` 触发的快照生成请求中还未生成的快照。
 */
- (void)cancelAllSnapshotGeneration;

@end

NS_ASSUME_NONNULL_END
