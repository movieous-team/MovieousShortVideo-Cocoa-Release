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
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype _Nullable)mainTrackClipWithType:(MSVClipType)type path:(NSString *)path error:(NSError *_Nullable *_Nullable)outError;

/**
 * use AVAsset to create the main track clip of MSVClipTypeAV.
 *
 * @param asset AVAsset object used to create the main track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype _Nullable)mainTrackClipWithAsset:(AVAsset *)asset error:(NSError *_Nullable *_Nullable)outError;

/**
 * Create a main track clip of a image type using UIImage.
 *
 * @param image UIImage object used to create the main track clip.
 * @param duration Duration of the image for the clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype _Nullable)mainTrackClipWithImage:(UIImage *)image duration:(NSTimeInterval)duration error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a MSVMainTrackClip with a existing MSVMainTrackClip.
 *
 * @param mainTrackClip The existing MSVMainTrackClip object.
 *
 * @return return the initialized instance.
 */
- (instancetype)initWithMainTrackClip:(MSVMainTrackClip *)mainTrackClip;

@end

NS_ASSUME_NONNULL_END
