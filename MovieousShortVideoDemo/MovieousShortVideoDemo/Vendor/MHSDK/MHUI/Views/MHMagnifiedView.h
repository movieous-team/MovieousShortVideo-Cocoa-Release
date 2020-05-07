//


#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MHMagnifiedViewDelegate <NSObject>

- (void)handleMagnify:(NSInteger)type;

@end
@interface MHMagnifiedView : UIView
@property (nonatomic, weak) id<MHMagnifiedViewDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
