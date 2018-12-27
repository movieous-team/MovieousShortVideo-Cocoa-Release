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

extern NSString *kMSVEditorCurrentTimeUpdatedNotification;

@class MSVEditor;
@protocol MSVEditorDelegate <NSObject>

@optional
- (void)editor:(MSVEditor *)editor currentTimeDidUpdate:(NSTimeInterval)currentTime;

- (void)editor:(MSVEditor *)editor playStateChanged:(BOOL)playing;

@end

@interface MSVEditor : NSObject

/**
 * @brief Please operate the underlying, draft object and related edits through the draft object
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * @brief Edit preview view
 */
@property (nonatomic, strong, readonly) UIView *preview;

/**
 * @brief The area where the video content is displayed in the preview
 */
@property (nonatomic, assign, readonly) CGRect contentFrame;

/**
 * @brief The fill mode of preview view , the default is MovieousScalingModeAspectFit
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * @brief Current playback progress
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentTime;

/**
 * @brief Whether it currently playback
 */
@property (nonatomic, assign, readonly) BOOL playing;

/**
 * @brief Whether to loop
 */
@property (nonatomic, assign) BOOL loop;

/**
 * @brief Editor proxy object
 */
@property (nonatomic, weak) id<MSVEditorDelegate> delegate;

/**
 * @brief The queue callback made by the proxy method, the default is the main queue
 */
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

/**
 * @brief Initialize an MSVEditor object with an audio and video URL
 * @param URL Audio and video address
 * @param outError If an error occurs, return the error that occurred
 * @return It returns the draft object if the initialization is successful, returns nil if it fails.
 */
- (instancetype)initWithAVURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief Initialize an MSVEditor object with a image URL
 * @param URL Image address
 * @param outError If an error occurs, return the error that occurred
 * @return It returns the draft object if the initialization is successful, returns nil if it fails.
 */
- (instancetype)initWithImageURL:(NSURL *)URL error:(NSError **)outError;

/**
 * @brief Initialize an MSVEditor object with a draft object
 * @param draft Draft object
 * @param outError If an error occurs, return the error that occurred
 * @return It returns the draft object if the initialization is successful, returns nil if it fails.
 */
- (instancetype)initWithDraft:(MSVDraft *)draft error:(NSError **)outError;

/**
 * @brief Start previewing
 */
- (void)play;

/**
 * @brief Pause previewing
 */
- (void)pause;

/**
 * @brief The player fast forwards to the appropriate position
 * @param time Target position
 * @param completionHandler The callback at the end of fast-forwarding, finished: whether the fast forward is complete。
 */
- (void)seekToTime:(NSTimeInterval)time completionHandler:(void (^)(BOOL finished))completionHandler;

@end
