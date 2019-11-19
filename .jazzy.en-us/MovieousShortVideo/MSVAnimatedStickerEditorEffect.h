//
//  MSVAnimatedStickerEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/8/16.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

@interface MSVAnimatedStickerEditorEffect : MovieousAnimatedStickerCaptureEffect
<
MSVEditorEffect
>

/**
 * The time range to apply the effect.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
