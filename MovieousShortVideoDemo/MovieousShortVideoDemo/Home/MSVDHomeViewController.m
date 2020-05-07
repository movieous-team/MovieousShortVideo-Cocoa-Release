//
//  MSVDHomeViewController.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDHomeViewController.h"
#import <TZImagePickerController/TZImagePickerController.h>
#import "MSVDEditorViewController.h"
#import "MSVDUtils.h"
#import "MSVDRecorderViewController.h"
#import "MSVDExportViewController.h"

@interface MSVDHomeViewController ()
<
TZImagePickerControllerDelegate
>

@end

@implementation MSVDHomeViewController {
    UIButton *_startCompositionButton;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    _startCompositionButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_startCompositionButton setTitle:NSLocalizedString(@"MSVDHomeViewController.startComposition", nil) forState:UIControlStateNormal];
    [_startCompositionButton addTarget:self action:@selector(startEditingButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    _startCompositionButton.titleLabel.textColor = UIColor.whiteColor;
    _startCompositionButton.backgroundColor = [UIColor colorWithRed:0.1255 green:0.1255 blue:0.1333 alpha:1];
    [self.view addSubview:_startCompositionButton];
    [_startCompositionButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(@0);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
        make.height.equalTo(@240);
    }];
}

- (void)startEditingButtonPressed:(UIButton *)sender {
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:NSLocalizedString(@"global.prompt", nil) message:NSLocalizedString(@"MSVDHomeViewController.resourceSource", nil) preferredStyle:UIAlertControllerStyleActionSheet];
    [alertController addAction:[UIAlertAction actionWithTitle:NSLocalizedString(@"MSVDHomeViewController.record", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self presentViewController:[MSVDRecorderViewController new] animated:YES completion:nil];
    }]];
    [alertController addAction:[UIAlertAction actionWithTitle:NSLocalizedString(@"MSVDHomeViewController.photoLibrary", nil) style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [self presentViewController:[MSVDUtils generateImagePickerControllerWithDelegate:self maxImagesCount:9] animated:YES completion:nil];
    }]];
    [alertController addAction:[UIAlertAction actionWithTitle:NSLocalizedString(@"global.cancel", nil) style:UIAlertActionStyleCancel handler:nil]];
    [self presentViewController:alertController animated:YES completion:nil];
}

- (void)imagePickerController:(TZImagePickerController *)picker didFinishPickingPhotos:(NSArray<UIImage *> *)photos sourceAssets:(NSArray *)assets isSelectOriginalPhoto:(BOOL)isSelectOriginalPhoto infos:(NSArray<NSDictionary *> *)infos {
    dispatch_async(dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0), ^{
        NSError *error;
        NSArray *mainTrackClips = [MSVDUtils generateMainTrackClipsWithAssets:assets videoSize:CGSizeZero scalingMode:MovieousScalingModeAspectFit error:&error];
        if (error) {
            SHOW_ERROR_ALERT;
            return;
        }
        [self presentEditorViewControllerWithMainTrackClips:mainTrackClips];
    });
}

- (void)presentEditorViewControllerWithMainTrackClips:(NSArray<MSVMainTrackClip *> *)mainTrackClips {
    MSVDraft *draft = [MSVDraft new];
    NSError *error;
    [draft updateMainTrackClips:mainTrackClips error:&error];
    if (error) {
        SHOW_ERROR_ALERT
        return;
    }
//    draft.maximumSize =
//    MSVBasicMainTrackTransition *transition = [MSVBasicMainTrackTransition new];
//    transition.duration = 2;
//    transition.transitionType = MSVVideoTransitionTypeFade;
//    [draft updateMainTrackClips:mainTrackClips mainTrackTransitions:@{@0: transition} error:&error];
//    if (error) {
//        SHOW_ERROR_ALERT
//        return;
//    }
    dispatch_async(dispatch_get_main_queue(), ^{
        MSVDEditorViewController *editorViewController = [[MSVDEditorViewController alloc] initWithDraft:draft];
        [self presentViewController:editorViewController animated:YES completion:nil];
    });
}

- (BOOL)isAssetCanSelect:(PHAsset *)asset {
    if (asset.mediaType == PHAssetMediaTypeVideo) {
        if (asset.duration < MovieousTimeGetSeconds(MinDurationPerClip)) {
            return NO;
        }
    }
    return YES;
}

@end
