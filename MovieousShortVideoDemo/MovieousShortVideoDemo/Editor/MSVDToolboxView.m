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

#define TopToolboxHeight    40.0
#define BottomToolboxHeight 80.0

@interface MSVDToolboxCollectionViewCell : UICollectionViewCell

@property (nonatomic, strong) NSString *title;
@property (nonatomic, strong) UIImage *icon;
@property (nonatomic, assign) NSInteger value;
@property (nonatomic, assign) UIColor *color;
@property (nonatomic, assign) BOOL enabled;

- (void)setIconWithTemplate:(UIImage *)template;

@end

@implementation MSVDToolboxCollectionViewCell {
    UIImageView *_iconImageView;
    UILabel *_valueLabel;
    UILabel *_titleLabel;
}

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        _iconImageView = [UIImageView new];
        _iconImageView.contentMode = UIViewContentModeScaleAspectFit;
        [self.contentView addSubview:_iconImageView];
        [_iconImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@15);
            make.left.equalTo(@27);
            make.right.equalTo(@-27);
            make.height.equalTo(_iconImageView.mas_width);
        }];
        
        _valueLabel = [UILabel new];
        _valueLabel.textColor = UIColor.whiteColor;
        _valueLabel.highlightedTextColor = UIColor.purpleColor;
        _valueLabel.font = [UIFont systemFontOfSize:35];
        _valueLabel.textAlignment = NSTextAlignmentCenter;
        [self.contentView addSubview:_valueLabel];
        [_valueLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(@5);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
        
        _titleLabel = [UILabel new];
        _titleLabel.textColor = UIColor.whiteColor;
        _titleLabel.highlightedTextColor = UIColor.purpleColor;
        _titleLabel.font = [UIFont systemFontOfSize:12];
        _titleLabel.textAlignment = NSTextAlignmentCenter;
        [self.contentView addSubview:_titleLabel];
        [_titleLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.centerX.equalTo(@0);
            make.bottom.equalTo(@-15);
        }];
    }
    return self;
}

- (void)setTitle:(NSString *)title {
    _titleLabel.text = title;
}

- (NSString *)title {
    return _titleLabel.text;
}

- (void)setIcon:(UIImage *)icon {
    _iconImageView.hidden = NO;
    _valueLabel.hidden = YES;
    _iconImageView.image = icon;
    _iconImageView.backgroundColor = nil;
}

- (UIImage *)icon {
    return _iconImageView.image;
}

- (void)setIconWithTemplate:(UIImage *)template {
    _iconImageView.hidden = NO;
    _valueLabel.hidden = YES;
    _iconImageView.image = [template imageWithRenderingMode:UIImageRenderingModeAlwaysTemplate];
    _iconImageView.backgroundColor = nil;
}

- (void)setValue:(NSInteger)value {
    _value = value;
    _iconImageView.hidden = YES;
    _valueLabel.hidden = NO;
    _valueLabel.text = [NSString stringWithFormat:@"%ld", (long)value];
}

- (void)setColor:(UIColor *)color {
    _iconImageView.hidden = NO;
    _valueLabel.hidden = YES;
    _iconImageView.image = nil;
    _iconImageView.backgroundColor = color;
}

- (UIColor *)color {
    return _iconImageView.backgroundColor;
}

- (void)setEnabled:(BOOL)enabled {
    _enabled = enabled;
    self.userInteractionEnabled = enabled;
    _titleLabel.textColor = enabled ? UIColor.whiteColor : UIColor.lightGrayColor;
    _valueLabel.textColor = enabled ? UIColor.whiteColor : UIColor.lightGrayColor;
    _iconImageView.tintColor = enabled ? UIColor.whiteColor : UIColor.lightGrayColor;
}

@end

typedef NS_ENUM(NSUInteger, MSVDToolboxStyle) {
    MSVDToolboxStyleNormal,
};

@interface MSVDToolboxView ()
<
UICollectionViewDelegateFlowLayout,
UICollectionViewDataSource
>

@end

@implementation MSVDToolboxView {
    MSVEditor *_editor;
    UIButton *_backButton;
    UIView *_topToolboxView;
    UISlider *_slider;
    UICollectionViewFlowLayout *_flowLayout;
    UICollectionView *_collectionView;
    NSDictionary *_homeConfiguration;
    NSDictionary *_clipConfiguration;
    NSDictionary *_currentConfiguration;
    id _selectedClipOrEffect;
    NSString *_sliderKey;
    NSMutableArray<NSString *> *_filterPaths;
    NSArray<UIColor *> *_colors;
    BOOL _withinSelectedClipTimeRange;
}

- (instancetype)initWithEditor:(MSVEditor *)editor {
    if (self = [super init]) {
        _editor = editor;
        
        _filterPaths = [NSMutableArray array];
        NSString *filterBundlePath = [NSBundle.mainBundle pathForResource:@"Filters" ofType:@"bundle"];
        NSError *error;
        NSArray *names = [NSFileManager.defaultManager contentsOfDirectoryAtPath:filterBundlePath error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return nil;
        }
        for (NSString *name in names) {
            [_filterPaths addObject:[NSString stringWithFormat:@"%@/%@", filterBundlePath, name]];
        }
        
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
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.music"
                        },
                        @{
                            @"key": @"home.audio.record",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.audio.record"
                        },
                    ]
                ],
        };
        _colors = @[
            UIColor.blackColor,
            UIColor.darkGrayColor,
            UIColor.lightGrayColor,
            UIColor.whiteColor,
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
                @"key": @"home.canvas.background.color",
                @"iconColor": color,
                @"keepSelect": @YES,
                @"didSelect": NSStringFromSelector(@selector(backgroundColorSelected:)),
            }];
        }
        NSDictionary *backgroundColorsConfiguration = @{
            @"key": @"home.canvas.background.color",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    colorsConfiguration
                ],
        };
        NSDictionary *backgroundConfiguration = @{
            @"key": @"home.canvas.background",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"home.canvas.background.color",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.color",
                            @"child": backgroundColorsConfiguration
                        },
                        @{
                            @"key": @"home.canvas.background.blur",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.blur"
                        },
                    ]
                ],
        };
        NSDictionary *canvasConfiguration = @{
            @"key": @"home.canvas",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    @[
                        @{
                            @"key": @"home.canvas.ratio",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.ratio",
                        },
                        @{
                            @"key": @"home.canvas.background",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.background",
                            @"child": backgroundConfiguration,
                        },
                    ]
                ],
        };
        NSMutableArray *homeFilters = [NSMutableArray arrayWithCapacity:_filterPaths.count];
        for (NSString *path in _filterPaths) {
            NSString *filterName = path.lastPathComponent;
            [homeFilters addObject:@{
                @"key": [NSString stringWithFormat:@"home.filter.%@", filterName],
                @"iconImage": [UIImage imageNamed:@"filter_template.jpg"],
                @"titleKey": filterName,
                @"didSelect": NSStringFromSelector(@selector(homeFilterSelected:)),
            }];
        }
        NSDictionary *homeFiltersConfiguration = @{
            @"key": @"home.filter",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    homeFilters
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
                            @"key": @"home.canvas",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.canvas",
                            @"child": canvasConfiguration,
                        },
                        @{
                            @"key": @"home.pip",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.pip",
                        },
                        @{
                            @"key": @"home.text",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.text",
                        },
                        @{
                            @"key": @"home.sticker",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.sticker",
                        },
                        @{
                            @"key": @"home.audio",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.audio",
                            @"child": audioConfiguration
                        },
                        @{
                            @"key": @"home.filter",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.filter",
                            @"child": homeFiltersConfiguration
                        },
                        @{
                            @"key": @"home.beautify",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
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
                                    @"continuous": @YES
                            }
                        },
                    ]
                ],
        };
        NSMutableArray *clipFilters = [@[@{
                                         @"key": @"clip.filter.none",
                                         @"iconImage": [UIImage imageNamed:@"filter_template.jpg"],
                                         @"titleKey": @"none",
                                         @"keepSelect": @YES,
                                         @"didSelect": NSStringFromSelector(@selector(clipFilterSelected:)),
        }] mutableCopy];
        for (NSString *path in _filterPaths) {
            NSString *filterName = path.lastPathComponent;
            [clipFilters addObject:@{
                @"key": [NSString stringWithFormat:@"clip.filter.%@", filterName],
                @"iconImage": [UIImage imageNamed:@"filter_template.jpg"],
                @"titleKey": filterName,
                @"keepSelect": @YES,
                @"adjustSlider": @{
                        @"key": @"clipFilterIntensity",
                        @"min": @0,
                        @"max": @100,
                        @"continuous": @YES
                },
                @"didSelect": NSStringFromSelector(@selector(clipFilterSelected:)),
            }];
        }
        NSDictionary *clipFiltersConfiguration = @{
            @"key": @"clip.filter",
            @"style": @(MSVDToolboxStyleNormal),
            @"content":
                @[
                    clipFilters
                ],
        };
        _clipConfiguration = @{
            @"key": @"clip",
            @"style": @(MSVDToolboxStyleNormal),
            @"depth": @1,
            @"parent": _homeConfiguration,
            @"content":
                @[
                    @[
                        @{
                            @"key": @"clip.delete",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.delete",
                            @"didSelect": NSStringFromSelector(@selector(deleteSelectedClip:)),
                        },
                        @{
                            @"key": @"clip.split",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.split",
                            @"didSelect": NSStringFromSelector(@selector(spliteSelectedClip:)),
                        },
                        @{
                            @"key": @"clip.speed",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.speed",
                            @"keepSelect": @YES,
                            @"adjustSlider": @{
                                    @"key": @"clipSpeed",
                                    @"min": @0.1,
                                    @"max": @2,
                                    @"continuous": @NO
                            }
                        },
                        @{
                            @"key": @"clip.audio",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.audio",
                            @"child": clipAudioConfiguration,
                        },
                        @{
                            @"key": @"clip.replace",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
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
                                    @"continuous": @YES
                            }
                        },
                        @{
                            @"key": @"clip.filter",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.filter",
                            @"child": clipFiltersConfiguration,
                        },
                        @{
                            @"key": @"clip.copy",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.copy",
                            @"didSelect": NSStringFromSelector(@selector(copySelectedClip:)),
                        },
                        @{
                            @"key": @"clip.reverse",
                            @"iconImage": [UIImage imageNamed:@"pencil"],
                            @"isTemplateIconImage": @YES,
                            @"titleKey": @"MSVDToolboxView.reverse",
                        },
                    ]
                ],
        };
        _currentConfiguration = _homeConfiguration;
        
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
        
        _flowLayout = [UICollectionViewFlowLayout new];
        _flowLayout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        _flowLayout.minimumLineSpacing = 0;
        _flowLayout.minimumInteritemSpacing = 0;
        _flowLayout.itemSize = CGSizeMake(BottomToolboxHeight, BottomToolboxHeight);
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero collectionViewLayout:_flowLayout];
        _collectionView.backgroundColor = [UIColor colorWithRed:0.0784 green:0.0784 blue:0.0863 alpha:1];
        [_collectionView registerClass:MSVDToolboxCollectionViewCell.class forCellWithReuseIdentifier:@"cell"];
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [self addSubview:_collectionView];
        [_collectionView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.top.equalTo(_topToolboxView.mas_bottom);
            make.bottom.equalTo(@0);
            make.left.equalTo(@0);
            make.right.equalTo(@0);
        }];
        _backButton = [UIButton buttonWithType:UIButtonTypeCustom];
        _backButton.backgroundColor = UIColor.lightGrayColor;
        [self addSubview:_backButton];
        [_backButton mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@3);
            make.top.equalTo(_collectionView.mas_top).offset(3);
            make.bottom.equalTo(@-3);
            make.width.equalTo(@30);
        }];
        [_backButton addTarget:self action:@selector(backButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        _backButton.hidden = YES;
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didSelectClipOrEffect:) name:MSVDDidSelectClipOrEffectNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(didDeselectClipOrEffect:) name:MSVDDidDeselectClipOrEffectNotification object:nil];
        [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(editorCurrentTimeUpdated:) name:kMSVEditorCurrentTimeUpdatedNotification object:nil];
        [self updateWithinSelectedClipTimeRange];
    }
    return self;
}

- (void)dealloc {
    [NSNotificationCenter.defaultCenter removeObserver:self];
}

- (void)editorCurrentTimeUpdated:(NSNotification *)notification {
    BOOL previeousWithinTimeRange = _withinSelectedClipTimeRange;
    [self updateWithinSelectedClipTimeRange];
    if (_selectedClipOrEffect && previeousWithinTimeRange != _withinSelectedClipTimeRange) {
        [_collectionView reloadData];
    }
}

- (void)updateWithinSelectedClipTimeRange {
    MovieousTime currentTime = _editor.currentTime;
    if ([_selectedClipOrEffect isKindOfClass:MSVClip.class]) {
        MSVClip *clip = (MSVClip *)_selectedClipOrEffect;
        if (currentTime > clip.startTimeAtMainTrack && currentTime < MovieousTimeRangeGetEnd(clip.timeRangeAtMainTrack)) {
            _withinSelectedClipTimeRange = YES;
            return;
        }
    }
    _withinSelectedClipTimeRange = NO;
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
    return [(MSVClip *)_selectedClipOrEffect speed];
}

- (NSUInteger)clipFilterIntensity {
    return [(MSVClip *)_selectedClipOrEffect LUTFilterIntensity] * 100;
}

- (void)setClipFilterIntensity:(float)value {
    [(MSVClip *)_selectedClipOrEffect setLUTFilterIntensity:value / 100];
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

- (void)clipFilterSelected:(NSIndexPath *)indexPath {
    if (indexPath.item == 0) {
        [_selectedClipOrEffect setLUTFilterImage:nil];
    } else {
        [_selectedClipOrEffect setLUTFilterImage:[UIImage imageWithContentsOfFile:_filterPaths[indexPath.item - 1]]];
    }
}

- (void)homeFilterSelected:(NSIndexPath *)indexPath {
    NSMutableArray *mixTrackClipsOrEffects = [_editor.draft.mixTrackClipsOrEffects mutableCopy];
    MSVLUTFilterEffect *lutFilterEffect = [MSVLUTFilterEffect new];
    lutFilterEffect.image = [UIImage imageWithContentsOfFile:_filterPaths[indexPath.item]];
    lutFilterEffect.timeRangeAtMainTrack = MovieousTimeRangeMake(_editor.currentTime, 3e6);
    [mixTrackClipsOrEffects addObject:lutFilterEffect];
    NSError *error;
    [_editor.draft updateMixTrackClipsOrEffects:mixTrackClipsOrEffects error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
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
}

- (void)backgroundColorSelected:(NSIndexPath *)indexPath {
    _editor.draft.canvasConfiguration = [[MSVPureColorCanvasConfiguration alloc] initWithColor:_colors[indexPath.item]];
}

- (void)deleteSelectedClip:(NSIndexPath *)indexPath {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [_editor.draft.mainTrackClips mutableCopy];
        NSUInteger index = 0;
        MovieousTime timeToSeek = 0;
        for (NSUInteger i = 0; i < _editor.draft.mainTrackClips.count; i++) {
            MSVMainTrackClip *clip = _editor.draft.mainTrackClips[i];
            if (_selectedClipOrEffect == clip) {
                index = i;
                break;
            } else {
                timeToSeek += clip.durationAtMainTrack;
            }
        }
        [mainTrackClips removeObjectAtIndex:index];
        NSError *error;
        [_editor.draft updateMainTrackClips:mainTrackClips error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:timeToSeek accurate:YES];
    }
}

- (void)copySelectedClip:(NSIndexPath *)indexPath {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [_editor.draft.mainTrackClips mutableCopy];
        NSUInteger index = 0;
        MovieousTime timeToSeek = 0;
        for (NSUInteger i = 0; i < _editor.draft.mainTrackClips.count; i++) {
            MSVMainTrackClip *clip = _editor.draft.mainTrackClips[i];
            timeToSeek += clip.durationAtMainTrack;
            if (_selectedClipOrEffect == clip) {
                index = i;
                break;
            }
        }
        MSVMainTrackClip *clipToInsert = [_selectedClipOrEffect copy];
        [clipToInsert removeAllAttachments];
        [mainTrackClips insertObject:clipToInsert atIndex:index];
        NSError *error;
        [_editor.draft updateMainTrackClips:mainTrackClips error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        [_editor seekToTime:timeToSeek accurate:YES];
    }
}

- (void)spliteSelectedClip:(NSIndexPath *)indexPath {
    if ([_selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        NSMutableArray<MSVMainTrackClip *> *mainTrackClips = [NSMutableArray array];
        MovieousTime currentTime = _editor.currentTime;
        MovieousTime timePointer = 0;
        [_editor.draft beginChangeTransaction];
        for (MSVMainTrackClip *clip in _editor.draft.mainTrackClips) {
            if (_selectedClipOrEffect == clip) {
                if (clip.type == MSVClipTypeStillImage) {
                    MSVMainTrackClip *splitClip = [clip copy];
                    splitClip.durationAtMainTrack = currentTime - timePointer;
                    [mainTrackClips addObject:splitClip];
                    [splitClip removeAllAttachments];
                    clip.durationAtMainTrack = clip.durationAtMainTrack - splitClip.durationAtMainTrack;
                    [mainTrackClips addObject:clip];
                } else {
                    double ratio = (currentTime - timePointer) / clip.durationAtMainTrack;
                    MSVMainTrackClip *splitClip = [clip copy];
                    splitClip.timeRange = MovieousTimeRangeMake(splitClip.timeRange.start, splitClip.timeRange.duration * ratio);
                    [mainTrackClips addObject:splitClip];
                    // 避免使用过同一个 snapshotBar
                    [splitClip removeAllAttachments];
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
    NSArray<NSIndexPath *> *indexPathsForSelectedItems = [_collectionView indexPathsForSelectedItems];
    [_collectionView reloadItemsAtIndexPaths:indexPathsForSelectedItems];
    [_collectionView selectItemAtIndexPath:indexPathsForSelectedItems.firstObject animated:NO scrollPosition:UICollectionViewScrollPositionNone];
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
        cell.enabled = ((MSVClip *)_selectedClipOrEffect).type != MSVClipTypeStillImage;
    } else if ([key isEqualToString:@"clip.delete"]) {
        cell.enabled = _editor.draft.mainTrackClips.count > 1;
    } else {
        cell.enabled = YES;
    }
    if ([key isEqualToString:@"clip.split"]) {
        cell.enabled = _withinSelectedClipTimeRange;
    }
    if (cellConfiguration[@"iconImage"]) {
        if ([cellConfiguration[@"isTemplateIconImage"] boolValue]) {
            [cell setIconWithTemplate:cellConfiguration[@"iconImage"]];
        } else {
            cell.icon = cellConfiguration[@"iconImage"];
        }
    } else if (cellConfiguration[@"iconColor"]) {
        cell.color = cellConfiguration[@"iconColor"];
    } else {
        cell.value = [[self valueForKey:cellConfiguration[@"iconValueKey"]] integerValue] ;
    }
    return cell;
}

- (UIEdgeInsets)collectionView:(UICollectionView *)collectionView layout:(UICollectionViewLayout *)collectionViewLayout insetForSectionAtIndex:(NSInteger)section {
    if (_backButton.hidden) {
        return UIEdgeInsetsZero;
    } else {
        return UIEdgeInsetsMake(0, 40, 0, 0);
    }
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    _slider.hidden = YES;
    NSDictionary *cellConfiguration = _currentConfiguration[@"content"][indexPath.section][indexPath.item];
    NSDictionary *adjustSlider = cellConfiguration[@"adjustSlider"];
    if (adjustSlider) {
        _sliderKey = adjustSlider[@"key"];
        _slider.hidden = NO;
        _slider.minimumValue = [adjustSlider[@"min"] floatValue];
        _slider.maximumValue = [adjustSlider[@"max"] floatValue];
        _slider.value = [[self valueForKey:_sliderKey] integerValue] ;
        _slider.continuous = [adjustSlider[@"continuous"] boolValue];
    }
    if (cellConfiguration[@"child"]) {
        [self pushConfiguration:cellConfiguration[@"child"]];
    }
    if (![cellConfiguration[@"keepSelect"] boolValue]) {
        [collectionView deselectItemAtIndexPath:indexPath animated:YES];
    }
    if (cellConfiguration[@"didSelect"]) {
        [self performSelectorWithName:cellConfiguration[@"didSelect"] object:indexPath];
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewToolSelectedNotification object:self userInfo:@{MSVDToolboxViewSelectedToolKey: cellConfiguration[@"key"]}];
}

- (void)performSelectorWithName:(NSString *)name object:(id)object {
    SEL selector = NSSelectorFromString(name);
    ((void (*)(id, SEL, id))[self methodForSelector:selector])(self, selector, object);
}

- (void)didSelectClipOrEffect:(NSNotification *)notification {
    MSVDClipsAndEeffectsView *clipsAndEeffectsView = notification.object;
    if ([clipsAndEeffectsView.selectedClipOrEffect isKindOfClass:MSVMainTrackClip.class]) {
        [self pushConfiguration:_clipConfiguration];
        _selectedClipOrEffect = clipsAndEeffectsView.selectedClipOrEffect;
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
    _slider.hidden = YES;
    if ([configuration[@"depth"] integerValue] > 0) {
        _backButton.hidden = NO;
    } else {
        _backButton.hidden = YES;
    }
    _currentConfiguration = configuration;
    [_collectionView reloadData];
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDToolboxViewChangeToToolboxNotification object:self userInfo:@{MSVDToolboxViewToolboxConfigurationKey: configuration[@"key"]}];
}

- (void)didDeselectClipOrEffect:(NSNotification *)notification {
    [self changeToConfiguration:_homeConfiguration];
}

@end
