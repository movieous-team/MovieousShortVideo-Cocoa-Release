//
//  MHPrintView.h


#import <UIKit/UIKit.h>
@class MHBeautiesModel;
NS_ASSUME_NONNULL_BEGIN
@protocol MHPrintViewDelegate <NSObject>

- (void)handlePrint:(MHBeautiesModel *)model;

@end
@interface MHPrintView : UIView
@property (nonatomic, weak) id<MHPrintViewDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
