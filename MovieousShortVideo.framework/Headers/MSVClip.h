//
//  MSVClip.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/29.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief Media clip protocol
 */
@protocol MSVClip
<
NSObject,
NSCopying
>

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;


/**
 * @brief Media clip URL, only local file is supported
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief Time range on main track in draft
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * @brief Check if the clip is valid
 * @param outError If an error occurs, return the error that occurred
 * @return Return YES if valid, or else NO
 */
- (BOOL)validateWithError:(NSError **)outError;

@end
