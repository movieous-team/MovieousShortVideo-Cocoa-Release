//
//  MSVDEditorViewController.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDEditorViewController.h"
#import "MSVDExportViewController.h"
#import "MSVDClipsAndEeffectsView.h"
#import "MSVDToolboxView.h"
#import "MSVDUtils.h"
#import <TZImagePickerController/TZImagePickerController.h>
#import "MSVDMusicsViewController.h"
#import "MSVDStickersView.h"
#import "MSVDStickersLibrary.h"
#import "MSVDFrameView.h"

#define MSVDPreviewHeight   350

typedef NS_ENUM(NSUInteger, MSVDPickerPurpose) {
    MSVDPickerPurposeAdd,
    MSVDPickerPurposePip,
    MSVDPickerPurposeReplace,
};

@interface MSVDEditorViewController ()
<
TZImagePickerControllerDelegate,
MSVDMusicsViewControllerDelegate,
UIGestureRecognizerDelegate,
UITextViewDelegate
>

@end

@implementation MSVDEditorViewController {
    MSVDraft *_draft;
    MSVEditor *_editor;
    UIButton *_closeButton;
    UIButton *_exportButton;
    UIButton *_playButton;
    UILabel *_playTimeLabel;
    MSVDClipsAndEeffectsView *_clipsAndEffectsView;
    MSVDToolboxView *_toolboxView;
    MSVDPickerPurpose _pickerPurpose;
    MSVDStickersView *_stickersView;
    MSVDFrameView *_selectedItemFrameView;
    UITapGestureRecognizer *_tapGestureRecognizer;
    UIPanGestureRecognizer *_panGestureRecognizer;
    UIPinchGestureRecognizer *_pinchGestureRecognizer;
    UIRotationGestureRecognizer *_rotationGestureRecognizer;
    CGPoint _lastTranslation;
    CGFloat _lastScale;
    CGFloat _lastRotation;
    UIView *_textEditContainer;
    UITextView *_textEditView;
    UIButton *_textEditButton;
}

- (instancetype)initWithDraft:(MSVDraft *)draft {
    if (self = [super init]) {
        self.modalPresentationStyle = UIModalPresentationFullScreen;
        self.view.backgroundColor = [UIColor colorWithRed:0.1176 green:0.1176 blue:0.1176 alpha:1];
        
        // 拷贝一份，根据预览分辨率来调整大小。
        _draft = [draft copy];
        CGSize previewSize = CGSizeMake(UIScreen.mainScreen.bounds.size.width * UIScreen.mainScreen.scale, MSVDPreviewHeight * UIScreen.mainScreen.scale);
        _draft.maximumSize = previewSize;
        NSError *error;
        _editor = [MSVEditor editorWithDraft:_draft error:&error];
        if (error) {
            SHOW_ERROR_ALERT
        }
        _tapGestureRecognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(previewTapped:)];
        _tapGestureRecognizer.delegate = self;
        _tapGestureRecognizer.cancelsTouchesInView = NO;
        [_editor.preview addGestureRecognizer:_tapGestureRecognizer];
        
        _panGestureRecognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(previewPanned:)];
        _panGestureRecognizer.delegate = self;
        _panGestureRecognizer.cancelsTouchesInView = NO;
        [_editor.preview addGestureRecognizer:_panGestureRecognizer];
        
        _pinchGestureRecognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(previewPinched:)];
        _pinchGestureRecognizer.delegate = self;
        _pinchGestureRecognizer.cancelsTouchesInView = NO;
        [_editor.preview addGestureRecognizer:_pinchGestureRecognizer];
        
        _rotationGestureRecognizer = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(previewRotated:)];
        _rotationGestureRecognizer.delegate = self;
        _rotationGestureRecognizer.cancelsTouchesInView = NO;
        [_editor.preview addGestureRecognizer:_rotationGestureRecognizer];
        
        _editor.preview.backgroundColor = [UIColor colorWithRed:0.0784 green:0.0784 blue:0.0863 alpha:1];
        [self.view addSubview:_editor.preview];
        [_editor.preview mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.height.equalTo(@(MSVDPreviewHeight));
        }];
        
        _closeButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_closeButton setImage:[UIImage imageNamed:@"ic_close_n_Normal"] forState:UIControlStateNormal];
        [_closeButton addTarget:self action:@selector(closeButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.view addSubview:_closeButton];
        [_closeButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
        }];
        
        _exportButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _exportButton.backgroundColor = [UIColor colorWithRed:0.1922 green:0.1922 blue:0.2157 alpha:1];
        _exportButton.titleLabel.font = [UIFont systemFontOfSize:12];
        _exportButton.layer.masksToBounds = YES;
        _exportButton.layer.cornerRadius = 5;
        [_exportButton setTitle:NSLocalizedString(@"global.export", "") forState:UIControlStateNormal];
        [_exportButton addTarget:self action:@selector(exportButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.view addSubview:_exportButton];
        [_exportButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerY.equalTo(_closeButton);
            make.right.equalTo(@-5);
            make.width.equalTo(@80);
            make.height.equalTo(@30);
        }];
        
        _playButton = [UIButton buttonWithType:UIButtonTypeCustom];
        [_playButton setImage:[UIImage imageNamed:@"edit_ic_play_n_Normal"] forState:UIControlStateNormal];
        [_playButton setImage:[UIImage imageNamed:@"ic_stop_n_Normal"] forState:UIControlStateSelected];
        [_playButton addTarget:self action:@selector(playButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.view addSubview:_playButton];
        [_playButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.bottom.equalTo(_editor.preview.mas_bottom).offset(-3);
            make.size.equalTo(@30);
        }];
        
        _playTimeLabel = [UILabel new];
        _playTimeLabel.font = [UIFont systemFontOfSize:10];
        _playTimeLabel.textColor = UIColor.whiteColor;
        [self refreshPlayTimeLabel];
        [self.view addSubview:_playTimeLabel];
        [_playTimeLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.centerY.equalTo(_playButton);
            make.left.equalTo(@10);
        }];
        
        _toolboxView = [[MSVDToolboxView alloc] initWithEditor:_editor];
        [self.view addSubview:_toolboxView];
        [_toolboxView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.bottom.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
        
        _clipsAndEffectsView = [[MSVDClipsAndEeffectsView alloc] initWithEditor:_editor];
        [self.view addSubview:_clipsAndEffectsView];
        [_clipsAndEffectsView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_editor.preview.mas_bottom);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.bottom.equalTo(_toolboxView.mas_top);
        }];
        
        _stickersView = [MSVDStickersView new];
        _stickersView.hidden = YES;
        [self.view addSubview:_stickersView];
        [_stickersView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.top.equalTo(_editor.preview.mas_bottom);
            make.bottom.equalTo(@0);
        }];
        
        _selectedItemFrameView = [MSVDFrameView new];
        _selectedItemFrameView.userInteractionEnabled = NO;
        _selectedItemFrameView.hidden = YES;
        _selectedItemFrameView.frameColor = UIColor.redColor;
        [self.view addSubview:_selectedItemFrameView];
        
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(addMainTrackClipButtonPressed:) name:MSVDAddMainTrackClipButtonPressedNotification object:_clipsAndEffectsView];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didSelectClipOrEffect:) name:MSVDDidSelectClipOrEffectNotification object:_clipsAndEffectsView];
        
        [_editor addObserver:self forKeyPath:@"status" options:0 context:nil];
        [_editor addObserver:self forKeyPath:@"currentTime" options:0 context:nil];
        
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(toolSelected:) name:MSVDToolboxViewToolSelectedNotification object:_toolboxView];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(selectedClipGeoUpdated:) name:MSVDToolboxViewSelectedClipGeoUpdatedNotification object:_toolboxView];
        
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickerSelected:) name:MSVDStickersViewSelectStickerNotification object:_stickersView];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickerDone:) name:MSVDStickersViewDoneNotification object:_stickersView];
        
        _textEditContainer = [UIView new];
        _textEditContainer.backgroundColor = UIColor.darkGrayColor;
        [self.view addSubview:_textEditContainer];
        _textEditContainer.frame = CGRectMake(0, UIScreen.mainScreen.bounds.size.height, UIScreen.mainScreen.bounds.size.width, 60);
        
        _textEditView = [UITextView new];
        _textEditView.delegate = self;
        _textEditView.backgroundColor = UIColor.whiteColor;
        _textEditView.textColor = UIColor.blackColor;
        _textEditView.font = [UIFont systemFontOfSize:20];
        _textEditView.layer.cornerRadius = 5;
        _textEditView.layer.masksToBounds = YES;
        [_textEditContainer addSubview:_textEditView];
        [_textEditView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@5);
            make.top.equalTo(@8);
            make.bottom.equalTo(@-8);
        }];
        
        _textEditButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _textEditButton.backgroundColor = UIColor.redColor;
        _textEditButton.layer.cornerRadius = 5;
        _textEditButton.layer.masksToBounds = YES;
        [_textEditContainer addSubview:_textEditButton];
        [_textEditButton setImage:[UIImage imageNamed:@"check"] forState:UIControlStateNormal];
        [_textEditButton addTarget:self action:@selector(textEditButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [_textEditButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.right.equalTo(@-5);
            make.top.equalTo(_textEditView);
            make.bottom.equalTo(_textEditView);
            make.left.equalTo(_textEditView.mas_right).offset(5);
            make.width.equalTo(@70);
        }];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardChange:) name:UIKeyboardWillChangeFrameNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    }
    return self;
}

- (void)dealloc {
    [NSNotificationCenter.defaultCenter removeObserver:self];
    [_editor removeObserver:self forKeyPath:@"status"];
    [_editor removeObserver:self forKeyPath:@"currentTime"];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"status"]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self->_playButton.selected = self->_editor.status == MSVEditorStatusPlaying;
        });
    } else if ([keyPath isEqualToString:@"currentTime"]) {
        if (!NSThread.currentThread.isMainThread) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self observeValueForKeyPath:keyPath ofObject:object change:change context:context];
            });
            return;
        }
        [self refreshPlayTimeLabel];
        if (_clipsAndEffectsView.selectedClipOrEffect) {
            if ([_clipsAndEffectsView.selectedClipOrEffect isKindOfClass:MSVClip.class]) {
                MSVClip *clip = (MSVClip *)[_clipsAndEffectsView selectedClipOrEffect];
                if (clip.hasVisualContent && !clip.ignoreVisualContent && _editor.currentTime >= clip.startTimeAtMainTrack && _editor.currentTime <= MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack)) {
                    [self showSelectedItemFrameView:clip];
                    return;
                }
            }
        }
        _selectedItemFrameView.hidden = YES;
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

- (void)viewWillAppear:(BOOL)animated {
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(errorOccured:) name:MSVDErrorNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated {
    [NSNotificationCenter.defaultCenter removeObserver:self name:MSVDErrorNotification object:nil];
    [_editor pause];
}

- (void)previewTapped:(UITapGestureRecognizer *)sender {
    CGRect contentFrame = _editor.contentFrame;
    CGPoint location = [sender locationInView:_editor.preview];
    NSMutableArray<MSVClip *> *clips = [_editor.draft.mainTrackClips mutableCopy];
    for (id mixTrackClipOrEffect in _editor.draft.mixTrackClipsOrEffects) {
        if ([mixTrackClipOrEffect isKindOfClass:MSVClip.class] && [mixTrackClipOrEffect hasVisualContent] && ![mixTrackClipOrEffect ignoreVisualContent]) {
            // 从上到下排布
            [clips insertObject:mixTrackClipOrEffect atIndex:0];
        }
    }
    
    id selectedClipOrEffect;
    for (MSVClip *clip in clips) {
        CGAffineTransform transform = CGAffineTransformMakeTranslation(-(contentFrame.origin.x + contentFrame.size.width * clip.destCenter.x), -(contentFrame.origin.y + contentFrame.size.height * clip.destCenter.y));
        transform = CGAffineTransformConcat(transform, CGAffineTransformMakeRotation(-clip.destRotation));
        CGPoint convertedLocation = CGPointApplyAffineTransform(location, transform);
        CGSize size = CGSizeMake(contentFrame.size.width * clip.destSize.width, contentFrame.size.height * clip.destSize.height);
        if (_editor.currentTime >= clip.startTimeAtMainTrack && _editor.currentTime <= MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack) && CGRectContainsPoint(CGRectMake(-size.width / 2, -size.height / 2, size.width, size.height), convertedLocation)) {
            selectedClipOrEffect = clip;
            break;
        }
    }
    if (_clipsAndEffectsView.selectedClipOrEffect == selectedClipOrEffect) {
        if ([(MSVClip *)selectedClipOrEffect type] == MSVClipTypeStillText) {
            [self beginTextEdit];
        }
    } else {
        [_clipsAndEffectsView selectClipOrEffect:selectedClipOrEffect];
    }
}

- (void)previewPanned:(UIPanGestureRecognizer *)sender {
    if (sender.state == UIGestureRecognizerStateBegan) {
        _lastTranslation = [sender translationInView:_editor.preview];
    } else {
        CGRect contentFrame = _editor.contentFrame;
        CGPoint translation = [sender translationInView:_editor.preview];
        CGPoint translationDelta = CGPointMake(translation.x - _lastTranslation.x, translation.y - _lastTranslation.y);
        _lastTranslation = translation;
        MSVClip *clip = (MSVClip *)_clipsAndEffectsView.selectedClipOrEffect;
        clip.destCenter = CGPointMake(clip.destCenter.x + translationDelta.x / contentFrame.size.width, clip.destCenter.y + translationDelta.y / contentFrame.size.height);
        _selectedItemFrameView.center = CGPointMake(_selectedItemFrameView.center.x + translationDelta.x, _selectedItemFrameView.center.y + translationDelta.y);
    }
}

- (void)previewPinched:(UIPinchGestureRecognizer *)sender {
    if (sender.state == UIGestureRecognizerStateBegan) {
        _lastScale = 1;
    } else {
        CGFloat deltaScale = sender.scale / _lastScale;
        _lastScale = sender.scale;
        [_editor.draft beginChangeTransaction];
        MSVClip *clip = (MSVClip *)_clipsAndEffectsView.selectedClipOrEffect;
        clip.destSize = CGSizeMake(clip.destSize.width * deltaScale, clip.destSize.height * deltaScale);
        if (clip.type == MSVClipTypeStillText) {
            NSAttributedString *text = clip.text;
            NSMutableDictionary *attributes = [[text attributesAtIndex:0 effectiveRange:nil] mutableCopy];
            UIFont *font = attributes[NSFontAttributeName];
            attributes[NSFontAttributeName] = [font fontWithSize:font.pointSize * deltaScale];
            clip.text = [[NSAttributedString alloc] initWithString:text.string attributes:attributes];
        }
        [_editor.draft commitChangeWithError:nil];
        _selectedItemFrameView.bounds = CGRectMake(0, 0, _selectedItemFrameView.bounds.size.width * deltaScale, _selectedItemFrameView.bounds.size.height * deltaScale);
    }
}

- (void)previewRotated:(UIRotationGestureRecognizer *)sender {
    if (sender.state == UIGestureRecognizerStateBegan) {
        _lastRotation = 0;
    } else {
        CGFloat deltaRotation = sender.rotation - _lastRotation;
        _lastRotation = sender.rotation;
        MSVClip *clip = (MSVClip *)_clipsAndEffectsView.selectedClipOrEffect;
        clip.destRotation = clip.destRotation + deltaRotation;
        _selectedItemFrameView.transform = CGAffineTransformMakeRotation(clip.destRotation);
    }
}

- (void)closeButtonPressed:(UIButton *)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)exportButtonPressed:(UIButton *)sender {
    MSVDExportViewController *exportViewController = [[MSVDExportViewController alloc] initWithDraft:_draft];
    [self presentViewController:exportViewController animated:YES completion:nil];
}

- (void)playButtonPressed:(UIButton *)sender {
    if (_playButton.selected) {
        [_editor pause];
    } else {
        [_editor play];
    }
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)refreshPlayTimeLabel {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self refreshPlayTimeLabel];
        });
        return;
    }
    _playTimeLabel.text = [NSString stringWithFormat:@"%@/%@", [MSVDUtils formatTimeInterval:_editor.currentTime], [MSVDUtils formatTimeInterval:_editor.draft.originalDuration]];
}

- (void)imagePickerController:(TZImagePickerController *)picker didFinishPickingPhotos:(NSArray<UIImage *> *)photos sourceAssets:(NSArray *)assets isSelectOriginalPhoto:(BOOL)isSelectOriginalPhoto infos:(NSArray<NSDictionary *> *)infos {
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0), ^{
        NSError *error;
        if (self->_pickerPurpose == MSVDPickerPurposeAdd) {
            NSMutableArray *mainTrackClipsToAdd = [MSVDUtils generateMainTrackClipsWithAssets:assets videoSize:self->_editor.draft.videoSize scalingMode:MovieousScalingModeAspectFit error:&error];
            if (error) {
                SHOW_ERROR_ALERT;
                return;
            }
            MovieousTime durationToSeek = 0;
            NSMutableArray<MSVMainTrackClip *> *mainTrackClipsToUpdate = [NSMutableArray array];
            MovieousTime currentTime = self->_editor.currentTime;
            // 避免时间戳误差导致无法插入片段的问题。
            BOOL added = NO;
            for (MSVMainTrackClip *clip in self->_editor.draft.mainTrackClips) {
                if (!added && currentTime >= clip.startTimeAtMainTrack && currentTime <= MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack)) {
                    if (MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack) - currentTime >= clip.durationAtMainTrack / 2) {
                        [mainTrackClipsToUpdate addObjectsFromArray:mainTrackClipsToAdd];
                        [mainTrackClipsToUpdate addObject:clip];
                        durationToSeek = clip.startTimeAtMainTrack;
                        added = YES;
                    } else {
                        [mainTrackClipsToUpdate addObject:clip];
                        [mainTrackClipsToUpdate addObjectsFromArray:mainTrackClipsToAdd];
                        durationToSeek = MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack);
                        added = YES;
                    }
                } else {
                    [mainTrackClipsToUpdate addObject:clip];
                }
            }
            if (!added) {
                durationToSeek = MovieousTimeRangeGetEnd(mainTrackClipsToUpdate.lastObject.timeRangeAtMainTrack);
                [mainTrackClipsToUpdate addObjectsFromArray:mainTrackClipsToAdd];
            }
            [self->_editor.draft beginChangeTransaction];
            [self->_editor.draft updateMainTrackClips:mainTrackClipsToUpdate error:nil];
            [MSVDUtils ensureTransitionDurationWithDraft:self->_editor.draft error:nil];
            [self->_editor.draft commitChangeWithError:&error];
            if (error) {
                SHOW_ERROR_ALERT
                return;
            }
            [self->_editor seekToTime:durationToSeek accurate:YES];
            [self->_clipsAndEffectsView selectClipOrEffect:mainTrackClipsToAdd.firstObject];
        } else if (self->_pickerPurpose == MSVDPickerPurposePip) {
            MSVMixTrackClip *mixTrackClipToAdd = [MSVDUtils generateMixTrackClipWithAsset:assets.firstObject videoSize:self->_editor.draft.videoSize scalingMode:MovieousScalingModeAspectFit startTimeAtMainTrack:self->_editor.currentTime error:&error];
            if (error) {
                SHOW_ERROR_ALERT;
                return;
            }
            NSMutableArray<MSVMixTrackClip *> *mixTrackClipsOrEffectsToUpdate = [self->_editor.draft.mixTrackClipsOrEffects mutableCopy];
            [mixTrackClipsOrEffectsToUpdate addObject:mixTrackClipToAdd];
            [self->_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffectsToUpdate error:&error];
            if (error) {
                SHOW_ERROR_ALERT
                return;
            }
            [self->_clipsAndEffectsView selectClipOrEffect:mixTrackClipToAdd];
        } else if (self->_pickerPurpose == MSVDPickerPurposeReplace) {
            MSVMainTrackClip *mainTrackClipToReplace = [MSVDUtils generateMainTrackClipsWithAssets:assets videoSize:self->_editor.draft.videoSize scalingMode:MovieousScalingModeAspectFit error:&error].firstObject;
            if (error) {
                SHOW_ERROR_ALERT;
                return;
            }
            NSUInteger index = 0;
            MovieousTime timeToSeek = 0;
            for (NSUInteger i = 0; i < self->_editor.draft.mainTrackClips.count; i++) {
                MSVMainTrackClip *clip = self->_editor.draft.mainTrackClips[i];
                if (self->_clipsAndEffectsView.selectedClipOrEffect == clip) {
                    index = i;
                    break;
                } else {
                    timeToSeek += clip.durationAtMainTrack;
                }
            }
            NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [self->_editor.draft.mainTrackClips mutableCopy];
            [mainTrackClips replaceObjectAtIndex:index withObject:mainTrackClipToReplace];
            [self->_editor.draft beginChangeTransaction];
            [self->_editor.draft updateMainTrackClips:mainTrackClips error:nil];
            NSError *error;
            [MSVDUtils ensureTransitionDurationWithDraft:self->_editor.draft error:nil];
            [self->_editor.draft commitChangeWithError:&error];
            if (error) {
                SHOW_ERROR_ALERT;
                return;
            }
            [self->_editor seekToTime:timeToSeek accurate:YES];
            [self->_clipsAndEffectsView selectClipOrEffect:mainTrackClipToReplace];
        }
    });
}

- (void)addMainTrackClipButtonPressed:(NSNotification *)notification {
    _pickerPurpose = MSVDPickerPurposeAdd;
    [self presentViewController:[MSVDUtils generateImagePickerControllerWithDelegate:self maxImagesCount:9] animated:YES completion:nil];
}

- (void)didSelectClipOrEffect:(NSNotification *)notification {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self didSelectClipOrEffect:notification];
        });
        return;
    }
    if (_clipsAndEffectsView.selectedClipOrEffect) {
        if ([_clipsAndEffectsView.selectedClipOrEffect isKindOfClass:MSVClip.class]) {
            MSVClip *clip = (MSVClip *)[_clipsAndEffectsView selectedClipOrEffect];
            if (clip.hasVisualContent && !clip.ignoreVisualContent && _editor.currentTime >= clip.startTimeAtMainTrack && _editor.currentTime <= MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack)) {
                [self showSelectedItemFrameView:clip];
                return;
            }
        }
    }
    _selectedItemFrameView.hidden = YES;
    [_textEditView resignFirstResponder];
}

- (void)showSelectedItemFrameView:(MSVClip *)clip {
    _selectedItemFrameView.hidden = NO;
    _selectedItemFrameView.center = CGPointMake(_editor.contentFrame.origin.x + _editor.contentFrame.size.width * clip.destCenter.x, _editor.contentFrame.origin.y + _editor.contentFrame.size.height * clip.destCenter.y);
    _selectedItemFrameView.bounds = CGRectMake(0, 0, _editor.contentFrame.size.width * clip.destSize.width, _editor.contentFrame.size.height * clip.destSize.height);
    _selectedItemFrameView.transform = CGAffineTransformMakeRotation(clip.destRotation);
}

- (void)errorOccured:(NSNotification *)notification {
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self errorOccured:notification];
        });
        return;
    }
    if (!self.presentedViewController) {
        NSError *error = notification.userInfo[MSVDErrorKey];
        SHOW_ERROR_ALERT;
    }
}

- (void)musicsViewController:(MSVDMusicsViewController *)musicsViewController didSelectMusic:(MSVDMusic *)music {
    NSError *error;
    MSVMixTrackClip *clip = [MSVMixTrackClip mixTrackClipWithAVPath:music.localPath startTimeAtMainTrack:_editor.currentTime error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
    NSMutableArray *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
    [mixTrackClipsOrEffects addObject:clip];
    [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
}

- (void)toolSelected:(NSNotification *)notification {
    NSString *key = notification.userInfo[MSVDToolboxViewSelectedToolKey];
    if ([key isEqualToString:@"home.pip"]) {
        _pickerPurpose = MSVDPickerPurposePip;
        [self presentViewController:[MSVDUtils generateImagePickerControllerWithDelegate:self maxImagesCount:2] animated:YES completion:nil];
    } else if ([key isEqualToString:@"clip.replace"]) {
        _pickerPurpose = MSVDPickerPurposeReplace;
        [self presentViewController:[MSVDUtils generateImagePickerControllerWithDelegate:self maxImagesCount:2] animated:YES completion:nil];
    } else if ([key isEqualToString:@"home.audio.music"]) {
        MSVDMusicsViewController *controller = [MSVDMusicsViewController new];
        controller.delegate = self;
        [self presentViewController:controller animated:YES completion:nil];
    } else if ([key isEqualToString:@"home.sticker"]) {
        _stickersView.hidden = NO;
    }
}

- (void)selectedClipGeoUpdated:(NSNotification *)notification {
    [self didSelectClipOrEffect:notification];
}

- (void)stickerSelected:(NSNotification *)notification {
    MovieousTime currentTime = _editor.currentTime;
    MSVDSticker *sticker = notification.userInfo[MSVDStickersViewSelectedStickerKey];
    NSError *error;
    NSMutableArray *mixTrackClipsOrEffects = [_draft.mixTrackClipsOrEffects mutableCopy];
    MSVMixTrackClip *clip;
    if (sticker.type == MSVDStickerTypeImage) {
        clip = [MSVMixTrackClip mixTrackClipWithStillImagePath:sticker.localPaths[0] duration:3e6 startTimeAtMainTrack:currentTime error:&error];
        if (error) {
            SHOW_ERROR_ALERT;
            return;
        }
    } else if (sticker.type == MSVDStickerTypeGif) {
        clip = [MSVMixTrackClip mixTrackClipWithAnimatedImagePath:sticker.localPaths[0] startTimeAtMainTrack:currentTime error:&error];
        if (error) {
            SHOW_ERROR_ALERT;
            return;
        }
    } else {
        NSMutableArray *images = [NSMutableArray array];
        for (NSString *localPath in sticker.localPaths) {
            [images addObject:[UIImage imageWithContentsOfFile:localPath]];
        }
        UIImage *image = [UIImage animatedImageWithImages:images duration:3];
        clip = [MSVMixTrackClip mixTrackClipWithAnimatedImage:image startTimeAtMainTrack:currentTime error:&error];
    }
    clip.sourceCenter = CGPointMake(0.5, 0.5);
    clip.sourceSize = CGSizeMake(1, 1);
    clip.destSize = CGSizeMake(clip.defaultSize.width / _draft.videoSize.width, clip.defaultSize.height / _draft.videoSize.height);
    clip.destCenter = CGPointMake(0.5, 0.5);
    [mixTrackClipsOrEffects addObject:clip];
    [_draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
    [_editor seekToTime:currentTime accurate:YES];
}

- (void)stickerDone:(NSNotification *)notification {
    _stickersView.hidden = YES;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer {
    return YES;
}

- (BOOL)isAssetCanSelect:(PHAsset *)asset {
    if (asset.mediaType == PHAssetMediaTypeVideo) {
        if (asset.duration < MovieousTimeGetSeconds(MinDurationPerClip)) {
            return NO;
        }
    }
    return YES;
}

- (void)beginTextEdit {
    MSVClip *clip = (MSVClip *)_clipsAndEffectsView.selectedClipOrEffect;
    if ([[clip getAttachmentForKey:IsEmptyStringKey] boolValue]) {
        _textEditView.text = @"";
    } else {
        _textEditView.text = clip.text.string;
    }
    [_textEditView becomeFirstResponder];
}

- (void)keyboardWillHide:(NSNotification *)notification {
    CGRect frame = [notification.userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat duration = [notification.userInfo[UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    [UIView animateWithDuration:duration animations:^{
        self->_textEditContainer.frame = CGRectMake(0, frame.origin.y, self->_textEditContainer.frame.size.width, self->_textEditContainer.frame.size.height);
    }];
}

- (void)keyboardChange:(NSNotification *)notification {
    CGRect frame = [notification.userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat duration = [notification.userInfo[UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    [UIView animateWithDuration:duration animations:^{
        self->_textEditContainer.frame = CGRectMake(0, frame.origin.y - self->_textEditContainer.frame.size.height, self->_textEditContainer.frame.size.width, self->_textEditContainer.frame.size.height);
    }];
}

- (void)textEditButtonPressed:(UIButton *)sender {
    [_textEditView resignFirstResponder];
}

- (void)textViewDidChange:(UITextView *)textView {
    MSVClip *clip = (MSVClip *)_clipsAndEffectsView.selectedClipOrEffect;
    NSString *pendingText;
    if (textView.text.length == 0) {
        pendingText = NSLocalizedString(@"global.inputText", nil);
        [clip setAttachment:@YES forKey:IsEmptyStringKey];
    } else {
        pendingText = textView.text;
        [clip setAttachment:@NO forKey:IsEmptyStringKey];
    }
    NSMutableAttributedString *text = [clip.text mutableCopy];
    [text replaceCharactersInRange:NSMakeRange(0, text.length) withString:pendingText];
    [_editor.draft beginChangeTransaction];
    clip.text = text;
    clip.destSize = CGSizeMake(clip.defaultSize.width / _editor.draft.videoSize.width, clip.defaultSize.height / _editor.draft.videoSize.height);
    [_editor.draft commitChangeWithError:nil];
    _selectedItemFrameView.bounds = CGRectMake(0, 0, _editor.contentFrame.size.width * clip.destSize.width, _editor.contentFrame.size.height * clip.destSize.height);
}

@end
