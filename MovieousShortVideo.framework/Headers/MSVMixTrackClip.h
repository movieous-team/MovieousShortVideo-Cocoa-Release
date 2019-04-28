//
//  MSVMixTrackClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/1.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVClip.h"
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * clip used to mix video.
 */
@interface MSVMixTrackClip : MSVClip

/**
 * Create a mix track clip.
 *
 * @param type The type of mix track clip.
 * @param URL The file path of the mix track clip supports local files only.
 * @param startTimeAtMainTrack Start time at main track for the mix track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype _Nullable)mixTrackClipWithType:(MSVClipType)type URL:(NSURL *)URL startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * Use AVAsset Create the mix track clip of audio and video type using AVAsset.
 *
 * @param asset AVAsset object used to create the mix track clip.
 * @param startTimeAtMainTrack Start time at main track for the mix track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype _Nullable)mixTrackClipWithAsset:(AVAsset *)asset  startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * Create a mix track clip of a image type using UIImage.
 *
 * @param image UIImage object used to create the mix track clip.
 * @param duration Image duration.
 * @param startTimeAtMainTrack Start time at main track for the mix track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the creation is successful, the completed object is returned, otherwise returns nil.
 */
+ (instancetype _Nullable)mixTrackClipWithImage:(UIImage *)image duration:(NSTimeInterval)duration startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a mix track clip.
 *
 * @param type Type of mix track clip.
 * @param URL The file path of the mix track clip supports local files only.
 * @param startTimeAtMainTrack Start time at main track for the mix track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the initialization is successful, the completed object is returned, otherwise returns nil.
 */
- (instancetype _Nullable)initWithType:(MSVClipType)type URL:(NSURL *)URL startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a mix track clip of an audio and video type using AVAsset.
 *
 * @param asset AVAsset object used to create the mix track clip.
 * @param startTimeAtMainTrack Start time at main track for the mix track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the initialization is successful, the completed object is returned, otherwise returns nil.
 */
- (instancetype _Nullable)initWithAsset:(AVAsset *)asset startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a mix track clip of a image type using UIImage.
 *
 * @param image UIImage object used to create the mix track clip.
 * @param duration Image duration.
 * @param startTimeAtMainTrack Start time at main track for the mix track clip.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return If the initialization is successful, the completed object is returned, otherwise returns nil.
 */
- (instancetype _Nullable)initWithImage:(UIImage *)image duration:(NSTimeInterval)duration startTimeAtMainTrack:(NSTimeInterval)startTimeAtMainTrack error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize a MSVMixTrackClip with a existing MSVMixTrackClip.
 *
 * @param mixTrackClip The existing MSVMixTrackClip object.
 *
 * @return return the initialized instance.
 */
- (instancetype)initWithMixTrackClip:(MSVMixTrackClip *)mixTrackClip;

/**
 * Start time at main track to mix the clip from.
 */
@property (nonatomic, assign) NSTimeInterval startTimeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
