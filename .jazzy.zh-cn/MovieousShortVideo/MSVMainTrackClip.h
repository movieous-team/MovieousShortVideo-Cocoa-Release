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
 * Main track Clip.
 */
@interface MSVMainTrackClip : MSVClip

/**
 * Create a main track clip.
 *
 * @param type The type of main track clip.
 * @param URL The file path of the main track clip supports local files only.
 * @param outError 如果发生错误，返回错误对象。
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype)mainTrackClipWithType:(MSVClipType)type URL:(NSURL *)URL error:(NSError **)outError;

/**
 * use AVAsset to create the main track clip of audio and video type using AVAsset.
 *
 * @param asset AVAsset object used to create the main track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype)mainTrackClipWithAsset:(AVAsset *)asset error:(NSError **)outError;

/**
 * Create a main track clip of a image type using UIImage.
 *
 * @param image UIImage object used to create the main track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype)mainTrackClipWithImage:(UIImage *)image duration:(NSTimeInterval)duration error:(NSError **)outError;

/**
 * Initialize a MSVMainTrackClip with a existing MSVMainTrackClip.
 *
 * @param mainTrackClip The existing MSVMainTrackClip object.
 *
 * @return If the initialized instance.
 */
- (instancetype)initWithMainTrackClip:(MSVMainTrackClip *)mainTrackClip;

@end

NS_ASSUME_NONNULL_END
