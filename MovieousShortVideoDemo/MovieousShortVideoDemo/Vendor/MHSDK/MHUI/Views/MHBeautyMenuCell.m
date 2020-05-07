//
//  MHBeautyMenuCell.m


#import "MHBeautyMenuCell.h"
#import "MHBeautyParams.h"
#import "MHBeautiesModel.h"
@interface MHBeautyMenuCell()
@property (nonatomic, strong) UIImageView *imgView;
@property (nonatomic, strong) UILabel *beautyLabel;
@property (nonatomic, strong) UIImageView *animationView;
@property (nonatomic, strong) UIImageView *selectedImgView;
@property (nonatomic, strong) UIButton *effectBtn;
@end
@implementation MHBeautyMenuCell

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self addSubview:self.imgView];
        [self addSubview:self.beautyLabel];
    }
    return self;
}

- (void)setMenuModel:(MHBeautiesModel *)menuModel {
    if (!menuModel) {
        return;
    }
    _menuModel = menuModel;
    self.beautyLabel.text = menuModel.beautyTitle;
    if (menuModel.menuType == MHBeautyMenuType_Menu) {
        if ([menuModel.beautyTitle isEqualToString:@""]) {//仅限菜单页，@""的时候是相机功能
            self.beautyLabel.hidden = YES;
            UIImage *img = BundleImg(@"cameraBG");
            self.imgView.image = img;
            self.imgView.frame = CGRectMake((self.width - 50)/2, (self.height - 50)/2, 50, 50);
            [self.imgView addSubview:self.animationView];
            self.animationView.frame = CGRectMake(5, 5, 40, 40);
        } else {
            [self.imgView removeAllSubViews];
            self.imgView.image = BundleImg(menuModel.imgName);
            self.imgView.frame = CGRectMake((self.width - 35)/2, 15, 35, 35);
            self.beautyLabel.top = self.imgView.bottom + 10;
            self.beautyLabel.hidden = NO;
        }
    } else if (menuModel.menuType == MHBeautyMenuType_QuickBeauty){
            self.imgView.frame = CGRectMake((self.width - 55)/2,2, 55, 55);
            self.selectedImgView.frame = self.imgView.frame;
            self.beautyLabel.frame = CGRectMake(3, _imgView.bottom+15, self.width - 6, 15);
            self.beautyLabel.textColor = menuModel.isSelected ? FontColorSelected : FontColorNormal;
            self.selectedImgView.hidden = !menuModel.isSelected;
            self.imgView.image = BundleImg(menuModel.imgName);
        } else if (menuModel.menuType == MHBeautyMenuType_Specify || menuModel.menuType == MHBeautyMenuType_Filter ) {
            if (menuModel.menuType == MHBeautyMenuType_Specify) {
                self.imgView.frame = CGRectMake((self.width - 50)/2,2, 50, 60);
            } else {
                self.imgView.frame = CGRectMake((self.width - 55)/2,2, 55, 55);
            }
            self.beautyLabel.frame = CGRectMake(3, _imgView.bottom+8, self.width - 6, 15);
            self.beautyLabel.textColor = menuModel.isSelected ? FontColorSelected : FontColorNormal;
            self.selectedImgView.hidden = !menuModel.isSelected;
            self.selectedImgView.frame = self.imgView.frame;
            self.imgView.image = BundleImg(menuModel.imgName);
        }
        else if (menuModel.menuType == MHBeautyMenuType_Beauty || menuModel.menuType == MHBeautyMenuType_Face){
            self.imgView.frame = CGRectMake((self.width - 40)/2, 15, 40, 40);
            self.selectedImgView.hidden = YES;
            self.beautyLabel.textColor = menuModel.isSelected ? FontColorSelected : FontColorNormal;
            if (menuModel.isSelected) {
                NSString *name = [NSString stringWithFormat:@"%@_selected",menuModel.imgName];
                UIImage *img = BundleImg(name);
                self.imgView.image = img;
            } else {
                self.imgView.image = BundleImg(menuModel.imgName);
            }
        } else if (menuModel.menuType == MHBeautyMenuType_Magnify){
            
            
        } else if (menuModel.menuType == MHBeautyMenuType_Watermark){
            self.selectedImgView.frame = CGRectMake(5, 5, self.width - 10, self.height - 10);
            self.beautyLabel.textColor = menuModel.isSelected ? FontColorSelected : FontColorNormal;
            if (menuModel.isSelected) {
                NSString *selectedImg = [NSString stringWithFormat:@"%@_selected",menuModel.imgName];
                [self.imgView setImage:[UIImage imageNamed:selectedImg]];
            } else {
                [self.imgView setImage:[UIImage imageNamed:menuModel.imgName]];
            }
        }
}
- (void)switchBeautyEffect:(BOOL)isSelected {
    self.beautyLabel.textColor = isSelected ? FontColorSelected : FontColorNormal;
}
    

- (void)takePhotoAnimation {
    [UIView animateWithDuration:0.2 animations:^{
        self.animationView.transform = CGAffineTransformMakeScale(0.9, 0.9);
    } completion:^(BOOL finished) {
        [UIView animateWithDuration:0.2 animations:^{
            self.animationView.transform = CGAffineTransformMakeScale(1, 1);
        }];
    }];
}
#pragma mark - lazy
- (UIImageView *)imgView {
    if (!_imgView) {
        _imgView = [[UIImageView alloc] initWithFrame:CGRectMake((self.width - 40)/2, 15, 40, 40)];
    }
    return _imgView;
}
- (UILabel *)beautyLabel {
    if (!_beautyLabel) {
        _beautyLabel = [[UILabel alloc] initWithFrame:CGRectMake(3, _imgView.bottom+8, self.width - 6, 15)];
        _beautyLabel.font = Font_10;
        _beautyLabel.textColor = [UIColor whiteColor];
        _beautyLabel.textAlignment = NSTextAlignmentCenter;
    }
    return _beautyLabel;
}

- (UIImageView *)animationView {
    if (!_animationView) {
        UIImage *img = BundleImg(@"cameraPoint");
        _animationView = [[UIImageView alloc] initWithImage:img];
        _animationView.contentMode = UIViewContentModeScaleAspectFit;
    }
    return _animationView;
}
    
- (UIImageView *)selectedImgView {
    if (!_selectedImgView) {
        UIImage *img = BundleImg(@"filter_selected2");
        _selectedImgView = [[UIImageView alloc] initWithImage:img];
        _selectedImgView.hidden = YES;
        [self addSubview:_selectedImgView];
    }
    return _selectedImgView;
}
@end
