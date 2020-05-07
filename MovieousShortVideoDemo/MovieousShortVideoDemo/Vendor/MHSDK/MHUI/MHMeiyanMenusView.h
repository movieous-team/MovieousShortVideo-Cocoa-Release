//
//  MHMeiyanMenusView.h


#import <UIKit/UIKit.h>
#import <MHBeautySDK/MHBeautyManager.h>
NS_ASSUME_NONNULL_BEGIN
@protocol MHMeiyanMenusViewDelegate <NSObject>
@required


/**
 
美颜
 @param beauty 磨皮 0-9，数值越大，效果越明显
 @param white 美白 0-9，数值越大，效果越明显
 @param ruddiness 红润 0-9，数值越大，效果越明显
 */
- (void)beautyEffectWithLevel:(NSInteger)beauty whitenessLevel:(NSInteger)white ruddinessLevel:(NSInteger)ruddiness;

@end
@interface MHMeiyanMenusView : UIView

/// 初始化美颜菜单
/// @param frame frame
/// @param superView 所要添加到的视图
/// @param delegate 代理
/// @param manager  美颜管理器，完成初始化后传入
/// @param isTx 是否是腾讯直播SDK，YES：是，NO：其他直播SDK

- (instancetype)initWithFrame:(CGRect)frame superView:(UIView *)superView delegate:(id<MHMeiyanMenusViewDelegate>)delegate beautyManager:(MHBeautyManager *)manager isTXSDK:(BOOL)isTx;

@property (nonatomic, weak) id<MHMeiyanMenusViewDelegate> delegate;

/**
 控制美颜菜单显示

 @param show YES表示显示，NO表示隐藏
 */
- (void)showMenuView:(BOOL)show;

/**
 获取当前美颜菜单显示状态，YES：显示，NO：隐藏
 */
@property (nonatomic, assign,getter=isShow) BOOL show;

/**
是否是腾讯直播SDK，YES：是，NO：其他直播SDK
*/

@property (nonatomic, assign) BOOL isTX;

///设置默认美型或者美颜数据，供外部调用，需要在m文件的该方法中完善数据
/// @param isTX 是否是腾讯SDK
- (void)setupDefaultBeautyAndFaceValueWithIsTX:(BOOL)isTX;

@end

NS_ASSUME_NONNULL_END
