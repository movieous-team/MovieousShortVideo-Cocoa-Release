//
//  MSVSpeedEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/11/2.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief Speed effects
 */
@interface MSVSpeedEffect : NSObject

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief The time interval in which the speed effect needs to be applied in the main track. This time interval refers to the time interval without the speed effect applied.
 * @warning It should be noted that if multiple time-related effects (MSVRepeatEffect and MSVSpeedEffect) are inserted, the timeRangeAtMainTrack in the inserted time effect should be based on the timeline after all previous special effects are applied.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * @brief Speed, the actual speed in the corresponding effect time interval after adding the speed effect will become the speed of each MSVMainTrackClip object in the time interval multiplied by the special effect speed.
 */
@property (nonatomic, assign) float speed;

@end

