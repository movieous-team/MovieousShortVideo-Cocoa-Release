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
* 此特效在主轨中的有效时间区间.
*/
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

- (instancetype)initWithAnimatedStickerEditorEffect:(MSVAnimatedStickerEditorEffect *)animatedStickerEditorEffect;

@end

NS_ASSUME_NONNULL_END
