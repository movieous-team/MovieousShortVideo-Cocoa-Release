//
//  MSVMainTrackClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 18/3/1.
//  Copyright © 2018年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MovieousBase/MovieousBase.h>
#import "MSVClip.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 主轨片段。
 */
@interface MSVMainTrackClip : MSVClip

/**
 * 创建一个 MSVClipTypeAV 类型的主轨片段。
 *
 * @param path 源文件路径，仅支持本地文件，支持 iOS 系统原生支持的所有音视频文件格式。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithAVPath:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 用 AVAsset 来生成一个 MSVClipTypeAV 类型的 MSVMainTrackClip 对象。
 *
 * @param asset 用来创建 MSVMainTrackClip 的 AVAsset 对象。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithAsset:(AVAsset *)asset error:(NSError *_Nullable *_Nullable)outError;

/**
 * 创建一个 MSVClipTypeStillImage 类型的主轨片段。
 *
 * @param path 源文件路径，仅支持本地文件，支持 iOS 系统原生支持的所有图片文件格式。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithStillImagePath:(NSString *)path duration:(MovieousTime)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用 UIImage 对象来生成一个 MSVClipTypeStillImage 类型的 MSVMainTrackClip 对象。
 *
 * @param image 用来创建 MSVMainTrackClip 对象的 UIImage 对象。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithStillImage:(UIImage *)image duration:(MovieousTime)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片地址来创建一个 MSVMainTrackClip 对象。
 *
 * @param path 动态图片地址。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithAnimatedImagePath:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片数据来创建一个 MSVMainTrackClip 对象。
 *
 * @param data 动态图片数据。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithAnimatedImageData:(NSData *)data error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用动态图片对象来创建一个 MSVMainTrackClip 对象。
 *
 * @param image 动态图片对象，image 对象需要包含 images 属性（即为动态图片对象）。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithAnimatedImage:(UIImage *)image error:(NSError *_Nullable *_Nullable)outError;

+ (instancetype _Nullable)mainTrackClipWithStillText:(NSAttributedString *)text duration:(MovieousTime)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * 使用已存在的 MSVMainTrackClip 对象来初始化一个 MSVMainTrackClip 对象。
 *
 * @param mainTrackClip 已存在的 MSVMainTrackClip 对象.
 *
 * @return 返回初始化后的对象。
 */
- (instancetype)initWithMainTrackClip:(MSVMainTrackClip *)mainTrackClip;

@end

NS_ASSUME_NONNULL_END
