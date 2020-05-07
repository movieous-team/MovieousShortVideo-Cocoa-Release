//
//  MSVDToolboxView.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/10.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDToolboxView.h"
#import "MSVDClipsAndEeffectsView.h"
#import "UIImage+MSVD.h"
#import "MSVDFiltersLibrary.h"
#import "MSVDFrameView.h"

#define ToolboxWidth        60.0
#define TopToolboxHeight    40.0
#define BottomToolboxHeight 70.0
#define IconLength          30.0
#define IconCenterOffset    10.0

NSNotificationName const MSVDToolboxViewToolSelectedNotification = @"MSVDToolboxViewToolSelectedNotification";
NSNotificationName const MSVDToolboxViewChangeToToolboxNotification = @"MSVDToolboxViewChangeToToolboxNotification";
NSNotificationName const MSVDToolboxViewSelectedClipGeoUpdatedNotification = @"MSVDToolboxViewSelectedClipGeoUpdatedNotification";
NSNotificationName const MSVDToolboxViewShouldSelectClipOrEffectNotification = @"MSVDToolboxViewShouldSelectClipOrEffectNotification";
NSString *const MSVDToolboxViewSelectedToolKey = @"MSVDToolboxViewSelectedToolKey";
NSString *const MSVDToolboxViewConfigurationKey = @"MSVDToolboxViewConfigurationKey";
NSString *const MSVDToolboxViewClipOrEffectKey = @"MSVDToolboxViewClipOrEffectKey";

@interface MSVDToolboxCollectionViewCell : UICollectionViewCell

@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) id icon;
@property (nonatomic, assign) BOOL enabled;
@property (nonatomic, assign) BOOL customSelected;

@end

@implementation MSVDToolboxCollectionViewCell {
    UIImageView *_iconImageView;
    UILabel *_valueLabel;
    UILabel *_titleLabel;
    MSVDFrameView *_frameView;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        _iconImageView = [UIImageView new];
        _iconImageView.contentMode = UIViewContentModeScaleAspectFit;
        [self.contentView addSubview:_iconImageView];
        
        _valueLabel = [UILabel new];
        _valueLabel.font = [UIFont systemFontOfSize:20];
        _valueLabel.textAlignment = NSTextAlignmentCenter;
        [self.contentView addSubview:_valueLabel];
        
        _titleLabel = [UILabel new];
        _titleLabel.font = [UIFont systemFontOfSize:12];
        _titleLabel.textAlignment = NSTextAlignmentCenter;
        [self.contentView addSubview:_titleLabel];
        
        _frameView = [MSVDFrameView new];
        _frameView.frameWidth = 2;
        _frameView.frameColor = UIColor.whiteColor;
        [self.contentView addSubview:_frameView];
        [_frameView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_iconImageView);
            make.width.equalTo(_iconImageView).offset(4);
            make.height.equalTo(_iconImageView).offset(4);
        }];
    }
    return self;
}

- (void)setTitle:(NSString *)title {
    _title = title;
    _titleLabel.text = _title;
}

- (void)setIcon:(id)icon {
    _icon = icon;
    if ([_icon isKindOfClass:UIImage.class]) {
        _iconImageView.backgroundColor = nil;
        _iconImageView.image = _icon;
        _valueLabel.hidden = YES;
        _titleLabel.hidden = NO;
        _iconImageView.hidden = NO;
        [_titleLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.bottom.equalTo(@-8);
        }];
        [_iconImageView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.centerY.equalTo(@-IconCenterOffset);
            make.height.equalTo(@(IconLength));
            make.width.equalTo(@(IconLength));
        }];
    } else if ([_icon isKindOfClass:UIColor.class]) {
        _iconImageView.image = nil;
        _iconImageView.backgroundColor = _icon;
        _titleLabel.hidden = YES;
        _valueLabel.hidden = YES;
        _iconImageView.hidden = NO;
        [_iconImageView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@2);
        }];
    } else if ([_icon isKindOfClass:NSString.class]) {
        _valueLabel.text = _icon;
        _iconImageView.hidden = YES;
        _titleLabel.hidden = NO;
        _valueLabel.hidden = NO;
        [_titleLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.bottom.equalTo(@-8);
        }];
        [_valueLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.centerY.equalTo(@-IconCenterOffset);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
    } else if ([_icon isKindOfClass:NSValue.class]) {
        _iconImageView.image = nil;
        _iconImageView.backgroundColor = UIColor.darkGrayColor;
        _valueLabel.hidden = YES;
        _titleLabel.hidden = NO;
        _iconImageView.hidden = NO;
        CGSize aspectRatio = [_icon CGSizeValue];
        CGFloat part = 1.5;
        [_titleLabel mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_iconImageView);
        }];
        [_iconImageView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            if (aspectRatio.width > aspectRatio.height) {
                make.width.equalTo(@(IconLength * part));
                make.height.equalTo(@(IconLength * part * aspectRatio.height / aspectRatio.width));
            } else {
                make.width.equalTo(@(IconLength * part * aspectRatio.width / aspectRatio.height));
                make.height.equalTo(@(IconLength * part));
            }
        }];
    }
}

- (void)setEnabled:(BOOL)enabled {
    _enabled = enabled;
    self.userInteractionEnabled = enabled;
    [self refreshTextColors];
}

- (void)setCustomSelected:(BOOL)customSelected {
    _customSelected = customSelected;
    if (customSelected && !_iconImageView.hidden) {
        _frameView.hidden = NO;
    } else {
        _frameView.hidden = YES;
    }
    [self refreshTextColors];
}

- (void)refreshTextColors {
    if (_enabled) {
        if (_customSelected) {
            _titleLabel.textColor = UIColor.purpleColor;
            _valueLabel.textColor = UIColor.purpleColor;
            _iconImageView.tintColor = UIColor.purpleColor;
        } else {
            _titleLabel.textColor = UIColor.whiteColor;
            _valueLabel.textColor = UIColor.whiteColor;
            _iconImageView.tintColor = UIColor.whiteColor;
        }
    } else {
        _titleLabel.textColor = UIColor.lightGrayColor;
        _valueLabel.textColor = UIColor.lightGrayColor;
        _iconImageView.tintColor = UIColor.lightGrayColor;
    }
}

@end

typedef NS_ENUM(NSUInteger, MSVDToolboxStyle) {
    MSVDToolboxStyleNormal,
    MSVDToolboxStyleColor,
};

@interface MSVDToolboxView ()
<
UICollectionViewDelegateFlowLayout,
UICollectionViewDataSource
>

@end

@implementation MSVDToolboxView {
    MSVEditor *_editor;
    UIView *_topToolboxView;
    UISlider *_slider;
    UIView *_bottomToolboxView;
    UIButton *_backButton;
    UICollectionViewFlowLayout *_flowLayout;
    UICollectionView *_collectionView;
    NSDictionary *_homeConfiguration;
    NSDictionary *_clipConfiguration;
    NSDictionary *_textClipConfiguration;
    NSDictionary *_lutEffectConfiguration;
    NSDictionary *_beautifyFilterConfiguration;
    NSDictionary *_transitionConfiguration;
    NSArray *_transitionTypes;
    NSDictionary *_currentConfiguration;
    id<MSVClipOrEffect> _selectedClipOrEffect;
    NSInteger _selectedTransitionIndex;
    NSString *_sliderKey;
    NSArray<UIColor *> *_colors;
    NSArray<NSValue *> *_aspectRatios;
    BOOL _withinSelectedClipTimeRange;
    NSIndexPath *_selectedIndexPath;
}

- (instancetype)initWithEditor:(MSVEditor *)editor {
    if (self = [super init]) {
        _editor = editor;
        /*
         {
         key: ${key},
         style: ${style},
         depth: ${depth}, // optional
         parent: ${parent}, // optional
         content:
         [
         [
         {
         key: ${key},
         iconImage: ${icon}, // optional
         iconValueKey: ${iconValueKey}, // optional
         titleKey: ${titleKey},
         child: ${child},
         keepSelect: ${keepSelect},
         adjustSlider:
         {
         ...
         }
         }, // item
         ...other items
         ], // section
         ...other sections
         ]
         }
         */
        NSDictionary *audioConfiguration = @{
            @"key": @"home.audio",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"home.audio.music",
                            @"iconImage": [UIImage imageNamed:@"music_ic_music_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.music"
                        },
                        //                        @{
                        //                            @"key": @"home.audio.record",
                        //                            @"iconImage": [UIImage imageNamed:@"music_ic_voice_n_Normal"],
                        //                            @"isTemplateIconImage": @YES,
                        //                            @"titleKey": @"MSVDToolboxView.audio.record"
                        //                        },
                    ]
                ],
        };
        _aspectRatios = @[
            // 原始横纵比（即主轨第一段视频的横纵比）
            @(CGSizeZero),
            @(CGSizeMake(9, 16)),
            @(CGSizeMake(3, 4)),
            @(CGSizeMake(1, 1)),
            @(CGSizeMake(4, 3)),
            @(CGSizeMake(16, 9)),
        ];
        NSMutableArray *aspectRatioContent = [NSMutableArray array];
        for (NSValue *aspectRatio in _aspectRatios) {
            [aspectRatioContent addObject:                            @{
                @"key": [NSString stringWithFormat:@"home.aspectRatio.%.0f:%.0f", aspectRatio.CGSizeValue.width, aspectRatio.CGSizeValue.height],
                @"aspectRatio": aspectRatio,
                @"keepSelect": @YES,
                @"didSelect": NSStringFromSelector(@selector(aspectRatioSelected:)),
            }];
        }
        NSDictionary *aspectRatioConfiguration = @{
            @"key": @"home.aspectRatio",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    aspectRatioContent
                ],
        };
        _homeConfiguration = @{
            @"key": @"home",
            @"style": @(MSVDToolboxStyleNormal),
            @"depth": @0,
            @"content":
                @[
                    @[
                        @{
                            @"key": @"home.aspectRatio",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_canvas_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.aspectRatio",
                            @"child": aspectRatioConfiguration,
                        },
                        @{
                            @"key": @"home.pip",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_mix_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.pip",
                        },
                        @{
                            @"key": @"home.text",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_text_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.text",
                            @"didSelect": NSStringFromSelector(@selector(textSelected:)),
                        },
                        @{
                            @"key": @"home.sticker",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_sticker_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.sticker",
                        },
                        @{
                            @"key": @"home.audio",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_music_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.audio",
                            @"child": audioConfiguration
                        },
                        @{
                            @"key": @"home.filter",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_fliter_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.filter",
                            @"didSelect": NSStringFromSelector(@selector(homeFilterSelected:)),
                        },
                        @{
                            @"key": @"home.beautify",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_beauty_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.beautify",
                            @"didSelect": NSStringFromSelector(@selector(beautifySelected:)),
                        },
                    ]
                ],
        };
        NSDictionary *clipAudioConfiguration = @{
            @"key": @"clip.audio",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"clip.audio.volume",
                            @"iconValueKey": @"clipVolume",
                            @"titleKey": @"MSVDToolboxView.volume",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"clipVolume",
                                    @"min": @0,
                                    @"max": @200,
                                    @"updateCellValue": @YES,
                                    @"continuous": @YES
                            }
                        },
                    ]
                ],
        };
        NSMutableArray *clipFilters = [@[@{
                                             @"key": @"clip.filters.none",
                                             @"iconImage": [UIImage imageNamed:@"filter_template.jpg"],
                                             @"titleKey": @"clip.filters.none",
                                             @"keepSelect": @YES,
                                             @"didSelect": NSStringFromSelector(@selector(clipFilterSelected:)),
        }] mutableCopy];
        for (MSVDFilter *filter in MSVDFiltersLibrary.filters) {
            [clipFilters addObject:@{
                @"key": [NSString stringWithFormat:@"clip.filters.%@", filter.name],
                @"iconImage": filter.cover,
                @"titleKey": filter.name,
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"clipFilterIntensity",
                        @"min": @0,
                        @"max": @100,
                        @"updateCellValue": @YES,
                        @"continuous": @YES
                },
                @"didSelect": NSStringFromSelector(@selector(clipFilterSelected:)),
            }];
        }
        NSDictionary *clipFiltersConfiguration = @{
            @"key": @"clip.filters",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    clipFilters
                ],
        };
        _colors = @[
            UIColor.whiteColor,
            UIColor.blackColor,
            UIColor.darkGrayColor,
            UIColor.lightGrayColor,
            UIColor.grayColor,
            UIColor.redColor,
            UIColor.greenColor,
            UIColor.blueColor,
            UIColor.cyanColor,
            UIColor.yellowColor,
            UIColor.magentaColor,
            UIColor.orangeColor,
            UIColor.purpleColor,
            UIColor.brownColor,
        ];
        NSMutableArray *colorsConfiguration = [NSMutableArray array];
        for (UIColor *color in _colors) {
            [colorsConfiguration addObject:                            @{
                @"key": [NSString stringWithFormat:@"clip.background.color.%p", color],
                @"iconColor": color,
                @"keepSelect": @YES,
                @"didSelect": NSStringFromSelector(@selector(backgroundColorSelected:)),
            }];
        }
        NSDictionary *backgroundColorsConfiguration = @{
            @"key": @"clip.background.color",
            @"style": @(MSVDToolboxStyleColor),
            @"content":
                @[
                    colorsConfiguration
                ],
        };
        NSDictionary *backgroundConfiguration = @{
            @"key": @"clip.background",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"clip.background.color",
                            @"iconImage": [UIImage imageNamed:@"canvas_ic_colors_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.color",
                            @"child": backgroundColorsConfiguration
                        },
                        //                        @{
                        //                            @"key": @"clip.background.blur",
                        //                            @"iconImage": [UIImage imageNamed:@"canvas_ic_blur_n_Normal"],
                        //                            @"isTemplateIconImage": @YES,
                        //                            @"titleKey": @"MSVDToolboxView.blur"
                        //                        },
                    ]
                ],
        };
        _clipConfiguration = @{
            @"key": @"clip",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"clip.delete",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_delete_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.delete",
                            @"didSelect": NSStringFromSelector(@selector(deleteSelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"clip.split",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_split_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.split",
                            @"didSelect": NSStringFromSelector(@selector(spliteSelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"clip.speed",
                            @"iconValueKey": @"clipSpeed",
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.speed",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"clipSpeed",
                                    @"min": @0.1,
                                    @"max": @2,
                                    @"updateCellValue": @YES,
                                    @"continuous": @NO
                            }
                        },
                        @{
                            @"key": @"clip.audio",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_volum_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.audio",
                            @"child": clipAudioConfiguration,
                        },
                        @{
                            @"key": @"clip.replace",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_replace_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.replace",
                        },
                        @{
                            @"key": @"clip.opacity",
                            @"iconValueKey": @"clipOpacity",
                            @"titleKey": @"MSVDToolboxView.opacity",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"clipOpacity",
                                    @"min": @0,
                                    @"max": @100,
                                    @"updateCellValue": @YES,
                                    @"continuous": @YES
                            }
                        },
                        @{
                            @"key": @"clip.filters",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_fliter_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.filter",
                            @"child": clipFiltersConfiguration,
                        },
                        @{
                            @"key": @"clip.copy",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_copy_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.copy",
                            @"didSelect": NSStringFromSelector(@selector(copySelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"clip.background",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_background_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.background",
                            @"child": backgroundConfiguration,
                        },
                        //                        @{
                        //                            @"key": @"clip.reverse",
                        //                            @"iconImage": [UIImage imageNamed:@"clip_ic_rewind_n_Normal"],
                        //                            @"isTemplateIconImage": @YES,
                        //                            @"titleKey": @"MSVDToolboxView.reverse",
                        //                        },
                    ]
                ],
        };
        
        NSMutableArray *lutEffectFilters = [NSMutableArray array];
        for (MSVDFilter *filter in MSVDFiltersLibrary.filters) {
            [lutEffectFilters addObject:@{
                @"key": [NSString stringWithFormat:@"lut.filters.%@", filter.name],
                @"iconImage": filter.cover,
                @"titleKey": filter.name,
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"effectFilterIntensity",
                        @"min": @0,
                        @"max": @100,
                        @"updateCellValue": @YES,
                        @"continuous": @YES
                },
                @"didSelect": NSStringFromSelector(@selector(effectFilterSelected:)),
            }];
        }
        NSDictionary *lutEffectFiltersConfiguration = @{
            @"key": @"lut.filters",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    lutEffectFilters
                ],
        };
        _lutEffectConfiguration = @{
            @"key": @"lut",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"lut.filters",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_fliter_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.filter",
                            @"child": lutEffectFiltersConfiguration,
                        },
                        @{
                            @"key": @"lut.delete",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_delete_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.delete",
                            @"didSelect": NSStringFromSelector(@selector(deleteSelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"lut.split",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_split_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.split",
                            @"didSelect": NSStringFromSelector(@selector(spliteSelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"lut.copy",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_copy_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.copy",
                            @"didSelect": NSStringFromSelector(@selector(copySelectedClipOrEffect:)),
                        },
                    ]
                ],
        };
        
        NSDictionary *beautifyEffectParametersConfiguration = @{
            @"key": @"beautify.parameters",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"beautify.parameters.smoothLevel",
                            @"iconValueKey": @"smoothLevel",
                            @"titleKey": @"MSVDToolboxView.smoothLevel",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"smoothLevel",
                                    @"min": @0,
                                    @"max": @100,
                                    @"updateCellValue": @YES,
                                    @"continuous": @YES
                            }
                        },
                        @{
                            @"key": @"beautify.parameters.whiteLevel",
                            @"iconValueKey": @"whiteLevel",
                            @"titleKey": @"MSVDToolboxView.whiteLevel",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"whiteLevel",
                                    @"min": @0,
                                    @"max": @100,
                                    @"updateCellValue": @YES,
                                    @"continuous": @YES
                            }
                        },
                        @{
                            @"key": @"beautify.parameters.redLevel",
                            @"iconValueKey": @"redLevel",
                            @"titleKey": @"MSVDToolboxView.redLevel",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"redLevel",
                                    @"min": @0,
                                    @"max": @100,
                                    @"updateCellValue": @YES,
                                    @"continuous": @YES
                            }
                        },
                    ]
                ],
        };
        
        _beautifyFilterConfiguration = @{
            @"key": @"beautify",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"beautify.parameters",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_fliter_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.beautify",
                            @"child": beautifyEffectParametersConfiguration,
                        },
                        @{
                            @"key": @"beautify.delete",
                            @"iconImage": [UIImage imageNamed:@"edit_ic_delete_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.delete",
                            @"didSelect": NSStringFromSelector(@selector(deleteSelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"beautify.split",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_split_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.split",
                            @"didSelect": NSStringFromSelector(@selector(spliteSelectedClipOrEffect:)),
                        },
                        @{
                            @"key": @"beautify.copy",
                            @"iconImage": [UIImage imageNamed:@"clip_ic_copy_n_Normal"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.copy",
                            @"didSelect": NSStringFromSelector(@selector(copySelectedClipOrEffect:)),
                        },
                    ]
                ],
        };
        
        _transitionTypes = @[
            @{
                @"key": @"transition.none",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationNoneThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.none",
                @"keepSelect": @YES,
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
            },
            @{
                @"key": @"transition.dissolve",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationDissolveThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.dissolve",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeDissolve),
            },
            @{
                @"key": @"transition.fade",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationFadeThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.fade",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeFade),
            },
            @{
                @"key": @"transition.wipeRight",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationWipeRightThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.wipeRight",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeWipeRight),
            },
            @{
                @"key": @"transition.wipeLeft",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationWipeLeftThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.wipeLeft",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeWipeLeft),
            },
            @{
                @"key": @"transition.wipeUp",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationWipeUpThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.wipeUp",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeWipeUp),
            },
            @{
                @"key": @"transition.wipeDown",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationWipeDownThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.wipeDown",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeWipeDown),
            },
            @{
                @"key": @"transition.slideRight",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationSlideRightThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.slideRight",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeSlideRight),
            },
            @{
                @"key": @"transition.slideLeft",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationSlideLeftThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.slideLeft",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeSlideLeft),
            },
            @{
                @"key": @"transition.slideUp",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationSlideUpThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.slideUp",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeSlideUp),
            },
            @{
                @"key": @"transition.slideDown",
                @"iconImage": [UIImage imageNamed:@"EVDAnimationSlideDownThumbnail_Normal"],
                @"titleKey": @"MSVDToolboxView.slideDown",
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"transitionDuration",
                        @"min": @MinTransitionDuration,
                        @"max": @"maxTransitionDuration",
                        @"updateCellValue": @NO,
                        @"continuous": @NO
                },
                @"didSelect": NSStringFromSelector(@selector(transitionSelected:)),
                @"type": @(MSVVideoTransitionTypeSlideDown),
            },
        ];
        
        _transitionConfiguration = @{
            @"key": @"transition",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    _transitionTypes,
                ],
        };
        
        _topToolboxView = [UIView new];
        _topToolboxView.backgroundColor = [UIColor colorWithRed:0.1255 green:0.1255 blue:0.1333 alpha:1];
        [self addSubview:_topToolboxView];
        [_topToolboxView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.height.equalTo(@(TopToolboxHeight));
        }];
        
        _slider = [UISlider new];
        _slider.hidden = YES;
        _slider.minimumTrackTintColor = UIColor.blackColor;
        _slider.maximumTrackTintColor = UIColor.lightGrayColor;
        UIImage *thumbImage = [UIImage rectangleImageWithSize:CGSizeMake(6, 20) color:UIColor.whiteColor];
        [_slider setThumbImage:thumbImage forState:UIControlStateNormal];
        [_slider setThumbImage:thumbImage forState:UIControlStateHighlighted];
        [_slider addTarget:self action:@selector(sliderValueChanged:) forControlEvents:UIControlEventValueChanged];
        
        [_topToolboxView addSubview:_slider];
        [_slider mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            make.width.equalTo(@200);
        }];
        
        _bottomToolboxView = [UIView new];
        _bottomToolboxView.backgroundColor = [UIColor colorWithRed:0.0784 green:0.0784 blue:0.0863 alpha:1];
        [self addSubview:_bottomToolboxView];
        [_bottomToolboxView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_topToolboxView.mas_bottom);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
            make.bottom.equalTo(@0);
        }];
        
        _flowLayout = [UICollectionViewFlowLayout new];
        _flowLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        _flowLayout.sectionInset = UIEdgeInsetsMake(0, 10, 0, 10);
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:_flowLayout];
        _collectionView.backgroundColor = UIColor.clearColor;
        [_collectionView registerClass:MSVDToolboxCollectionViewCell.class forCellWithReuseIdentifier:@"cell"];
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [_bottomToolboxView addSubview:_collectionView];
        
        _backButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _backButton.backgroundColor = [UIColor colorWithRed:0.1255 green:0.1255 blue:0.1333 alpha:1];
        [_bottomToolboxView addSubview:_backButton];
        [_backButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@3);
            make.top.equalTo(@8);
            make.bottom.equalTo(@-8);
            make.width.equalTo(@35);
        }];
        
        [_backButton addTarget:self action:@selector(backButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        _backButton.hidden = YES;
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didSelectClipOrEffect:) name:MSVDDidSelectClipOrEffectNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didSelectTransition:) name:MSVDDidSelectTransitionNotification object:nil];
        [_editor addObserver:self forKeyPath:@"currentTime" options:0 context:nil];
        [self updateWithinSelectedClipTimeRange];
        [self changeToConfiguration:_homeConfiguration];
    }
    return self;
}

- (void)dealloc {
    [NSNotificationCenter.defaultCenter removeObserver:self];
    [_editor removeObserver:self forKeyPath:@"currentTime"];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context {
    if ([keyPath isEqualToString:@"currentTime"]) {
        BOOL previeousWithinTimeRange = _withinSelectedClipTimeRange;
        [self updateWithinSelectedClipTimeRange];
        if (_selectedClipOrEffect && previeousWithinTimeRange != _withinSelectedClipTimeRange) {
            [_collectionView reloadData];
        }
    } else {
        [super observeValueForKeyPath:keyPath ofObject:object change:change context:context];
    }
}

- (void)updateWithinSelectedClipTimeRange {
    MovieousTime currentTime = _editor.currentTime;
    if (currentTime - _selectedClipOrEffect.startTimeAtMainTrack >= MinDurationPerClip && MovieousTimeRangeGetEnd(_selectedClipOrEffect.timeRangeAtMainTrack) - currentTime >= MinDurationPerClip) {
        _withinSelectedClipTimeRange = YES;
        return;
    }
    _withinSelectedClipTimeRange = NO;
}

- (float)maxTransitionDuration {
    MSVClip *clipA = _editor.draft.mainTrackClips[_selectedTransitionIndex];
    MSVClip *clipB = _editor.draft.mainTrackClips[_selectedTransitionIndex + 1];
    return MovieousTimeGetSeconds(MIN(clipA.durationAtMainTrack / 2, clipB.durationAtMainTrack / 2));
}

- (NSInteger)clipOpacity {
    return [(MSVClip *)_selectedClipOrEffect alpha] * 100;
}

- (void)setClipOpacity:(float)value {
    [(MSVClip *)_selectedClipOrEffect setAlpha:value / 100];
}

- (NSInteger)clipVolume {
    return [(MSVClip *)_selectedClipOrEffect volumeMultiplier] * 100;
}

- (void)setClipVolume:(float)value {
    [(MSVClip *)_selectedClipOrEffect setVolumeMultiplier:value / 100];
}

- (float)clipSpeed {
    MSVClip *clip = _selectedClipOrEffect;
    if (clip.type == MSVClipTypeStillImage || clip.type == MSVClipTypeStillText) {
        return 1;
    } else {
        return clip.speed;
    }
}

- (void)setClipSpeed:(float)value {
    MovieousTime timePointer = 0;
    for (MSVMainTrackClip *clip in _editor.draft.mainTrackClips) {
        if (clip == _selectedClipOrEffect) {
            break;
        }
        timePointer += clip.durationAtMainTrack;
    }
    MovieousTime timeToSeek = 0;
    if (_editor.currentTime <= timePointer) {
        timeToSeek = _editor.currentTime;
    } else {
        timeToSeek = timePointer + (_editor.currentTime - timePointer) * ((MSVClip *)_selectedClipOrEffect).speed / value;
    }
    ((MSVClip *)_selectedClipOrEffect).speed = value;
    [_editor seekToTime:timeToSeek accurate:YES];
}

- (NSUInteger)clipFilterIntensity {
    return [(MSVClip *)_selectedClipOrEffect LUTFilterIntensity] * 100;
}

- (void)setClipFilterIntensity:(float)value {
    [(MSVClip *)_selectedClipOrEffect setLUTFilterIntensity:value / 100];
}

- (void)clipFilterSelected:(NSIndexPath *)indexPath {
    if (indexPath.item == 0) {
        ((MSVClip *)_selectedClipOrEffect).LUTFilterImage = nil;
    } else {
        ((MSVClip *)_selectedClipOrEffect).LUTFilterImage = MSVDFiltersLibrary.filters[indexPath.item - 1].image;
    }
}

- (void)backgroundColorSelected:(NSIndexPath *)indexPath {
    ((MSVClip *)_selectedClipOrEffect).backgroundColor = _colors[indexPath.item];
}

- (NSUInteger)effectFilterIntensity {
    return [(MSVLUTFilterEffect *)_selectedClipOrEffect intensity] * 100;
}

- (void)setEffectFilterIntensity:(float)value {
    [(MSVLUTFilterEffect *)_selectedClipOrEffect setIntensity:value / 100];
}

- (NSTimeInterval)transitionDuration {
    MSVBasicMainTrackTransition *transition = (MSVBasicMainTrackTransition *)_editor.draft.mainTrackTransitions[@(_selectedTransitionIndex)];
    return MovieousTimeGetSeconds(transition.durationAtMainTrack);
}

- (void)setTransitionDuration:(float)transitionDuration {
    MSVBasicMainTrackTransition *transition = (MSVBasicMainTrackTransition *)_editor.draft.mainTrackTransitions[@(_selectedTransitionIndex)];
    transition.durationAtMainTrack = MovieousTimeMakeWithSeconds(transitionDuration);
}

- (void)effectFilterSelected:(NSIndexPath *)indexPath {
    ((MSVLUTFilterEffect *)_selectedClipOrEffect).image = MSVDFiltersLibrary.filters[indexPath.item].image;
}

- (NSUInteger)smoothLevel {
    return [(MSVBeautifyFilterEffect *)_selectedClipOrEffect smoothLevel] * 100;
}

- (void)setSmoothLevel:(float)value {
    [(MSVBeautifyFilterEffect *)_selectedClipOrEffect setSmoothLevel:value / 100];
}

- (NSUInteger)whiteLevel {
    return [(MSVBeautifyFilterEffect *)_selectedClipOrEffect whiteLevel] * 100;
}

- (void)setWhiteLevel:(float)value {
    [(MSVBeautifyFilterEffect *)_selectedClipOrEffect setWhiteLevel:value / 100];
}

- (NSUInteger)redLevel {
    return [(MSVBeautifyFilterEffect *)_selectedClipOrEffect redLevel] * 100;
}

- (void)setRedLevel:(float)value {
    [(MSVBeautifyFilterEffect *)_selectedClipOrEffect setRedLevel:value / 100];
}


- (void)homeFilterSelected:(NSIndexPath *)indexPath {
    NSMutableArray *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
    MSVLUTFilterEffect *lutFilterEffect = [MSVLUTFilterEffect new];
    lutFilterEffect.image = MSVDFiltersLibrary.filters.firstObject.image;
    lutFilterEffect.timeRangeAtMainTrack = MovieousTimeRangeMake(_editor.currentTime, 3e6);
    [mixTrackClipsOrEffects addObject:lutFilterEffect];
    NSError *error;
    [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewShouldSelectClipOrEffectNotification object:self userInfo:@{MSVDToolboxViewClipOrEffectKey: lutFilterEffect}];
}

- (void)textSelected:(NSIndexPath *)indexPath {
    NSMutableArray *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
    NSError *error;
    MSVMixTrackClip *mixTrackClip = [MSVMixTrackClip mixTrackClipWithStillText:[[NSAttributedString alloc] initWithString:NSLocalizedString(@"global.inputText", nil) attributes:@{NSFontAttributeName: [UIFont systemFontOfSize:100], NSForegroundColorAttributeName: UIColor.whiteColor}] duration:3e6 startTimeAtMainTrack:_editor.currentTime error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
    [mixTrackClip setAttachment:@YES forKey:IsEmptyStringKey];
    mixTrackClip.destSize = CGSizeMake(mixTrackClip.defaultSize.width / _editor.draft.videoSize.width, mixTrackClip.defaultSize.height / _editor.draft.videoSize.height);
    [mixTrackClipsOrEffects addObject:mixTrackClip];
    [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewShouldSelectClipOrEffectNotification object:self userInfo:@{MSVDToolboxViewClipOrEffectKey: mixTrackClip}];
}

- (void)beautifySelected:(NSIndexPath *)indexPath {
    NSMutableArray *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
    MSVBeautifyFilterEffect *beautifyFilterEffect = [MSVBeautifyFilterEffect new];
    beautifyFilterEffect.timeRangeAtMainTrack = MovieousTimeRangeMake(_editor.currentTime, 3e6);
    [mixTrackClipsOrEffects addObject:beautifyFilterEffect];
    NSError *error;
    [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewShouldSelectClipOrEffectNotification object:self userInfo:@{MSVDToolboxViewClipOrEffectKey: beautifyFilterEffect}];
}

- (void)transitionSelected:(NSIndexPath *)indexPath {
    NSMutableDictionary *mainTrackTransitions = [_editor.draft.mainTrackTransitions mutableCopy];
    MSVBasicMainTrackTransition *transition = (MSVBasicMainTrackTransition *)_editor.draft.mainTrackTransitions[@(_selectedTransitionIndex)];
    if (indexPath.row == 0) {
        transition = nil;
    } else if (!transition) {
        transition = [MSVBasicMainTrackTransition new];
        transition.durationAtMainTrack = MIN(MIN(_editor.draft.mainTrackClips[_selectedTransitionIndex].durationAtMainTrack, _editor.draft.mainTrackClips[_selectedTransitionIndex + 1].durationAtMainTrack) / 2, DefaultTransitionDuration);
        transition.transitionType = [_transitionTypes[indexPath.row][@"type"] integerValue];
    } else {
        // 仅仅切换 transitionType 就可以了，不需要 updateMainTrackTransitions
        transition.transitionType = [_transitionTypes[indexPath.row][@"type"] integerValue];
        return;
    }
    mainTrackTransitions[@(_selectedTransitionIndex)] = transition;
    NSError *error;
    [_editor.draft updateMainTrackTransitions:mainTrackTransitions error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
}

- (void)aspectRatioSelected:(NSIndexPath *)indexPath {
    [_editor.draft beginChangeTransaction];
    _editor.draft.aspectRatio = _aspectRatios[indexPath.item].CGSizeValue;
    for (MSVMainTrackClip *clip in _editor.draft.mainTrackClips) {
        [clip resetGeometryWithVideoSize:_editor.draft.videoSize scalingMode:MovieousScalingModeAspectFit];
    }
    for (id clipOrEffect in _editor.draft.mixTrackClipsOrEffects) {
        if ([clipOrEffect isKindOfClass:MSVMixTrackClip.class]) {
            MSVMixTrackClip *clip = clipOrEffect;
            [clip resetGeometryWithVideoSize:_editor.draft.videoSize scalingMode:MovieousScalingModeAspectFit];
        }
    }
    [_editor.draft commitChangeWithError:nil];
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewSelectedClipGeoUpdatedNotification object:self];
}

- (void)deleteSelectedClipOrEffect:(NSIndexPath *)indexPath {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [_editor.draft.mainTrackClips mutableCopy];
        NSUInteger index = 0;
        MovieousTime timeToSeek = 0;
        for (NSUInteger i = 0; i < _editor.draft.mainTrackClips.count; i++) {
            MSVMainTrackClip *clip = _editor.draft.mainTrackClips[i];
            if (_selectedClipOrEffect == clip) {
                index = i;
                timeToSeek = clip.startTimeAtMainTrack;
                break;
            }
        }
        [mainTrackClips removeObjectAtIndex:index];
        NSError *error;
        [_editor.draft beginChangeTransaction];
        [_editor.draft updateMainTrackClips:mainTrackClips error:nil];
        [MSVDUtils ensureTransitionDurationWithDraft:_editor.draft error:nil];
        [_editor.draft commitChangeWithError:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:timeToSeek accurate:YES];
    } else {
        NSMutableArray<id<MSVMutableClipOrEffect>> *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
        NSUInteger index = 0;
        MovieousTime timeToSeek = _editor.currentTime;
        for (NSUInteger i = 0; i < _editor.draft.mixTrackClipsOrEffects.count; i++) {
            id<MSVMutableClipOrEffect> clipOrEffect = (MSVMixTrackClip *)_editor.draft.mixTrackClipsOrEffects[i];
            if (_selectedClipOrEffect == clipOrEffect) {
                index = i;
                break;
            }
        }
        [mixTrackClipsOrEffects removeObjectAtIndex:index];
        NSError *error;
        [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        if (timeToSeek > _editor.draft.timeRange.duration) {
            timeToSeek = _editor.draft.timeRange.duration;
        }
        [_editor seekToTime:timeToSeek accurate:YES];
    }
}

- (void)copySelectedClipOrEffect:(NSIndexPath *)indexPath {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [_editor.draft.mainTrackClips mutableCopy];
        NSUInteger index = 0;
        MovieousTime timeToSeek = 0;
        for (NSUInteger i = 0; i < _editor.draft.mainTrackClips.count; i++) {
            MSVMainTrackClip *clip = _editor.draft.mainTrackClips[i];
            if (_selectedClipOrEffect == clip) {
                timeToSeek = MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack);
                index = i;
                break;
            }
        }
        MSVMainTrackClip *clipToInsert = [_selectedClipOrEffect copy];
        [clipToInsert removeAllAttachments];
        [mainTrackClips insertObject:clipToInsert atIndex:index];
        NSError *error;
        [_editor.draft beginChangeTransaction];
        [_editor.draft updateMainTrackClips:mainTrackClips error:nil];
        [MSVDUtils ensureTransitionDurationWithDraft:_editor.draft error:nil];
        [_editor.draft commitChangeWithError:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:timeToSeek accurate:YES];
    } else {
        NSMutableArray *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
        NSUInteger index = 0;
        MovieousTime timeToSeek = _editor.currentTime;
        for (NSUInteger i = 0; i < _editor.draft.mixTrackClipsOrEffects.count; i++) {
            id<MSVMutableClipOrEffect> clipOrEffect = _editor.draft.mixTrackClipsOrEffects[i];
            if (_selectedClipOrEffect == clipOrEffect) {
                index = i;
                break;
            }
        }
        MovieousObject *clipOrEffectToInsert = [_selectedClipOrEffect copy];
        [clipOrEffectToInsert removeAllAttachments];
        [mixTrackClipsOrEffects insertObject:clipOrEffectToInsert atIndex:index];
        NSError *error;
        [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:timeToSeek accurate:YES];
    }
}

- (void)spliteSelectedClipOrEffect:(NSIndexPath *)indexPath {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [NSMutableArray array];
        MovieousTime currentTime = _editor.currentTime;
        MovieousTime timePointer = 0;
        [_editor.draft beginChangeTransaction];
        for (MSVMainTrackClip *clip in _editor.draft.mainTrackClips) {
            if (_selectedClipOrEffect == clip) {
                if (clip.type == MSVClipTypeStillImage || clip.type == MSVClipTypeStillText) {
                    MSVMainTrackClip *splitClip = [clip copy];
                    splitClip.durationAtMainTrack = currentTime - timePointer;
                    // 避免使用过同一个 snapshotBar
                    [splitClip removeAllAttachments];
                    [mainTrackClips addObject:splitClip];
                    clip.durationAtMainTrack = clip.durationAtMainTrack - splitClip.durationAtMainTrack;
                    [mainTrackClips addObject:clip];
                } else {
                    double ratio = (double)(currentTime - timePointer) / clip.durationAtMainTrack;
                    MSVMainTrackClip *splitClip = [clip copy];
                    splitClip.timeRange = MovieousTimeRangeMake(splitClip.timeRange.start, splitClip.timeRange.duration * ratio);
                    // 避免使用过同一个 snapshotBar
                    [splitClip removeAllAttachments];
                    [mainTrackClips addObject:splitClip];
                    clip.timeRange = MovieousTimeRangeMake(splitClip.timeRange.start + splitClip.timeRange.duration, clip.timeRange.duration * (1 - ratio));
                    [mainTrackClips addObject:clip];
                }
            } else {
                [mainTrackClips addObject:clip];
                timePointer += clip.durationAtMainTrack;
            }
        }
        NSError *error;
        [_editor.draft updateMainTrackClips:mainTrackClips error:nil];
        [MSVDUtils ensureTransitionDurationWithDraft:_editor.draft error:nil];
        [_editor.draft commitChangeWithError:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:currentTime accurate:YES];
    } else {
        NSMutableArray *mixTrackClipsOrEffects = [NSMutableArray array];
        MovieousTime currentTime = _editor.currentTime;
        [_editor.draft beginChangeTransaction];
        for (id<MSVMutableClipOrEffect> clipOrEffect in _editor.draft.mixTrackClipsOrEffects) {
            if (_selectedClipOrEffect == clipOrEffect) {
                if ([clipOrEffect isKindOfClass:MSVMixTrackClip.class] && ((MSVMixTrackClip *)clipOrEffect).type != MSVClipTypeStillImage && ((MSVMixTrackClip *)clipOrEffect).type != MSVClipTypeStillText) {
                    MSVMixTrackClip *clip = (MSVMixTrackClip *)clipOrEffect;
                    double ratio = (double)(currentTime - clip.startTimeAtMainTrack) / clip.durationAtMainTrack;
                    MSVMainTrackClip *splitClip = [clip copy];
                    splitClip.timeRange = MovieousTimeRangeMake(splitClip.timeRange.start, splitClip.timeRange.duration * ratio);
                    [mixTrackClipsOrEffects addObject:splitClip];
                    // 避免使用过同一个 snapshotBar
                    [splitClip removeAllAttachments];
                    clip.timeRange = MovieousTimeRangeMake(splitClip.timeRange.start + splitClip.timeRange.duration, clip.timeRange.duration * (1 - ratio));
                    clip.startTimeAtMainTrack = currentTime;
                    [mixTrackClipsOrEffects addObject:clip];
                } else {
                    id<MSVMutableClipOrEffect> splitClipOrEffect = [clipOrEffect copy];
                    splitClipOrEffect.durationAtMainTrack = currentTime - splitClipOrEffect.startTimeAtMainTrack;
                    [mixTrackClipsOrEffects addObject:splitClipOrEffect];
                    [(MovieousObject *)splitClipOrEffect removeAllAttachments];
                    clipOrEffect.startTimeAtMainTrack = currentTime;
                    clipOrEffect.durationAtMainTrack = clipOrEffect.durationAtMainTrack - splitClipOrEffect.durationAtMainTrack;
                    [mixTrackClipsOrEffects addObject:clipOrEffect];
                }
            } else {
                [mixTrackClipsOrEffects addObject:clipOrEffect];
            }
        }
        NSError *error;
        [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:nil];
        [_editor.draft commitChangeWithError:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:currentTime accurate:YES];
    }
}

- (CGSize)intrinsicContentSize {
    return CGSizeMake(0, TopToolboxHeight + BottomToolboxHeight);
}

- (void)sliderValueChanged:(UISlider *)sender {
    [self setValue:@(sender.value) forKey:_sliderKey];
    MSVDToolboxCollectionViewCell *cell = (MSVDToolboxCollectionViewCell *)[_collectionView cellForItemAtIndexPath:_selectedIndexPath];
    NSDictionary *cellConfiguration = _currentConfiguration[@"content"][_selectedIndexPath.section][_selectedIndexPath.item];
    if ([cellConfiguration[@"adjustSlider"][@"updateCellValue"] boolValue]) {
        if ([_sliderKey isEqualToString:@"clipSpeed"]) {
            cell.icon = [NSString stringWithFormat:@"%.1f", sender.value];
        } else {
            cell.icon = [NSString stringWithFormat:@"%d", (int)sender.value];
        }
    }
}

- (void)backButtonPressed:(UIButton *)sender {
    [self popConfiguration];
}

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return [_currentConfiguration[@"content"] count];
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return [_currentConfiguration[@"content"][section] count];
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    MSVDToolboxCollectionViewCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"cell" forIndexPath:indexPath];
    NSDictionary *cellConfiguration = _currentConfiguration[@"content"][indexPath.section][indexPath.item];
    cell.title = NSLocalizedString(cellConfiguration[@"titleKey"], @"");
    NSString *key = cellConfiguration[@"key"];
    if ([key isEqualToString:@"clip.audio"]) {
        cell.enabled = ((MSVClip *)_selectedClipOrEffect).hasAuditoryContent;
    } else if ([key isEqualToString:@"clip.speed"]) {
        cell.enabled = ((MSVClip *)_selectedClipOrEffect).type != MSVClipTypeStillImage && ((MSVClip *)_selectedClipOrEffect).type != MSVClipTypeStillText;
    } else if ([key isEqualToString:@"clip.delete"]) {
        if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
            cell.enabled = _editor.draft.mainTrackClips.count > 1;
        } else {
            cell.enabled = YES;
        }
    } else if ([key hasPrefix:@"transition."]) {
        MSVMainTrackClip *leadingClip = _editor.draft.mainTrackClips[_selectedTransitionIndex];
        MSVMainTrackClip *trailingClip = _editor.draft.mainTrackClips[_selectedTransitionIndex + 1];
        MovieousTime maxDuration = MIN(leadingClip.durationAtMainTrack / 2, trailingClip.durationAtMainTrack / 2);
        if (maxDuration < MovieousTimeMakeWithSeconds(MinTransitionDuration)) {
            cell.enabled = NO;
        } else {
            cell.enabled = YES;
        }
    } else {
        cell.enabled = YES;
    }
    if ([key isEqualToString:@"clip.split"] || [key isEqualToString:@"lut.split"] || [key isEqualToString:@"beautify.split"]) {
        cell.enabled = _withinSelectedClipTimeRange;
    }
    if (cellConfiguration[@"iconImage"]) {
        if ([cellConfiguration[@"isTemplateIconImage"] boolValue]) {
            cell.icon = [cellConfiguration[@"iconImage"] imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
        } else {
            cell.icon = cellConfiguration[@"iconImage"];
        }
    } else if (cellConfiguration[@"iconColor"]) {
        cell.icon = cellConfiguration[@"iconColor"];
    } else if (cellConfiguration[@"aspectRatio"]) {
        CGSize size;
        NSString *title;
        if (CGSizeEqualToSize(_aspectRatios[indexPath.item].CGSizeValue, CGSizeZero)) {
            size = CGSizeMake(1, 1);
            title = NSLocalizedString(@"MSVToolboxView.originalSize", nil);
        } else {
            size = _aspectRatios[indexPath.item].CGSizeValue;
            title = [NSString stringWithFormat:@"%.0f:%.0f", size.width, size.height];
        }
        cell.icon = @(size);
        cell.title = title;
    } else if (cellConfiguration[@"iconValueKey"]) {
        if ([key isEqualToString:@"clip.speed"]) {
            cell.icon = [NSString stringWithFormat:@"%.1f", [[self valueForKey:cellConfiguration[@"iconValueKey"]] floatValue]];
        } else {
            cell.icon = [NSString stringWithFormat:@"%d", [[self valueForKey:cellConfiguration[@"iconValueKey"]] intValue]];
        }
    }
    cell.customSelected = [indexPath isEqual:_selectedIndexPath];
    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    NSDictionary *cellConfiguration = _currentConfiguration[@"content"][indexPath.section][indexPath.item];
    if (cellConfiguration[@"didSelect"]) {
        [self performSelectorWithName:cellConfiguration[@"didSelect"] object:indexPath];
    }
    if (cellConfiguration[@"child"]) {
        _selectedIndexPath = nil;
        [self pushConfiguration:cellConfiguration[@"child"]];
    } else {
        if ([cellConfiguration[@"keepSelect"] boolValue]) {
            _selectedIndexPath = indexPath;
        } else {
            _selectedIndexPath = nil;
        }
        [self updateSliderWithConfiguration:cellConfiguration];
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewToolSelectedNotification object:self userInfo:@{MSVDToolboxViewSelectedToolKey: cellConfiguration[@"key"]}];
    [collectionView reloadData];
}

- (void)updateSliderWithConfiguration:(NSDictionary *)configuration {
    NSDictionary *adjustSlider = configuration[@"adjustSlider"];
    if (adjustSlider) {
        _sliderKey = adjustSlider[@"key"];
        _slider.hidden = NO;
        if ([adjustSlider[@"min"] isKindOfClass:NSNumber.class]) {
            _slider.minimumValue = [adjustSlider[@"min"] floatValue];
        } else if ([adjustSlider[@"min"] isKindOfClass:NSString.class]) {
            _slider.minimumValue = [[self valueForKeyPath:adjustSlider[@"min"]] floatValue];
        }
        if ([adjustSlider[@"max"] isKindOfClass:NSNumber.class]) {
            _slider.maximumValue = [adjustSlider[@"max"] floatValue];
        } else if ([adjustSlider[@"max"] isKindOfClass:NSString.class]) {
            _slider.maximumValue = [[self valueForKeyPath:adjustSlider[@"max"]] floatValue];
        }
        _slider.value = [[self valueForKey:_sliderKey] doubleValue];
        _slider.continuous = [adjustSlider[@"continuous"] boolValue];
    } else {
        _slider.hidden = YES;
    }
}

- (void)performSelectorWithName:(NSString *)name object:(id)object {
    SEL selector = NSSelectorFromString(name);
    ((void (*)(id, SEL, id))[self methodForSelector:selector])(self, selector, object);
}

- (void)didSelectClipOrEffect:(NSNotification *)notification {
    MSVDClipsAndEeffectsView *clipsAndEeffectsView = notification.object;
    _selectedClipOrEffect = clipsAndEeffectsView.selectedClipOrEffect;
    [self updateWithinSelectedClipTimeRange];
    if (_selectedClipOrEffect) {
        // 作为父配置，以便返回 home
        _currentConfiguration = _homeConfiguration;
        if ([_selectedClipOrEffect isKindOfClass:MSVClip.class]) {
            [self pushConfiguration:_clipConfiguration];
        } else if ([_selectedClipOrEffect isKindOfClass:MSVLUTFilterEffect.class]) {
            [self pushConfiguration:_lutEffectConfiguration];
        } else if ([_selectedClipOrEffect isKindOfClass:MSVBeautifyFilterEffect.class]) {
            [self pushConfiguration:_beautifyFilterConfiguration];
        }
    } else {
        // 返回主页
        [self changeToConfiguration:_homeConfiguration];
    }
}

- (void)didSelectTransition:(NSNotification *)notification {
    MSVDClipsAndEeffectsView *clipsAndEeffectsView = notification.object;
    _selectedTransitionIndex = clipsAndEeffectsView.selectedMainTrackTransitionIndex;
    if (clipsAndEeffectsView.selectedMainTrackTransitionIndex == NSNotFound) {
        // 返回主页
        [self changeToConfiguration:_homeConfiguration];
    } else {
        // 作为父配置，以便返回 home
        _currentConfiguration = _homeConfiguration;
        [self pushConfiguration:_transitionConfiguration];
    }
}

- (void)pushConfiguration:(NSDictionary *)configuration {
    NSMutableDictionary *mutableConfiguration = [configuration mutableCopy];
    mutableConfiguration[@"depth"] = @([_currentConfiguration[@"depth"] integerValue] + 1);
    mutableConfiguration[@"parent"] = _currentConfiguration;
    [self changeToConfiguration:mutableConfiguration];
}

- (void)popConfiguration {
    if (_currentConfiguration[@"parent"]) {
        [self changeToConfiguration:_currentConfiguration[@"parent"]];
    }
}

- (void)changeToConfiguration:(NSDictionary *)configuration {
    if ([_currentConfiguration[@"key"] isEqualToString:configuration[@"key"]]) {
        return;
    }
    if (!NSThread.currentThread.isMainThread) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [self changeToConfiguration:configuration];
        });
        return;
    }
    _selectedIndexPath = nil;
    NSInteger depth = [configuration[@"depth"] integerValue];
    if (depth > 0) {
        _backButton.hidden = NO;
        if (depth == 1) {
            [_backButton setImage:[UIImage imageNamed:@"level2_ic_back _n_Normal"] forState:UIControlStateNormal];
        } else if (depth == 2) {
            [_backButton setImage:[UIImage imageNamed:@"level3_ic_back _n_Normal"] forState:UIControlStateNormal];
        } else {
            [_backButton setImage:[UIImage imageNamed:@"level4_ic_back_n_Normal"] forState:UIControlStateNormal];
        }
        [_collectionView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_backButton.mas_right);
            make.right.equalTo(@0);
            make.top.equalTo(@0);
            make.bottom.equalTo(@0);
        }];
    } else {
        _backButton.hidden = YES;
        [_collectionView mas_remakeConstraints:^(MASConstraintMaker *make) {
            make.edges.equalTo(@0);
        }];
    }
    _currentConfiguration = configuration;
    [self refreshSelectedIndexPath];
    MSVDToolboxStyle style = [_currentConfiguration[@"style"] unsignedIntegerValue];
    if (style == MSVDToolboxStyleNormal) {
        _flowLayout.minimumLineSpacing = 0;
        _flowLayout.minimumInteritemSpacing = 0;
        _flowLayout.itemSize = CGSizeMake(ToolboxWidth, BottomToolboxHeight);
    } else if (style == MSVDToolboxStyleColor) {
        _flowLayout.minimumLineSpacing = 10;
        _flowLayout.minimumInteritemSpacing = 0;
        _flowLayout.itemSize = CGSizeMake(BottomToolboxHeight / 3, BottomToolboxHeight * 2 / 3);
    }
    if (_selectedIndexPath) {
        [self updateSliderWithConfiguration:_currentConfiguration[@"content"][_selectedIndexPath.section][_selectedIndexPath.item]];
    } else {
        _slider.hidden = YES;
    }
    [_collectionView reloadData];
    _collectionView.contentOffset = CGPointZero;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewChangeToToolboxNotification object:self userInfo:@{MSVDToolboxViewConfigurationKey: configuration[@"key"]}];
}

- (void)refreshSelectedIndexPath {
    NSString *key = _currentConfiguration[@"key"];
    if ([key isEqualToString:@"clip.background.color"]) {
        MSVClip *clip = _selectedClipOrEffect;
        NSUInteger index = [_colors indexOfObject:clip.backgroundColor];
        if (index == NSNotFound) {
            _selectedIndexPath = nil;
        } else {
            _selectedIndexPath = [NSIndexPath indexPathForItem:index inSection:0];
        }
    } else if ([key isEqualToString:@"clip.filters"]) {
        MSVClip *clip = _selectedClipOrEffect;
        for (NSUInteger i = 0; i < MSVDFiltersLibrary.filters.count; i++) {
            MSVDFilter *filter = MSVDFiltersLibrary.filters[i];
            if (filter.image == clip.LUTFilterImage) {
                _selectedIndexPath = [NSIndexPath indexPathForItem:i + 1 inSection:0];
                return;
            }
        }
        _selectedIndexPath = [NSIndexPath indexPathForItem:0 inSection:0];
    } else if ([key isEqualToString:@"lut.filters"]) {
        MSVLUTFilterEffect *effect = (MSVLUTFilterEffect *)_selectedClipOrEffect;
        for (NSUInteger i = 0; i < MSVDFiltersLibrary.filters.count; i++) {
            MSVDFilter *filter = MSVDFiltersLibrary.filters[i];
            if (filter.image == effect.image) {
                _selectedIndexPath = [NSIndexPath indexPathForItem:i inSection:0];
                return;
            }
        }
        _selectedIndexPath = nil;
    } else if ([key isEqualToString:@"home.aspectRatio"]) {
        for (NSUInteger i = 0; i < _aspectRatios.count; i++) {
            if (CGSizeEqualToSize(_aspectRatios[i].CGSizeValue, _editor.draft.aspectRatio)) {
                _selectedIndexPath = [NSIndexPath indexPathForItem:i inSection:0];
                return;
            }
        }
        _selectedIndexPath = nil;
    } else if ([key isEqualToString:@"transition"]) {
        MSVBasicMainTrackTransition *transition = (MSVBasicMainTrackTransition *)_editor.draft.mainTrackTransitions[@(_selectedTransitionIndex)];
        NSUInteger selectedIndex = 0;
        if (transition) {
            for (NSUInteger i = 1; i < _transitionTypes.count; i++) {
                if ([_transitionTypes[i][@"type"] unsignedIntValue] == transition.transitionType) {
                    selectedIndex = i;
                    break;
                }
            }
        }
        _selectedIndexPath = [NSIndexPath indexPathForItem:selectedIndex inSection:0];
    }
}

@end
