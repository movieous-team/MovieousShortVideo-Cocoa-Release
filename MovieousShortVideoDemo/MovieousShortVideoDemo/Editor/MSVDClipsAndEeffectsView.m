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
#import "MovieousShortVideoDemo-Swift.h"

#define ClipMargin      2.0
#define IndicatorWidth  2.0

#define VideoFrameRate  30
#define DefaultDurationPerSnapshot 1e6
#define MaxDurationPerSnapshot 15e6
#define SnapshotBarSideLength   50.0

#define DurationDeviders    @[@10e6, @5e6, @2.5e6, @1.5e6, @1e6, @0.5e6]
#define FrameDeviders       @[@7.5, @5, @2.5, @1.5, @1]

#define LabelWidth  20
#define RatioToScroll   0.25
#define ScrollTimerSpeed    40

@interface MSVDClipsAndEeffectsView ()
<
UIScrollViewDelegate
>

@end

@implementation MSVDClipsAndEeffectsView {
    MSVEditor *_editor;
    MSVDraft *_originalDraft;
    UIScrollView *_horizontalScrollView;
    UIView *_indicatorView;
    MASConstraint *_leftMargin;
    MASConstraint *_rightMargin;
    UIPinchGestureRecognizer *_pinchGestureRecognizer;
    MovieousTime _durationPerSnapshot;
    MovieousTime _durationPerSnapshotBeforeScale;
    CGFloat _offsetXBeforeScale;
    NSMutableArray<UILabel *> *_timeLineLabelPool;
    NSMutableArray<UILabel *> *_visibleTimeLineLabels;
    UIButton *_addMainTrackClipButton;
    UIView *_snapshotBarUpperBound;
    UIView *_snapshotBarLowerBound;
    UIView *_snapshotBarLeftBound;
    UIView *_snapshotBarRightBound;
    MovieousTime _lastDurationPerSnapshot;
    NSUInteger _lastStartIndex;
    NSUInteger _lastEndIndex;
    CGFloat _lastTranslationAddon;
    CGFloat _originalEdgeBarMargin;
    CGFloat _originalBarWidth;
    BOOL _panning;
    NSTimer *_scrollTimer;
    CGFloat _leftTranslationTotalDelta;
    CGFloat _rightTranslationTotalDelta;
}

- (instancetype)initWithEditor:(MSVEditor *)editor {
    if (self = [super initWithFrame:CGRectZero]) {
        _editor = editor;
        _originalDraft = editor.draft;
        _horizontalScrollView = [UIScrollView new];
        _horizontalScrollView.backgroundColor = [UIColor colorWithRed:0.1255 green:0.1255 blue:0.1333 alpha:1];
        _horizontalScrollView.delegate = self;
        _horizontalScrollView.showsHorizontalScrollIndicator = NO;
        [self addSubview:_horizontalScrollView];
        [_horizontalScrollView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@0);
        }];
        
        _pinchGestureRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(pinched:)];
        [_horizontalScrollView addGestureRecognizer:_pinchGestureRecognizer];
        
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
        
        _durationPerSnapshot = DefaultDurationPerSnapshot;
        
        [self updateSnapshotBars];
        _addMainTrackClipButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [self addSubview:_addMainTrackClipButton];
        [_addMainTrackClipButton setTitle:@"Add" forState:UIControlStateNormal];
        [_addMainTrackClipButton addTarget:self action:@selector(addMainTrackClipButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_addMainTrackClipButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(@0);
            make.right.equalTo(@-10);
        }];
        _timeLineLabelPool = [NSMutableArray array];
        _visibleTimeLineLabels = [NSMutableArray array];
        UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(viewTapped:)];
        [self addGestureRecognizer:tapGestureRecognizer];
        [self addObservers];
    }
    return self;
}

- (void)addObservers {
    [_editor.draft addObserver:self forKeyPath:@"mainTrackClips" options:NSKeyValueObservingOptionOld | NSKeyValueObservingOptionNew context:NULL];
    [self addObserversWithMainTrackClips:_editor.draft.mainTrackClips];
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(currentTimeDidUpdate:) name:kMSVEditorCurrentTimeUpdatedNotification object:nil];
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didChangeToToolbox:) name:MSVDToolboxViewChangeToToolboxNotification object:nil];
}

- (void)removeObservers {
    [NSNotificationCenter.defaultCenter removeObserver:self];
    [_editor.draft removeObserver:self forKeyPath:@"mainTrackClips"];
    [self removeObserversWithMainTrackClips:_editor.draft.mainTrackClips];
}

- (void)addObserversWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips {
    for (MSVMainTrackClip *clip in mainTrackClips) {
        [clip addObserver:self forKeyPath:@"durationAtMainTrack" options:0 context:nil];
        [clip addObserver:self forKeyPath:@"timeRange" options:0 context:nil];
    }
}

- (void)removeObserversWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips {
    for (MSVMainTrackClip *clip in mainTrackClips) {
        [clip removeObserver:self forKeyPath:@"durationAtMainTrack" context:nil];
        [clip removeObserver:self forKeyPath:@"timeRange" context:nil];
    }
}

- (void)dealloc {
    [self removeObservers];
}

- (void)viewTapped:(UITapGestureRecognizer *)sender {
    [self deselectClipOrEffect];
}

- (void)snapshotBarLeftBoundPan:(UIPanGestureRecognizer *)sender {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        MSVMainTrackClip *selectedMainTrackClip = _selectedClipOrEffect;
        if (sender.state == UIGestureRecognizerStateBegan) {
            MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
            MSVDSnapshotBar *firstBar = [_originalDraft.mainTrackClips.firstObject getAttachmentForKey:MSVDSnapshotBarKey];
            _originalEdgeBarMargin = firstBar.frame.origin.x;
            _originalBarWidth = bar.frame.size.width;
            bar.originalWidthWhenLeftPanStarts = _originalBarWidth;
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                MSVDraft *draft = [MSVDraft new];
                NSError *error;
                draft.aspectRatio = _originalDraft.aspectRatio;
                draft.maximumSize = _originalDraft.maximumSize;
                MSVMainTrackClip *clip = [selectedMainTrackClip copy];
                clip.timeRange = kMovieousTimeRangeDefault;
                clip.speed = 1;
                [draft updateMainTrackClips:@[clip] error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
                [_editor updateDraft:draft error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
            }
            _panning = YES;
        } else if (sender.state == UIGestureRecognizerStateChanged) {
            [self updateSnapshotBarsWithLeftPanGestureRecognizer:sender];
        } else {
            MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
            bar.originalWidthWhenLeftPanStarts = -1;
            MSVDSnapshotBar *firstBar = [_originalDraft.mainTrackClips.firstObject getAttachmentForKey:MSVDSnapshotBarKey];
            _panning = NO;
            _leftTranslationTotalDelta = 0;
            [self disableScrollTimer];
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                selectedMainTrackClip.timeRange = bar.timeRange;
                NSError *error;
                [_editor updateDraft:_originalDraft error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
            } else {
                selectedMainTrackClip.durationAtMainTrack = bar.frame.size.width * _durationPerSnapshot / SnapshotBarSideLength;
            }
            MovieousTime timePointer = 0;
            for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
                if (clip == selectedMainTrackClip) {
                    break;
                } else {
                    timePointer += clip.durationAtMainTrack;
                }
            }
            [firstBar mas_updateConstraints:^(MASConstraintMaker *make) {
                make.left.equalTo(@(_originalEdgeBarMargin));
            }];
            // 如果时间相同不会触发回调，所以手动调用一下。
            if (timePointer == _editor.currentTime) {
                [NSNotificationCenter.defaultCenter postNotificationName:kMSVEditorCurrentTimeUpdatedNotification object:self userInfo:@{kMSVEditorCurrentTimeKey: @(timePointer)}];
            } else {
                [_editor seekToTime:timePointer accurate:YES];
            }
        }
    }
}


- (void)snapshotBarRightBoundPan:(UIPanGestureRecognizer *)sender {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        MSVMainTrackClip *selectedMainTrackClip = _selectedClipOrEffect;
        if (sender.state == UIGestureRecognizerStateBegan) {
            MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
            MSVDSnapshotBar *lastBar = [_originalDraft.mainTrackClips.lastObject getAttachmentForKey:MSVDSnapshotBarKey];
            _originalEdgeBarMargin = _horizontalScrollView.contentSize.width - (lastBar.frame.origin.x + lastBar.frame.size.width);
            _originalBarWidth = bar.frame.size.width;
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                MSVDraft *draft = [MSVDraft new];
                NSError *error;
                draft.aspectRatio = _originalDraft.aspectRatio;
                draft.maximumSize = _originalDraft.maximumSize;
                MSVMainTrackClip *clip = [selectedMainTrackClip copy];
                clip.timeRange = kMovieousTimeRangeDefault;
                clip.speed = 1;
                [draft updateMainTrackClips:@[clip] error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
                [_editor updateDraft:draft error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
            }
            _panning = YES;
        } else if (sender.state == UIGestureRecognizerStateChanged) {
            [self updateSnapshotBarsWithRightPanGestureRecognizer:sender];
        } else {
            MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
            MSVDSnapshotBar *lastBar = [_originalDraft.mainTrackClips.lastObject getAttachmentForKey:MSVDSnapshotBarKey];
            _panning = NO;
            _rightTranslationTotalDelta = 0;
            [self disableScrollTimer];
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                selectedMainTrackClip.timeRange = bar.timeRange;
                NSError *error;
                [_editor updateDraft:_originalDraft error:&error];
                if (error) {
                    [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                    return;
                }
            } else {
                selectedMainTrackClip.durationAtMainTrack = bar.frame.size.width * _durationPerSnapshot / SnapshotBarSideLength;
            }
            MovieousTime timePointer = 0;
            for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
                timePointer += clip.durationAtMainTrack;
                if (clip == selectedMainTrackClip) {
                    break;
                }
            }
            [lastBar mas_updateConstraints:^(MASConstraintMaker *make) {
                make.right.equalTo(@(-_originalEdgeBarMargin));
            }];
            // 如果时间相同不会触发回调，所以手动调用一下。
            if (timePointer == _editor.currentTime) {
                [NSNotificationCenter.defaultCenter postNotificationName:kMSVEditorCurrentTimeUpdatedNotification object:self userInfo:@{kMSVEditorCurrentTimeKey: @(timePointer)}];
            } else {
                [_editor seekToTime:timePointer accurate:YES];
            }
        }
    }
}

- (void)updateSnapshotBarsWithLeftPanGestureRecognizer:(UIPanGestureRecognizer *)sender {
    MSVMainTrackClip *selectedMainTrackClip = _selectedClipOrEffect;
    MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
    MSVDSnapshotBar *firstBar = [_originalDraft.mainTrackClips.firstObject getAttachmentForKey:MSVDSnapshotBarKey];
    CGPoint translation = [sender translationInView:_horizontalScrollView];
    CGFloat width = _originalBarWidth - (translation.x + _leftTranslationTotalDelta);
    if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
        MovieousTime duration = selectedMainTrackClip.timeRange.duration * width / _originalBarWidth;
        MovieousTime startTime = selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration - duration;
        if (startTime < 0) {
            startTime = 0;
            duration = selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration;
            width = duration * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
        } else if (duration < MinDurationPerClip) {
            duration = MinDurationPerClip;
            startTime = selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration - duration;
            width = duration * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
        }
        bar.timeRange = MovieousTimeRangeMake(startTime, duration);
        [_editor seekToTime:startTime accurate:YES];
    } else {
        MovieousTime duration = width / SnapshotBarSideLength * _durationPerSnapshot;
        if (duration < MinDurationPerClip) {
            duration = MinDurationPerClip;
            width = duration * SnapshotBarSideLength / _durationPerSnapshot;
        }
    }
    
    CGFloat firstBarMargin = _originalEdgeBarMargin + (_originalBarWidth - _leftTranslationTotalDelta - width);
    [bar mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(@(width));
    }];
    [firstBar mas_updateConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(@(firstBarMargin));
    }];
    if ([sender locationInView:self].x > self.frame.size.width * (1 - RatioToScroll) || [sender locationInView:self].x < self.frame.size.width * RatioToScroll) {
        [self enableLeftScrollTimerWithPanGestureRecognizer:sender];
    }  else {
        [self disableScrollTimer];
    }
}

- (void)updateSnapshotBarsWithRightPanGestureRecognizer:(UIPanGestureRecognizer *)sender {
    MSVMainTrackClip *selectedMainTrackClip = _selectedClipOrEffect;
    MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
    MSVDSnapshotBar *lastBar = [_originalDraft.mainTrackClips.lastObject getAttachmentForKey:MSVDSnapshotBarKey];
    CGPoint translation = [sender translationInView:_horizontalScrollView];
    CGFloat width = _originalBarWidth + (translation.x + _rightTranslationTotalDelta);
    if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
        MovieousTime duration = selectedMainTrackClip.timeRange.duration * width / _originalBarWidth;
        MovieousTime startTime = selectedMainTrackClip.timeRange.start;
        if (duration < MinDurationPerClip) {
            duration = MinDurationPerClip;
            width = duration * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
        } if (startTime + duration > selectedMainTrackClip.originalDuration) {
            duration = selectedMainTrackClip.originalDuration - startTime;
            width = duration * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
        }
        bar.timeRange = MovieousTimeRangeMake(startTime, duration);
        [_editor seekToTime:startTime + duration accurate:YES];
    } else {
        MovieousTime duration = width / SnapshotBarSideLength * _durationPerSnapshot;
        if (duration < MinDurationPerClip) {
            duration = MinDurationPerClip;
            width = duration * SnapshotBarSideLength / _durationPerSnapshot;
        }
    }
    CGFloat lastBarMargin = _originalEdgeBarMargin + (_originalBarWidth + _rightTranslationTotalDelta - width);
    [bar mas_updateConstraints:^(MASConstraintMaker *make) {
        make.width.equalTo(@(width));
    }];
    [lastBar mas_updateConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(@(-lastBarMargin));
    }];
    if ([sender locationInView:self].x > self.frame.size.width * (1 - RatioToScroll) || [sender locationInView:self].x < self.frame.size.width * RatioToScroll) {
        [self enableRightScrollTimerWithPanGestureRecognizer:sender];
    } else {
        [self disableScrollTimer];
    }
}

- (void)enableLeftScrollTimerWithPanGestureRecognizer:(UIPanGestureRecognizer *)sender {
    if (!_scrollTimer) {
        _scrollTimer = [NSTimer scheduledTimerWithTimeInterval:0.03 target:self selector:@selector(leftScrollTimerFired:) userInfo:sender repeats:YES];
    }
}

- (void)enableRightScrollTimerWithPanGestureRecognizer:(UIPanGestureRecognizer *)sender {
    if (!_scrollTimer) {
        _scrollTimer = [NSTimer scheduledTimerWithTimeInterval:0.03 target:self selector:@selector(rightScrollTimerFired:) userInfo:sender repeats:YES];
    }
}

- (void)disableScrollTimer {
    if (_scrollTimer) {
        [_scrollTimer invalidate];
        _scrollTimer = nil;
        [self updateTimeLineLabels];
    }
}

- (void)leftScrollTimerFired:(NSTimer *)sender {
    MSVMainTrackClip *selectedMainTrackClip = _selectedClipOrEffect;
    UIPanGestureRecognizer *panGestureRecognizer = sender.userInfo;
    CGFloat locationX = [panGestureRecognizer locationInView:self].x;
    CGFloat lowerBaseLineX = self.frame.size.width * RatioToScroll;
    CGFloat upperBaseLineX = self.frame.size.width * (1 - RatioToScroll);
    if (locationX < lowerBaseLineX) {
        MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
        if (selectedMainTrackClip.type != MSVClipTypeStillImage && bar.timeRange.start <= 0) {
            [sender invalidate];
            return;
        }
        if (_horizontalScrollView.contentOffset.x > 0) {
            CGFloat deltaX = ScrollTimerSpeed * (locationX - lowerBaseLineX) / lowerBaseLineX;
            CGPoint translation = [panGestureRecognizer translationInView:_horizontalScrollView];
            CGFloat pendingTranslationX = translation.x + deltaX;
            CGFloat pendingWidth = _originalBarWidth - pendingTranslationX;
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                MovieousTime pendingDuration = selectedMainTrackClip.timeRange.duration * pendingWidth / _originalBarWidth;
                MovieousTime pendingStartTime = selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration - pendingDuration;
                if (pendingStartTime < 0) {
                    pendingTranslationX = _originalBarWidth - (selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration) * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
                    deltaX = pendingTranslationX - translation.x;
                }
            }
            if (_horizontalScrollView.contentOffset.x + deltaX < 0) {
                deltaX = -_horizontalScrollView.contentOffset.x;
                pendingTranslationX = translation.x + deltaX;
            }
            if (deltaX != 0) {
                _horizontalScrollView.contentOffset = CGPointMake(_horizontalScrollView.contentOffset.x + deltaX, _horizontalScrollView.contentOffset.y);
                [panGestureRecognizer setTranslation:CGPointMake(pendingTranslationX, translation.y) inView:_horizontalScrollView];
                [self updateSnapshotBarsWithLeftPanGestureRecognizer:panGestureRecognizer];
            }
        } else {
            CGFloat deltaX = _leftTranslationTotalDelta + ScrollTimerSpeed * (locationX - lowerBaseLineX) / lowerBaseLineX;
            CGPoint translation = [panGestureRecognizer translationInView:_horizontalScrollView];
            CGFloat pendingTranslationX = translation.x + deltaX;
            CGFloat pendingWidth = _originalBarWidth - pendingTranslationX;
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                MovieousTime pendingDuration = selectedMainTrackClip.timeRange.duration * pendingWidth / _originalBarWidth;
                MovieousTime pendingStartTime = selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration - pendingDuration;
                if (pendingStartTime < 0) {
                    pendingTranslationX = _originalBarWidth - (selectedMainTrackClip.timeRange.start + selectedMainTrackClip.timeRange.duration) * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
                    deltaX = pendingTranslationX - translation.x;
                }
            }
            if (_leftTranslationTotalDelta != deltaX) {
                _leftTranslationTotalDelta = deltaX;
                [self updateSnapshotBarsWithLeftPanGestureRecognizer:panGestureRecognizer];
                [self updateTimeLineLabels];
            }
        }
    } else if (locationX > upperBaseLineX) {
        CGFloat deltaX = ScrollTimerSpeed * (locationX - upperBaseLineX) / lowerBaseLineX;
        CGPoint translation = [panGestureRecognizer translationInView:_horizontalScrollView];
        CGFloat pendingTranslationX = translation.x + deltaX;
        CGFloat pendingWidth = _originalBarWidth - pendingTranslationX - _leftTranslationTotalDelta;
        if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
            MovieousTime pendingDuration = selectedMainTrackClip.timeRange.duration * pendingWidth / _originalBarWidth;
            if (pendingDuration < MinDurationPerClip) {
                pendingTranslationX = _originalBarWidth - _leftTranslationTotalDelta - MinDurationPerClip * _originalBarWidth / selectedMainTrackClip.timeRange.duration;
                deltaX = pendingTranslationX - translation.x;
            }
        } else {
            MovieousTime duration = pendingWidth / SnapshotBarSideLength * _durationPerSnapshot;
            if (duration < MinDurationPerClip) {
                pendingTranslationX = _originalBarWidth - _leftTranslationTotalDelta - MinDurationPerClip * SnapshotBarSideLength / _durationPerSnapshot;
                deltaX = pendingTranslationX - translation.x;
            }
        }
        if (deltaX != 0) {
            _horizontalScrollView.contentOffset = CGPointMake(_horizontalScrollView.contentOffset.x + deltaX, _horizontalScrollView.contentOffset.y);
            [panGestureRecognizer setTranslation:CGPointMake(pendingTranslationX, translation.y) inView:_horizontalScrollView];
            [self updateSnapshotBarsWithLeftPanGestureRecognizer:panGestureRecognizer];
        }
    }
}

- (void)rightScrollTimerFired:(NSTimer *)sender {
    MSVMainTrackClip *selectedMainTrackClip = _selectedClipOrEffect;
    UIPanGestureRecognizer *panGestureRecognizer = sender.userInfo;
    CGFloat locationX = [panGestureRecognizer locationInView:self].x;
    CGFloat lowerBaseLineX = self.frame.size.width * RatioToScroll;
    CGFloat upperBaseLineX = self.frame.size.width * (1 - RatioToScroll);
    if (locationX < lowerBaseLineX) {
        CGFloat deltaX = ScrollTimerSpeed * (locationX - lowerBaseLineX) / lowerBaseLineX;
        CGPoint translation = [panGestureRecognizer translationInView:_horizontalScrollView];
        CGFloat pendingTranslationX = translation.x + deltaX;
        CGFloat pendingWidth = _originalBarWidth + pendingTranslationX + _rightTranslationTotalDelta;
        if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
            MovieousTime pendingDuration = selectedMainTrackClip.timeRange.duration * pendingWidth / _originalBarWidth;
            if (pendingDuration < MinDurationPerClip) {
                pendingTranslationX = MinDurationPerClip * _originalBarWidth / selectedMainTrackClip.timeRange.duration - _originalBarWidth - _rightTranslationTotalDelta;
                deltaX = pendingTranslationX - translation.x;
            }
        } else {
            MovieousTime duration = pendingWidth / SnapshotBarSideLength * _durationPerSnapshot;
            if (duration < MinDurationPerClip) {
                pendingTranslationX = MinDurationPerClip * SnapshotBarSideLength / _durationPerSnapshot - _originalBarWidth - _rightTranslationTotalDelta;
                deltaX = pendingTranslationX - translation.x;
            }
        }
        if (deltaX != 0) {
            _horizontalScrollView.contentOffset = CGPointMake(_horizontalScrollView.contentOffset.x + deltaX, _horizontalScrollView.contentOffset.y);
            [panGestureRecognizer setTranslation:CGPointMake(pendingTranslationX, translation.y) inView:_horizontalScrollView];
            [self updateSnapshotBarsWithRightPanGestureRecognizer:panGestureRecognizer];
        }
    } else if (locationX > upperBaseLineX) {
        MSVDSnapshotBar *bar = [selectedMainTrackClip getAttachmentForKey:MSVDSnapshotBarKey];
        if (selectedMainTrackClip.type != MSVClipTypeStillImage && bar.timeRange.start + bar.timeRange.duration >= selectedMainTrackClip.originalDuration) {
            [sender invalidate];
            return;
        }
        CGFloat maxContentOffsetX = _horizontalScrollView.contentSize.width - _horizontalScrollView.frame.size.width;
        if (_horizontalScrollView.contentOffset.x < maxContentOffsetX) {
            CGFloat deltaX = ScrollTimerSpeed * (locationX - upperBaseLineX) / lowerBaseLineX;
            CGPoint translation = [panGestureRecognizer translationInView:_horizontalScrollView];
            CGFloat pendingTranslationX = translation.x + deltaX;
            CGFloat pendingWidth = _originalBarWidth + pendingTranslationX;
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                MovieousTime pendingDuration = selectedMainTrackClip.timeRange.duration * pendingWidth / _originalBarWidth;
                MovieousTime pendingStartTime = selectedMainTrackClip.timeRange.start;
                if (pendingStartTime + pendingDuration > selectedMainTrackClip.originalDuration) {
                    pendingTranslationX = (selectedMainTrackClip.originalDuration - selectedMainTrackClip.timeRange.start) * _originalBarWidth / selectedMainTrackClip.timeRange.duration - _originalBarWidth;
                    deltaX = pendingTranslationX - translation.x;
                }
            }
            if (_horizontalScrollView.contentOffset.x + deltaX > maxContentOffsetX) {
                deltaX = maxContentOffsetX - _horizontalScrollView.contentOffset.x;
                pendingTranslationX = translation.x + deltaX;
            }
            if (deltaX != 0) {
                _horizontalScrollView.contentOffset = CGPointMake(_horizontalScrollView.contentOffset.x + deltaX, _horizontalScrollView.contentOffset.y);
                [panGestureRecognizer setTranslation:CGPointMake(pendingTranslationX, translation.y) inView:_horizontalScrollView];
                [self updateSnapshotBarsWithRightPanGestureRecognizer:panGestureRecognizer];
            }
        } else {
            CGFloat deltaX = _rightTranslationTotalDelta + ScrollTimerSpeed * (locationX - upperBaseLineX) / lowerBaseLineX;
            CGPoint translation = [panGestureRecognizer translationInView:_horizontalScrollView];
            CGFloat pendingTranslationX = translation.x + deltaX;
            CGFloat pendingWidth = _originalBarWidth + pendingTranslationX;
            if (selectedMainTrackClip.type != MSVClipTypeStillImage) {
                MovieousTime pendingDuration = selectedMainTrackClip.timeRange.duration * pendingWidth / _originalBarWidth;
                MovieousTime pendingStartTime = selectedMainTrackClip.timeRange.start;
                if (pendingStartTime + pendingDuration > selectedMainTrackClip.originalDuration) {
                    pendingTranslationX = (selectedMainTrackClip.originalDuration - selectedMainTrackClip.timeRange.start) * _originalBarWidth / selectedMainTrackClip.timeRange.duration - _originalBarWidth;
                    deltaX = pendingTranslationX - translation.x;
                }
            }
            if (_rightTranslationTotalDelta != deltaX) {
                _rightTranslationTotalDelta = deltaX;
                [self updateSnapshotBarsWithRightPanGestureRecognizer:panGestureRecognizer];
                _horizontalScrollView.contentOffset = CGPointMake(maxContentOffsetX + deltaX, _horizontalScrollView.contentOffset.y);
                [self updateTimeLineLabels];
            }
        }
    }
}

- (void)updateSnapshotBars {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self updateSnapshotBars];
        });
        return;
    }
    for (UIView *subview in _horizontalScrollView.subviews) {
        if ([subview isKindOfClass:MSVDSnapshotBar.class]) {
            [subview removeFromSuperview];
        }
    }
    MASViewAttribute *leftBase = _horizontalScrollView.mas_left;
    for (int i = 0; i < _originalDraft.mainTrackClips.count; i++) {
        MSVMainTrackClip *clip = _originalDraft.mainTrackClips[i];
        MSVDSnapshotBar *bar = [clip getAttachmentForKey:MSVDSnapshotBarKey];
        if (!bar) {
            if (clip.type != MSVClipTypeStillImage) {
                MSVDSnapshotsCache *exisCache = nil;
                for (MSVClip *tmpClip in _originalDraft.mainTrackClips) {
                    if ([clip isSameSourceWithClip:tmpClip]) {
                        MSVDSnapshotBar *tmpBar = [tmpClip getAttachmentForKey:MSVDSnapshotBarKey];
                        if (tmpBar) {
                            exisCache = tmpBar.snapshotsCache;
                            break;
                        }
                    }
                }
                for (id<MSVTimeDomainObject> mixTrackClipOrEffect in _originalDraft.mixTrackClipsOrEffects) {
                    if ([mixTrackClipOrEffect isKindOfClass:MSVMixTrackClip.class]) {
                        MSVMixTrackClip *tmpClip = (MSVMixTrackClip *)mixTrackClipOrEffect;
                        if ([clip isSameSourceWithClip:tmpClip]) {
                            MSVDSnapshotBar *tmpBar = [tmpClip getAttachmentForKey:MSVDSnapshotBarKey];
                            if (tmpBar) {
                                exisCache = tmpBar.snapshotsCache;
                                break;
                            }
                        }
                    }
                }
                if (exisCache) {
                    bar = [[MSVDSnapshotBar alloc] initWithSnapshotsCache:exisCache timeRange:clip.timeRange];
                } else {
                    bar = [[MSVDSnapshotBar alloc] initWithSnapshotGenerator:clip.snapshotGenerator timeRange:clip.timeRange];
                }
            } else {
                bar = [[MSVDSnapshotBar alloc] initWithImage:clip.image];
            }
            [clip setAttachment:bar forKey:MSVDSnapshotBarKey];
            if (clip.defaultSize.width > clip.defaultSize.height) {
                clip.snapshotGenerator.maximumSize = CGSizeMake(SnapshotBarSideLength * clip.defaultSize.width / clip.defaultSize.height * UIScreen.mainScreen.scale, SnapshotBarSideLength * UIScreen.mainScreen.scale);
            } else {
                clip.snapshotGenerator.maximumSize = CGSizeMake(SnapshotBarSideLength * UIScreen.mainScreen.scale, SnapshotBarSideLength * clip.defaultSize.height / clip.defaultSize.width * UIScreen.mainScreen.scale);
            }
            UITapGestureRecognizer *tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(barTapped:)];
            [bar addGestureRecognizer:tapGestureRecognizer];
            [bar setNeedRefreshSnapshots];
        }
        [_horizontalScrollView addSubview:bar];
        CGFloat width = SnapshotBarSideLength * clip.durationAtMainTrack / _durationPerSnapshot;
        [bar mas_remakeConstraints:^(MASConstraintMaker *make) {
            if (i == 0) {
                _leftMargin = make.left.equalTo(leftBase).offset(self.bounds.size.width / 2);
            } else {
                make.left.equalTo(leftBase);
            }
            make.centerY.equalTo(@0);
            make.height.equalTo(@(SnapshotBarSideLength));
            make.width.equalTo(@(width));
            if (i == _originalDraft.mainTrackClips.count - 1) {
                _rightMargin = make.right.equalTo(@(-self.bounds.size.width / 2));
            }
        }];
        if (_originalDraft.mainTrackClips.count == 1) {
            bar.leadingMargin = 0;
            bar.trailingMargin = 0;
        } else if (i == 0) {
            bar.leadingMargin = 0;
            bar.trailingMargin = ClipMargin / 2;
        } else if (i == _originalDraft.mainTrackClips.count - 1) {
            bar.leadingMargin = ClipMargin / 2;
            bar.trailingMargin = 0;
        } else {
            bar.leadingMargin = ClipMargin / 2;
            bar.trailingMargin = ClipMargin / 2;
        }
        leftBase = bar.mas_right;
    }
    [self updateVisibleAreas];
    [self bringBoundToFront];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"mainTrackClips"]) {
        if (!NSThread.currentThread.isMainThread) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self observeValueForKeyPath:keyPath ofObject:object change:change context:context];
            });
            return;
        }
        id oldMainTrackClips = change[NSKeyValueChangeOldKey];
        if (oldMainTrackClips != [NSNull null]) {
            [self removeObserversWithMainTrackClips:oldMainTrackClips];
        }
        id newMainTrackClips = change[NSKeyValueChangeNewKey];
        if (newMainTrackClips != [NSNull null]) {
            [self addObserversWithMainTrackClips:newMainTrackClips];
        }
        [self updateSnapshotBars];
        [self selectClipOrEffect:_selectedClipOrEffect];
    } else if ([object isKindOfClass:MSVMainTrackClip.class]) {
        MSVMainTrackClip *clip = object;
        MSVDSnapshotBar *bar = [clip getAttachmentForKey:MSVDSnapshotBarKey];
        [bar mas_updateConstraints:^(MASConstraintMaker *make) {
            make.width.equalTo(@(SnapshotBarSideLength * clip.durationAtMainTrack / _durationPerSnapshot));
        }];
    }
}

- (void)barTapped:(UITapGestureRecognizer *)sender {
    MSVDSnapshotBar *bar = (MSVDSnapshotBar *)sender.view;
    for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
        if ([clip getAttachmentForKey:MSVDSnapshotBarKey] == bar) {
            [self selectClipOrEffect:clip];
            break;
        }
    }
}

- (void)selectClipOrEffect:(id)clipOrEffect {
    if ([clipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSUInteger barIndex = [_editor.draft.mainTrackClips indexOfObject:clipOrEffect];
        if (barIndex == NSNotFound) {
            [self deselectClipOrEffect];
            return;
        }
        MSVDSnapshotBar *bar = [clipOrEffect getAttachmentForKey:MSVDSnapshotBarKey];
        if (!_snapshotBarUpperBound) {
            _snapshotBarUpperBound = [UIView new];
            _snapshotBarUpperBound.backgroundColor = UIColor.whiteColor;
            [_horizontalScrollView addSubview:_snapshotBarUpperBound];
        }
        [_snapshotBarUpperBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(bar.mas_top);
            make.left.equalTo(bar);
            make.right.equalTo(bar);
            make.height.equalTo(@2);
        }];
        if (!_snapshotBarLowerBound) {
            _snapshotBarLowerBound = [UIView new];
            _snapshotBarLowerBound.backgroundColor = UIColor.whiteColor;
            [_horizontalScrollView addSubview:_snapshotBarLowerBound];
        } else {
            [_horizontalScrollView bringSubviewToFront:_snapshotBarLowerBound];
        }
        [_snapshotBarLowerBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(bar.mas_bottom);
            make.left.equalTo(bar);
            make.right.equalTo(bar);
            make.height.equalTo(@2);
        }];
        if (!_snapshotBarLeftBound) {
            _snapshotBarLeftBound = [UIView new];
            _snapshotBarLeftBound.backgroundColor = UIColor.whiteColor;
            [_horizontalScrollView addSubview:_snapshotBarLeftBound];
            UIView *view = [UIView new];
            view.backgroundColor = UIColor.blackColor;
            [_snapshotBarLeftBound addSubview:view];
            [view mas_makeConstraints:^(MASConstraintMaker *make) {
                make.center.equalTo(@0);
                make.width.equalTo(@2);
                make.height.equalTo(@10);
            }];
            UIPanGestureRecognizer *panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(snapshotBarLeftBoundPan:)];
            [_snapshotBarLeftBound addGestureRecognizer:panGestureRecognizer];
        }
        [_snapshotBarLeftBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_snapshotBarUpperBound.mas_top);
            make.bottom.equalTo(_snapshotBarLowerBound.mas_bottom);
            if (barIndex == 0) {
                make.right.equalTo(bar.mas_left);
            } else {
                // 避免有一个间隔
                make.right.equalTo(bar.mas_left).offset(ClipMargin / 2);
            }
            make.width.equalTo(@25);
        }];
        if (!_snapshotBarRightBound) {
            _snapshotBarRightBound = [UIView new];
            _snapshotBarRightBound.backgroundColor = UIColor.whiteColor;
            [_horizontalScrollView addSubview:_snapshotBarRightBound];
            UIView *view = [UIView new];
            view.backgroundColor = UIColor.blackColor;
            [_snapshotBarRightBound addSubview:view];
            [view mas_makeConstraints:^(MASConstraintMaker *make) {
                make.center.equalTo(@0);
                make.width.equalTo(@2);
                make.height.equalTo(@10);
            }];
            UIPanGestureRecognizer *panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(snapshotBarRightBoundPan:)];
            [_snapshotBarRightBound addGestureRecognizer:panGestureRecognizer];
        }
        [_snapshotBarRightBound mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_snapshotBarUpperBound.mas_top);
            make.bottom.equalTo(_snapshotBarLowerBound.mas_bottom);
            if (barIndex == _originalDraft.mainTrackClips.count - 1) {
                make.left.equalTo(bar.mas_right);
            } else {
                make.left.equalTo(bar.mas_right).offset(-ClipMargin / 2);
            }
            make.width.equalTo(@25);
        }];
    }
    _selectedClipOrEffect = clipOrEffect;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDDidSelectClipOrEffectNotification object:self];
}

- (void)bringBoundToFront {
    [_horizontalScrollView bringSubviewToFront:_snapshotBarUpperBound];
    [_horizontalScrollView bringSubviewToFront:_snapshotBarLowerBound];
    [_horizontalScrollView bringSubviewToFront:_snapshotBarLeftBound];
    [_horizontalScrollView bringSubviewToFront:_snapshotBarRightBound];
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
    CGFloat startBaseline = _horizontalScrollView.contentOffset.x - self.frame.size.width / 2 - LabelWidth / 2;
    MovieousTime startInterval = _durationPerSnapshot * startBaseline / SnapshotBarSideLength;
    if (startInterval < 0) {
        startInterval = 0;
    }
    NSUInteger startIndex = ceil((double)startInterval / labelDevider);
    CGFloat endBaseline = _horizontalScrollView.contentOffset.x + self.frame.size.width / 2 + LabelWidth / 2;
    MovieousTime endInterval = endBaseline / SnapshotBarSideLength * _durationPerSnapshot;
    if (endInterval > _originalDraft.originalDuration) {
        endInterval = _originalDraft.originalDuration;
    }
    NSUInteger endIndex = (NSUInteger)(endInterval / labelDevider);
    if (_lastTranslationAddon == _leftTranslationTotalDelta && _lastDurationPerSnapshot == _durationPerSnapshot && _lastStartIndex == startIndex && _lastEndIndex == endIndex) {
        return;
    }
    _lastTranslationAddon = _leftTranslationTotalDelta;
    _lastDurationPerSnapshot = _durationPerSnapshot;
    _lastStartIndex = startIndex;
    _lastEndIndex = endIndex;
    NSMutableArray *visibleTimeLineLabels = _visibleTimeLineLabels;
    _visibleTimeLineLabels = [NSMutableArray array];
    for (NSUInteger i = startIndex; i <= endIndex; i++) {
        UILabel *label;
        if (visibleTimeLineLabels.count > 0) {
            label = visibleTimeLineLabels.lastObject;
            [visibleTimeLineLabels removeLastObject];
        } else if (_timeLineLabelPool.count > 0) {
            label = _timeLineLabelPool.lastObject;
            [_horizontalScrollView addSubview:label];
            [_timeLineLabelPool removeLastObject];
        } else {
            label = [UILabel new];
            label.textColor = UIColor.whiteColor;
            label.font = [UIFont systemFontOfSize:10];
            [_horizontalScrollView addSubview:label];
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
            make.centerX.equalTo(@(i * SnapshotBarSideLength * labelDevider / _durationPerSnapshot - _leftTranslationTotalDelta));
        }];
    }
    for (UILabel *label in visibleTimeLineLabels) {
        [label removeFromSuperview];
        [_timeLineLabelPool addObject:label];
    }
}

- (void)addMainTrackClipButtonPressed:(UIButton *)sender {
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDAddMainTrackClipButtonPressedNotification object:self];
}

- (void)layoutSubviews {
    _leftMargin.offset(self.bounds.size.width / 2);
    _rightMargin.offset(-self.bounds.size.width / 2);
    [self updateTimeLineLabels];
    [self updateVisibleAreas];
}

- (void)pinched:(UIPinchGestureRecognizer *)sender {
    if (sender.state == UIGestureRecognizerStateBegan) {
        _durationPerSnapshotBeforeScale = _durationPerSnapshot;
        _offsetXBeforeScale = _horizontalScrollView.contentOffset.x;
        _horizontalScrollView.scrollEnabled = NO;
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
            MSVDSnapshotBar *bar = [clip getAttachmentForKey:MSVDSnapshotBarKey];
            CGFloat width = SnapshotBarSideLength * clip.durationAtMainTrack / _durationPerSnapshot;
            [bar mas_updateConstraints:^(MASConstraintMaker *make) {
                make.width.equalTo(@(width));
            }];
            // 松开手再刷新，避免频繁刷新，影响性能。
            if (sender.state >= UIGestureRecognizerStateEnded) {
                [bar refreshSnapshots];
            }
        }
        _horizontalScrollView.contentOffset = CGPointMake(_offsetXBeforeScale * sender.scale, _horizontalScrollView.contentOffset.y);
        [self updateTimeLineLabels];
        if (sender.state >= UIGestureRecognizerStateEnded) {
            _horizontalScrollView.scrollEnabled = YES;
        }
    }
}

- (void)currentTimeDidUpdate:(NSNotification *)notification {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self currentTimeDidUpdate:notification];
        });
        return;
    }
    if (_editor.status != MSVEditorStatusSeeking && !_horizontalScrollView.isDragging && !_horizontalScrollView.isDecelerating) {
        CGFloat offsetX = (_horizontalScrollView.contentSize.width - self.bounds.size.width) * _editor.currentTime / _editor.draft.originalDuration;
        _horizontalScrollView.contentOffset = CGPointMake(offsetX, 0);
    }
}

- (void)scrollViewWillBeginDragging:(UIScrollView *)scrollView {
    [_editor pause];
}

- (void)scrollViewDidScroll:(UIScrollView *)scrollView {
    if (scrollView.isDragging || scrollView.isDecelerating) {
        [_editor seekToTime:_editor.draft.originalDuration * scrollView.contentOffset.x / (scrollView.contentSize.width - self.bounds.size.width) accurate:YES];
    }
    [self updateTimeLineLabels];
    [self updateVisibleAreas];
}

- (void)updateVisibleAreas {
    for (MSVMainTrackClip *clip in _originalDraft.mainTrackClips) {
        MSVDSnapshotBar *bar = [clip getAttachmentForKey:MSVDSnapshotBarKey];
        bar.visibleArea = (MSVDSnapshotBarVisibleArea){_horizontalScrollView.contentOffset.x, self.frame.size.width};
    }
}

- (void)deselectClipOrEffect {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self deselectClipOrEffect];
        });
        return;
    }
    [_snapshotBarUpperBound removeFromSuperview];
    _snapshotBarUpperBound = nil;
    [_snapshotBarLowerBound removeFromSuperview];
    _snapshotBarLowerBound = nil;
    [_snapshotBarLeftBound removeFromSuperview];
    _snapshotBarLeftBound = nil;
    [_snapshotBarRightBound removeFromSuperview];
    _snapshotBarRightBound = nil;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDDidDeselectClipOrEffectNotification object:self];
    _selectedClipOrEffect = nil;
}

- (void)didChangeToToolbox:(NSNotification *)notification {
    NSString *key = notification.userInfo[MSVDToolboxViewToolboxConfigurationKey];
    if ([key isEqualToString:@"home"]) {
        [self deselectClipOrEffect];
    }
}

@end
