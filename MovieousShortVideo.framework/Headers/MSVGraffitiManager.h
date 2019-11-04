//
//  MSVGraffitiManager.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/9/22.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVBrush.h"
#import "MSVImageStickerEditorEffect.h"

NS_ASSUME_NONNULL_BEGIN

@class MSVGraffitiManager;
/**
 * 涂鸦代理对象，用于接受 MSVGraffitiManager 的回调。
 */
@protocol MSVGraffitiManagerDelegate <NSObject>

@optional
/**
* MSVGraffitiManager 的撤销重做状态改变。
*
* @param graffitiManager 发生事件的 MSVGraffitiManager 对象。
*/
- (void)graffitiManagerUndoRedoStatusChanged:(MSVGraffitiManager *)graffitiManager;

@end

/**
 * 管理涂鸦状态的管理器。
 */
@interface MSVGraffitiManager : NSObject

/**
 * 代理对象。
 */
@property (nonatomic, weak) id<MSVGraffitiManagerDelegate> delegate;

/**
 * 是否隐藏内部的 graffitiView。
 */
@property (nonatomic, assign) BOOL hideGraffitiView;

/**
 * 最大的撤销栈深度，如果当前撤销堆栈超过此限制，最老的操作将会被清除，当设置限制为 0 时表示没有限制。
 * 默认为 20。
 */
@property (nonatomic, assign) NSUInteger maxUndoSteps;

/**
 * 定义绘画参数的 MSVBrush 对象。
 */
@property (nonatomic, strong) MSVBrush *brush;

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
