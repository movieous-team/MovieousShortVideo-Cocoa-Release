//
//  MSVLUTEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVBasicEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Color lookup table filter effect class.
 */
@interface MSVLUTFilterEditorEffect : MovieousLUTFilterCaptureEffect
<
MSVBasicEditorEffect
>

/**
 * 自定义 ID 字段，供用户使用来区分不同的对象类型。
 */
@property (nonatomic, strong) NSString *ID;

/**
 * 此特效在主轨中的有效时间区间.
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 用另一个 MSVLUTFilterEditorEffect 对象初始化此 MSVLUTFilterEditorEffect
 *
 * @param LUTFilterCaptureEffect 用于初始化的另一个 MSVLUTFilterEditorEffect 对象。
 *
 * @return 初始化完成的 MSVLUTFilterEditorEffect 对象。
 */
- (instancetype)initWithLUTFilterCaptureEffect:(MSVLUTFilterEditorEffect *)LUTFilterCaptureEffect;

@end

NS_ASSUME_NONNULL_END
