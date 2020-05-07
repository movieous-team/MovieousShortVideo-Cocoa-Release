//
//  MSVDStickersView.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/1.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDStickersView.h"
#import <Masonry/Masonry.h>
#import <SDWebImage/SDWebImage.h>
#import "MSVDStickersLibrary.h"
#import <M13ProgressSuite/M13ProgressViewPie.h>

NSNotificationName const MSVDStickersViewSelectStickerNotification = @"MSVDStickersViewSelectStickerNotification";
NSNotificationName const MSVDStickersViewDoneNotification = @"MSVDStickersViewDoneNotification";
NSString *const MSVDStickersViewSelectedStickerKey = @"MSVDStickersViewSelectedStickerKey";

@interface MSVDCategoriesCollectionViewCell: UICollectionViewCell

@property (nonatomic, strong) UIImage *iconImage;

@end

@implementation MSVDCategoriesCollectionViewCell {
    UIImageView *_iconView;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        _iconView = [UIImageView new];
        _iconView.contentMode = UIViewContentModeScaleAspectFit;
        [self.contentView addSubview:_iconView];
        [_iconView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@0);
        }];
    }
    return self;
}

- (void)setIconImage:(UIImage *)icon {
    _iconView.image = icon;
}

- (UIImage *)iconImage {
    return _iconView.image;
}

@end

@interface MSVDStickersCollectionViewCell: UICollectionViewCell

- (void)updateWithSticker:(MSVDSticker *)sticker animated:(BOOL)animated;

@end

@implementation MSVDStickersCollectionViewCell {
    UIImageView *_thumbnailView;
    UIImageView *_downloadView;
    M13ProgressViewPie *_progressView;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        _thumbnailView = [UIImageView new];
        _thumbnailView.contentMode = UIViewContentModeScaleAspectFit;
        [self.contentView addSubview:_thumbnailView];
        [_thumbnailView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@0);
        }];
        
        _downloadView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"download"]];
        [self.contentView addSubview:_downloadView];
        [_downloadView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(@0);
            make.bottom.equalTo(@0);
            make.size.equalTo(@7);
        }];
        
        _progressView = [M13ProgressViewPie new];
        _progressView.primaryColor = [UIColor colorWithR:173 G:173 B:173 A:1];
        _progressView.secondaryColor = [UIColor colorWithR:126 G:126 B:126 A:1];
        _progressView.animationDuration = 0.01;
        [self.contentView addSubview:_progressView];
        [_progressView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(@0);
            make.bottom.equalTo(@0);
            make.size.equalTo(@7);
        }];
    }
    return self;
}

- (void)updateWithSticker:(MSVDSticker *)sticker animated:(BOOL)animated {
    [_thumbnailView sd_setImageWithURL:sticker.thumbnailURL];
    if (!sticker.localPaths.count) {
        if (sticker.downloading) {
            _downloadView.hidden = YES;
            _progressView.hidden = NO;
            [_progressView setProgress:sticker.progress animated:animated];
        } else {
            _downloadView.hidden = NO;
            _progressView.hidden = YES;
        }
    } else {
        _downloadView.hidden = YES;
        _progressView.hidden = YES;
    }
}

@end

@interface MSVDStickersView ()
<
UICollectionViewDelegate,
UICollectionViewDataSource
>

@end

@implementation MSVDStickersView {
    // 顶部选择工具栏
    UIView *_topView;
    UIButton *_doneButton;
    UICollectionView *_categoriesCollectionView;
    UICollectionView *_stickersCollectionView;
    NSMutableArray *_stickers;
}

- (instancetype)init {
    if (self = [super init]) {
        self.backgroundColor = UIColor.blackColor;
        
        CGFloat topViewHeight = 40;
        _topView = [UIView new];
        [self addSubview:_topView];
        [_topView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.height.equalTo(@(topViewHeight));
        }];
        
        _doneButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _doneButton.titleLabel.textColor = UIColor.whiteColor;
        [_doneButton setImage:[UIImage imageNamed:@"text_ic_confirm_n_Normal"] forState:UIControlStateNormal];
        [_doneButton addTarget:self action:@selector(doneButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_topView addSubview:_doneButton];
        [_doneButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.bottom.equalTo(@0);
            make.right.equalTo(@0);
            make.width.equalTo(@50);
        }];
        
        UICollectionViewFlowLayout *categoriesLayout = [UICollectionViewFlowLayout new];
        categoriesLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        categoriesLayout.itemSize = CGSizeMake(topViewHeight, topViewHeight);
        _categoriesCollectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:categoriesLayout];
        _categoriesCollectionView.showsHorizontalScrollIndicator = NO;
        _categoriesCollectionView.delegate = self;
        _categoriesCollectionView.dataSource = self;
        [_topView addSubview:_categoriesCollectionView];
        [_categoriesCollectionView registerClass:MSVDCategoriesCollectionViewCell.class forCellWithReuseIdentifier:@"cell"];
        [_categoriesCollectionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.bottom.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(_doneButton.mas_left);
        }];
        
        UICollectionViewFlowLayout *stickersLayout = [UICollectionViewFlowLayout new];
        stickersLayout.scrollDirection = UICollectionViewScrollDirectionVertical;
        _stickersCollectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:stickersLayout];
        _stickersCollectionView.showsVerticalScrollIndicator = NO;
        _stickersCollectionView.delegate = self;
        _stickersCollectionView.dataSource = self;
        [self addSubview:_stickersCollectionView];
        [_stickersCollectionView registerClass:MSVDStickersCollectionViewCell.class forCellWithReuseIdentifier:@"cell"];
        [_stickersCollectionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_topView.mas_bottom);
            make.bottom.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
        [MSVDStickersLibrary refresh];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickersLibraryUpdated:) name:MSVDStickersLibraryUpdatedNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickerUpdated:) name:MSVDStickerUpdatedNotification object:nil];
    }
    return self;
}

- (void)setBackgroundColor:(UIColor *)backgroundColor {
    super.backgroundColor = backgroundColor;
    _stickersCollectionView.backgroundColor = backgroundColor;
    _categoriesCollectionView.backgroundColor = backgroundColor;
}

- (void)stickersLibraryUpdated:(NSNotification *)notification {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self stickersLibraryUpdated:notification];
        });
        return;
    }
    [_stickersCollectionView reloadData];
}

- (void)stickerUpdated:(NSNotification *)notification {
    MSVDSticker *sticker = notification.object;
    [(MSVDStickersCollectionViewCell *)([_stickersCollectionView cellForItemAtIndexPath:[NSIndexPath indexPathForItem:[MSVDStickersLibrary.stickers indexOfObject:sticker] inSection:0]]) updateWithSticker:sticker animated:YES];
    if (sticker.localPaths.count > 0) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickersViewSelectStickerNotification object:self userInfo:@{MSVDStickersViewSelectedStickerKey: sticker}];
    }
}

- (void)doneButtonPressed:(UIButton *)sender {
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickersViewDoneNotification object:self];
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    MSVDSticker *sticker = MSVDStickersLibrary.stickers[indexPath.item];
    if (sticker.localPaths.count > 0) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickersViewSelectStickerNotification object:self userInfo:@{MSVDStickersViewSelectedStickerKey: sticker}];
    } else {
        [sticker download];
    }
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    if (collectionView == _categoriesCollectionView) {
        return 0;
    } else {
        return MSVDStickersLibrary.stickers.count;
    }
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    if (collectionView == _categoriesCollectionView) {
        MSVDCategoriesCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
        return cell;
    } else {
        MSVDStickersCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
        [cell updateWithSticker:MSVDStickersLibrary.stickers[indexPath.item] animated:NO];
        return cell;
    }
}

@end
