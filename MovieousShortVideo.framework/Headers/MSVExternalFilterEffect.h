//
//  MSVExternalFilterEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/23.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MSVExternalFilter.h"
#import <MovieousBase/MovieousBase.h>

@interface MSVExternalFilterEffect : NSObject

/**
 * @brief 用户自定义 ID 字段，业务使用用于区分对象
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief 外部滤镜的 class
 */
@property (nonatomic, assign) Class<MSVExternalFilter> externalFilterClass;

/**
 * @brief 在主轨当中应用外部滤镜的时间区间
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end
