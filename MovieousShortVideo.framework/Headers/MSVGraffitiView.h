//
//  MSVGraffitiView.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/19.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVBrush.h"

NS_ASSUME_NONNULL_BEGIN

@class MSVGraffitiView;
@protocol MSVGraffitiViewDelegate <NSObject>

@optional
/**
 * @brief Notify the delegate that the canUndo or canRedo status of the graffiti view has changed
 * @param graffitiView The graffitiView send the event
 */
- (void)graffitiViewUndoRedoStatusChanged:(MSVGraffitiView *)graffitiView;

@end

/**
 * @brief UIView subclass used for drawing graffiti
 */
@interface MSVGraffitiView : UIView

/**
 * @brief The delegate object used for receiving callbacks
 */
@property (nonatomic, weak) id<MSVGraffitiViewDelegate> delegate;

/**
 * @brief The maximum steps undo stack can save, if current undo stack has exceeded the limit, the oldest operation saved will be dropped, a limit of 0 indicates no limit. The default is 20
 */
@property (nonatomic, assign) NSUInteger maxUndoSteps;

/**
 * @brief The MSVBrush object defining drawing properties
 */
@property (nonatomic, strong) MSVBrush *brush;

/**
 * @brief Instantiate a MSVGraffitiView object with frame and brush
 * @param frame Frame for the view
 * @param brush Brush defining drawing properties
 * @return The instantiated brush instance
 */
+ (instancetype)graffitiViewWithFrame:(CGRect)frame brush:(MSVBrush *)brush;

/**
 * @brief Initiate a MSVGraffitiView object with frame and brush
 * @param frame Frame for the view
 * @param brush Brush defining drawing properties
 * @return The initiate brush instance
 */
- (instancetype)initWithFrame:(CGRect)frame brush:(MSVBrush *)brush;

/**
 * @brief Take a snapshot of the MSVGraffitiView object
 * @return The image taken
 */
- (UIImage *)takeSnapshot;

/**
 * @brief Is there operation that can be undone in the undo stack
 * @return YES so that you can perform undo operation, otherwise you can't
 */
- (BOOL)canUndo;

/**
 * @brief Is there operation that can be redone in the redo stack
 * @return YES so that you can perform redo operation, otherwise you can't
 */
- (BOOL)canRedo;

/**
 * @brief Undo the last operation
 */
- (void)undo;

/**
 * @brief Redo the last undone operation, any drawing operation will clear the redo stack
 */
- (void)redo;

/**
 * @brief Clear the undo stack and redo stack
 */
- (void)reset;

/**
 * @brief Clear the undo stack, redo stack and any thing drawn on the view
 */
- (void)clear;

@end

NS_ASSUME_NONNULL_END