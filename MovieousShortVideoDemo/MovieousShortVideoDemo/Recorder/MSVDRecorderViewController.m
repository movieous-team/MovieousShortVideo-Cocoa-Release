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

@interface MSVDRecorderViewController ()
<
MSVRecorderDelegate
>

@end

@implementation MSVDRecorderViewController {
    MSVRecorder *_recorder;
    UIButton *_closeButton;
    UIButton *_recordButton;
    UIButton *_switchButton;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = UIColor.whiteColor;
    MSVRecorderAudioConfiguration *audioConfiguration = [MSVRecorderAudioConfiguration defaultConfiguration];
    MSVRecorderVideoConfiguration *videoConfiguration = [MSVRecorderVideoConfiguration defaultConfiguration];
    videoConfiguration.videoSize = CGSizeMake(1080, 1920);
    videoConfiguration.preferredDevicePosition = AVCaptureDevicePositionBack;
    videoConfiguration.preferredFlashMode = AVCaptureFlashModeOn;
    videoConfiguration.previewScalingMode = MovieousScalingModeAspectFit;
    videoConfiguration.blurSwitch = YES;
    NSError *error;
    _recorder = [MSVRecorder recorderWithAudioConfiguration:audioConfiguration videoConfiguration:videoConfiguration error:&error];
    if (error) {
        SHOW_ERROR_ALERT;
        return;
    }
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
        make.left.equalTo(@20);
        make.top.equalTo(@50);
        make.size.equalTo(@50);
    }];
    
    _recordButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_recordButton addTarget:self action:@selector(recordButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_recordButton setTitle:@"start" forState:UIControlStateNormal];
    [_recordButton setTitle:@"stop" forState:UIControlStateSelected];
    [self.view addSubview:_recordButton];
    [_recordButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerX.equalTo(@0);
        make.bottom.equalTo(@-50);
    }];
    
    _switchButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_switchButton addTarget:self action:@selector(switchButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [_switchButton setTitle:@"switch" forState:UIControlStateNormal];
    [self.view addSubview:_switchButton];
    [_switchButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.right.equalTo(@-20);
        make.top.equalTo(@20);
    }];
}

- (void)closeButtonPressed:(UIButton *)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)recordButtonPressed:(UIButton *)sender {
    if (sender.selected) {
        sender.enabled = NO;
        [_recorder finishRecordingWithCompletionHandler:^(NSString * _Nullable path, NSError * _Nullable error) {
            dispatch_async(dispatch_get_main_queue(), ^{
                sender.enabled = YES;
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
                MSVDraft *draft = [MSVDraft draftWithMainTrackClips:@[clip] error:&error];
                if (error) {
                    SHOW_ERROR_ALERT;
                    return;
                }
                sender.selected = NO;
                MSVDEditorViewController *editorViewController = [[MSVDEditorViewController alloc] initWithDraft:draft];
                [self presentViewController:editorViewController animated:YES completion:nil];
            });
        }];
    } else {
        NSError *error;
        [_recorder startRecordingWithError:&error];
        if (error) {
            SHOW_ERROR_ALERT;
        }
        sender.selected = YES;
    }
}

- (void)switchButtonPressed:(UIButton *)sender {
    [_recorder switchCamera];
}

- (void)viewWillAppear:(BOOL)animated {
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

@end
