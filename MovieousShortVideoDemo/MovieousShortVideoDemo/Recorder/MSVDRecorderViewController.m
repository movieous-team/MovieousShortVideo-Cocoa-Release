//
//  MSVDRecorderViewController.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/20.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDRecorderViewController.h"
#import <MovieousShortVideo/MovieousShortVideo.h>
#import <Masonry/Masonry.h>
#import "MSVDEditorViewController.h"
#import <SDMagicHook/SDMagicHook.h>
#import "MSVDMusicsViewController.h"
#import "MSVDSlider.h"
#import "MSVDFiltersLibrary.h"
#import "MSVDStickersView.h"
#import "MHFilter.h"
#import "MHMeiyanMenusView.h"
#import "MHBeautyParams.h"

#define MSVDRecordTypeSelectViewButtonMargin    20

typedef NS_ENUM(NSUInteger, MSVDRecordType) {
    MSVDRecordTypePhoto,
    MSVDRecordTypeVideo
};

@class MSVDRecordTypeSelectView;
@protocol MSVDRecordTypeSelectViewDelegate <NSObject>

- (void)recordTypeSelectView:(MSVDRecordTypeSelectView *)recordTypeSelectView type:(MSVDRecordType)type;

@end

@interface MSVDRecordTypeSelectView : UIView
<
UIScrollViewDelegate
>

@property (nonatomic, weak) id<MSVDRecordTypeSelectViewDelegate> delegate;

@end

@implementation MSVDRecordTypeSelectView {
    UIScrollView *_scrollView;
    UIButton *_photoButton;
    UIButton *_videoButton;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        UIView *recordTypeIndicator = [UIView new];
        recordTypeIndicator.backgroundColor = UIColor.whiteColor;
        recordTypeIndicator.layer.cornerRadius = 3;
        [self addSubview:recordTypeIndicator];
        [recordTypeIndicator mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.bottom.equalTo(@-5);
            make.size.equalTo(@6);
        }];
        
        _scrollView = [UIScrollView new];
        _scrollView.delegate = self;
        _scrollView.decelerationRate = UIScrollViewDecelerationRateFast;
        _scrollView.showsHorizontalScrollIndicator = NO;
        _scrollView.showsVerticalScrollIndicator = NO;
        [self addSubview:_scrollView];
        [_scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.bottom.equalTo(recordTypeIndicator).offset(-10);
        }];
        
        _photoButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_photoButton setTitleColor:UIColor.lightGrayColor forState:UIControlStateNormal];
        [_photoButton setTitleColor:UIColor.whiteColor forState:UIControlStateSelected];
        _photoButton.layer.shadowOffset = CGSizeZero;
        _photoButton.layer.shadowOpacity = 1;
        _photoButton.layer.shadowRadius = 1;
        [_photoButton setTitle:NSLocalizedString(@"MSVDRecordTypeSelectView.photo", nil) forState:UIControlStateNormal];
        [_photoButton addTarget:self action:@selector(photoButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_scrollView addSubview:_photoButton];
        [_photoButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(_scrollView.mas_left).offset(self.frame.size.width / 2);
            make.top.equalTo(@0);
            make.bottom.equalTo(@0);
        }];
        
        _videoButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_videoButton setTitleColor:UIColor.lightGrayColor forState:UIControlStateNormal];
        [_videoButton setTitleColor:UIColor.whiteColor forState:UIControlStateSelected];
        _videoButton.layer.shadowOffset = CGSizeZero;
        _videoButton.layer.shadowOpacity = 1;
        _videoButton.layer.shadowRadius = 1;
        [_videoButton setTitle:NSLocalizedString(@"MSVDRecordTypeSelectView.video", nil) forState:UIControlStateNormal];
        [_videoButton addTarget:self action:@selector(videoButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_scrollView addSubview:_videoButton];
        [_videoButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(_scrollView.mas_right).offset(-self.frame.size.width / 2);
            make.top.equalTo(@0);
            make.bottom.equalTo(@0);
            make.left.equalTo(_photoButton.mas_right).offset(MSVDRecordTypeSelectViewButtonMargin);
        }];
        
        [self videoButtonPressed:_videoButton];
    }
    return self;
}

- (void)layoutSubviews {
    [_photoButton mas_updateConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_scrollView.mas_left).offset(self.frame.size.width / 2);
    }];
    [_videoButton mas_updateConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_scrollView.mas_right).offset(-self.frame.size.width / 2);
    }];
    [self videoButtonPressed:_videoButton];
}

- (void)photoButtonPressed:(UIButton *)sender {
    [_scrollView setContentOffset:CGPointMake(0, 0) animated:YES];
    _photoButton.selected = YES;
    _videoButton.selected = NO;
    if ([_delegate respondsToSelector:@selector(recordTypeSelectView:type:)]) {
        [_delegate recordTypeSelectView:self type:MSVDRecordTypePhoto];
    }
}

- (void)videoButtonPressed:(UIButton *)sender {
    [_scrollView setContentOffset:CGPointMake(_photoButton.frame.size.width / 2 + MSVDRecordTypeSelectViewButtonMargin + _videoButton.frame.size.width / 2, 0) animated:YES];
    _photoButton.selected = NO;
    _videoButton.selected = YES;
    if ([_delegate respondsToSelector:@selector(recordTypeSelectView:type:)]) {
        [_delegate recordTypeSelectView:self type:MSVDRecordTypeVideo];
    }
}

- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset {
    if (targetContentOffset->x <= _photoButton.frame.size.width / 2 + MSVDRecordTypeSelectViewButtonMargin / 2) {
        *targetContentOffset = CGPointMake(0, 0);
        _photoButton.selected = YES;
        _videoButton.selected = NO;
        if ([_delegate respondsToSelector:@selector(recordTypeSelectView:type:)]) {
            [_delegate recordTypeSelectView:self type:MSVDRecordTypePhoto];
        }
    } else {
        *targetContentOffset = CGPointMake(_photoButton.frame.size.width / 2 + MSVDRecordTypeSelectViewButtonMargin + _videoButton.frame.size.width / 2, 0);
        _photoButton.selected = NO;
        _videoButton.selected = YES;
        if ([_delegate respondsToSelector:@selector(recordTypeSelectView:type:)]) {
            [_delegate recordTypeSelectView:self type:MSVDRecordTypeVideo];
        }
    }
}

@end

@interface MSVDBeautifyView : UIView

- (instancetype)initWithRecorder:(MSVRecorder *)recorder;

@end

@implementation MSVDBeautifyView {
    MSVRecorder *_recorder;
    MovieousBeautifyFilterCaptureEffect *_beautifyEffect;
}

- (instancetype)initWithRecorder:(MSVRecorder *)recorder {
    if (self = [super init]) {
        _recorder = recorder;
        _beautifyEffect = [MovieousBeautifyFilterCaptureEffect new];
        
        self.backgroundColor = [UIColor.blackColor colorWithAlphaComponent:0.5];
        
        UILabel *titleLabel = [UILabel new];
        titleLabel.font = [UIFont boldSystemFontOfSize:18];
        titleLabel.textColor = UIColor.whiteColor;
        titleLabel.text = NSLocalizedString(@"MSVDRecorderViewController.beautify", nil);
        [self addSubview:titleLabel];
        [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@15);
            make.centerX.equalTo(@0);
        }];
        
        UILabel *smoothLabel = [UILabel new];
        smoothLabel.font = [UIFont systemFontOfSize:13];
        smoothLabel.textColor = UIColor.whiteColor;
        smoothLabel.text = NSLocalizedString(@"MSVDRecorderViewController.smooth", nil);
        [self addSubview:smoothLabel];
        
        MSVDSlider *smoothSlider = [MSVDSlider new];
        [smoothSlider setTarget:self action:@selector(smoothSliderValueChanged:)];
        smoothSlider.slider.minimumValue = 0;
        smoothSlider.slider.maximumValue = 1;
        smoothSlider.slider.value = _beautifyEffect.smoothLevel;
        [self addSubview:smoothSlider];

        [smoothLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(smoothSlider.slider);
            make.left.equalTo(@20);
        }];
        
        [smoothSlider mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(titleLabel.mas_bottom);
            make.left.equalTo(smoothLabel.mas_right).offset(10);
            make.right.equalTo(@-20);
        }];
        
        UILabel *whiteLabel = [UILabel new];
        whiteLabel.font = [UIFont systemFontOfSize:13];
        whiteLabel.textColor = UIColor.whiteColor;
        whiteLabel.text = NSLocalizedString(@"MSVDRecorderViewController.white", nil);
        [self addSubview:whiteLabel];
        
        MSVDSlider *whiteSlider = [MSVDSlider new];
        [whiteSlider setTarget:self action:@selector(whiteSliderValueChanged:)];
        whiteSlider.slider.minimumValue = 0;
        whiteSlider.slider.maximumValue = 1;
        whiteSlider.slider.value = _beautifyEffect.whiteLevel;
        [self addSubview:whiteSlider];

        [whiteLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(whiteSlider.slider);
            make.left.equalTo(@20);
        }];
        
        [whiteSlider mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(smoothSlider.mas_bottom).offset(10);
            make.left.equalTo(whiteLabel.mas_right).offset(10);
            make.right.equalTo(@-20);
        }];
        
        UILabel *redLabel = [UILabel new];
        redLabel.font = [UIFont systemFontOfSize:13];
        redLabel.textColor = UIColor.whiteColor;
        redLabel.text = NSLocalizedString(@"MSVDRecorderViewController.red", nil);
        [self addSubview:redLabel];
        
        MSVDSlider *redSlider = [MSVDSlider new];
        [redSlider setTarget:self action:@selector(redSliderValueChanged:)];
        redSlider.slider.minimumValue = 0;
        redSlider.slider.maximumValue = 1;
        redSlider.slider.value = _beautifyEffect.redLevel;
        [self addSubview:redSlider];

        [redLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(redSlider.slider);
            make.left.equalTo(@20);
        }];
        
        [redSlider mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(whiteSlider.mas_bottom).offset(10);
            make.left.equalTo(redLabel.mas_right).offset(10);
            make.right.equalTo(@-20);
        }];
        
        UISwitch *isOnSwitch = [UISwitch new];
        [isOnSwitch addTarget:self action:@selector(beautifySwitchValueChanged:) forControlEvents:UIControlEventValueChanged];
        [self addSubview:isOnSwitch];
        [isOnSwitch mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(redSlider.mas_bottom).offset(15);
            make.bottom.equalTo(@-15);
            make.right.equalTo(@-15);
        }];
        
        UILabel *isOnLabel = [UILabel new];
        isOnLabel.font = [UIFont systemFontOfSize:15];
        isOnLabel.textColor = UIColor.whiteColor;
        isOnLabel.text = NSLocalizedString(@"MSVDRecorderViewController.isOn", nil);
        [self addSubview:isOnLabel];
        [isOnLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(isOnSwitch);
            make.right.equalTo(isOnSwitch.mas_left).offset(-10);
        }];
    }
    return self;
}

- (void)beautifySwitchValueChanged:(UISwitch *)sender {
    if (sender.isOn) {
        NSMutableArray *captureEffects = [_recorder.videoConfiguration.captureEffects mutableCopy];
        [captureEffects insertObject:_beautifyEffect atIndex:0];
        _recorder.videoConfiguration.captureEffects = captureEffects;
    } else {
        NSMutableArray *captureEffects = [_recorder.videoConfiguration.captureEffects mutableCopy];
        [captureEffects removeObjectAtIndex:0];
        _recorder.videoConfiguration.captureEffects = captureEffects;
    }
}

- (void)smoothSliderValueChanged:(MSVDSlider *)sender {
    _beautifyEffect.smoothLevel = sender.slider.value;
}

- (void)whiteSliderValueChanged:(MSVDSlider *)sender {
    _beautifyEffect.whiteLevel = sender.slider.value;
}

- (void)redSliderValueChanged:(MSVDSlider *)sender {
    _beautifyEffect.redLevel = sender.slider.value;
}

@end

@interface MSVDFiltersCollectionViewCell : UICollectionViewCell

@property (nonatomic, strong) MSVDFilter *filter;

@end

@implementation MSVDFiltersCollectionViewCell {
    UIImageView *_icon;
    UILabel *_title;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        _icon = [UIImageView new];
        [self.contentView addSubview:_icon];
        [_icon mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.height.equalTo(_icon.mas_width);
        }];
        
        _title = [UILabel new];
        _title.font = [UIFont systemFontOfSize:10];
        _title.textColor = UIColor.whiteColor;
        _title.textAlignment = NSTextAlignmentCenter;
        [self.contentView addSubview:_title];
        [_title mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_icon.mas_bottom);
            make.bottom.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
    }
    return self;
}

- (void)setFilter:(MSVDFilter *)filter {
    _filter = filter;
    if (_filter) {
        _icon.image = filter.cover;
        _title.text = filter.name;
    } else {
        _icon.image = [UIImage imageNamed:@"none"];
        _title.text = @"none";
    }
}

@end

@interface MSVDFiltersView : UIView
<
UICollectionViewDataSource,
UICollectionViewDelegate
>

- (instancetype)initWithRecorder:(MSVRecorder *)recorder;

@end

@implementation MSVDFiltersView {
    MSVRecorder *_recorder;
    MovieousLUTFilterCaptureEffect *_lutEffect;
}

- (instancetype)initWithRecorder:(MSVRecorder *)recorder {
    if (self = [super init]) {
        _recorder = recorder;
        
        self.backgroundColor = [UIColor.blackColor colorWithAlphaComponent:0.5];
        
        _lutEffect = [MovieousLUTFilterCaptureEffect new];
        
        UILabel *titleLabel = [UILabel new];
        titleLabel.font = [UIFont boldSystemFontOfSize:18];
        titleLabel.textColor = UIColor.whiteColor;
        titleLabel.text = NSLocalizedString(@"MSVDRecorderViewController.filter", nil);
        [self addSubview:titleLabel];
        [titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@15);
            make.centerX.equalTo(@0);
        }];
        
        UICollectionViewFlowLayout *layout = [UICollectionViewFlowLayout new];
        layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        layout.itemSize = CGSizeMake(50, 80);
        UICollectionView *collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:layout];
        collectionView.backgroundColor = UIColor.clearColor;
        collectionView.tag = 1;
        collectionView.delegate = self;
        collectionView.dataSource = self;
        [collectionView registerClass:MSVDFiltersCollectionViewCell.class forCellWithReuseIdentifier:@"cell"];
        [self addSubview:collectionView];
        [collectionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(titleLabel.mas_bottom).offset(10);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.bottom.equalTo(@0);
            make.height.equalTo(@80);
        }];
    }
    return self;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return MSVDFiltersLibrary.filters.count + 1;
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    MSVDFiltersCollectionViewCell *cell = (MSVDFiltersCollectionViewCell *)[collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
    if (indexPath.item == 0) {
        cell.filter = nil;
    } else {
        cell.filter = MSVDFiltersLibrary.filters[indexPath.item - 1];
    }
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    NSMutableArray *captureEffects = [_recorder.videoConfiguration.captureEffects mutableCopy];
    for (int i = 0; i < captureEffects.count;) {
        if ([captureEffects[i] isKindOfClass:MovieousLUTFilterCaptureEffect.class]) {
            [captureEffects removeObjectAtIndex:i];
        } else {
            i++;
        }
    }
    if (indexPath.item != 0) {
        _lutEffect.image = MSVDFiltersLibrary.filters[indexPath.item - 1].image;
        NSUInteger index = 0;
        if ([captureEffects.firstObject isKindOfClass:MovieousBeautifyFilterCaptureEffect.class]) {
            index = 1;
        }
        [captureEffects insertObject:_lutEffect atIndex:index];
    }
    _recorder.videoConfiguration.captureEffects = captureEffects;
}

@end

@interface MSVDRecorderViewController ()
<
MSVRecorderDelegate,
MSVDRecordTypeSelectViewDelegate,
MSVDMusicsViewControllerDelegate,
UIGestureRecognizerDelegate,
MHMeiyanMenusViewDelegate
>

@end

@implementation MSVDRecorderViewController {
    MSVRecorder *_recorder;
    UIButton *_closeButton;
    UIButton *_recordButton;
    UIButton *_doneButton;
    UIButton *_discardButton;
    UILabel *_recordedDurationLabel;
    UILabel *_recordedCountLabel;
    MSVDRecordTypeSelectView *_recordTypeView;
    NSMutableArray<MSVMainTrackClip *> *_recordedClips;
    MSVDRecordType _recordType;
    MovieousLUTFilterCaptureEffect *_lutEffect;
    UIView *_musicInformationView;
    UILabel *_musicNameLabel;
    UIButton *_switchButton;
    UILabel *_switchLabel;
    UIButton *_torchButton;
    UILabel *_torchLabel;
    UIButton *_beautifyButton;
    UILabel *_beautifyLabel;
    UIButton *_filterButton;
    UILabel *_filterLabel;
    UIButton *_stickerButton;
    UILabel *_stickerLabel;
    UIButton *_meihuButton;
    UILabel *_meihuLabel;
    MSVDBeautifyView *_beautifyView;
    MSVDFiltersView *_filtersView;
    MSVDStickersView *_stickersView;
    BOOL _bottomPopover;
    MHBeautyManager *_beautyManager;
    MHFilter *_filter;
    MHMeiyanMenusView *_meihuView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = UIColor.blackColor;
    
    _recordedClips = [NSMutableArray array];
    
    MSVRecorderAudioConfiguration *audioConfiguration = [MSVRecorderAudioConfiguration defaultConfiguration];
    MSVRecorderAVVideoConfiguration *videoConfiguration = [MSVRecorderAVVideoConfiguration defaultConfiguration];
    videoConfiguration.videoSize = CGSizeMake(544, 960);
    videoConfiguration.preferredDevicePosition = AVCaptureDevicePositionBack;
    videoConfiguration.previewScalingMode = MovieousScalingModeAspectFit;
    videoConfiguration.blurSwitch = YES;
    _beautyManager = [MHBeautyManager new];
    _filter = [MHFilter new];
    _filter.beautyManager = _beautyManager;
    MovieousExternalFilterCaptureEffect *externalFilterCaptureEffect = [MovieousExternalFilterCaptureEffect new];
    externalFilterCaptureEffect.processor = _filter;
    videoConfiguration.captureEffects = @[externalFilterCaptureEffect];
    
    NSError *error;
    _recorder = [MSVRecorder recorderWithAudioConfiguration:audioConfiguration videoConfiguration:videoConfiguration error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
    UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(viewTapped:)];
    tapGestureRecognizer.delegate = self;
    [_recorder.previewView addGestureRecognizer:tapGestureRecognizer];
    _recorder.delegate = self;
    [self.view addSubview:_recorder.previewView];
    [_recorder.previewView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.edges.equalTo(@0);
    }];
    
    _closeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_closeButton addTarget:self action:@selector(closeButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_closeButton setImage:[UIImage imageNamed:@"close_white"] forState:UIControlStateNormal];
    [self.view addSubview:_closeButton];
    [_closeButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(@25);
        make.top.equalTo(@25);
    }];
    [_closeButton hookMethod:@selector(pointInside:withEvent:) impBlock:^(UIView *v, CGPoint p, UIEvent *e) {
        [v callOriginalMethodInBlock:^{
            [v pointInside:p withEvent:e];
        }];
        if (fabs(p.x) <= 20 && fabs(p.y) <= 20) {
            return YES;
        } else {
            return NO;
        }
    }];
    
    _recordButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_recordButton addTarget:self action:@selector(recordButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_recordButton setImage:[UIImage imageNamed:@"start_recording"] forState:UIControlStateNormal];
    [_recordButton setImage:[UIImage imageNamed:@"stop_recording"] forState:UIControlStateSelected];
    [self.view addSubview:_recordButton];
    [_recordButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(@0);
        make.bottom.equalTo(@-50);
    }];
    
    _discardButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_discardButton addTarget:self action:@selector(discardButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_discardButton setImage:[UIImage imageNamed:@"discard"] forState:UIControlStateNormal];
    [self.view addSubview:_discardButton];
    [_discardButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(_recordButton);
        make.right.equalTo(_recordButton.mas_left).offset(-50);
    }];
    [_discardButton hookMethod:@selector(pointInside:withEvent:) impBlock:^(UIView *v, CGPoint p, UIEvent *e) {
        [v callOriginalMethodInBlock:^{
            [v pointInside:p withEvent:e];
        }];
        if (fabs(p.x) <= 30 && fabs(p.y) <= 30) {
            return YES;
        } else {
            return NO;
        }
    }];
    
    _doneButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_doneButton addTarget:self action:@selector(doneButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_doneButton setImage:[UIImage imageNamed:@"done"] forState:UIControlStateNormal];
    [self.view addSubview:_doneButton];
    [_doneButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(_recordButton);
        make.left.equalTo(_recordButton.mas_right).offset(50);
    }];
    [_doneButton hookMethod:@selector(pointInside:withEvent:) impBlock:^(UIView *v, CGPoint p, UIEvent *e) {
        [v callOriginalMethodInBlock:^{
            [v pointInside:p withEvent:e];
        }];
        if (fabs(p.x) <= 30 && fabs(p.y) <= 30) {
            return YES;
        } else {
            return NO;
        }
    }];
    
    _recordedCountLabel = [UILabel new];
    _recordedCountLabel.font = [UIFont systemFontOfSize:15];
    _recordedCountLabel.textColor = UIColor.whiteColor;
    _recordedCountLabel.layer.shadowOffset = CGSizeZero;
    _recordedCountLabel.layer.shadowOpacity = 1;
    _recordedCountLabel.layer.shadowRadius = 1;
    [self.view addSubview:_recordedCountLabel];
    [_recordedCountLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.center.equalTo(_recordButton);
    }];
    
//    _musicInformationView = [UIView new];
//    UITapGestureRecognizer *recognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(musicInformationViewTapped:)];
//    [_musicInformationView addGestureRecognizer:recognizer];
//    [self.view addSubview:_musicInformationView];
//    [_musicInformationView mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.centerX.equalTo(@0);
//        make.centerY.equalTo(_closeButton);
//    }];
//
//    UIImageView *musicIcon = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"music_white"]];
//    [_musicInformationView addSubview:musicIcon];
//    [musicIcon mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.left.equalTo(@0);
//        make.centerY.equalTo(@0);
//    }];
//
//    _musicNameLabel = [UILabel new];
//    _musicNameLabel.textColor = UIColor.whiteColor;
//    _musicNameLabel.text = NSLocalizedString(@"MSVDRecorderViewController.musics", nil);
//    _musicNameLabel.shadowOffset = CGSizeMake(1, 1);
//    _musicNameLabel.shadowColor = UIColor.blackColor;
//    [_musicInformationView addSubview:_musicNameLabel];
//    [_musicNameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
//        make.left.equalTo(musicIcon.mas_right);
//        make.right.equalTo(@0);
//        make.top.equalTo(@0);
//        make.bottom.equalTo(@0);
//    }];
    
    _recordedDurationLabel = [UILabel new];
    _recordedDurationLabel.font = [UIFont systemFontOfSize:10];
    _recordedDurationLabel.textColor = UIColor.whiteColor;
    _recordedDurationLabel.layer.shadowOffset = CGSizeZero;
    _recordedDurationLabel.layer.shadowOpacity = 1;
    _recordedDurationLabel.layer.shadowRadius = 1;
    [self.view addSubview:_recordedDurationLabel];
    [_recordedDurationLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(_recordButton.mas_top).offset(-5);
        make.centerX.equalTo(@0);
    }];
    
    _recordTypeView = [MSVDRecordTypeSelectView new];
    _recordTypeView.delegate = self;
    [self.view addSubview:_recordTypeView];
    [_recordTypeView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(@0);
        make.height.equalTo(@50);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
    }];
    
    _switchButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_switchButton addTarget:self action:@selector(switchButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_switchButton setImage:[UIImage imageNamed:@"switch_camera"] forState:UIControlStateNormal];
    [self.view addSubview:_switchButton];
    [_switchButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(@-20);
        make.top.equalTo(_closeButton);
    }];
    
    _switchLabel = [UILabel new];
    _switchLabel.text = NSLocalizedString(@"MSVDRecorderViewController.switch", nil);
    _switchLabel.font = [UIFont systemFontOfSize:13];
    _switchLabel.textColor = UIColor.whiteColor;
    _switchLabel.layer.shadowOffset = CGSizeZero;
    _switchLabel.layer.shadowOpacity = 1;
    _switchLabel.layer.shadowRadius = 1;
    [self.view addSubview:_switchLabel];
    [_switchLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_switchButton);
        make.top.equalTo(_switchButton.mas_bottom).offset(5);
    }];
    
    _torchButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_torchButton addTarget:self action:@selector(torchButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_torchButton setImage:[UIImage imageNamed:@"torch_off"] forState:UIControlStateNormal];
    [_torchButton setImage:[UIImage imageNamed:@"torch_on"] forState:UIControlStateSelected];
    [self.view addSubview:_torchButton];
    [_torchButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_switchLabel);
        make.top.equalTo(_switchLabel.mas_bottom).offset(10);
    }];
    
    _torchLabel = [UILabel new];
    _torchLabel.text = NSLocalizedString(@"MSVDRecorderViewController.torch", nil);
    _torchLabel.font = [UIFont systemFontOfSize:13];
    _torchLabel.textColor = UIColor.whiteColor;
    _torchLabel.layer.shadowOffset = CGSizeZero;
    _torchLabel.layer.shadowOpacity = 1;
    _torchLabel.layer.shadowRadius = 1;
    [self.view addSubview:_torchLabel];
    [_torchLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_torchButton);
        make.top.equalTo(_torchButton.mas_bottom).offset(5);
    }];
    
    _beautifyButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_beautifyButton addTarget:self action:@selector(beautifyButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_beautifyButton setImage:[UIImage imageNamed:@"beautify"] forState:UIControlStateNormal];
    [self.view addSubview:_beautifyButton];
    [_beautifyButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_torchLabel);
        make.top.equalTo(_torchLabel.mas_bottom).offset(10);
    }];
    
    _beautifyLabel = [UILabel new];
    _beautifyLabel.text = NSLocalizedString(@"MSVDRecorderViewController.beautify", nil);
    _beautifyLabel.font = [UIFont systemFontOfSize:13];
    _beautifyLabel.textColor = UIColor.whiteColor;
    _beautifyLabel.layer.shadowOffset = CGSizeZero;
    _beautifyLabel.layer.shadowOpacity = 1;
    _beautifyLabel.layer.shadowRadius = 1;
    [self.view addSubview:_beautifyLabel];
    [_beautifyLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_beautifyButton);
        make.top.equalTo(_beautifyButton.mas_bottom).offset(5);
    }];
    
    _filterButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_filterButton addTarget:self action:@selector(filterButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_filterButton setImage:[UIImage imageNamed:@"filter"] forState:UIControlStateNormal];
    [self.view addSubview:_filterButton];
    [_filterButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_beautifyLabel);
        make.top.equalTo(_beautifyLabel.mas_bottom).offset(10);
    }];
    
    _filterLabel = [UILabel new];
    _filterLabel.text = NSLocalizedString(@"MSVDRecorderViewController.filter", nil);
    _filterLabel.font = [UIFont systemFontOfSize:13];
    _filterLabel.textColor = UIColor.whiteColor;
    _filterLabel.layer.shadowOffset = CGSizeZero;
    _filterLabel.layer.shadowOpacity = 1;
    _filterLabel.layer.shadowRadius = 1;
    [self.view addSubview:_filterLabel];
    [_filterLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_filterButton);
        make.top.equalTo(_filterButton.mas_bottom).offset(5);
    }];
    
    _stickerButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_stickerButton addTarget:self action:@selector(stickerButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_stickerButton setImage:[UIImage imageNamed:@"sticker"] forState:UIControlStateNormal];
    [self.view addSubview:_stickerButton];
    [_stickerButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_filterLabel);
        make.top.equalTo(_filterLabel.mas_bottom).offset(10);
    }];
    
    _stickerLabel = [UILabel new];
    _stickerLabel.text = NSLocalizedString(@"MSVDRecorderViewController.sticker", nil);
    _stickerLabel.font = [UIFont systemFontOfSize:13];
    _stickerLabel.textColor = UIColor.whiteColor;
    _stickerLabel.layer.shadowOffset = CGSizeZero;
    _stickerLabel.layer.shadowOpacity = 1;
    _stickerLabel.layer.shadowRadius = 1;
    [self.view addSubview:_stickerLabel];
    [_stickerLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_stickerButton);
        make.top.equalTo(_stickerButton.mas_bottom).offset(5);
    }];
    
    _meihuButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_meihuButton addTarget:self action:@selector(meihuButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_meihuButton setImage:[UIImage imageNamed:@"meihu_logo"] forState:UIControlStateNormal];
    [self.view addSubview:_meihuButton];
    [_meihuButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_stickerLabel);
        make.top.equalTo(_stickerLabel.mas_bottom).offset(10);
    }];
    
    _meihuLabel = [UILabel new];
    _meihuLabel.text = NSLocalizedString(@"MSVDRecorderViewController.meihu", nil);
    _meihuLabel.font = [UIFont systemFontOfSize:13];
    _meihuLabel.textColor = UIColor.whiteColor;
    _meihuLabel.layer.shadowOffset = CGSizeZero;
    _meihuLabel.layer.shadowOpacity = 1;
    _meihuLabel.layer.shadowRadius = 1;
    [self.view addSubview:_meihuLabel];
    [_meihuLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(_meihuButton);
        make.top.equalTo(_meihuButton.mas_bottom).offset(5);
    }];
    
    _beautifyView = [[MSVDBeautifyView alloc] initWithRecorder:_recorder];
    _beautifyView.hidden = YES;
    [self.view addSubview:_beautifyView];
    [_beautifyView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
    }];
    
    _filtersView = [[MSVDFiltersView alloc] initWithRecorder:_recorder];
    _filtersView.hidden = YES;
    [self.view addSubview:_filtersView];
    [_filtersView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
    }];
    
    _stickersView = [MSVDStickersView new];
    _stickersView.backgroundColor = [UIColor.blackColor colorWithAlphaComponent:0.5];
    _stickersView.hidden = YES;
    [self.view addSubview:_stickersView];
    [_stickersView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
        make.height.equalTo(@200);
    }];
    
    _meihuView = [[MHMeiyanMenusView alloc] initWithFrame:CGRectMake(0, self.view.frame.size.height - MHMeiyanMenuHeight, self.view.frame.size.width, MHMeiyanMenuHeight) superView:self.view delegate:self beautyManager:_beautyManager isTXSDK:NO];
    
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickerSelected:) name:MSVDStickersViewSelectStickerNotification object:_stickersView];
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickerDone:) name:MSVDStickersViewDoneNotification object:_stickersView];
    [self refreshForClipsCountChange];
    [self refreshDurationLabel];
    [self refreshMirror];
}

- (void)dealloc {
    [NSNotificationCenter.defaultCenter removeObserver:self];
    [_beautyManager destroy];
}

- (void)refreshMirror {
    if (_recorder.devicePosition == AVCaptureDevicePositionBack) {
        _recorder.videoConfiguration.videoMirrored = NO;
    } else {
        _recorder.videoConfiguration.videoMirrored = YES;
    }
}

- (void)viewTapped:(UITapGestureRecognizer *)sender {
    [self refreshForBottomPopover:NO];
}

- (void)refreshForBottomPopover:(BOOL)bottomPopover {
    _bottomPopover = bottomPopover;
    if (bottomPopover) {
        _recordedDurationLabel.hidden = YES;
        _recordedCountLabel.hidden = YES;
        _discardButton.hidden = YES;
        _doneButton.hidden = YES;
        _recordButton.hidden = YES;
        _recordTypeView.hidden = YES;
    } else {
        [self refreshDurationLabel];
        [self refreshForClipsCountChange];
        _recordButton.hidden = NO;
        _recordTypeView.hidden = NO;
    }
    _beautifyView.hidden = YES;
    _stickersView.hidden = YES;
    _filtersView.hidden = YES;
    [_meihuView showMenuView:NO];
}

- (void)stickerSelected:(NSNotification *)notification {
    MSVDSticker *sticker = notification.userInfo[MSVDStickersViewSelectedStickerKey];
    MovieousStickerCaptureEffect *effect = [MovieousStickerCaptureEffect new];
    UIImage *image = [UIImage imageWithContentsOfFile:sticker.localPaths.firstObject];
    effect.image = image;
    effect.destSize = CGSizeMake(image.size.width / _recorder.videoConfiguration.videoSize.width, image.size.height / _recorder.videoConfiguration.videoSize.height);
    NSMutableArray *captureEffects = [_recorder.videoConfiguration.captureEffects mutableCopy];
    [captureEffects addObject:effect];
    _recorder.videoConfiguration.captureEffects = captureEffects;
}

- (void)stickerDone:(NSNotification *)notification {
    [self refreshForBottomPopover:NO];
}

- (void)closeButtonPressed:(UIButton *)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)musicInformationViewTapped:(UIButton *)sender {
    MSVDMusicsViewController *vc = [MSVDMusicsViewController new];
    vc.delegate = self;
    [self presentViewController:vc animated:YES completion:nil];
}

- (void)recordButtonPressed:(UIButton *)sender {
    if (_recordType == MSVDRecordTypeVideo) {
        if (sender.selected) {
            sender.enabled = NO;
            [_recorder finishRecordingWithCompletionHandler:^(NSString * _Nullable path, NSError * _Nullable error) {
                dispatch_async(dispatch_get_main_queue(), ^{
                    sender.enabled = YES;
                    sender.selected = NO;
                    self->_recordTypeView.hidden = NO;
                    if (error) {
                        SHOW_ERROR_ALERT;
                        return;
                    }
                    NSError *error;
                    MSVMainTrackClip *clip = [MSVMainTrackClip mainTrackClipWithAVPath:path error:&error];
                    if (error) {
                        SHOW_ERROR_ALERT;
                        return;
                    }
                    [self->_recordedClips addObject:clip];
                    [self refreshForClipsCountChange];
                    [self refreshDurationLabel];
                });
            }];
        } else {
            NSError *error;
            [_recorder startRecordingWithError:&error];
            if (error) {
                SHOW_ERROR_ALERT;
                return;
            }
            sender.selected = YES;
            _recordTypeView.hidden = YES;
            [self refreshForClipsCountChange];
        }
    } else {
        sender.enabled = NO;
        _recordTypeView.hidden = YES;
        [_recorder snapshotWithCompletion:^(UIImage * _Nullable image, NSError * _Nullable error) {
            dispatch_async(dispatch_get_main_queue(), ^{
                sender.enabled = YES;
                self->_recordTypeView.hidden = NO;
                if (error) {
                    SHOW_ERROR_ALERT;
                    return;
                }
                NSError *error;
                MSVMainTrackClip *clip = [MSVMainTrackClip mainTrackClipWithStillImage:image duration:3e6 error:&error];
                if (error) {
                    SHOW_ERROR_ALERT;
                    return;
                }
                [self->_recordedClips addObject:clip];
                [self refreshForClipsCountChange];
                [self refreshDurationLabel];
            });
        }];
    }
}

- (void)discardButtonPressed:(UIButton *)sender {
    [_recordedClips removeLastObject];
    [self refreshDurationLabel];
    [self refreshForClipsCountChange];
}

- (void)doneButtonPressed:(UIButton *)sender {
    NSError *error;
    MSVDraft *draft = [MSVDraft draftWithMainTrackClips:_recordedClips error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
    MSVDEditorViewController *editorViewController = [[MSVDEditorViewController alloc] initWithDraft:draft];
    [self presentViewController:editorViewController animated:YES completion:nil];
}

- (void)switchButtonPressed:(UIButton *)sender {
    [_recorder switchCamera];
    [self refreshMirror];
}

- (void)torchButtonPressed:(UIButton *)sender {
    sender.selected = !sender.selected;
    if (sender.selected) {
        _recorder.videoConfiguration.preferredTorchMode = AVCaptureTorchModeOn;
    } else {
        _recorder.videoConfiguration.preferredTorchMode = AVCaptureTorchModeOff;
    }
}

- (void)beautifyButtonPressed:(UIButton *)sender {
    BOOL previeousValue = _beautifyView.hidden;
    [self refreshForBottomPopover:_beautifyView.hidden];
    _beautifyView.hidden = !previeousValue;
}

- (void)filterButtonPressed:(UIButton *)sender {
    BOOL previeousValue = _filtersView.hidden;
    [self refreshForBottomPopover:_filtersView.hidden];
    _filtersView.hidden = !previeousValue;
}

- (void)stickerButtonPressed:(UIButton *)sender {
    BOOL previeousValue = _stickersView.hidden;
    [self refreshForBottomPopover:_stickersView.hidden];
    _stickersView.hidden = !previeousValue;
}

- (void)meihuButtonPressed:(UIButton *)sender {
    BOOL previeousValue = _meihuView.show;
    [self refreshForBottomPopover:!_meihuView.show];
    [_meihuView showMenuView:!previeousValue];
}

- (void)viewWillAppear:(BOOL)animated {
    [self tryStartCapturing];
}

- (void)tryStartCapturing {
    __weak typeof(self) wSelf = self;
    [_recorder startCapturingWithCompletion:^(BOOL audioGranted, NSError * _Nullable audioError, BOOL videoGranted, NSError * _Nullable videoError) {
        __strong typeof(wSelf) self = wSelf;
        NSError *error;
        if (videoError) {
            error = videoError;
            SHOW_ERROR_ALERT;
            return;
        }
        if (audioError) {
            error = audioError;
            SHOW_ERROR_ALERT;
            return;
        }
        if (!videoGranted) {
            SHOW_ALERT(NSLocalizedString(@"MSVDRecorderViewController.warning", nil), NSLocalizedString(@"MSVDRecorderViewController.vpermission", nil), NSLocalizedString(@"MSVDRecorderViewController.ok", nil));
            return;
        }
        if (!audioGranted) {
            SHOW_ALERT(NSLocalizedString(@"MSVDRecorderViewController.warning", nil), NSLocalizedString(@"MSVDRecorderViewController.apermission", nil), NSLocalizedString(@"MSVDRecorderViewController.ok", nil));
            return;
        }
    }];
}

- (void)viewDidDisappear:(BOOL)animated {
    [_recorder stopCapturing];
}

- (UIModalPresentationStyle)modalPresentationStyle {
    return UIModalPresentationFullScreen;
}

- (void)refreshDurationLabel {
    if (!NSThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self refreshDurationLabel];
        });
        return;
    }
    MovieousTime duration = 0;
    for (MSVMainTrackClip *clip in _recordedClips) {
        duration += clip.durationAtMainTrack;
    }
    duration += _recorder.duration;
    if (_bottomPopover || duration == 0) {
        _recordedDurationLabel.hidden = YES;
    } else {
        _recordedDurationLabel.hidden = NO;
        _recordedDurationLabel.text = [MSVDUtils formatTimeInterval:duration];
    }
}

- (void)refreshForClipsCountChange {
    if (!NSThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self refreshForClipsCountChange];
        });
        return;
    }
    if (_recordedClips.count == 0 || _recordButton.selected) {
        _recordedCountLabel.hidden = YES;
        _discardButton.hidden = YES;
        _doneButton.hidden = YES;
    } else {
        _recordedCountLabel.hidden = NO;
        _recordedCountLabel.text = [NSString stringWithFormat:@"%lu", (unsigned long)_recordedClips.count];
        _discardButton.hidden = NO;
        _doneButton.hidden = NO;
    }
}

- (void)recorder:(MSVRecorder *)recorder durationDidUpdated:(MovieousTime)duration {
    [self refreshDurationLabel];
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)recordTypeSelectView:(MSVDRecordTypeSelectView *)recordTypeSelectView type:(MSVDRecordType)type {
    _recordType = type;
}

- (void)musicsViewController:(MSVDMusicsViewController *)musicsViewController didSelectMusic:(MSVDMusic *)music {
    
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch {
    if (touch.view == _recorder.previewView) {
        return YES;
    } else {
        return NO;
    }
}

- (void)beautyEffectWithLevel:(NSInteger)beauty whitenessLevel:(NSInteger)white ruddinessLevel:(NSInteger)ruddiness {
    
}

@end
