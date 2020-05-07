//
//  MHMagnifiedEffectCell.m


#import "MHMagnifiedEffectCell.h"
#import "MHBeautiesModel.h"
#import "MHBeautyParams.h"

@interface MHMagnifiedEffectCell ()
@property (nonatomic, strong) UIButton *effectBtn;

@end
@implementation MHMagnifiedEffectCell

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [UIColor whiteColor];
        [self.contentView addSubview:self.effectBtn];
    }
    return self;
}

- (void)setModel:(MHBeautiesModel *)model {
    if (!model) {
        return;
    }
    if (model.menuType == MHBeautyMenuType_Magnify) {
        _effectBtn.frame = CGRectMake(CGRectGetWidth(self.frame)/2-35, 2,  70, 90 - 4);
        NSString *magnifyTitle = model.beautyTitle;
        [self.effectBtn setTitle:magnifyTitle forState:UIControlStateNormal];
        UIImage *img = BundleImg(model.imgName);
        [self.effectBtn setImage:img forState:UIControlStateNormal];
        CGFloat totalH = self.effectBtn.imageView.frame.size.height + self.effectBtn.titleLabel.frame.size.height;
        
        //设置按钮图片偏移
        [self.effectBtn setImageEdgeInsets:UIEdgeInsetsMake(-(totalH - self.effectBtn.imageView.frame.size.height),0.0, 0.0, -self.effectBtn.titleLabel.frame.size.width)];
        //设置按钮标题偏移
        [self.effectBtn setTitleEdgeInsets:UIEdgeInsetsMake(15, -self.effectBtn.imageView.frame.size.width, -(totalH - self.effectBtn.titleLabel.frame.size.height),0.0)];
        
    } else if (model.menuType == MHBeautyMenuType_Watermark){
        _effectBtn.frame = CGRectMake(CGRectGetWidth(self.frame)/2-22.5, 2,  55, 60);
        [self.effectBtn setImage:[UIImage imageNamed:model.imgName] forState:UIControlStateNormal];
    }
    
    [self switchBtnSelectedStatus:model.isSelected];
}

- (void)switchBtnSelectedStatus:(BOOL)isSelected {
    if (isSelected) {
        [self.effectBtn setTitleColor:FontColorSelected forState:0];
        self.effectBtn.layer.borderColor = FontColorSelected.CGColor;
    } else {
        [self.effectBtn setTitleColor:FontColorNormal forState:0];
        self.effectBtn.layer.borderColor = [UIColor clearColor].CGColor;
    }
    if (self.model.menuType == MHBeautyMenuType_Watermark) {
        if (isSelected) {
            NSString *selectedImg = [NSString stringWithFormat:@"%@_selected",self.model.imgName];
            [self.effectBtn setImage:[UIImage imageNamed:selectedImg] forState:UIControlStateNormal];
        } else {
            [self.effectBtn setImage:[UIImage imageNamed:self.model.imgName] forState:UIControlStateNormal];
        }
    }
}

#pragma mark - lazy
- (UIButton *)effectBtn {
    if (!_effectBtn) {
        _effectBtn = [UIButton buttonWithType:UIButtonTypeCustom];
        _effectBtn.userInteractionEnabled = NO;
        _effectBtn.titleLabel.font = [UIFont systemFontOfSize:10];
        _effectBtn.layer.borderWidth = 1;
        _effectBtn.layer.cornerRadius = 3;
        _effectBtn.layer.masksToBounds = YES;
        _effectBtn.layer.borderColor = [UIColor clearColor].CGColor;
    }
    return _effectBtn;
}
@end
