//
//  MSVGraffitiView.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/19.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVBrush.h"
#import "MSVImageStickerEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

@class MSVGraffitiView;
/**
 * 涂鸦代理对象，用于接受 MSVGraffitiView 的回调。
 */
@protocol MSVGraffitiViewDelegate <NSObject>

@optional
/**
 * 涂鸦视图的撤销重做状态改变。
 *
 * @param graffitiView 发生事件的 MSVGraffitiView 对象。
 */
- (void)graffitiViewUndoRedoStatusChanged:(MSVGraffitiView *)graffitiView;

@end

/**
 * 用来画涂鸦的 UIView 子类。
 */
@interface MSVGraffitiView : UIView

/**
 * 代理对象。
 */
@property (nonatomic, weak) id<MSVGraffitiViewDelegate> delegate;

/**
 * 最大的撤销栈深度，如果当前撤销堆栈超过此限制，最老的操作将会被清除，当设置限制为 0 时表示没有限制。
 * 默认为 20。
 */
@property (nonatomic, assign) NSUInteger maxUndoSteps;

/**
 * 在 preview 上展示画面的区域的 frame。
 */
@property (nonatomic, assign) CGRect displayingRect;

/**
 * 定义绘画参数的 MSVBrush 对象。
 */
@property (nonatomic, strong) MSVBrush *brush;

/**
 * 使用 frame 和 brush 来创建一个 MSVGraffitiView 对象。
 *
 * @param frame 用来创建 view 的 frame。
 * @param brush 定义绘画参数的 brush。
 *
 * @return 创建完成的 MSVGraffitiView 对象。
 */
+ (instancetype)graffitiViewWithFrame:(CGRect)frame brush:(MSVBrush *)brush;

/**
 * 使用 frame 和 brush 来初始化一个 MSVGraffitiView 对象。
 *
 * @param frame 用来创建 view 的 frame。
 * @param brush 定义绘画参数的 brush。
 *
 * @return 初始化完成的 MSVGraffitiView 对象。
 */
- (instancetype)initWithFrame:(CGRect)frame brush:(MSVBrush *)brush;

/**
 * 获取 MSVGraffitiView 的快照
 *
 * @return 获取到的快照
 */
- (UIImage *)takeSnapshot;

/**
 * 当前是否可以撤销。
 *
 * @return 当你可以撤销时返回 YES，否则返回 NO。
 */
- (BOOL)canUndo;

/**
 * 当前是否可以重做。
 *
 * @return 当你可以重做时返回 YES，否则返回 NO。
 */
- (BOOL)canRedo;

/**
 * 撤销之前的操作。
 */
- (void)undo;

/**
 * 重做之前撤销的操作，所有绘画操作都将会清空重做堆栈。
 */
- (void)redo;

/**
 * 清除撤销堆栈和重做堆栈。
 */
- (void)reset;

/**
 * 清除撤销堆栈，重做堆栈以及 view 上已经绘画的内容。
 */
- (void)clear;

/**
 * 将涂鸦导出为一个 MSVImageStickerEditorEffect 用于添加到 MSVDraft 的特效当中。
 *
 * @return 生成的 MSVImageStickerEditorEffect 对象。
 */
- (MSVImageStickerEditorEffect *)exportAsImageStickerEditorEffect;

@end

NS_ASSUME_NONNULL_END
