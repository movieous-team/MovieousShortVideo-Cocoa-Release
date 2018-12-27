//
//  MSVRepeatEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/11/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief Repeat effects
 */
@interface MSVRepeatEffect : NSObject

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief The time interval for applying repeat effects in the main track
 * @warning It should be noted that if multiple time-related effects (MSVRepeatEffect and MSVSpeedEffect) are inserted, the timeRangeAtMainTrack in the inserted time effect should be based on the timeline after all previous special effects are applied.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * @brief Repeat times
 */
@property (nonatomic, assign) NSUInteger count;

@end
