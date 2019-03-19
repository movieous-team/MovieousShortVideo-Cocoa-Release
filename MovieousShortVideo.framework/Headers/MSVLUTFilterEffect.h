//
//  MSVLUTEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVBasicEffect.h"

/**
 * @brief Color lookup table filter effect class
 */
@interface MSVLUTFilterEffect : NSObject
<
MSVBasicEffect
>

/**
 * @brief User defined ID field, used to store any information you want
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief LUT(look up table) file location, only local file is supported
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief Time range on main track in draft to use this LUT effect
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end
