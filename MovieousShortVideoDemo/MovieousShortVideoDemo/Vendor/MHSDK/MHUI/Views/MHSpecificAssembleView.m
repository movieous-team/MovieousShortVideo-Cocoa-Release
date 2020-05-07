//
//  MHSpecificAssembleView.m

//特效合集

#import "MHSpecificAssembleView.h"
#import "MHBeautyParams.h"
#import "MHPrintView.h"
#import "MHSpecificEffectView.h"
#import "WNSegmentControl.h"
#import "MHBeautiesModel.h"
@interface MHSpecificAssembleView ()<MHSpecificEffectViewDelegate,MHPrintViewDelegate>
@property (nonatomic, strong) MHSpecificEffectView *specificView;//特效
@property (nonatomic, strong) MHPrintView *printView;//水印
@property (nonatomic, strong) UIView *lineView;
@property (nonatomic, strong) NSArray *viewsArray;
@property (nonatomic, strong) UIView *lastView;
@property (nonatomic, strong) WNSegmentControl *segmentControl;
@end

@implementation MHSpecificAssembleView
- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        self.backgroundColor = [UIColor clearColor];
        self.alpha = 1;
        [self addSubview:self.segmentControl];
        [self addSubview:self.lineView];
        [self addSubview:self.specificView];
        self.lastView = self.specificView;
    }
    return self;
}

#pragma mark - Action
- (void)switchList:(WNSegmentControl *)segmentControl {
    UIView *currentView = self.viewsArray[segmentControl.selectedSegmentIndex];
    if (![currentView isEqual:self.lastView]) {
        [self.lastView removeFromSuperview];
    }
    [self addSubview:currentView];
    self.lastView = currentView;
}

#pragma mark - delegate
//水印
- (void)handlePrint:(MHBeautiesModel *)model {
    if ([self.delegate respondsToSelector:@selector(handleWatermarkWithModel:)]) {
        [self.delegate handleWatermarkWithModel:model];
    }
    
}

//特效
- (void)handleSpecific:(NSInteger)type {
    if ([self.delegate respondsToSelector:@selector(handleSpecificWithType:)]) {
        [self.delegate handleSpecificWithType:type];
    }
}

#pragma mark - lazy
- (NSArray *)viewsArray {
    if (!_viewsArray) {
        _viewsArray = @[self.specificView,self.printView];
    }
    return _viewsArray;
}

- (MHSpecificEffectView *)specificView {
    if (!_specificView) {
        _specificView = [[MHSpecificEffectView alloc] initWithFrame:CGRectMake(0, _lineView.bottom, window_width, MHSpecificAssembleViewHeight-_lineView.bottom)];
        _specificView.delegate = self;
    }
    return _specificView;
}

- (MHPrintView *)printView {
    if (!_printView) {
        _printView = [[MHPrintView alloc] initWithFrame:CGRectMake(0, _lineView.bottom, window_width, MHSpecificAssembleViewHeight-_lineView.bottom)];
        _printView.delegate = self;
    }
    return _printView;
}

- (WNSegmentControl *)segmentControl {
    if (!_segmentControl) {
        _segmentControl = [[WNSegmentControl alloc] initWithTitles:@[@"特效",@"水印"]];
        _segmentControl.frame = CGRectMake(0, 0, window_width, MHStickerSectionHeight);
        _segmentControl.backgroundColor = [UIColor whiteColor];
        [_segmentControl setTextAttributes:@{NSFontAttributeName: Font_12, NSForegroundColorAttributeName: FontColorNormal}
                                  forState:UIControlStateNormal];
        [_segmentControl setTextAttributes:@{NSFontAttributeName: Font_12, NSForegroundColorAttributeName: FontColorSelected}
                                  forState:UIControlStateSelected];
        _segmentControl.selectedSegmentIndex = 0;
        _segmentControl.widthStyle = WNSegmentedControlWidthStyleFixed;
        [_segmentControl addTarget:self action:@selector(switchList:) forControlEvents:UIControlEventValueChanged];
    }
    return _segmentControl;
}
- (UIView *)lineView {
    if (!_lineView) {
        _lineView = [[UIView alloc] initWithFrame:CGRectMake(0, _segmentControl.bottom, window_width, 0.5)];
        _lineView.backgroundColor = LineColor;
    }
    return _lineView;
}

@end
