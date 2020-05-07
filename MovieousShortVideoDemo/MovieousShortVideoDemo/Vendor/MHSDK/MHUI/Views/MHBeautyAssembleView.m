//
//  MHBeautyAssembleView.m

//美颜

#import "MHBeautyAssembleView.h"
#import "MHBeautyFaceView.h"
#import "MHFiltersView.h"
#import "MHBeautyView.h"
#import "WNSegmentControl.h"
#import "MHBeautyParams.h"
#import "MHCompleteBeautyView.h"
#import "MHBeautySlider.h"
#import <MHBeautySDK/MHFiltersContants.h>
#import "MHBeautiesModel.h"

@interface MHBeautyAssembleView()<MHBeautyViewDelegate,MHBeautyFaceViewDelegate,MHFiltersViewDelegate,MHCompleteBeautyViewDelegate>
@property (nonatomic, strong) WNSegmentControl *segmentControl;
@property (nonatomic, strong) MHBeautyView *beautyView;//美颜
@property (nonatomic, strong) MHBeautyFaceView *faceView;//美型
@property (nonatomic, strong) MHCompleteBeautyView *completeView;//一键美颜
@property (nonatomic, strong) MHFiltersView *filtersView;//滤镜
@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) NSArray *viewsArray;
@property (nonatomic, strong) UIView *lastView;
@property (nonatomic, strong) MHBeautySlider *slider;
@property (nonatomic, assign) NSInteger beautyLevel;
@property (nonatomic, assign) NSInteger whiteLevel;
@property (nonatomic, assign) NSInteger ruddinessLevel;
@property (nonatomic, assign) NSInteger brightnessLevel;
@property (nonatomic, assign) MHBeautyAssembleType assembleType;
@property (nonatomic, assign) MHBeautyType beautyType;
@property (nonatomic, assign) MHBeautyFaceType faceType;
@property (nonatomic, strong) MHBeautiesModel *quickBeautyModel;

@end
@implementation MHBeautyAssembleView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor clearColor];
        self.beautyLevel = 0;
        self.whiteLevel = 0;
        self.ruddinessLevel = 0;
        self.faceType = -1;//默认不选择状态
        self.beautyType = -1;//默认不选择状态
        [self addSubview:self.slider];
        [self configureUI];
    }
    return self;
}

- (void)configureUI {
    NSArray *arr = [[NSUserDefaults standardUserDefaults] objectForKey: @"kBeautyAssembleWithVersion"];
    _segmentControl = [[WNSegmentControl alloc] initWithTitles:arr];
    _segmentControl.frame = CGRectMake(0, _slider.bottom+20, window_width, MHStickerSectionHeight);
    _segmentControl.backgroundColor = [UIColor whiteColor];
    [_segmentControl setTextAttributes:@{NSFontAttributeName: Font_12, NSForegroundColorAttributeName: FontColorNormal}
                              forState:UIControlStateNormal];
    [_segmentControl setTextAttributes:@{NSFontAttributeName: Font_12, NSForegroundColorAttributeName: FontColorSelected}
                              forState:UIControlStateSelected];
    _segmentControl.selectedSegmentIndex = 0;
    _segmentControl.widthStyle = WNSegmentedControlWidthStyleFixed;
    [_segmentControl addTarget:self action:@selector(switchList:) forControlEvents:UIControlEventValueChanged];
    [self addSubview:_segmentControl];
    [self addSubview:self.lineView];
    [self addSubview:self.beautyView];
    self.lastView = self.beautyView;
    
    [self.faceView configureFaceData];
    NSString *type = [[NSUserDefaults standardUserDefaults] objectForKey: @"MHSDKVersion"];
    _viewsArray = type.integerValue == 1 ? @[self.beautyView,self.faceView,self.completeView,self.filtersView] : @[self.beautyView,self.faceView,self.filtersView];
}

#pragma mark - Action
- (void)switchList:(WNSegmentControl *)segment {
    UIView *view = [self.viewsArray objectAtIndex:segment.selectedSegmentIndex];
    self.slider.hidden = [view isEqual:self.filtersView];
    self.assembleType = segment.selectedSegmentIndex;
    
    if ([view isEqual:self.faceView]) {
        [self.faceView configureFaceData];
    }
    if ([view isEqual:self.completeView]) {
        [self.slider setSliderValue:@"50"];
        [self.slider setValue:50 animated:YES];
    }
    if (![view isEqual:self.lastView]) {
       [self.lastView removeFromSuperview];
    }
    [self addSubview:view];
    self.lastView = view;
}
//slider 滑动修改对应的效果
- (void)handleBeautyAssembleEffectWithValue:(NSInteger)value {
    switch (self.assembleType) {
        case 0:{
            if (self.isTXSDK) {
                [self handleBeautyEffectsOfTXWithSliderValue:value];
            } else {
                [self handleBeautyEffectsWithSliderValue:value];
            }
        }
            
            break;
        case 1:
            [self handleFaceEffectsWithSliderValue:value];
            
            break;
        case 2:
            [self handleQuickBeautyWithSliderValue:value];
            break;
        default:
            break;
    }
}
#pragma mark - 美颜-腾讯直播用
- (void)handleBeautyEffectsOfTXWithSliderValue:(NSInteger)value {
    switch (self.beautyType) {
        case MHBeautyType_Original:{
            self.beautyLevel = 0;
            self.whiteLevel = 0;
            self.ruddinessLevel = 0;
            self.brightnessLevel = 50;//默认
        }
            break;
        case MHBeautyType_White:
            self.whiteLevel = value/10.f;

            break;
        case MHBeautyType_Mopi:
            self.beautyLevel = value/10.f;
            break;
        case MHBeautyType_Ruddiess:
            self.ruddinessLevel = value/10.f;
            break;
        case MHBeautyType_Brightness:
            self.brightnessLevel = value;
            break;
        default:
            break;
    }
    if (self.beautyType != MHBeautyType_Brightness) {
        self.brightnessLevel = 50;
    }
    
    if ([self.delegate respondsToSelector:@selector(beautyLevel:whitenessLevel:ruddinessLevel: brightnessLevel:)]) {
        NSString *str = [[NSUserDefaults standardUserDefaults] objectForKey:@"hasSelectedQuickBeauty"];
        if ([str isEqualToString:@"YES"]) {
             [self.delegate beautyLevel:0 whitenessLevel:0 ruddinessLevel:0 brightnessLevel:50];//为了取消一键美颜的效果
            [self.completeView cancelQuickBeautyEffect:self.quickBeautyModel];
            [[NSUserDefaults standardUserDefaults] setObject:@"NO" forKey:@"hasSelectedQuickBeauty"];//保证只执行一次
        }
       
        
        [self.delegate beautyLevel:self.beautyLevel whitenessLevel:self.whiteLevel ruddinessLevel:self.ruddinessLevel brightnessLevel:self.brightnessLevel];
    }
    NSString *beautKey = [NSString stringWithFormat:@"beauty_%ld",(long)self.beautyType];
    [[NSUserDefaults standardUserDefaults] setInteger:value forKey:beautKey];
}

- (void)handleBeautyEffectsWithSliderValue:(NSInteger)value {
    if ([self.delegate respondsToSelector:@selector(handleBeautyWithType:level:)]) {
        NSString *str = [[NSUserDefaults standardUserDefaults] objectForKey:@"hasSelectedQuickBeauty"];
        if ([str isEqualToString:@"YES"]) {
            [self.delegate handleBeautyWithType:0 level:0];//为了取消一键美颜的效果
            [self.completeView cancelQuickBeautyEffect:self.quickBeautyModel];
            [[NSUserDefaults standardUserDefaults] setObject:@"NO" forKey:@"hasSelectedQuickBeauty"];//保证只执行一次
        }
        [self.delegate handleBeautyWithType:self.beautyType level:value];
    }
    NSString *beautKey = [NSString stringWithFormat:@"beauty_%ld",(long)self.beautyType];
    [[NSUserDefaults standardUserDefaults] setInteger:value forKey:beautKey];
}

#pragma mark - 美型
- (void)handleFaceEffectsWithSliderValue:(NSInteger)value {
    if ([self.delegate respondsToSelector:@selector(handleFaceBeautyWithType:sliderValue:)]) {
        NSString *str = [[NSUserDefaults standardUserDefaults] objectForKey:@"hasSelectedQuickBeauty"];
        if ([str isEqualToString:@"YES"]) {
             [self.delegate handleFaceBeautyWithType:0 sliderValue:0];//为了取消一键美颜的效果
            [self.completeView cancelQuickBeautyEffect:self.quickBeautyModel];
            [[NSUserDefaults standardUserDefaults] setObject:@"NO" forKey:@"hasSelectedQuickBeauty"];//保证只执行一次
        }
        [self.delegate handleFaceBeautyWithType:self.faceType sliderValue:value];
    }
    NSString *faceKey = [NSString stringWithFormat:@"face_%ld",(long)self.faceType];
    [[NSUserDefaults standardUserDefaults] setInteger:value forKey:faceKey];
}

#pragma mark - 一键美颜
- (void)handleQuickBeautyWithSliderValue:(NSInteger)value {
    if ([self.delegate respondsToSelector:@selector(handleQuickBeautyWithSliderValue: quickBeautyModel:)]) {
        [self.delegate handleQuickBeautyWithSliderValue:value quickBeautyModel:self.quickBeautyModel];
    }
}

#pragma mark - delegate
//美颜
- (void)handleBeautyEffects:(NSInteger)type sliderValue:(NSInteger)value {
    self.beautyType = type;
    [self.slider setSliderValue:[NSString stringWithFormat:@"%ld",(long)value]];
    [self.slider setValue:(NSInteger)value animated:YES];
}
//美型
- (void)handleFaceEffects:(NSInteger)type sliderValue:(NSInteger)value {
    self.faceType = type;
    [self.slider setSliderValue:[NSString stringWithFormat:@"%ld",(long)value]];
    [self.slider setValue:(NSInteger)value animated:YES];
}

//一键美颜
- (void)handleCompleteEffect:(MHBeautiesModel *)model {
    if ([model.beautyTitle isEqualToString:@"原图"]) {
        self.quickBeautyModel = nil;
    }
    self.quickBeautyModel = model;
    if ([self.delegate respondsToSelector:@selector(handleQuickBeautyValue:)]) {
        [self.delegate handleQuickBeautyValue:model];
    }
     //取消美颜美型的选中状态
    if (self.faceType != -1) {
        [self.faceView cancelSelectedFaceType:self.faceType];
        self.faceType = -1;
       
    }
    if (self.beautyType != -1) {
        [self.beautyView cancelSelectedBeautyType:self.beautyType];
        self.beautyType = -1;
    }
}

//滤镜
- (void)handleFiltersEffect:(NSInteger)filterType filterName:(nonnull NSString *)filtetName {
    if ([self.delegate respondsToSelector:@selector(handleFiltersEffectWithType: withFilterName:)]) {
        [self.delegate handleFiltersEffectWithType:filterType withFilterName:filtetName];
    }
}


#pragma mark - lazy

- (MHBeautyView *)beautyView {
    if (!_beautyView) {
        _beautyView = [[MHBeautyView alloc] initWithFrame:CGRectMake(0, _lineView.bottom, window_width, MHBeautyAssembleViewHeight-_lineView.bottom)];
        _beautyView.delegate = self;
        _beautyView.backgroundColor = [UIColor redColor];
    }
    return _beautyView;
}

- (MHBeautyFaceView *)faceView {
    if (!_faceView) {
        _faceView = [[MHBeautyFaceView alloc] initWithFrame:CGRectMake(0, _lineView.bottom, window_width, MHBeautyAssembleViewHeight-_lineView.bottom)];
        _faceView.delegate = self;
    }
    return _faceView;
}

- (MHFiltersView *)filtersView {
    if (!_filtersView) {
        _filtersView = [[MHFiltersView alloc] initWithFrame:CGRectMake(0, _lineView.bottom, window_width, MHBeautyAssembleViewHeight-_lineView.bottom)];
        _filtersView.delegate = self;
    }
    return _filtersView;
}

- (MHCompleteBeautyView *)completeView {
    if (!_completeView) {
        _completeView = [[MHCompleteBeautyView alloc] initWithFrame:CGRectMake(0, _lineView.bottom  , window_width, MHBeautyAssembleViewHeight-_lineView.bottom)];
        _completeView.delegate = self;
        
    }
    return _completeView;
}

- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] initWithFrame:CGRectMake(0, _segmentControl.bottom, window_width, 0.5)];
        _lineView.backgroundColor = LineColor;
    }
    return _lineView;
}

- (MHBeautySlider *)slider {
    if (!_slider) {
        _slider = [[MHBeautySlider alloc] initWithFrame:CGRectMake(50, MHSliderwTop, self.width - 50 * 2, MHSliderwHeight)];
        _slider.minimumValue = 0;
        _slider.maximumValue = 100;
        UIImage *minImg = BundleImg(@"wire")
        [_slider setMinimumTrackImage:minImg forState:UIControlStateNormal];
        UIImage *maxImg = BundleImg(@"wire drk");
        [_slider setMaximumTrackImage:maxImg forState:UIControlStateNormal];
        UIImage *pointImg = BundleImg(@"sliderButton");
        [_slider setThumbImage:pointImg forState:UIControlStateNormal];
        _slider.continuous = YES;
        __weak typeof(self) weakSelf = self;
        _slider.valueChanged = ^(MHBeautySlider * _Nonnull slider) {
            [weakSelf handleBeautyAssembleEffectWithValue:slider.value];
            weakSelf.slider.sliderValue = [NSString stringWithFormat:@"%ld", (long)slider.value];
        };
    }
    return _slider;
}
@end
