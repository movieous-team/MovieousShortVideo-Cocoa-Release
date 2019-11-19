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
 * Delegate used to receive callback。
 */
@protocol MSVGraffitiManagerDelegate <NSObject>

@optional
/**
 * Notify the delegate that the canUndo or canRedo status of the graffiti view has changed.
 *
 * @param graffitiManager The graffitiManager send the event.
 */
- (void)graffitiManagerUndoRedoStatusChanged:(MSVGraffitiManager *)graffitiManager;

@end

/**
 * Graffity state manager.
 */
@interface MSVGraffitiManager : NSObject

/**
 * The delegate object used for receiving callbacks.
 */
@property (nonatomic, weak) id<MSVGraffitiManagerDelegate> delegate;

/**
 * hide inner graffitty view or not.
 */
@property (nonatomic, assign) BOOL hideGraffitiView;

/**
 * The maximum steps undo stack can save, if current undo stack has exceeded the limit, the oldest operation saved will be dropped, a limit of 0 indicates no limit.
 * The default is 20.
 */
@property (nonatomic, assign) NSUInteger maxUndoSteps;

/**
 * The MSVBrush object defining drawing properties.
 */
@property (nonatomic, strong) MSVBrush *brush;

/**
 * Is there operation that can be undone in the undo stack.
 *
 * @return YES so that you can perform undo operation, otherwise you can't.
 */
- (BOOL)canUndo;

/**
 * Is there operation that can be redone in the redo stack.
 *
 * @return YES so that you can perform redo operation, otherwise you can't.
 */
- (BOOL)canRedo;

/**
 * Undo the last operation.
 */
- (void)undo;

/**
 * Redo the last undone operation, any drawing operation will clear the redo stack.
 */
- (void)redo;

/**
 * Clear the undo stack and redo stack.
 */
- (void)reset;

/**
 * Clear the undo stack, redo stack and any thing drawn on the view.
 */
- (void)clear;

/**
 * Export graffity to a MSVImageStickerEditorEffect object so that you can add it to effects of MSVDraft.
 *
 * @return The generated MSVImageStickerEditorEffect object.
 */
- (MSVImageStickerEditorEffect *)exportAsImageStickerEditorEffect;

@end

NS_ASSUME_NONNULL_END
