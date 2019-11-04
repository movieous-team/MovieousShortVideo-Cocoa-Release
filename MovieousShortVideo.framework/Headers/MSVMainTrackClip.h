//
//  MSVMainTrackClip.h
//  MSVShortVideoKit
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
 * 创建一个主轨片段。
 *
 * @param type 主轨片段的类型。
 * @param path 主轨片段的文件路径。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithType:(MSVClipType)type path:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

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
 * 使用 UIImage 对象来生成一个 MSVClipTypeImage 类型的 MSVMainTrackClip 对象。
 *
 * @param image 用来创建 MSVMainTrackClip 对象的 UIImage 对象。
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return 如果创建成功，返回创建后的对象，否则返回 nil。
 */
+ (instancetype _Nullable)mainTrackClipWithImage:(UIImage *)image duration:(NSTimeInterval)duration error:(NSError *_Nullable *_Nullable)outError;

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
