//
//  MSVDExportViewController.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/10.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDExportViewController.h"

@interface MSVDExportViewController ()

@end

@implementation MSVDExportViewController {
    MSVDraft *_draft;
    MSVExporter *_exporter;
    UIButton *_closeButton;
    UIButton *_exportButton;
    UISegmentedControl *_resolutionSegmentControl;
    NSArray<NSDictionary<NSString *, NSValue *> *> *_resolutionConfigurations;
}

- (instancetype)initWithDraft:(MSVDraft *)draft {
    if (self = [super init]) {
        self.modalPresentationStyle = UIModalPresentationFullScreen;
        _draft = [draft copy];
        _exporter = [MSVExporter exporterWithDraft:_draft];
        _exporter.saveToPhotosAlbum = YES;
        MovieousWeakSelf
        _exporter.progressHandler = ^(float progress) {
            [SVProgressHUD showProgress:progress status:NSLocalizedString(@"MSVDExportViewController.exporting", "")];
        };
        _exporter.completionHandler = ^(NSString * _Nonnull path) {
            [SVProgressHUD dismiss];
            SHOW_ALERT_FOR(NSLocalizedString(@"global.prompt", ""), NSLocalizedString(@"MSVDExportViewController.done", ""), NSLocalizedString(@"global.ok", ""), wSelf);
        };
        _exporter.failureHandler = ^(NSError * _Nonnull error) {
            [SVProgressHUD dismiss];
            SHOW_ERROR_ALERT_FOR(wSelf)
        };
        _resolutionConfigurations = @[
            @{
                @"name": @"360p",
                @"long": @480,
                @"short": @360,
            },
            @{
                @"name": @"480p",
                @"long": @720,
                @"short": @480,
            },
            @{
                @"name": @"540p",
                @"long": @960,
                @"short": @544,
            },
            @{
                @"name": @"720p",
                @"long": @1280,
                @"short": @720,
            },
            @{
                @"name": @"1080p",
                @"long": @1920,
                @"short": @1080,
            },
        ];
    }
    return self;
}

- (void)viewWillAppear:(BOOL)animated {
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(errorOccured:) name:MSVDErrorNotification object:nil];
}

- (void)viewWillDisappear:(BOOL)animated {
    [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = UIColor.blackColor;
    
    _closeButton = [UIButton buttonWithType:UIButtonTypeCustom];
    [_closeButton setImage:[UIImage imageNamed:@"close_white"] forState:UIControlStateNormal];
    [_closeButton addTarget:self action:@selector(closeButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_closeButton];
    [_closeButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(@10);
        make.left.equalTo(@10);
    }];
    
    _exportButton = [UIButton buttonWithType:UIButtonTypeCustom];
    _exportButton.backgroundColor = [UIColor colorWithRed:0.1922 green:0.1922 blue:0.2157 alpha:1];
    _exportButton.titleLabel.font = [UIFont systemFontOfSize:12];
    _exportButton.layer.masksToBounds = YES;
    _exportButton.layer.cornerRadius = 5;
    [_exportButton setTitle:NSLocalizedString(@"MSVDExportViewController.export", nil) forState:UIControlStateNormal];
    [_exportButton addTarget:self action:@selector(exportButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:_exportButton];
    [_exportButton mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(@100);
        make.centerX.equalTo(@0);
        make.width.equalTo(@150);
        make.height.equalTo(@40);
    }];
    
    NSMutableArray *items = [NSMutableArray array];
    for (NSDictionary *configuration in _resolutionConfigurations) {
        [items addObject:configuration[@"name"]];
    }
    _resolutionSegmentControl = [[UISegmentedControl alloc] initWithItems:items];
    _resolutionSegmentControl.selectedSegmentIndex = items.count / 2;
    [self.view addSubview:_resolutionSegmentControl];
    [_resolutionSegmentControl mas_makeConstraints:^(MASConstraintMaker *make) {
        make.centerY.equalTo(@-100);
        make.left.equalTo(@20);
        make.right.equalTo(@-20);
    }];
    
    UILabel *resolutionLabel = [UILabel new];
    resolutionLabel.textColor = UIColor.whiteColor;
    resolutionLabel.text = NSLocalizedString(@"MSVDExportViewController.resolution", nil);
    [self.view addSubview:resolutionLabel];
    [resolutionLabel mas_makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(_resolutionSegmentControl);
        make.bottom.equalTo(_resolutionSegmentControl.mas_top).offset(-30);
    }];
}

- (void)closeButtonPressed:(UIButton *)sender {
    [_exporter cancelExport];
    [SVProgressHUD dismiss];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)updateDraftSize {
    NSDictionary *configuration = _resolutionConfigurations[_resolutionSegmentControl.selectedSegmentIndex];
    CGFloat longSide = [configuration[@"long"] doubleValue];
    CGFloat shortSide = [configuration[@"short"] doubleValue];
    if (_draft.videoSize.width >= _draft.videoSize.height) {
        _draft.maximumSize = CGSizeMake(longSide, shortSide);
    } else {
        _draft.maximumSize = CGSizeMake(shortSide, longSide);
    }
}

- (void)exportButtonPressed:(UIButton *)sender {
    [self startExport];
}

- (void)startExport {
    [self updateDraftSize];
    [_exporter startExport];
}

- (BOOL)prefersStatusBarHidden {
    return YES;
}

- (void)errorOccured:(NSNotification *)notification {
    NSError *error = notification.userInfo[MSVDErrorKey];
    SHOW_ERROR_ALERT;
}

@end
