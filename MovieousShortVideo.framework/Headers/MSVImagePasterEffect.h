//
//  MSVImagePasterEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/24.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MovieousBase/MovieousBase.h>

/**
 * @brief 图片贴纸效果
 */
@interface MSVImagePasterEffect : NSObject

/**
 * @brief 用户自定义 ID 字段，业务使用用于区分对象
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief 图片贴纸所使用的图片
 */
@property (nonatomic, strong, readonly) UIImage *image;

/**
 * @brief 贴纸的目标位置和大小
 * @warning 长宽比例和贴纸本身的长宽比不一致时贴纸会发生变形
 */
@property (nonatomic, assign) CGRect destRect;

/**
 * @brief 在主轨当中应用外部滤镜的时间区间
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

- (instancetype)initWithImage:(UIImage *)image;

+ (instancetype)pasterEffectWithImage:(UIImage *)image;

@end
