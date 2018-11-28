//
//  MSVLUTEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/20.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 颜色查找表滤镜特效
 */
@interface MSVLUTFilterEffect : NSObject

/**
 * @brief 用户自定义 ID 字段，业务使用用于区分对象
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief LUT(look up table) 滤镜的图片文件地址，只支持本地文件
 */
@property (nonatomic, strong, readonly) NSURL *URL;

/**
 * @brief 在主轨当中应用颜色查找表滤镜特效的时间区间
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end
