//
//  MSVDSnapshotBar.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/11.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef struct {
    CGFloat x;
    CGFloat width;
} MSVDSnapshotBarVisibleArea;

@interface MSVDSnapshotsCache : NSObject

+ (instancetype)createSnapshotCacheWithClip:(MSVClip *)clip;

@end

@interface MSVDSnapshotBar : UIView

@property (nonatomic, assign) CGFloat leadingTransitionWidth;
@property (nonatomic, assign) CGFloat trailingTransitionWidth;
@property (nonatomic, assign) CGFloat leadingMargin;
@property (nonatomic, assign) CGFloat trailingMargin;

@property (nonatomic, assign) MSVDSnapshotBarVisibleArea visibleArea;

#pragma mark -- 视频或动图类型的
@property (nonatomic, strong, readonly) MSVDSnapshotsCache *snapshotsCache;
@property (nonatomic, assign) MovieousTimeRange timeRange;

- (instancetype)initWithSnapshotsCache:(MSVDSnapshotsCache *)snapshotsCache timeRange:(MovieousTimeRange)timeRange;
// 等待尺寸改变再刷新。
- (void)setNeedRefreshSnapshots;
- (void)refreshSnapshots;

#pragma mark -- 静态图片类型的
// 之前的起始点，用于计算 imageView 如何排布
@property (nonatomic, assign) CGFloat originalWidthWhenLeftPanStarts;

- (instancetype)initWithImage:(UIImage *)image originalWidthWhenLeftPanStarts:(CGFloat)originalWidthWhenLeftPanStarts;

@end

NS_ASSUME_NONNULL_END
