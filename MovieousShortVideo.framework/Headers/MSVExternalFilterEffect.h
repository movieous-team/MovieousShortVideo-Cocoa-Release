//
//  MSVExternalFilterEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVExternalFilter.h"
#import "MSVBasicEffect.h"

@interface MSVExternalFilterEffect : NSObject
<
MSVBasicEffect
>

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief  The external filter class
 */
@property (nonatomic, assign) Class<MSVExternalFilter> externalFilterClass;

/**
 * @brief The time interval for applying an external filter in the main track
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

