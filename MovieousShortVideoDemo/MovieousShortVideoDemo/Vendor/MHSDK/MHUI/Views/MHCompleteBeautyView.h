//
//  MHCompleteBeautyView.h


#import <UIKit/UIKit.h>
@class MHBeautiesModel;

NS_ASSUME_NONNULL_BEGIN
@protocol MHCompleteBeautyViewDelegate <NSObject>
@required
- (void)handleCompleteEffect:(MHBeautiesModel *)model;
@end

@interface MHCompleteBeautyView : UIView
@property (nonatomic, weak) id<MHCompleteBeautyViewDelegate> delegate;

/**
 点击美颜或者美型，取消一键美颜的选中效果和状态

 @param selectedModel 选中的一键美颜的数据模型
 */
- (void)cancelQuickBeautyEffect:(MHBeautiesModel *)selectedModel;
@end

NS_ASSUME_NONNULL_END
