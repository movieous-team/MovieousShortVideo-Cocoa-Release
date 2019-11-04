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
 * 包含一些基础功能的对象基类，请不要直接使用该类初始化对象使用。
 */
@interface MovieousObject : NSObject

/**
 * 使用现有的 MovieousObject 对象初始化 MovieousObject，其相关 attachments 和 object 保持一致。
 *
 * @param object 现有的 MovieousObject 对象。
 *
 * @return 初始化后的 MovieousObject 对象。
 */
- (instancetype)initWithObject:(MovieousObject *)object;

/**
 * 使用键值设置关联的附件，设置后的附件可以供用户在业务逻辑当中使用相关的键值来取用，需要释放时请调用 `-removeAttachmentForKey` 或 `-removeAllAttachments` 来移除相关附件。
 *
 * @param attachment 需要设置的附件对象。
 * @param key 关联附件对象的键值。
 */
- (void)setAttachment:(id)attachment forKey:(NSString *)key;

/**
 * 移除键值关联的附件。
 *
 * @param key 需要移除附件的键值。
 */
- (void)removeAttachmentForKey:(NSString *)key;

/**
 * 移除所有键值关联的附件。
 */
- (void)removeAllAttachments;

/**
 * 获取简直相关的附件。
 *
 * @param key 需要获取附件的键值。
 *
 * @return 获取到的附件对象，如果不存在键值关联的附件，则返回 nil。
 */
- (id _Nullable)getAttachmentForKey:(NSString *)key;

@end

NS_ASSUME_NONNULL_END
