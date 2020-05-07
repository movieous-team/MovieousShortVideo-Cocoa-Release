//
//  MovieousTypeDefines.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

#define MovieousInnerTimeScale 1e6

/// 视频朝向类型。
typedef NS_ENUM(NSInteger, MovieousVideoOrientation) {
    // 手机顶部采集到的视频在预览视图或编码视频的上部。
    MovieousVideoOrientationPortrait = 1,
    // 手机顶部采集到的视频在预览视图或编码视频的下部。
    MovieousVideoOrientationPortraitUpsideDown = 2,
    // 手机顶部采集到的视频在预览视图或编码视频的右部。
    MovieousVideoOrientationLandscapeRight = 3,
    // 手机顶部采集到的视频在预览视图或编码视频的左部。
    MovieousVideoOrientationLandscapeLeft = 4,
};

/// 填充模式类型。
typedef NS_ENUM(NSInteger, MovieousScalingMode) {
    /// 填充满目标容器，不保持原始比例，比例不一致会出现画面变形。
    MovieousScalingModeFill,
    /// 以嵌入的方式填充到目标容器，保持原始比例，比例不一致会出现黑边。
    MovieousScalingModeAspectFit,
    /// 填充满目标容器，保持原始比例，比例不一致会出现部分画面被裁剪掉。
    MovieousScalingModeAspectFill
};

/// 时间戳类型，单位为微秒。
typedef int64_t MovieousTime;

/// 时间范围类型
typedef struct {
    /// 时间范围的开始时间
    MovieousTime start;
    /// 时间范围的持续时长。
    MovieousTime duration;
} MovieousTimeRange;

/**
 * 使用 MovieousTime 生成 CMTime。
 *
 * @param time 时间。
 *
 * @return 生成的 CMTime。
 */
CMTime CMTimeMakeWithMovieousTime(MovieousTime time);

/**
 * 使用 CMTime 生成 MovieousTime。
 *
 * @param time 时间。
 *
 * @return 生成的 MovieousTime。
 */
MovieousTime MovieousTimeMakeWithCMTime(CMTime time);

/**
 * 使用 MovieousTime 生成 NSTimeInterval。
 *
 * @param time 时间。
 *
 * @return 生成的 MovieousTimeRange。
 */
NSTimeInterval MovieousTimeGetSeconds(MovieousTime time);

/**
 * 使用 NSTimeInterval 生成 MovieousTime。
 *
 * @param time 时间。
 *
 * @return 生成的 MovieousTimeRange。
 */
MovieousTime MovieousTimeMakeWithSeconds(NSTimeInterval time);

/// 默认的时间范围。
extern MovieousTimeRange kMovieousTimeRangeDefault;

/**
 * 用开始时间和持续时长初始化一个 MovieousTimeRange。
 *
 * @param startTime 开始时间。
 * @param duration 时长。
 *
 * @return 生成的 MovieousTimeRange。
 */
MovieousTimeRange MovieousTimeRangeMake(MovieousTime startTime, MovieousTime duration);

/**
 * 获取时间区间的。
 *
 * @param timeRange 时间区间。
 *
 * @return 判断结果。
 */
MovieousTime MovieousTimeRangeGetEnd(MovieousTimeRange timeRange);

/**
 * 判断两个时间区间是否相同。
 *
 * @param timeRange1 第一个时间区间。
 * @param timeRange2 第二个时间区间。
 *
 * @return 判断结果。
 */
BOOL MovieousTimeRangeIsEqual(MovieousTimeRange timeRange1,MovieousTimeRange timeRange2);

/**
 * 判断是否是默认时间区间。
 *
 * @param timeRange 时间区间。
 *
 * @return 判断结果。
 */
BOOL MovieousTimeRangeIsDefault(MovieousTimeRange timeRange);

/**
 * 使用 MovieousTimeRange 来创建一个 CMTimeRange。
 *
 * @param timeRange 用于初始化的 MovieousTimeRange。
 *
 * @return 生成的 CMTimeRange。
 */
CMTimeRange CMTimeRangeMakeWithMovieousTimeRange(MovieousTimeRange timeRange);

/**
 * 使用 CMTimeRange 来创建一个 MovieousTimeRange。
 *
 * @param timeRange 用于初始化的 CMTimeRange。
 *
 * @return 生成的 MovieousTimeRange。
 */
MovieousTimeRange MovieousTimeRangeMakeWithCMTimeRange(CMTimeRange timeRange);

/**
 * 快照完成的回调句柄.
 *
 * @param image 采集到的照片.
 * @param error 如果发生错误返回相应的错误.
 */
typedef void(^MovieousSnapshotCompletionHandler)(UIImage *_Nullable image, NSError *_Nullable error);
