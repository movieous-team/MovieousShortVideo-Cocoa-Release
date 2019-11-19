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
 * The output path for the generated GIF file, only supports local file path.
 * The default is the automatically generated path.
 */
@property (strong, nonatomic, nullable) NSString *outputPath;

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
 * The loop count of the generated gif, 0 means loop forever.
 * The default is 0.
 */
@property (assign, nonatomic) NSUInteger loopCount;

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
@property (nonatomic, copy, nullable) void(^completionHandler)(NSString *path);

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
