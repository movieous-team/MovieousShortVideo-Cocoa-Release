//
//  MSVEditor.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/10/5.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MSVDraft.h"
#import "MSVClip.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Notify the current play time of the editor has updated.
 */
extern NSString *kMSVEditorCurrentTimeUpdatedNotification;

/**
 * The current time key of kMSVEditorCurrentTimeUpdatedNotification.
 */
extern NSString *kMSVEditorCurrentTimeKey;

@class MSVEditor;
@protocol MSVEditorDelegate <NSObject>

@optional
/**
 * Notify the delegate that current play time has updated.
 *
 * @param editor The editor that send the event.
 * @param currentTime The current play time of the editor.
 */
- (void)editor:(MSVEditor *)editor currentTimeDidUpdate:(NSTimeInterval)currentTime;

/**
 * Notify the delegate that current play state has changed.
 *
 * @param editor The editor that send the event.
 * @param playing The current play state of the editor.
 */
- (void)editor:(MSVEditor *)editor playStateChanged:(BOOL)playing;

@end

@interface MSVEditor : NSObject

/**
 * Please operate the underlying, draft object and related edits through the draft object.
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * Edit preview view.
 */
@property (nonatomic, strong, readonly) UIView *preview;

/**
 * The area where the video content is displayed in the preview.
 */
@property (nonatomic, assign, readonly) CGRect contentFrame;

/**
 * The fill mode of preview view, the default is MovieousScalingModeAspectFit.
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * Current playback progress.
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentTime;

/**
 * Whether it currently playback.
 */
@property (nonatomic, assign, readonly) BOOL playing;

/**
 * Whether to loop.
 */
@property (nonatomic, assign) BOOL loop;

/**
 * Editor proxy object.
 */
@property (nonatomic, weak) id<MSVEditorDelegate> delegate;

/**
 * The queue callback made by the proxy method, the default is the main queue.
 */
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

/**
 * Initialize an MSVEditor object with a draft object.
 *
 * @param draft Draft object.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns the draft object if the initialization is successful, returns nil if it fails.
 */
+ (instancetype _Nullable)editorWithDraft:(MSVDraft *_Nullable)draft error:(NSError *_Nullable *_Nullable)outError;

/**
 * Initialize an MSVEditor object with a draft object.
 *
 * @param draft Draft object.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns the draft object if the initialization is successful, returns nil if it fails.
 */
- (instancetype _Nullable)initWithDraft:(MSVDraft *_Nullable)draft error:(NSError *_Nullable *_Nullable)outError NS_DESIGNATED_INITIALIZER;

/**
 * Update the underlying MSVDraft object.
 *
 * @param draft Draft object.
 * @param outError If an error occurs, return the error that occurred.
 *
 * @return It returns YES if the update is successful, returns NO if it fails.
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError **)outError;

/**
 * Start previewing.
 */
- (void)play;

/**
 * Pause previewing.
 */
- (void)pause;

/**
 * The player fast forwards to the appropriate position.
 *
 * @param time Target position.
 */
- (void)seekToTime:(NSTimeInterval)time accurate:(BOOL)accurate;

@end

NS_ASSUME_NONNULL_END
