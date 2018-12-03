//
//  MSVMainTrackClip.h
//  MSVShortVideoKit
//
//  Created by Chris Wang on 18/3/1.
//  Copyright © 2018年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MSVTypeDefines.h"
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 主轨片段的类型
 */
typedef NS_ENUM(NSInteger, MSVMainTrackClipType) {
    /**
     * 音视频媒体资源类型
     */
    MSVMainTrackClipTypeAV,
    /**
     * 图片资源类型
     */
    MSVMainTrackClipTypeImage
};

/**
 * @brief 主轨片段
 */
@interface MSVMainTrackClip : NSObject <NSCopying>

/**
 * @brief 用户自定义 ID 字段，业务使用用于区分对象
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief 主轨媒体的类型
 */
@property (nonatomic, assign, readonly) MSVMainTrackClipType type;

/**
 * @brief 媒体文件的地址
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief 上片段结束，本片段开始衔接的转场时间
 * @warning 需要注意的是每个片段的首尾转场效果时长总和不能超过该片段的有效时长，例如存在转场 A：1->2，时长为2秒，转场 B：2->3，时长为3秒，则片段2的时长应当大于5秒，否则将会出现错误
 */
@property (nonatomic, assign) NSTimeInterval transitionDuration;

/**
 * @brief 上片段结束，本片段开始衔接的转场效果的类型，默认为 MSVVideoTransitionTypeDissolve
 */
@property (nonatomic, assign) MSVVideoTransitionType videoTransitionType;

// 以下参数仅对 MSVMainTrackClipTypeAV 类型的主轨片段生效
#pragma mark - video properties
/**
 * @brief 音视频媒体文件生成的 AVAsset 对象，可以在这里获取一些需要的参数
 */
@property (nonatomic, strong, readonly) AVAsset *asset;

/**
 * @brief 在媒体片段当中截取使用的时间范围
 * @warning 这个时间范围是指没有经过快慢速处理及倒放处理之前的时间范围，另外，如果 timeRange.startTime + timeRange.duration > 媒体总时长将忽略超出的部分
 */
@property (nonatomic, assign) MovieousTimeRange timeRange;

/**
 * @brief 音频片段的速度
 * 一般来说可以进行如下配置：
 * 极快：2.0
 * 快：1.5
 * 正常：1.0
 * 慢：0.75
 * 极慢：0.5
 */
@property (nonatomic, assign) float speed;

/**
 * @brief 媒体音频的音量，默认为媒体文件中自带的 preferredVolume
 */
@property (nonatomic, assign) float volume;

/**
 * @brief 开始应用倒放效果到该片段
 * @discussion 倒放操作在首次应用时需要耗费一定的时间，传入 progressHandler 以获取操作的进度，传入 completionHandler 以获取操作的结果。首次倒放操作完成之后如果再次应用倒放效果将会瞬间完成，无需再次等待。
 * @param reverse 是否应用倒放效果
 * @param progressHandler 操作进度回调，参数 progress 为操作进度
 * @param completionHandler 操作结果回调，如果发生错误，参数 error 返回发生的错误，否则 error 为 nil。
 */
- (void)setReverse:(BOOL)reverse progressHandler:(void(^)(float progress))progressHandler completionHandler:(void(^)(NSError *error))completionHandler;

/**
 * @brief 是否取消正在进行的倒放处理
 * @warning 此处的取消倒放并非将已经倒放的视频恢复正常播放，如果需要清除已经应用成功的倒放效果请调用 -setReverse:progressHandler:completionHandler: 并传入参数 NO。
 */
- (void)cancelReverse;

/**
 * @brief 是否倒放该片段
 */
@property (nonatomic, assign, readonly) BOOL reverse;

// 以下参数仅对 MSVMainTrackClipTypeAV 类型的主轨片段生效
#pragma mark - image properties
/**
 * @brief 图片对象
 */
@property (nonatomic, assign, readonly) UIImage *image;

/**
 * @brief 主轨片段在主轨当中的时长，此参数和 speed 互相影响，具体的运算关系为 speed = timeRange.duration / durationAtMainTrack
 */
@property (nonatomic, assign) NSTimeInterval durationAtMainTrack;

/**
 * @brief 创建一个主轨片段
 * @param type 主轨片段的类型
 * @param URL 主轨片段的文件路径，只支持本地文件
 * @param outError 如果发生错误，返回发生的错误
 * @return 创建成功返回创建完成的对象，失败返回 nil
 */
+ (instancetype)mainTrackClipWithType:(MSVMainTrackClipType)type URL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 使用 UIImage 创建一个图片类型的主轨片段
 * @param image 用于创建主轨片段的 UIImage 对象
 * @param outError 如果发生错误，返回发生的错误
 * @return 创建成功返回创建完成的对象，失败返回 nil
 */
+ (instancetype)mainTrackClipWithImage:(UIImage *)image duration:(NSTimeInterval)duration error:(NSError **)outError;

/**
 * @brief 初始化一个主轨片段
 * @param type 主轨片段的类型
 * @param URL 主轨片段的文件路径，只支持本地文件
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功返回初始化完成的对象，失败返回 nil
 */
- (instancetype)initWithType:(MSVMainTrackClipType)type URL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief 使用 UIImage 初始化一个图片类型的主轨片段
 * @param image 用于创建主轨片段的 UIImage 对象
 * @param duration 图片时长
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功返回创建完成的对象，失败返回 nil
 */
- (instancetype)initWithImage:(UIImage *)image duration:(NSTimeInterval)duration error:(NSError **)outError;

/**
 * @brief 验证改主轨片段是否有效
 * @param outError 如果发生错误，返回发生的错误
 * @return 有效返回 YES，无效返回 NO
 */
- (BOOL)validateWithError:(NSError **)outError;

- (void)refreshAsset;

@end
