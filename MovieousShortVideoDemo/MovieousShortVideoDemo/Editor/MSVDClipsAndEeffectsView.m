//
//  MSVDClipsAndEeffectsView.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/10.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDClipsAndEeffectsView.h"
#import "MSVDSnapshotBar.h"
#import "MSVDToolboxView.h"
#import "MSVClip+MSVD.h"
#import "MSVDFrameView.h"

#define MSVDClipOrEffectViewKey  @"MSVDClipOrEffectViewKey"
#define MSVDBalloonKey      @"MSVDBalloonKey"
#define MSVDBalloonRearKey  @"MSVDBalloonRearKey"

#define DefaultDurationPerSnapshot      1e6
#define MaxDurationPerSnapshot          15e6
#define DurationDeviders                @[@10e6, @5e6, @2.5e6, @1.5e6, @1e6, @0.5e6]
#define FrameDeviders                   @[@7.5, @5, @2.5, @1.5, @1]
#define RatioToScroll                   0.25
#define ScrollTimerSpeed                20

#define ClipMargin                      2.0
#define IndicatorWidth                  2.0
#define MainTrackSnapshotBarSideLength  57.0
#define BalloonHeight                   47.0
#define BalloonRearHeight               10.0
#define VerticalItemMargin              6.0
#define CollapsedBarHeight              15.0
#define MixTrackSnapshotBarSideLength   45.0
#define MaxTimeLabelWidth               20.0
#define CollapseBarFrameWidth           2.0
#define TimeLabelSize                   10.0

NSNotificationName const MSVDAddMainTrackClipButtonPressedNotification = @"MSVDAddMainTrackClipButtonPressedNotification";
NSNotificationName const MSVDDidSelectClipOrEffectNotification = @"MSVDDidSelectClipOrEffectNotification";
NSNotificationName const MSVDDidSelectTransitionNotification = @"MSVDDidSelectTransitionNotification";

@interface MSVDClipOrEffectView : UIView

@property (nonatomic, strong, readonly) id<MSVClipOrEffect> clipOrEffect;
@property (nonatomic, assign) BOOL collapse;

@property (nonatomic, assign) CGFloat leadingTransitionWidth;
@property (nonatomic, assign) CGFloat trailingTransitionWidth;
@property (nonatomic, assign) CGFloat leadingMargin;
@property (nonatomic, assign) CGFloat trailingMargin;
@property (nonatomic, assign) MSVDSnapshotBarVisibleArea visibleArea;
@property (nonatomic, assign) MovieousTimeRange timeRange;
@property (nonatomic, assign) CGFloat originalWidthWhenLeftPanStarts;

- (instancetype)initWithClipOrEffect:(id<MSVClipOrEffect>)clipOrEffect;
- (void)refreshSnapshots;

@end

@implementation MSVDClipOrEffectView {
    MSVDSnapshotBar *_snapshotBar;
    MSVDFrameView *_collapsedBar;
}

- (instancetype)initWithClipOrEffect:(id<MSVClipOrEffect>)clipOrEffect {
    if (self = [super init]) {
        _clipOrEffect = clipOrEffect;
        if ([_clipOrEffect isKindOfClass:MSVClip.class] && [(MSVClip *)_clipOrEffect hasVisualContent] && ![(MSVClip *)_clipOrEffect ignoreVisualContent]) {
            MSVClip *clip = (MSVClip *)_clipOrEffect;
            if (clip.type != MSVClipTypeStillImage && clip.type != MSVClipTypeStillText) {
                _snapshotBar = [[MSVDSnapshotBar alloc] initWithSnapshotsCache:[MSVDSnapshotsCache createSnapshotCacheWithClip:clip] timeRange:clip.timeRange];
            } else {
                _snapshotBar = [[MSVDSnapshotBar alloc] initWithImage:[clip.snapshotGenerator generateSnapshotAtTime:0 actualTime:NULL error:nil] originalWidthWhenLeftPanStarts:0];
            }
            [self addSubview:_snapshotBar];
            [_snapshotBar mas_makeConstraints:^(MASConstraintMaker *make) {
                make.edges.equalTo(@0);
            }];
            [_snapshotBar setNeedRefreshSnapshots];
            [self addObserver:self forKeyPath:@"center" options:NSKeyValueObservingOptionNew context:nil];
            [self addObserver:self forKeyPath:@"bounds" options:NSKeyValueObservingOptionNew context:nil];
        }
        
        _collapsedBar = [MSVDFrameView new];
        _collapsedBar.cornerRadius = 2;
        _collapsedBar.frameWidth = CollapseBarFrameWidth;
        _collapsedBar.frameColor = UIColor.brownColor;
        _collapsedBar.hideTop = YES;
        _collapsedBar.hidden = YES;
        [self addSubview:_collapsedBar];
        [_collapsedBar mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@0);
        }];
        
        [self updateBackgroundColor];
    }
    return self;
}

- (void)dealloc {
    [self removeObserver:self forKeyPath:@"center"];
    [self removeObserver:self forKeyPath:@"bounds"];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context {
    [self updateVisibleArea];
}

- (void)setLeadingTransitionWidth:(CGFloat)leadingTransitionWidth {
    _leadingTransitionWidth = leadingTransitionWidth;
    _snapshotBar.leadingTransitionWidth = leadingTransitionWidth;
}

- (void)setTrailingTransitionWidth:(CGFloat)trailingTransitionWidth {
    _trailingTransitionWidth = trailingTransitionWidth;
    _snapshotBar.trailingTransitionWidth = trailingTransitionWidth;
}

- (void)setLeadingMargin:(CGFloat)leadingMargin {
    _leadingMargin = leadingMargin;
    _snapshotBar.leadingMargin = leadingMargin;
}

- (void)setTrailingMargin:(CGFloat)trailingMargin {
    _trailingMargin = trailingMargin;
    _snapshotBar.trailingMargin = trailingMargin;
}

- (void)setVisibleArea:(MSVDSnapshotBarVisibleArea)visibleArea {
    _visibleArea = visibleArea;
    [self updateVisibleArea];
}

- (void)setTimeRange:(MovieousTimeRange)timeRange {
    _timeRange = timeRange;
    _snapshotBar.timeRange = timeRange;
}

- (void)setOriginalWidthWhenLeftPanStarts:(CGFloat)originalWidthWhenLeftPanStarts {
    _originalWidthWhenLeftPanStarts = originalWidthWhenLeftPanStarts;
    _snapshotBar.originalWidthWhenLeftPanStarts = originalWidthWhenLeftPanStarts;
}

- (void)updateVisibleArea {
    _snapshotBar.visibleArea = (MSVDSnapshotBarVisibleArea) {
        _visibleArea.x - self.frame.origin.x,
        _visibleArea.width,
    };
}

- (void)refreshSnapshots {
    [_snapshotBar refreshSnapshots];
}

- (void)setCollapse:(BOOL)collapse {
    _collapse = collapse;
    _snapshotBar.hidden = collapse;
    _collapsedBar.hidden = !collapse;
    [self updateBackgroundColor];
}

- (void)updateBackgroundColor {
    if ([_clipOrEffect isKindOfClass:MSVMainTrackClip.class] || _collapse) {
        self.backgroundColor = UIColor.clearColor;
    } else {
        self.backgroundColor = UIColor.blueColor;
    }
}

@end

@interface MSVDClipsAndEeffectsView ()
<
UIScrollViewDelegate
>

@end

@implementation MSVDClipsAndEeffectsView {
    MSVEditor *_editor;
    MSVDraft *_originalDraft;
    UIScrollView *_scrollView;
    UIView *_contentView;
    UIView *_indicatorView;
    UIPinchGestureRecognizer *_pinchGestureRecognizer;
    MovieousTime _durationPerSnapshot;
    MovieousTime _durationPerSnapshotBeforeScale;
    CGFloat _offsetXBeforeScale;
    NSMutableArray<UILabel *> *_timeLineLabelPool;
    NSMutableArray<UILabel *> *_visibleTimeLineLabels;
    NSMutableArray<UIButton *> *_transitionButtons;
    UIButton *_addMainTrackClipButton;
    UIView *_snapshotBarUpperBound;
    UIView *_snapshotBarLowerBound;
    UIView *_snapshotBarLeftBound;
    UIView *_snapshotBarRightBound;
    UIPanGestureRecognizer *_leftBoundPanGestureRecognizer;
    UIPanGestureRecognizer *_rightBoundPanGestureRecognizer;
    MovieousTime _lastDurationPerSnapshot;
    NSUInteger _lastTimeLabelStartIndex;
    NSUInteger _lastTimeLabelEndIndex;
    CGFloat _lastTimeLabelLeftTranslationTotalDealta;
    CGFloat _lastTimeLabelLeftTranslation;
    CGFloat _originalBarStart;
    CGFloat _originalBarWidth;
    CGPoint _originalContentOffset;
    CGSize _originalContentSize;
    BOOL _panning;
    BOOL _panningLeft;
    NSTimer *_scrollTimer;
    CGFloat _translationTotalDelta;
    MSVDClipOrEffectView *_selectedClipOrEffectView;
    UIView *_timeLabelContainerView;
    UIView *_mixTrackContainerView;
    UIView *_mainTrackContainerView;
    NSMutableArray<MSVDSnapshotsCache *> *_snapshotsCaches;
    CGPoint _currentActualTranslation;
}

- (instancetype)initWithEditor:(MSVEditor *)editor {
    if (self = [super initWithFrame:CGRectZero]) {
        _durationPerSnapshot = DefaultDurationPerSnapshot;
        _editor = editor;
        _originalDraft = editor.draft;
        _timeLineLabelPool = [NSMutableArray array];
        _visibleTimeLineLabels = [NSMutableArray array];
        _transitionButtons = [NSMutableArray array];
        _selectedMainTrackClipIndex = NSNotFound;
        _selectedMainTrackTransitionIndex = NSNotFound;
        
        _scrollView = [UIScrollView new];
        _scrollView.backgroundColor = [UIColor colorWithRed:0.1255 green:0.1255 blue:0.1333 alpha:1];
        _scrollView.delegate = self;
        _scrollView.showsHorizontalScrollIndicator = NO;
        [self addSubview:_scrollView];
        [_scrollView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@0);
        }];
        
        _contentView = [UIView new];
        [_scrollView addSubview:_contentView];
        
        _pinchGestureRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(pinched:)];
        [_scrollView addGestureRecognizer:_pinchGestureRecognizer];
        
        _timeLabelContainerView = [UIView new];
        [_contentView addSubview:_timeLabelContainerView];
        [_timeLabelContainerView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.height.equalTo(@(TimeLabelSize));
        }];
        
        _mixTrackContainerView = [UIView new];
        [_contentView addSubview:_mixTrackContainerView];
        [_mixTrackContainerView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_timeLabelContainerView.mas_bottom).offset(VerticalItemMargin);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.height.equalTo(@(BalloonHeight + VerticalItemMargin + CollapsedBarHeight)).priorityLow();
        }];
        
        _mainTrackContainerView = [UIView new];
        [_contentView addSubview:_mainTrackContainerView];
        [_mainTrackContainerView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_mixTrackContainerView.mas_bottom).offset(VerticalItemMargin);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
        
        _indicatorView = [UIView new];
        _indicatorView.backgroundColor = UIColor.whiteColor;
        _indicatorView.layer.masksToBounds = YES;
        _indicatorView.layer.cornerRadius = IndicatorWidth / 2;
        [self addSubview:_indicatorView];
        [_indicatorView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            make.width.equalTo(@(IndicatorWidth));
            make.height.equalTo(self);
        }];
        
        _snapshotBarUpperBound = [UIView new];
        _snapshotBarUpperBound.backgroundColor = UIColor.whiteColor;
        [_contentView addSubview:_snapshotBarUpperBound];
        
        _snapshotBarLowerBound = [UIView new];
        _snapshotBarLowerBound.backgroundColor = UIColor.whiteColor;
        [_contentView addSubview:_snapshotBarLowerBound];
        
        _snapshotBarLeftBound = [UIView new];
        _snapshotBarLeftBound.backgroundColor = UIColor.whiteColor;
        [_contentView addSubview:_snapshotBarLeftBound];
        UIView *leftInnerView = [UIView new];
        leftInnerView.backgroundColor = UIColor.blackColor;
        [_snapshotBarLeftBound addSubview:leftInnerView];
        [leftInnerView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            make.width.equalTo(@2);
            make.height.equalTo(@10);
        }];
        _leftBoundPanGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(snapshotBarBoundPan:)];
        [_snapshotBarLeftBound addGestureRecognizer:_leftBoundPanGestureRecognizer];
        
        _snapshotBarRightBound = [UIView new];
        _snapshotBarRightBound.backgroundColor = UIColor.whiteColor;
        [_contentView addSubview:_snapshotBarRightBound];
        UIView *rightInnerView = [UIView new];
        rightInnerView.backgroundColor = UIColor.blackColor;
        [_snapshotBarRightBound addSubview:rightInnerView];
        [rightInnerView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            make.width.equalTo(@2);
            make.height.equalTo(@10);
        }];
        _rightBoundPanGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(snapshotBarBoundPan:)];
        [_snapshotBarRightBound addGestureRecognizer:_rightBoundPanGestureRecognizer];
        
        [self reloadMainTrackBars];
        [self reloadMixTrackBars];
        _addMainTrackClipButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self addSubview:_addMainTrackClipButton];
        [_addMainTrackClipButton setImage:[UIImage imageNamed:@"add_video_icon_Normal"] forState:UIControlStateNormal];
        [_addMainTrackClipButton addTarget:self action:@selector(addMainTrackClipButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_addMainTrackClipButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(_mainTrackContainerView.mas_top).offset(MainTrackSnapshotBarSideLength / 2);
            make.right.equalTo(@-10);
        }];
        UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(viewTapped:)];
        [self addGestureRecognizer:tapGestureRecognizer];
        [self addObservers];
    }
    return self;
}

- (void)layoutSubviews {
    [self reloadBarsLocation];
    [self updateTimeLineLabels];
    [self updateMainTrackVisibleAreas];
    [self updateMixTrackVisibleAreas];
}

- (void)addObservers {
    [_editor addObserver:self forKeyPath:@"currentTime" options:0 context:nil];
    [_editor.draft addObserver:self forKeyPath:@"mainTrackClips" options:NSKeyValueObservingOptionOld | NSKeyValueObservingOptionNew context:NULL];
    [_editor.draft addObserver:self forKeyPath:@"mainTrackTransitions" options:NSKeyValueObservingOptionOld | NSKeyValueObservingOptionNew context:NULL];
    [_editor.draft addObserver:self forKeyPath:@"mixTrackClipsOrEffects" options:NSKeyValueObservingOptionOld | NSKeyValueObservingOptionNew context:NULL];
    [_editor.draft addObserver:self forKeyPath:@"originalDuration" options:NSKeyValueObservingOptionOld | NSKeyValueObservingOptionNew context:NULL];
    [self addObserversWithMainTrackClips:_editor.draft.mainTrackClips];
    [self addObserversWithMainTrackTransitions:_editor.draft.mainTrackTransitions];
    [self addObserversWithMixTrackClipsOrEffects:_editor.draft.mixTrackClipsOrEffects];
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didChangeToToolbox:) name:MSVDToolboxViewChangeToToolboxNotification object:nil];
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(shouldSelectClipOrEffect:) name:MSVDToolboxViewShouldSelectClipOrEffectNotification object:nil];
    [_scrollView addObserver:self forKeyPath:@"contentSize" options:0 context:NULL];
}

- (void)removeObservers {
    [_editor removeObserver:self forKeyPath:@"currentTime"];
    [_editor.draft removeObserver:self forKeyPath:@"mainTrackClips"];
    [_editor.draft removeObserver:self forKeyPath:@"mainTrackTransitions"];
    [_editor.draft removeObserver:self forKeyPath:@"mixTrackClipsOrEffects"];
    [_editor.draft removeObserver:self forKeyPath:@"originalDuration"];
    [self removeObserversWithMainTrackClips:_editor.draft.mainTrackClips];
    [self removeObserversWithMainTrackTransitions:_editor.draft.mainTrackTransitions];
    [self removeObserversWithMixTrackClipsOrEffects:_editor.draft.mixTrackClipsOrEffects];
    [NSNotificationCenter.defaultCenter removeObserver:self];
    [_scrollView removeObserver:self forKeyPath:@"contentSize"];
}

- (void)addObserversWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips {
    for (MSVMainTrackClip *clip in mainTrackClips) {
        [clip addObserver:self forKeyPath:@"startTimeAtMainTrack" options:0 context:nil];
        [clip addObserver:self forKeyPath:@"durationAtMainTrack" options:0 context:nil];
        [clip addObserver:self forKeyPath:@"timeRange" options:0 context:nil];
    }
}

- (void)removeObserversWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips {
    for (MSVMainTrackClip *clip in mainTrackClips) {
        [clip removeObserver:self forKeyPath:@"startTimeAtMainTrack" context:nil];
        [clip removeObserver:self forKeyPath:@"durationAtMainTrack" context:nil];
        [clip removeObserver:self forKeyPath:@"timeRange" context:nil];
    }
}

- (void)addObserversWithMainTrackTransitions:(NSDictionary<NSNumber *, MSVMainTrackTransition *> *)mainTrackTransitions {
    for (NSNumber *index in mainTrackTransitions) {
        MSVMainTrackTransition *transition = mainTrackTransitions[index];
        [transition addObserver:self forKeyPath:@"durationAtMainTrack" options:0 context:nil];
        [transition addObserver:self forKeyPath:@"startTimeAtMainTrack" options:0 context:nil];
    }
}

- (void)removeObserversWithMainTrackTransitions:(NSDictionary<NSNumber *, MSVMainTrackTransition *> *)mainTrackTransitions {
    for (NSNumber *index in mainTrackTransitions) {
        MSVMainTrackTransition *transition = mainTrackTransitions[index];
        [transition removeObserver:self forKeyPath:@"durationAtMainTrack"];
        [transition removeObserver:self forKeyPath:@"startTimeAtMainTrack"];
    }
}

- (void)addObserversWithMixTrackClipsOrEffects:(NSArray *)mixTrackClipsOrEffects {
    for (id mixTrackClipOrEffect in mixTrackClipsOrEffects) {
        [mixTrackClipOrEffect addObserver:self forKeyPath:@"durationAtMainTrack" options:0 context:nil];
        [mixTrackClipOrEffect addObserver:self forKeyPath:@"timeRange" options:0 context:nil];
    }
}

- (void)removeObserversWithMixTrackClipsOrEffects:(NSArray *)mixTrackClipsOrEffects {
    for (id mixTrackClipOrEffect in mixTrackClipsOrEffects) {
        [mixTrackClipOrEffect removeObserver:self forKeyPath:@"durationAtMainTrack" context:nil];
        [mixTrackClipOrEffect removeObserver:self forKeyPath:@"timeRange" context:nil];
    }
}

- (void)dealloc {
    [self removeObservers];
}

- (void)viewTapped:(UITapGestureRecognizer *)sender {
    [self transitionButtonPressed:nil];
}

- (void)snapshotBarBoundPan:(UIPanGestureRecognizer *)sender {
    if (sender.state == UIGestureRecognizerStateBegan) {
        _originalBarStart = _selectedClipOrEffectView.frame.origin.x;
        _originalBarWidth = _selectedClipOrEffectView.frame.size.width;
        _originalContentSize = _scrollView.contentSize;
        _originalContentOffset = _scrollView.contentOffset;
        if (sender == _leftBoundPanGestureRecognizer) {
            _panningLeft = YES;
            _selectedClipOrEffectView.originalWidthWhenLeftPanStarts = _originalBarWidth;
        } else {
            _panningLeft = NO;
        }
        if ([_selectedClipOrEffect isKindOfClass:MSVClip.class]) {
            MSVClip *selectedClip = _selectedClipOrEffect;
            if (selectedClip.type != MSVClipTypeStillImage && selectedClip.type != MSVClipTypeStillText) {
                MSVDraft *draft = [MSVDraft new];
                NSError *error;
                draft.aspectRatio = _originalDraft.videoSize;
                draft.maximumSize = _originalDraft.videoSize;
                MSVMainTrackClip *clip = [[MSVMainTrackClip alloc] initWithClip:selectedClip];
                clip.timeRange = kMovieousTimeRangeDefault;
                clip.speed = 1;
                [draft updateMainTrackClips:@[clip] error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
                _editor.draft = draft;
            }
        }
        _panning = YES;
    } else if (sender.state == UIGestureRecognizerStateChanged) {
        CGFloat widthDelta = 0;
        _currentActualTranslation = [sender translationInView:_scrollView];
        CGFloat selectedStart = _originalBarStart;
        if (_panningLeft) {
            _currentActualTranslation.x = -_currentActualTranslation.x;
            selectedStart = _originalBarStart - _currentActualTranslation.x - _translationTotalDelta;
        }
        CGFloat selectedWidth = _originalBarWidth + _currentActualTranslation.x + _translationTotalDelta;
        if ([_selectedClipOrEffect isKindOfClass:MSVClip.class] && (((MSVClip *)_selectedClipOrEffect).type == MSVClipTypeAV || ((MSVClip *)_selectedClipOrEffect).type == MSVClipTypeAnimatedImage)) {
            MSVClip *clip = (MSVClip *)_selectedClipOrEffect;
            MovieousTime duration = selectedWidth * clip.timeRange.duration / _originalBarWidth;
            MovieousTime startTime;
            if (_panningLeft) {
                startTime = MovieousTimeRangeGetEnd(clip.timeRange) - duration;
                if (startTime < 0) {
                    startTime = 0;
                    duration = MovieousTimeRangeGetEnd(clip.timeRange) - startTime;
                    selectedWidth = duration * _originalBarWidth / clip.timeRange.duration;
                } else if (duration < MinDurationPerClip) {
                    duration = MinDurationPerClip;
                    startTime = MovieousTimeRangeGetEnd(clip.timeRange) - duration;
                    selectedWidth = duration * _originalBarWidth / clip.timeRange.duration;
                }
            } else {
                startTime = clip.timeRange.start;
                if (startTime + duration > clip.originalDuration) {
                    duration = clip.originalDuration - startTime;
                    selectedWidth = duration * _originalBarWidth / clip.timeRange.duration;
                } else if (duration < MinDurationPerClip) {
                    duration = MinDurationPerClip;
                    selectedWidth = duration * _originalBarWidth / clip.timeRange.duration;
                }
            }
            _selectedClipOrEffectView.timeRange = MovieousTimeRangeMake(startTime, duration);
            if (_panningLeft) {
                [_editor seekToTime:startTime accurate:YES];
            } else {
                [_editor seekToTime:startTime + duration accurate:YES];
            }
        } else {
            MovieousTime duration = selectedWidth / MainTrackSnapshotBarSideLength * _durationPerSnapshot;
            if (duration < MinDurationPerClip) {
                duration = MinDurationPerClip;
                selectedWidth = duration * MainTrackSnapshotBarSideLength / _durationPerSnapshot;
            }
        }
        _currentActualTranslation.x = selectedWidth - _originalBarWidth - _translationTotalDelta;
        if (_panningLeft) {
            selectedStart = _originalBarStart - _currentActualTranslation.x - _translationTotalDelta;
            if (![_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class] && selectedStart < self.frame.size.width / 2) {
                selectedStart = self.frame.size.width / 2;
                _currentActualTranslation.x = _originalBarStart - _translationTotalDelta - selectedStart;
                selectedWidth = _originalBarWidth + _currentActualTranslation.x + _translationTotalDelta;
            }
        }
        if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
            widthDelta = selectedWidth - _originalBarWidth;
        } else {
            widthDelta = self.frame.size.width + _originalBarStart + selectedWidth - _scrollView.contentSize.width;
        }
        [_selectedClipOrEffectView mas_updateConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@(selectedStart));
            make.width.equalTo(@(selectedWidth));
        }];
        if (_selectedMainTrackClipIndex != NSNotFound) {
            for (NSInteger i = 0; i < _originalDraft.mainTrackClips.count; i++) {
                MSVMainTrackClip *clip = _originalDraft.mainTrackClips[i];
                MSVDClipOrEffectView *clipOrEffectView = [clip getAttachmentForKey:MSVDClipOrEffectViewKey];
                [clipOrEffectView mas_updateConstraints:^(MASConstraintMaker *make) {
                    if (i < _selectedMainTrackClipIndex && _panningLeft) {
                        make.left.equalTo(@(self.frame.size.width / 2 + MainTrackSnapshotBarSideLength * clip.startTimeAtMainTrack / _durationPerSnapshot - _currentActualTranslation.x - _translationTotalDelta));
                    } else if (i > _selectedMainTrackClipIndex && !_panningLeft) {
                        make.left.equalTo(@(self.frame.size.width / 2 + MainTrackSnapshotBarSideLength * clip.startTimeAtMainTrack / _durationPerSnapshot + _translationTotalDelta + _currentActualTranslation.x));
                    }
                }];
            }
        }
        // 调整 _horizontalScrollView
        _scrollView.contentSize = CGSizeMake(_originalContentSize.width + widthDelta, self.frame.size.height);
        CGFloat contentOffsetX;
        if (_panningLeft) {
            contentOffsetX = _originalContentOffset.x - _translationTotalDelta;
        } else {
            contentOffsetX = _originalContentOffset.x + _translationTotalDelta;
        }
        
        _scrollView.contentOffset = CGPointMake(contentOffsetX, _originalContentOffset.y);
        if ([sender locationInView:self].x > self.frame.size.width * (1 - RatioToScroll) || [sender locationInView:self].x < self.frame.size.width * RatioToScroll) {
            [self enableScrollTimer];
        }  else {
            [self disableScrollTimer];
        }
    } else {
        MSVDClipOrEffectView *clipOrEffectView = [_selectedClipOrEffect getAttachmentForKey:MSVDClipOrEffectViewKey];
        [_originalDraft beginChangeTransaction];
        if (_panningLeft && ![_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
            ((id<MSVMutableClipOrEffect>)_selectedClipOrEffect).startTimeAtMainTrack = (clipOrEffectView.frame.origin.x - self.frame.size.width / 2) * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
        }
        NSError *error;
        if ([_selectedClipOrEffect isKindOfClass:MSVClip.class] && ((MSVClip *)_selectedClipOrEffect).type != MSVClipTypeStillImage && ((MSVClip *)_selectedClipOrEffect).type != MSVClipTypeStillText) {
            ((MSVClip *)_selectedClipOrEffect).timeRange = clipOrEffectView.timeRange;
        } else {
            _selectedClipOrEffect.durationAtMainTrack = clipOrEffectView.frame.size.width * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
        }
        [MSVDUtils ensureTransitionDurationWithDraft:_originalDraft error:nil];
        [_originalDraft commitChangeWithError:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        _editor.draft = _originalDraft;
        clipOrEffectView.originalWidthWhenLeftPanStarts = -1;
        _panning = NO;
        _currentActualTranslation = CGPointZero;
        _translationTotalDelta = 0;
        [sender setTranslation:CGPointMake(0, 0) inView:_scrollView];
        [self disableScrollTimer];
        [self reloadBarsLocation];
        MovieousTime timeToSeek;
        if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
            if (_panningLeft) {
                timeToSeek = _selectedClipOrEffect.startTimeAtMainTrack;
            } else {
                timeToSeek = MovieousTimeRangeGetEnd(_selectedClipOrEffect.timeRangeAtMainTrack) - 1;
            }
        } else {
            timeToSeek = _scrollView.contentOffset.x * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
        }
        if (timeToSeek == _editor.currentTime) {
            // 如果时间相同不会触发回调，所以手动调用一下。
            [_editor willChangeValueForKey:@"currentTime"];
            [_editor didChangeValueForKey:@"currentTime"];
        } else {
            [_editor seekToTime:timeToSeek accurate:YES];
        }
    }
    [self updateTimeLineLabels];
}

- (void)enableScrollTimer {
    if (!_scrollTimer) {
        _scrollTimer = [NSTimer scheduledTimerWithTimeInterval:0.03 target:self selector:@selector(scrollTimerFired:) userInfo:nil repeats:YES];
    }
}

- (void)disableScrollTimer {
    if (_scrollTimer) {
        [_scrollTimer invalidate];
        _scrollTimer = nil;
    }
}

- (void)scrollTimerFired:(NSTimer *)sender {
    CGFloat lowerBaseLineX = self.frame.size.width * RatioToScroll;
    CGFloat upperBaseLineX = self.frame.size.width * (1 - RatioToScroll);
    CGFloat deltaX = 0;
    if (_panningLeft) {
        CGFloat locationX = [_leftBoundPanGestureRecognizer locationInView:self].x;
        CGFloat width = _originalBarWidth + _currentActualTranslation.x - _translationTotalDelta;
        if (locationX < lowerBaseLineX) {
            // 不需要增加 translation
            if (![_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class] && _originalBarStart - _translationTotalDelta <= self.frame.size.width / 2) {
                [_scrollTimer invalidate];
                return;
            }
            deltaX = -_translationTotalDelta + ScrollTimerSpeed * (locationX - lowerBaseLineX) / lowerBaseLineX;
            if ([_selectedClipOrEffect isKindOfClass:MSVClip.class]) {
                MSVClip *selectedClip = (MSVClip *)_selectedClipOrEffect;
                if (selectedClip.type != MSVClipTypeStillImage && selectedClip.type != MSVClipTypeStillText) {
                    MovieousTime duration = width * selectedClip.timeRange.duration / _originalBarWidth;
                    MovieousTime startTime = selectedClip.timeRange.start + selectedClip.timeRange.duration - duration;
                    if (startTime < 0) {
                        [_scrollTimer invalidate];
                        return;
                    }
                    // 检查是否超过下限
                    CGFloat pendingWidth = _originalBarWidth + _currentActualTranslation.x - deltaX;
                    MovieousTime pendingDuration = pendingWidth * selectedClip.timeRange.duration / _originalBarWidth;
                    MovieousTime pendingStartTime = selectedClip.timeRange.start + selectedClip.timeRange.duration - pendingDuration;
                    if (pendingStartTime < 0) {
                        // pendingStartTime 置为 0
                        deltaX = _originalBarWidth + _currentActualTranslation.x - (selectedClip.timeRange.start + selectedClip.timeRange.duration) * _originalBarWidth / selectedClip.timeRange.duration;
                        [_scrollTimer invalidate];
                    }
                }
            }
            if (![_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class] && _originalBarStart - _currentActualTranslation.x + deltaX < self.frame.size.width / 2) {
                deltaX = self.frame.size.width / 2 - _originalBarStart + _currentActualTranslation.x;
                [_scrollTimer invalidate];
            }
        } else if (locationX > upperBaseLineX) {
            MovieousTime durationAtMainTrack = width * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
            if (durationAtMainTrack <= MinDurationPerClip) {
                [_scrollTimer invalidate];
                return;
            }
            deltaX = -_translationTotalDelta + ScrollTimerSpeed * (locationX - upperBaseLineX) / lowerBaseLineX;
            CGFloat pendingWidth = _originalBarWidth + _currentActualTranslation.x - deltaX;
            MovieousTime pendingDurationAtMainTrack = pendingWidth * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
            if (pendingDurationAtMainTrack < MinDurationPerClip) {
                deltaX = _originalBarWidth + _currentActualTranslation.x - MinDurationPerClip * MainTrackSnapshotBarSideLength / _durationPerSnapshot;
                [_scrollTimer invalidate];
            }
        }
        if (-_translationTotalDelta != deltaX) {
            _translationTotalDelta = -deltaX;
            [self snapshotBarBoundPan:_leftBoundPanGestureRecognizer];
        }
    } else {
        CGFloat locationX = [_rightBoundPanGestureRecognizer locationInView:self].x;
        CGFloat width = _originalBarWidth + _currentActualTranslation.x + _translationTotalDelta;
        if (locationX < lowerBaseLineX) {
            MovieousTime durationAtMainTrack = width * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
            if (durationAtMainTrack <= MinDurationPerClip) {
                [_scrollTimer invalidate];
                return;
            }
            deltaX = _translationTotalDelta + ScrollTimerSpeed * (locationX - lowerBaseLineX) / lowerBaseLineX;
            CGFloat pendingWidth = _originalBarWidth + _currentActualTranslation.x + deltaX;
            MovieousTime pendingDurationAtMainTrack = pendingWidth * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
            if (pendingDurationAtMainTrack < MinDurationPerClip) {
                deltaX = MinDurationPerClip * MainTrackSnapshotBarSideLength / _durationPerSnapshot - _originalBarWidth - _currentActualTranslation.x;
                [_scrollTimer invalidate];
            }
        } else if (locationX > upperBaseLineX) {
            deltaX = _translationTotalDelta + ScrollTimerSpeed * (locationX - upperBaseLineX) / lowerBaseLineX;
            if ([_selectedClipOrEffect isKindOfClass:MSVClip.class]) {
                MSVClip *selectedClip = (MSVClip *)_selectedClipOrEffect;
                if (selectedClip.type != MSVClipTypeStillImage && selectedClip.type != MSVClipTypeStillText) {
                    MovieousTime duration = selectedClip.timeRange.duration * width / _originalBarWidth;
                    if (selectedClip.timeRange.start + duration >= selectedClip.originalDuration) {
                        [_scrollTimer invalidate];
                        return;
                    }
                    CGFloat pendingWidth = _originalBarWidth + _currentActualTranslation.x + deltaX;
                    MovieousTime pendingDuration = pendingWidth * selectedClip.timeRange.duration / _originalBarWidth;
                    if (selectedClip.timeRange.start + pendingDuration > selectedClip.originalDuration) {
                        deltaX = (selectedClip.originalDuration - selectedClip.timeRange.start) * _originalBarWidth / selectedClip.timeRange.duration - _originalBarWidth - _currentActualTranslation.x;
                        [_scrollTimer invalidate];
                    }
                }
            }
        }
        if (_translationTotalDelta != deltaX) {
            _translationTotalDelta = deltaX;
            [self snapshotBarBoundPan:_rightBoundPanGestureRecognizer];
            [self updateTimeLineLabels];
        }
    }
}

- (void)reloadMainTrackBars {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self reloadMainTrackBars];
        });
        return;
    }
    for (UIView *subview in _mainTrackContainerView.subviews) {
        [subview removeFromSuperview];
    }
    [_transitionButtons removeAllObjects];
    for (int i = 0; i < _originalDraft.mainTrackClips.count; i++) {
        MSVDClipOrEffectView *clipOrEffectView = [self addClipOrEffectViewWithClipOrEffect:_originalDraft.mainTrackClips[i] startTransition:_originalDraft.mainTrackTransitions[@(i - 1)] endTransition:_originalDraft.mainTrackTransitions[@(i)]];
        if (_originalDraft.mainTrackClips.count == 1) {
            clipOrEffectView.leadingMargin = 0;
            clipOrEffectView.trailingMargin = 0;
        } else if (i == 0) {
            clipOrEffectView.leadingMargin = 0;
            clipOrEffectView.trailingMargin = ClipMargin / 2;
        } else if (i == _originalDraft.mainTrackClips.count - 1) {
            clipOrEffectView.leadingMargin = ClipMargin / 2;
            clipOrEffectView.trailingMargin = 0;
        } else {
            clipOrEffectView.leadingMargin = ClipMargin / 2;
            clipOrEffectView.trailingMargin = ClipMargin / 2;
        }
    }
    for (NSUInteger i = 0; i < _originalDraft.mainTrackClips.count - 1; i++) {
        MSVDClipOrEffectView *preClipOrEffectView = [_originalDraft.mainTrackClips[i] getAttachmentForKey:MSVDClipOrEffectViewKey];
        MSVDClipOrEffectView *postClipOrEffectView = [_originalDraft.mainTrackClips[i + 1] getAttachmentForKey:MSVDClipOrEffectViewKey];
        UIView *referenceView = [UIView new];
        referenceView.hidden = YES;
        [_mainTrackContainerView addSubview:referenceView];
        [referenceView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(postClipOrEffectView.mas_left);
            make.right.equalTo(preClipOrEffectView.mas_right);
            make.centerY.equalTo(_mainTrackContainerView.mas_top).offset(MainTrackSnapshotBarSideLength / 2);
            make.height.equalTo(@MainTrackSnapshotBarSideLength);
        }];
        UIButton *transitionButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [transitionButton setImage:[UIImage imageNamed:@"transition"] forState:UIControlStateNormal];
        [transitionButton addTarget:self action:@selector(transitionButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_mainTrackContainerView addSubview:transitionButton];
        [transitionButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(referenceView);
            make.centerX.equalTo(referenceView);
            make.width.equalTo(@38);
            make.height.equalTo(@32);
        }];
        [_transitionButtons addObject:transitionButton];
    }

    _scrollView.contentSize = CGSizeMake(self.frame.size.width + _originalDraft.originalDuration * MainTrackSnapshotBarSideLength / _durationPerSnapshot, self.frame.size.height);
    [self updateMainTrackVisibleAreas];
    [self bringBoundToFront];
}

- (void)reloadMixTrackBars {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self reloadMixTrackBars];
        });
        return;
    }
    for (UIView *subview in _mixTrackContainerView.subviews) {
        [subview removeFromSuperview];
    }
    for (id clipOrEffect in _originalDraft.mixTrackClipsOrEffects) {
        [self addClipOrEffectViewWithClipOrEffect:clipOrEffect startTransition:nil endTransition:nil];
    }
    [self updateMixTrackVerticalGeo];
    _scrollView.contentSize = CGSizeMake(self.frame.size.width + _originalDraft.originalDuration * MainTrackSnapshotBarSideLength / _durationPerSnapshot, self.frame.size.height);
    [self updateMixTrackVisibleAreas];
    [self bringBoundToFront];
}

- (void)reloadBarsLocation {
    _scrollView.contentSize = CGSizeMake(self.frame.size.width + _originalDraft.originalDuration * MainTrackSnapshotBarSideLength / _durationPerSnapshot, self.frame.size.height);
    for (NSUInteger i = 0; i < _originalDraft.mainTrackClips.count; i++) {
        MSVMainTrackClip *clip = _originalDraft.mainTrackClips[i];
        [self reloadBarLocationWithClipOrEffect:clip];
        MSVDClipOrEffectView *clipOrEffectView = [clip getAttachmentForKey:MSVDClipOrEffectViewKey];
        if (i == _selectedMainTrackClipIndex) {
            clipOrEffectView.leadingTransitionWidth = 0;
            clipOrEffectView.trailingTransitionWidth = 0;
        } else {
            MSVMainTrackTransition *preTransition = _originalDraft.mainTrackTransitions[@(i - 1)];
            MSVMainTrackTransition *postTransition = _originalDraft.mainTrackTransitions[@(i)];
            clipOrEffectView.leadingTransitionWidth = preTransition.durationAtMainTrack * MainTrackSnapshotBarSideLength / _durationPerSnapshot;
            clipOrEffectView.trailingTransitionWidth = postTransition.durationAtMainTrack * MainTrackSnapshotBarSideLength / _durationPerSnapshot;
        }
    }
    for (MSVMixTrackClip *clip in _originalDraft.mixTrackClipsOrEffects) {
        [self reloadBarLocationWithClipOrEffect:clip];
    }
}

- (MSVDClipOrEffectView *)addClipOrEffectViewWithClipOrEffect:(id<MSVClipOrEffect>)clipOrEffect startTransition:(MSVMainTrackTransition *)startTransition endTransition:(MSVMainTrackTransition *)endTransition {
    CGFloat sideLength = MixTrackSnapshotBarSideLength;
    UIView *containerView = _mixTrackContainerView;
    if ([clipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        sideLength = MainTrackSnapshotBarSideLength;
        containerView = _mainTrackContainerView;
    }
    if ([clipOrEffect isKindOfClass:MSVClip.class]) {
        MSVClip *clip = (MSVClip *)clipOrEffect;
        if (clip.defaultSize.width > clip.defaultSize.height) {
            clip.snapshotGenerator.maximumSize = CGSizeMake(sideLength * clip.defaultSize.width / clip.defaultSize.height * UIScreen.mainScreen.scale, sideLength * UIScreen.mainScreen.scale);
        } else {
            clip.snapshotGenerator.maximumSize = CGSizeMake(sideLength * UIScreen.mainScreen.scale, sideLength * clip.defaultSize.height / clip.defaultSize.width * UIScreen.mainScreen.scale);
        }
    }
    MSVDClipOrEffectView *clipOrEffectView = [clipOrEffect getAttachmentForKey:MSVDClipOrEffectViewKey];
    if (!clipOrEffectView) {
        clipOrEffectView = [[MSVDClipOrEffectView alloc] initWithClipOrEffect:clipOrEffect];
        [clipOrEffect setAttachment:clipOrEffectView forKey:MSVDClipOrEffectViewKey];
        UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(clipOrEffectViewTapped:)];
        [clipOrEffectView addGestureRecognizer:tapGestureRecognizer];
    }
    [containerView addSubview:clipOrEffectView];
    if ([clipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        [clipOrEffectView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.height.equalTo(@(sideLength));
            make.bottom.equalTo(@0);
        }];
    } else {
        UIButton *balloon = [clipOrEffect getAttachmentForKey:MSVDBalloonKey];
        if (!balloon) {
            balloon = [UIButton buttonWithType:UIButtonTypeCustom];
            [balloon addTarget:self action:@selector(balloonTapped:) forControlEvents:UIControlEventTouchUpInside];
            balloon.backgroundColor = UIColor.redColor;
            balloon.maskView = [UIView new];
            balloon.maskView.backgroundColor = [UIColor colorWithPatternImage:[UIImage imageNamed:@"balloon"]];
            balloon.maskView.frame = CGRectMake(0, 0, 35, BalloonHeight);
            [clipOrEffect setAttachment:balloon forKey:MSVDBalloonKey];
            if ([clipOrEffect isKindOfClass:MSVClip.class]) {
                MSVClip *clip = (MSVClip *)clipOrEffect;
                [balloon setImage:[clip.snapshotGenerator generateSnapshotAtTime:0 actualTime:NULL error:nil] forState:UIControlStateNormal];
            }
        }
        [_mixTrackContainerView addSubview:balloon];
        [balloon mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.centerX.equalTo(clipOrEffectView.mas_left);
            make.height.equalTo(@BalloonHeight);
            make.width.equalTo(@37);
        }];
        
        UIView *balloonRear = [clipOrEffect getAttachmentForKey:MSVDBalloonRearKey];
        if (!balloonRear) {
            balloonRear = [UIView new];
            balloonRear.backgroundColor = UIColor.whiteColor;
            [clipOrEffect setAttachment:balloonRear forKey:MSVDBalloonRearKey];
        }
        [_mixTrackContainerView addSubview:balloonRear];
        [balloonRear mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(balloon);
            make.top.equalTo(balloon.mas_bottom).offset(VerticalItemMargin);
            make.height.equalTo(@BalloonRearHeight);
            make.width.equalTo(@2);
        }];
        
        [clipOrEffectView mas_makeConstraints:^(MASConstraintMaker *make) {
            // 低优先级，不一定所有的 clipOrEffectView 底部都能跟 _mixTrackContainerView 底部对齐。
            make.bottom.equalTo(@0).priorityLow();
            make.bottom.lessThanOrEqualTo(@0);
        }];
    }
    [self reloadBarLocationWithClipOrEffect:clipOrEffect];
    return clipOrEffectView;
}

- (void)reloadBarLocationWithClipOrEffect:(id<MSVClipOrEffect>)clipOrEffect {
    MSVDClipOrEffectView *clipOrEffectView = [clipOrEffect getAttachmentForKey:MSVDClipOrEffectViewKey];
    [clipOrEffectView mas_updateConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(@(self.frame.size.width / 2 + MainTrackSnapshotBarSideLength * clipOrEffect.startTimeAtMainTrack / _durationPerSnapshot));
        make.width.equalTo(@(clipOrEffect.durationAtMainTrack * MainTrackSnapshotBarSideLength / _durationPerSnapshot));
    }];
}


- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self observeValueForKeyPath:keyPath ofObject:object change:change context:context];
        });
        return;
    }
    if ([object isKindOfClass:MSVDraft.class]) {
        if ([keyPath isEqualToString:@"mainTrackClips"]) {
            id oldMainTrackClips = change[NSKeyValueChangeOldKey];
            if (oldMainTrackClips != [NSNull null]) {
                [self removeObserversWithMainTrackClips:oldMainTrackClips];
            }
            id newMainTrackClips = change[NSKeyValueChangeNewKey];
            if (newMainTrackClips != [NSNull null]) {
                [self addObserversWithMainTrackClips:newMainTrackClips];
            }
            [self reloadMainTrackBars];
            id selectedClipOrEffect = _selectedClipOrEffect;
            if (![_originalDraft.mainTrackClips containsObject:selectedClipOrEffect] && ![_originalDraft.mixTrackClipsOrEffects containsObject:selectedClipOrEffect]) {
                selectedClipOrEffect = nil;
            }
            [self selectClipOrEffect:selectedClipOrEffect];
            [self updateTimeLineLabels];
        } else if ([keyPath isEqualToString:@"mainTrackTransitions"]) {
            id oldMainTrackTransitions = change[NSKeyValueChangeOldKey];
            if (oldMainTrackTransitions != [NSNull null]) {
                [self removeObserversWithMainTrackTransitions:oldMainTrackTransitions];
            }
            id newMainTrackTransitions = change[NSKeyValueChangeNewKey];
            if (newMainTrackTransitions != [NSNull null]) {
                [self addObserversWithMainTrackTransitions:newMainTrackTransitions];
            }
            [self reloadBarsLocation];
            [self updateTimeLineLabels];
        } else if ([keyPath isEqualToString:@"mixTrackClipsOrEffects"]) {
            id oldMixTrackClipsOrEffects = change[NSKeyValueChangeOldKey];
            if (oldMixTrackClipsOrEffects != [NSNull null]) {
                [self removeObserversWithMixTrackClipsOrEffects:oldMixTrackClipsOrEffects];
            }
            id newMixTrackClipsOrEffects = change[NSKeyValueChangeNewKey];
            if (newMixTrackClipsOrEffects != [NSNull null]) {
                [self addObserversWithMixTrackClipsOrEffects:newMixTrackClipsOrEffects];
            }
            [self reloadMixTrackBars];
            id selectedClipOrEffect = _selectedClipOrEffect;
            if (![_originalDraft.mainTrackClips containsObject:selectedClipOrEffect] && ![_originalDraft.mixTrackClipsOrEffects containsObject:selectedClipOrEffect]) {
                selectedClipOrEffect = nil;
            }
            [self selectClipOrEffect:selectedClipOrEffect];
            [self updateTimeLineLabels];
        } else if ([keyPath isEqualToString:@"originalDuration"]) {
            [self reloadBarsLocation];
            [self updateTimeLineLabels];
        }
    } else if ([object isKindOfClass:MSVClip.class]) {
        [self reloadBarsLocation];
        [self updateTimeLineLabels];
    } else if ([object isKindOfClass:MSVMainTrackTransition.class]) {
        [self reloadBarsLocation];
        [self updateTimeLineLabels];
    } else if ([object isKindOfClass:MSVEditor.class]) {
        if (!_panning && _editor.status != MSVEditorStatusSeeking && !_scrollView.isDragging && !_scrollView.isDecelerating) {
            CGFloat offsetX = (_scrollView.contentSize.width - self.frame.size.width) * _editor.currentTime / _editor.draft.originalDuration;
            _scrollView.contentOffset = CGPointMake(offsetX, 0);
        }
    } else if ([object isKindOfClass:UIScrollView.class]) {
        _contentView.frame = CGRectMake(0, 0, _scrollView.contentSize.width, _scrollView.contentSize.height);
    }
}

- (void)clipOrEffectViewTapped:(UITapGestureRecognizer *)sender {
    MSVDClipOrEffectView *clipOrEffectView = (MSVDClipOrEffectView *)sender.view;
    for (id<MSVMutableClipOrEffect> mixTrackClipOrEffect in _originalDraft.mixTrackClipsOrEffects) {
        if ([mixTrackClipOrEffect getAttachmentForKey:MSVDClipOrEffectViewKey] == clipOrEffectView) {
            [self selectClipOrEffect:mixTrackClipOrEffect];
            break;
        }
    }
    for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
        if ([clip getAttachmentForKey:MSVDClipOrEffectViewKey] == clipOrEffectView) {
            [self selectClipOrEffect:clip];
            break;
        }
    }
}

- (void)balloonTapped:(UIButton *)sender {
    for (id<MSVMutableClipOrEffect> mixTrackClipOrEffect in _originalDraft.mixTrackClipsOrEffects) {
        if ([mixTrackClipOrEffect getAttachmentForKey:MSVDBalloonKey] == sender) {
            [self selectClipOrEffect:mixTrackClipOrEffect];
            break;
        }
    }
    for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
        if ([clip getAttachmentForKey:MSVDBalloonKey] == sender) {
            [self selectClipOrEffect:clip];
            break;
        }
    }
}

- (void)transitionButtonPressed:(UIButton *)sender {
    [self selectClipOrEffect:nil];
    _selectedMainTrackTransitionIndex = [_transitionButtons indexOfObject:sender];
    sender.layer.borderWidth = 2;
    sender.layer.borderColor = UIColor.redColor.CGColor;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDDidSelectTransitionNotification object:self];
}

- (void)selectClipOrEffect:(id<MSVClipOrEffect>)clipOrEffect {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self selectClipOrEffect:clipOrEffect];
        });
        return;
    }
    for (UIButton *button in _transitionButtons) {
        button.layer.borderWidth = 0;
    }
    if (clipOrEffect == _selectedClipOrEffect) {
        return;
    }
    if (clipOrEffect) {
        _selectedClipOrEffectView = [clipOrEffect getAttachmentForKey:MSVDClipOrEffectViewKey];
        [_selectedClipOrEffectView.superview bringSubviewToFront:_selectedClipOrEffectView];
        [_contentView bringSubviewToFront:_snapshotBarUpperBound];
        _snapshotBarUpperBound.alpha = 1;
        [_snapshotBarUpperBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(_selectedClipOrEffectView.mas_top);
            make.left.equalTo(_selectedClipOrEffectView);
            make.right.equalTo(_selectedClipOrEffectView);
            make.height.equalTo(@2);
        }];
        
        [_contentView bringSubviewToFront:_snapshotBarLowerBound];
        _snapshotBarLowerBound.alpha = 1;
        [_snapshotBarLowerBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_selectedClipOrEffectView.mas_bottom);
            make.left.equalTo(_selectedClipOrEffectView);
            make.right.equalTo(_selectedClipOrEffectView);
            make.height.equalTo(@2);
        }];
        
        [_contentView bringSubviewToFront:_snapshotBarLeftBound];
        _snapshotBarLeftBound.alpha = 1;
        [_snapshotBarLeftBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            // 避免先更新上边界可能会出现无法满足限制的警告。
            make.top.equalTo(_snapshotBarUpperBound.mas_top).priorityHigh();
            make.bottom.equalTo(_snapshotBarLowerBound.mas_bottom).priorityHigh();
            make.right.equalTo(_selectedClipOrEffectView.mas_left);
            make.width.equalTo(@25);
        }];
        
        [_contentView bringSubviewToFront:_snapshotBarRightBound];
        _snapshotBarRightBound.alpha = 1;
        [_snapshotBarRightBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            // 避免先更新上边界可能会出现无法满足限制的警告。
            make.top.equalTo(_snapshotBarUpperBound.mas_top).priorityHigh();
            make.bottom.equalTo(_snapshotBarLowerBound.mas_bottom).priorityHigh();
            make.left.equalTo(_selectedClipOrEffectView.mas_right);
            make.width.equalTo(@25);
        }];
        
        if ([clipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
            _selectedMainTrackClipIndex = [_editor.draft.mainTrackClips indexOfObject:clipOrEffect];
            if (_selectedMainTrackClipIndex == NSNotFound) {
                [self selectClipOrEffect:nil];
                return;
            }
            if (_selectedMainTrackClipIndex != 0) {
                [_snapshotBarLeftBound mas_updateConstraints:^(MASConstraintMaker *make) {
                    // 避免有一个间隔
                    make.right.equalTo(_selectedClipOrEffectView.mas_left).offset(ClipMargin / 2);
                }];
            }
            if (_selectedMainTrackClipIndex != _originalDraft.mainTrackClips.count - 1) {
                [_snapshotBarRightBound mas_updateConstraints:^(MASConstraintMaker *make) {
                    // 避免有一个间隔
                    make.left.equalTo(_selectedClipOrEffectView.mas_right).offset(-ClipMargin / 2);
                }];
            }
        } else {
            _selectedMainTrackClipIndex = NSNotFound;
        }
    } else {
        _snapshotBarUpperBound.alpha = 0;
        _snapshotBarLowerBound.alpha = 0;
        _snapshotBarLeftBound.alpha = 0;
        _snapshotBarRightBound.alpha = 0;
        _selectedMainTrackClipIndex = NSNotFound;
    }
    if (_selectedMainTrackClipIndex == NSNotFound) {
        [self reloadBarsLocation];
        for (UIButton *button in _transitionButtons) {
            button.hidden = NO;
            [button.superview bringSubviewToFront:button];
        }
    } else {
        _selectedClipOrEffectView.leadingTransitionWidth = 0;
        _selectedClipOrEffectView.trailingTransitionWidth = 0;
        if (_selectedMainTrackClipIndex > 0 && _selectedMainTrackClipIndex <= _transitionButtons.count) {
            UIButton *button = _transitionButtons[_selectedMainTrackClipIndex - 1];
            button.hidden = YES;
            [button.superview bringSubviewToFront:button];
        }
        if (_selectedMainTrackClipIndex >= 0 && _selectedMainTrackClipIndex < _transitionButtons.count) {
            UIButton *button = _transitionButtons[_selectedMainTrackClipIndex];
            button.hidden = YES;
            [button.superview bringSubviewToFront:button];
        }
    }
    _selectedClipOrEffect = clipOrEffect;
    [self updateMixTrackVerticalGeo];
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDDidSelectClipOrEffectNotification object:self];
}

- (void)updateMixTrackVerticalGeo {
    for (id<MSVMutableClipOrEffect> clipOrEffect in _originalDraft.mixTrackClipsOrEffects) {
        UIButton *balloon = [clipOrEffect getAttachmentForKey:MSVDBalloonKey];
        UIView *balloonRear = [clipOrEffect getAttachmentForKey:MSVDBalloonRearKey];
        MSVDClipOrEffectView *clipOrEffectView = [clipOrEffect getAttachmentForKey:MSVDClipOrEffectViewKey];
        if (clipOrEffect == _selectedClipOrEffect) {
            balloonRear.hidden = NO;
            [clipOrEffectView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.top.equalTo(balloon.mas_bottom).offset(BalloonRearHeight + 2 * VerticalItemMargin);
                make.height.equalTo(@(MixTrackSnapshotBarSideLength));
            }];
            clipOrEffectView.collapse = NO;
        } else {
            balloonRear.hidden = YES;
            [clipOrEffectView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.top.equalTo(balloon.mas_bottom).offset(VerticalItemMargin);
                make.height.equalTo(@(CollapsedBarHeight));
            }];
            clipOrEffectView.collapse = YES;
        }
    }
}

- (void)bringBoundToFront {
    [_scrollView bringSubviewToFront:_snapshotBarUpperBound];
    [_scrollView bringSubviewToFront:_snapshotBarLowerBound];
    [_scrollView bringSubviewToFront:_snapshotBarLeftBound];
    [_scrollView bringSubviewToFront:_snapshotBarRightBound];
}

- (void)updateTimeLineLabels {
    MovieousTime labelDevider = 0;
    if (_durationPerSnapshot >= 0.5e6) {
        for (NSNumber *devider in DurationDeviders) {
            if (_durationPerSnapshot >= devider.longLongValue) {
                labelDevider = devider.longLongValue;
                break;
            }
        }
    } else {
        if (_durationPerSnapshot < [FrameDeviders.lastObject doubleValue] * 1e6 / VideoFrameRate) {
            labelDevider = [FrameDeviders.lastObject doubleValue] * 1e6 / VideoFrameRate;
        } else {
            for (NSNumber *devider in FrameDeviders) {
                if (_durationPerSnapshot >= devider.doubleValue * 1e6 / VideoFrameRate) {
                    labelDevider = devider.doubleValue * 1e6 / VideoFrameRate;
                    break;
                }
            }
        }
    }
    CGFloat leftTranslationTotalDelta = 0;
    CGFloat leftTranslation = 0;
    if (_panningLeft) {
        if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
            leftTranslationTotalDelta = -_translationTotalDelta;
            leftTranslation = -_currentActualTranslation.x;
        }
    }
    CGFloat startBaseline = _scrollView.contentOffset.x - self.frame.size.width / 2 - MaxTimeLabelWidth / 2 - leftTranslation - leftTranslationTotalDelta;
    MovieousTime startInterval = startBaseline * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
    if (startInterval < 0) {
        startInterval = 0;
    }
    NSUInteger startIndex = ceil((double)startInterval / labelDevider);
    CGFloat endBaseline = _scrollView.contentOffset.x + self.frame.size.width / 2 + MaxTimeLabelWidth / 2 - leftTranslation - leftTranslationTotalDelta;
    MovieousTime endInterval = endBaseline * _durationPerSnapshot / MainTrackSnapshotBarSideLength;
    if (endInterval < 0) {
        endInterval = 0;
    }
    if (endInterval > _originalDraft.originalDuration) {
        endInterval = _originalDraft.originalDuration;
    }
    NSUInteger endIndex = (NSUInteger)(endInterval / labelDevider);
    if (_lastTimeLabelLeftTranslationTotalDealta == leftTranslationTotalDelta && _lastDurationPerSnapshot == _durationPerSnapshot && _lastTimeLabelStartIndex == startIndex && _lastTimeLabelEndIndex == endIndex && _lastTimeLabelLeftTranslation == leftTranslation) {
        return;
    }
    _lastTimeLabelLeftTranslationTotalDealta = leftTranslationTotalDelta;
    _lastDurationPerSnapshot = _durationPerSnapshot;
    _lastTimeLabelStartIndex = startIndex;
    _lastTimeLabelEndIndex = endIndex;
    _lastTimeLabelLeftTranslation = leftTranslation;
    NSMutableArray *timeLineLabelsToRecycle = _visibleTimeLineLabels;
    _visibleTimeLineLabels = [NSMutableArray array];
    for (NSUInteger i = startIndex; i <= endIndex; i++) {
        UILabel *label;
        if (timeLineLabelsToRecycle.count > 0) {
            label = timeLineLabelsToRecycle.lastObject;
            [timeLineLabelsToRecycle removeLastObject];
        } else if (_timeLineLabelPool.count > 0) {
            label = _timeLineLabelPool.lastObject;
            [_timeLabelContainerView addSubview:label];
            [_timeLineLabelPool removeLastObject];
        } else {
            label = [UILabel new];
            label.textColor = UIColor.whiteColor;
            label.font = [UIFont systemFontOfSize:TimeLabelSize];
            [_timeLabelContainerView addSubview:label];
        }
        [_visibleTimeLineLabels addObject:label];
        if (i % 2 == 0) {
            if (_durationPerSnapshot >= 0.5e6) {
                label.text = [MSVDUtils formatTimeInterval:i * labelDevider];
            } else {
                unsigned long frameIndex = round((double)i * labelDevider * VideoFrameRate / 1e6);
                if (frameIndex % VideoFrameRate == 0) {
                    label.text = [MSVDUtils formatTimeInterval:1e6 * frameIndex / VideoFrameRate];
                } else {
                    label.text = [NSString stringWithFormat:@"%luf", frameIndex % (unsigned long)VideoFrameRate];
                }
            }
        } else {
            label.text = @"·";
        }
        [label mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.centerX.equalTo(_timeLabelContainerView.mas_left).offset(self.frame.size.width / 2 + i * MainTrackSnapshotBarSideLength * labelDevider / _durationPerSnapshot + leftTranslationTotalDelta + leftTranslation);
        }];
    }
    for (UILabel *label in timeLineLabelsToRecycle) {
        [label removeFromSuperview];
        [_timeLineLabelPool addObject:label];
    }
}

- (void)addMainTrackClipButtonPressed:(UIButton *)sender {
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDAddMainTrackClipButtonPressedNotification object:self];
}

- (void)pinched:(UIPinchGestureRecognizer *)sender {
    if (sender.state == UIGestureRecognizerStateBegan) {
        _durationPerSnapshotBeforeScale = _durationPerSnapshot;
        _offsetXBeforeScale = _scrollView.contentOffset.x;
        _scrollView.scrollEnabled = NO;
    } else {
        MovieousTime pendingDurationPerThumbnail = _durationPerSnapshotBeforeScale / sender.scale;
        if (pendingDurationPerThumbnail > MaxDurationPerSnapshot) {
            sender.scale = (CGFloat)_durationPerSnapshotBeforeScale / MaxDurationPerSnapshot;
            _durationPerSnapshot = MaxDurationPerSnapshot;
        } else if (pendingDurationPerThumbnail < 1e6 / VideoFrameRate) {
            sender.scale = _durationPerSnapshotBeforeScale * VideoFrameRate / 1e6;
            _durationPerSnapshot = 1e6 / VideoFrameRate;
        } else {
            _durationPerSnapshot = pendingDurationPerThumbnail;
        }
        for (int i = 0; i < _originalDraft.mainTrackClips.count; i++) {
            MSVMainTrackClip *clip = _originalDraft.mainTrackClips[i];
            MSVDClipOrEffectView *clipOrEffectView = [clip getAttachmentForKey:MSVDClipOrEffectViewKey];
            CGFloat width = MainTrackSnapshotBarSideLength * clip.durationAtMainTrack / _durationPerSnapshot;
            [clipOrEffectView mas_updateConstraints:^(MASConstraintMaker *make) {
                make.width.equalTo(@(width));
            }];
            // 松开手再刷新，避免频繁刷新，影响性能。
            if (sender.state >= UIGestureRecognizerStateEnded) {
                [clipOrEffectView refreshSnapshots];
            }
        }
        _scrollView.contentSize = CGSizeMake(self.frame.size.width + _originalDraft.originalDuration * MainTrackSnapshotBarSideLength / _durationPerSnapshot, self.frame.size.height);
        _scrollView.contentOffset = CGPointMake(_offsetXBeforeScale * sender.scale, _scrollView.contentOffset.y);
        [self reloadBarsLocation];
        [self updateTimeLineLabels];
        if (sender.state >= UIGestureRecognizerStateEnded) {
            _scrollView.scrollEnabled = YES;
        }
    }
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    [_editor pause];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    if (scrollView.isDragging || scrollView.isDecelerating) {
        [_editor seekToTime:_editor.draft.originalDuration * scrollView.contentOffset.x / (scrollView.contentSize.width - self.frame.size.width) accurate:YES];
    }
    [self updateTimeLineLabels];
    [self updateMainTrackVisibleAreas];
    [self updateMixTrackVisibleAreas];
}

- (void)updateMainTrackVisibleAreas {
    for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
        MSVDClipOrEffectView *clipOrEffectView = [clip getAttachmentForKey:MSVDClipOrEffectViewKey];
        clipOrEffectView.visibleArea = (MSVDSnapshotBarVisibleArea){_scrollView.contentOffset.x, self.frame.size.width};
    }
}

- (void)updateMixTrackVisibleAreas {
    for (MSVMixTrackClip *clip in _originalDraft.mixTrackClipsOrEffects) {
        if ([clip isKindOfClass:MSVMixTrackClip.class]) {
            MSVDClipOrEffectView *clipOrEffectView = [clip getAttachmentForKey:MSVDClipOrEffectViewKey];
            clipOrEffectView.visibleArea = (MSVDSnapshotBarVisibleArea){_scrollView.contentOffset.x, self.frame.size.width};
        }
    }
}

- (void)didChangeToToolbox:(NSNotification *)notification {
    NSString *key = notification.userInfo[MSVDToolboxViewConfigurationKey];
    if ([key isEqualToString:@"home"]) {
        [self selectClipOrEffect:nil];
    }
}

- (void)shouldSelectClipOrEffect:(NSNotification *)notification {
    [self selectClipOrEffect:notification.userInfo[MSVDToolboxViewClipOrEffectKey]];
}

@end
