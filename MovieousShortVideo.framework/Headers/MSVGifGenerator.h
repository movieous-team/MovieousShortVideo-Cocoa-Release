//
//  MSVGifGenerator.h
//  MSVShortVideoKit
//
//  Created by Chris Wang on 2019/7/14.
//  Copyright © 2019年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVGifGenerator : NSObject

/**
 * The output URL for the generated GIF file, only supports local file address.
 * The default is the automatically generated address.
 */
@property (strong, nonatomic, nullable) NSURL *outputURL;

/**
 * Whether the generating task is running.
 */
@property (nonatomic, assign, readonly) BOOL running;

/**
 * The interval between frames of the generated gif file.
 * The default is 0.1.
 */
@property (assign, nonatomic) float interval;

/**
 * Generating progress callback.
 */
@property (nonatomic, copy, nullable) void(^progressHandler)(float progress);

/**
 * Generating failure callback.
 */
@property (nonatomic, copy, nullable) void(^failureHandler)(NSError *error);

/**
 * Generating successful callback.
 */
@property (nonatomic, copy, nullable) void(^completionHandler)(NSURL *URL);

/**
 * Initialize an MSVGifGenerator objects with images.
 *
 * @param images Images used to generate gif.
 *
 * @return The initialized object.
 */
- (instancetype)initWithImages:(NSArray<UIImage *> *)images;

/**
 * Start the generating tasks.
 */
- (void)start;

/**
 * Cancel the generating task.
 */
- (void)cancel;

@end

NS_ASSUME_NONNULL_END
