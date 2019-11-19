//
//  MovieousObject.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/7/20.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * The base class which include some basic functions, please do not instantiate the class directly, use its subclasses.
 */
@interface MovieousObject : NSObject

/**
 * Initiate the MovieousObject with existing MovieousObject.
 *
 * @param object The existing MovieousObject object.
 *
 * @return The initialized MovieousObject object.
 */
- (instancetype)initWithObject:(MovieousObject *)object;

/**
 * Set attachment with key, you can use this attachment with the key, `-removeAttachmentForKey` and `-removeAllAttachments` can be used to remove related attachment.
 *
 * @param attachment Attachment object to set.
 * @param key Key for the attachment.
 */
- (void)setAttachment:(id)attachment forKey:(NSString *)key;

/**
 * Remove attachment.
 *
 * @param key Key of attachment to remove.
 */
- (void)removeAttachmentForKey:(NSString *)key;

/**
 * Remove all of the attachments.
 */
- (void)removeAllAttachments;

/**
 * Get attachment with specific key.
 *
 * @param key The key of attachment to get.
 *
 * @return The attachment retrieved, return nil if not found.
 */
- (id _Nullable)getAttachmentForKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
