//
//  MHSpecificEffectView.h


#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol MHSpecificEffectViewDelegate <NSObject>

- (void)handleSpecific:(NSInteger)type;

@end
@interface MHSpecificEffectView : UIView
@property (nonatomic, weak) id<MHSpecificEffectViewDelegate> delegate;
@end

NS_ASSUME_NONNULL_END
