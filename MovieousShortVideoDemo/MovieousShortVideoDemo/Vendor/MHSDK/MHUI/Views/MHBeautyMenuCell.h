//
//  MHBeautyMenuCell.h


#import <UIKit/UIKit.h>
@class MHBeautiesModel;
NS_ASSUME_NONNULL_BEGIN

@interface MHBeautyMenuCell : UICollectionViewCell

@property (nonatomic, strong) MHBeautiesModel *menuModel;
- (void)switchBeautyEffect:(BOOL)isSelected;
- (void)takePhotoAnimation;
@end

NS_ASSUME_NONNULL_END
