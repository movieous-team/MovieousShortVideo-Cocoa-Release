//
//  MSVExternalFilterEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

#import "MSVEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * 外部滤镜编辑器特效。
 */
@interface MSVExternalFilterEditorEffect : MovieousExternalFilterCaptureEffect
<
MSVEditorEffect
>

/**
 * 此特效在主轨中的有效时间区间.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 用另一个 MSVExternalFilterEditorEffect 对象初始化此 MSVExternalFilterEditorEffect
 *
 * @param externalFilterEditorEffect 用于初始化的另一个 MSVExternalFilterEditorEffect 对象。
 *
 * @return 初始化完成的 MSVExternalFilterEditorEffect 对象。
 */
- (instancetype)initWithExternalFilterEditorEffect:(MSVExternalFilterEditorEffect *)externalFilterEditorEffect;

@end

NS_ASSUME_NONNULL_END
