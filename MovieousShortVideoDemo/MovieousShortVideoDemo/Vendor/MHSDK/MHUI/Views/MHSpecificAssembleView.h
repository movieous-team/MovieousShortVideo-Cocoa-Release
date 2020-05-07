//
//  MHSpecificAssembleView.h


#import <UIKit/UIKit.h>
@class MHBeautiesModel;
NS_ASSUME_NONNULL_BEGIN
@protocol MHSpecificAssembleViewDelegate <NSObject>

/**
 特性

 @param type 特性类型
 */
- (void)handleSpecificWithType:(NSInteger)type;

/**
 水印

 @param model 水印数据模型
 */
- (void)handleWatermarkWithModel:(MHBeautiesModel *)model;

@end
@interface MHSpecificAssembleView : UIView
@property (nonatomic, weak) id<MHSpecificAssembleViewDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
