//
//  MHMagnifiedEffectCell.h

#import <UIKit/UIKit.h>
@class MHBeautiesModel;
NS_ASSUME_NONNULL_BEGIN

@interface MHMagnifiedEffectCell : UICollectionViewCell
//@property (nonatomic, copy) NSString *magnifyTitle;
@property (nonatomic, strong) MHBeautiesModel *model;
- (void)switchBtnSelectedStatus:(BOOL)isSelected;

@end

NS_ASSUME_NONNULL_END
