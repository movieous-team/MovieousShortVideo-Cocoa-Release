//
//  MSVLUTEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Color lookup table filter effect class.
 */
@interface MSVLUTFilterEditorEffect : MovieousLUTFilterCaptureEffect
<
MSVEditorEffect
>

/**
 * Time range on main track in draft to use this LUT effect.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * Initiate the MSVLUTFilterEditorEffect with another MSVLUTFilterEditorEffect object.
 *
 * @param LUTFilterCaptureEffect Another MSVLUTFilterEditorEffect used to initiate the instance.
 *
 * @return The initialized MSVLUTFilterEditorEffect instance.
 */
- (instancetype)initWithLUTFilterCaptureEffect:(MSVLUTFilterEditorEffect *)LUTFilterCaptureEffect;

@end

NS_ASSUME_NONNULL_END
