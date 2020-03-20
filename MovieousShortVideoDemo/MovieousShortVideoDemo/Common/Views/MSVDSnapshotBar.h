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

@end

@interface MSVDSnapshotBar : UIView

@property (nonatomic, assign) CGFloat leadingMargin;
@property (nonatomic, assign) CGFloat trailingMargin;

@property (nonatomic, assign) MSVDSnapshotBarVisibleArea visibleArea;

#pragma mark -- for video
@property (nonatomic, strong, readonly) MSVDSnapshotsCache *snapshotsCache;
@property (nonatomic, assign) MovieousTimeRange timeRange;

- (instancetype)initWithSnapshotGenerator:(MSVSnapshotGenerator *)snapshotGenerator timeRange:(MovieousTimeRange)timeRange;
- (instancetype)initWithSnapshotsCache:(MSVDSnapshotsCache *)snapshotsCache timeRange:(MovieousTimeRange)timeRange;
// 等待尺寸改变再刷新。
- (void)setNeedRefreshSnapshots;
- (void)refreshSnapshots;

#pragma mark -- for image
@property (nonatomic, strong) UIImage *image;
// 之前的起始点，用于计算 imageView 如何排布
@property (nonatomic, assign) CGFloat originalWidthWhenLeftPanStarts;

- (instancetype)initWithImage:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
