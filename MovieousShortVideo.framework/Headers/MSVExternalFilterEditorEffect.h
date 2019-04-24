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

@interface MSVExternalFilterEditorEffect : MovieousExternalFilterCaptureEffect
<
MSVBasicEditorEffect
>

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief The time interval for applying an external filter in the main track
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

- (instancetype)initWithExternalFilterCaptureEffect:(MSVExternalFilterEditorEffect *)externalFilterCaptureEffect;

@end

NS_ASSUME_NONNULL_END
