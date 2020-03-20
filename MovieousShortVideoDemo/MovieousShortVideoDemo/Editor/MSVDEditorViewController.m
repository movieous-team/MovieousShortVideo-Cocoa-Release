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

#define MSVDPreviewHeight   350

typedef NS_ENUM(NSUInteger, MSVDPickerPurpose) {
    MSVDPickerPurposeAdd,
    MSVDPickerPurposePip,
    MSVDPickerPurposeReplace,
};

@interface MSVDEditorViewController ()
<
TZImagePickerControllerDelegate,
MSVDMusicsViewControllerDelegate
>

@end

@implementation MSVDEditorViewController {
    MSVDraft *_draft;
    MSVEditor *_editor;
    UIButton *_closeButton;
    UIButton *_exportButton;
    UIButton *_playButton;
    UILabel *_playTimeLabel;
    MSVDClipsAndEeffectsView *_clipsView;
    MSVDToolboxView *_toolboxView;
    MSVDPickerPurpose _pickerPurpose;
}

- (instancetype)initWithDraft:(MSVDraft *)draft {
    if (self = [super init]) {
        self.modalPresentationStyle = UIModalPresentationFullScreen;
        // 拷贝一份，根据预览分辨率来调整大小。
        _draft = [draft copy];
        CGSize previewSize = CGSizeMake(UIScreen.mainScreen.bounds.size.width * UIScreen.mainScreen.scale, MSVDPreviewHeight * UIScreen.mainScreen.scale);
        _draft.maximumSize = previewSize;
        NSError *error;
        _editor = [MSVEditor editorWithDraft:_draft error:&error];
        if (error) {
            SHOW_ERROR_ALERT
        }
        _editor.preview.backgroundColor = [UIColor colorWithRed:0.0784 green:0.0784 blue:0.0863 alpha:1];
        _closeButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _exportButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _playButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _playTimeLabel = [UILabel new];
        _clipsView = [[MSVDClipsAndEeffectsView alloc] initWithEditor:_editor];
        _toolboxView = [[MSVDToolboxView alloc] initWithEditor:_editor];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(addMainTrackClipButtonPressed:) name:MSVDAddMainTrackClipButtonPressedNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(editorPlayStateChanged:) name:kMSVEditorPlayStateChangedNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(editorCurrentTimeUpdated:) name:kMSVEditorCurrentTimeUpdatedNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(toolSelected:) name:MSVDToolboxViewToolSelectedNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(stickerSelected:) name:MSVDStickersViewSelectStickerNotification object:nil];
    }
    return self;
}

- (void)dealloc {
    [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor colorWithRed:0.1176 green:0.1176 blue:0.1176 alpha:1];
    [self.view addSubview:_editor.preview];
    [_editor.preview mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
        make.height.equalTo(@(MSVDPreviewHeight));
    }];
    
    [_closeButton setImage:[UIImage imageNamed:@"close_white"] forState:UIControlStateNormal];
    [_closeButton addTarget:self action:@selector(closeButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_closeButton];
    [_closeButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(@10);
        make.left.equalTo(@10);
    }];
    
    _exportButton.backgroundColor = [UIColor colorWithRed:0.1922 green:0.1922 blue:0.2157 alpha:1];
    _exportButton.titleLabel.font = [UIFont systemFontOfSize:12];
    _exportButton.layer.masksToBounds = YES;
    _exportButton.layer.cornerRadius = 5;
    [_exportButton setTitle:NSLocalizedString(@"global.export", "") forState:UIControlStateNormal];
    [_exportButton addTarget:self action:@selector(exportButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_exportButton];
    [_exportButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(@3);
        make.right.equalTo(@-5);
        make.width.equalTo(@80);
        make.height.equalTo(@30);
    }];
    
    [_playButton setImage:[UIImage imageNamed:@"play_white"] forState:UIControlStateNormal];
    [_playButton setImage:[UIImage imageNamed:@"pause_white"] forState:UIControlStateSelected];
    [_playButton addTarget:self action:@selector(playButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_playButton];
    [_playButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(@0);
        make.bottom.equalTo(_editor.preview.mas_bottom).offset(-3);
        make.size.equalTo(@30);
    }];
    
    _playTimeLabel.font = [UIFont systemFontOfSize:10];
    _playTimeLabel.textColor = UIColor.whiteColor;
    [self refreshPlayTimeLabel];
    [self.view addSubview:_playTimeLabel];
    [_playTimeLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(@0);
        make.centerY.equalTo(_playButton);
        make.left.equalTo(@10);
    }];
    
    [self.view addSubview:_toolboxView];
    [_toolboxView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.bottom.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
    }];
    
    [self.view addSubview:_clipsView];
    [_clipsView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(_editor.preview.mas_bottom);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
        make.bottom.equalTo(_toolboxView.mas_top);
    }];
    
    [self.view addSubview:_clipsView];
}

- (void)viewWillAppear:(BOOL)animated {
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(errorOccured:) name:MSVDErrorNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated {
    [NSNotificationCenter.defaultCenter removeObserver:self name:MSVDErrorNotification object:nil];
    [_editor pause];
}

- (void)closeButtonPressed:(UIButton *)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)exportButtonPressed:(UIButton *)sender {
    MSVDExportViewController *exportViewController = [[MSVDExportViewController alloc] initWithDraft:_draft];
    [self presentViewController:exportViewController animated:YES completion:nil];
}

- (void)playButtonPressed:(UIButton *)sender {
    if (_editor.playing) {
        [_editor pause];
    } else {
        [_editor play];
    }
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)editorPlayStateChanged:(NSNotification *)notification {
    _playButton.selected = [[notification.userInfo objectForKey:kMSVEditorPlayingKey] boolValue];
}

- (void)editorCurrentTimeUpdated:(NSNotification *)notification {
    [self refreshPlayTimeLabel];
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
            MovieousTime durationPointer = 0;
            MovieousTime durationToSeek = 0;
            NSMutableArray<MSVMainTrackClip *> *mainTrackClipsToUpdate = [NSMutableArray array];
            MovieousTime currentTime = self->_editor.currentTime;
            // 避免时间戳误差导致无法插入片段的问题。
            BOOL added = NO;
            for (MSVMainTrackClip *clip in self->_editor.draft.mainTrackClips) {
                durationPointer += clip.durationAtMainTrack;
                if (currentTime >= (durationPointer - clip.durationAtMainTrack) && currentTime <= durationPointer) {
                    if (durationPointer - currentTime >= clip.durationAtMainTrack / 2) {
                        [mainTrackClipsToUpdate addObjectsFromArray:mainTrackClipsToAdd];
                        [mainTrackClipsToUpdate addObject:clip];
                        durationToSeek = durationPointer - clip.durationAtMainTrack;
                        added = YES;
                    } else {
                        [mainTrackClipsToUpdate addObject:clip];
                        [mainTrackClipsToUpdate addObjectsFromArray:mainTrackClipsToAdd];
                        durationToSeek = durationPointer;
                        added = YES;
                    }
                } else {
                    [mainTrackClipsToUpdate addObject:clip];
                }
            }
            if (!added) {
                [mainTrackClipsToUpdate addObjectsFromArray:mainTrackClipsToAdd];
                durationToSeek = durationPointer;
            }
            [self->_editor.draft updateMainTrackClips:mainTrackClipsToUpdate error:&error];
            if (error) {
                SHOW_ERROR_ALERT
                return;
            }
            [self->_editor seekToTime:durationToSeek accurate:YES];
            [self->_clipsView deselectClipOrEffect];
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
                if (self->_clipsView.selectedClipOrEffect == clip) {
                    index = i;
                    break;
                } else {
                    timeToSeek += clip.durationAtMainTrack;
                }
            }
            NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [self->_editor.draft.mainTrackClips mutableCopy];
            [mainTrackClips replaceObjectAtIndex:index withObject:mainTrackClipToReplace];
            self->_clipsView.selectedClipOrEffect = mainTrackClipToReplace;
            NSError *error;
            [self->_editor.draft updateMainTrackClips:mainTrackClips error:&error];
            if (error) {
                SHOW_ERROR_ALERT;
                return;
            }
            [self->_editor seekToTime:timeToSeek accurate:YES];
        }
    });
}

- (void)addMainTrackClipButtonPressed:(NSNotification *)notification {
    _pickerPurpose = MSVDPickerPurposeAdd;
    [self presentViewController:[MSVDUtils generateImagePickerControllerWithDelegate:self maxImagesCount:9] animated:YES completion:nil];
}

- (void)errorOccured:(NSNotification *)notification {
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
    clip.timeRange = MovieousTimeRangeMake(10e6, 3e6);
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
        MSVDStickersView *stickersView = [MSVDStickersView new];
        [self.view addSubview:stickersView];
        [stickersView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.top.equalTo(_editor.preview.mas_bottom);
            make.bottom.equalTo(@0);
        }];
    }
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
        UIImage *image = [UIImage animatedImageWithImages:images duration:3e6];
        clip = [MSVMixTrackClip mixTrackClipWithAnimatedImage:image startTimeAtMainTrack:currentTime error:&error];
    }
    [mixTrackClipsOrEffects addObject:clip];
    [_draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
    [_editor seekToTime:currentTime accurate:YES];
}

@end
