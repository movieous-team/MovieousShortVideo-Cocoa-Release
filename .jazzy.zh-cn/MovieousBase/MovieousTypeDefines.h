//
//  MLTypeDefines.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/10/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/// 填充模式类型。
typedef NS_ENUM(NSInteger, MovieousScalingMode) {
    /// 填充满目标容器，不保持原始比例，比例不一致会出现画面变形。
    MovieousScalingModeFill,
    /// 以嵌入的方式填充到目标容器，保持原始比例，比例不一致会出现黑边。
    MovieousScalingModeAspectFit,
    /// 填充满目标容器，保持原始比例，比例不一致会出现部分画面被裁剪掉。
    MovieousScalingModeAspectFill
};

/// 时间范围类型。
typedef struct {
    /// 时间范围的开始时间
    NSTimeInterval startTime;
    /// 时间范围的持续时长。
    NSTimeInterval duration;
} MovieousTimeRange;

/// 默认的时间范围。
extern MovieousTimeRange kMovieousTimeRangeDefault;

/// 用开始时间和持续时长初始化一个 MovieousTimeRange
MovieousTimeRange MovieousTimeRangeMake(NSTimeInterval startTime, NSTimeInterval duration);

/// 判断两个时间范围是否相同
BOOL MovieousTimeRangeIsEqual(MovieousTimeRange timeRange1,MovieousTimeRange timeRange2);

/// 判断一个时间范围是否是默认时间范围
BOOL MovieousTimeRangeIsDefault(MovieousTimeRange timeRange);

/// 使用 MovieousTimeRange 来创建一个 CMTimeRange
CMTimeRange CMTimeRangeMakeMovieousTimeRange(MovieousTimeRange timeRange, int32_t timeScale);

/// 使用 CMTimeRange 来创建一个 MovieousTimeRange
MovieousTimeRange MovieousTimeRangeMakeWithCMTimeRange(CMTimeRange timeRange);
