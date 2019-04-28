//
//  MSVExternalFilterEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

#import "MSVBasicEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * External filter editor effect.
 */
@interface MSVExternalFilterEditorEffect : MovieousExternalFilterCaptureEffect
<
MSVBasicEditorEffect
>

/**
 * User-defined ID field, business usage is used to distinguish objects.
 */
@property (nonatomic, strong) NSString *ID;

/**
 * The time interval for applying an external filter in the main track.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * Initiate the MSVExternalFilterEditorEffect with another MSVExternalFilterEditorEffect object.
 *
 * @param externalFilterCaptureEffect Another MSVExternalFilterEditorEffect used to initiate the instance.
 *
 * @return The initialized MSVExternalFilterEditorEffect instance.
 */
- (instancetype)initWithExternalFilterCaptureEffect:(MSVExternalFilterEditorEffect *)externalFilterCaptureEffect;

@end

NS_ASSUME_NONNULL_END
