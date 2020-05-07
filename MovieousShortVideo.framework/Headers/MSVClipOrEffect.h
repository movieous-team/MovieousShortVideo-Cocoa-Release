//
//  MSVClipOrEffect.h
//  MovieousShortVideo
//
//  Created by WangSiyu on 2020/3/6.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MSVClipOrEffect
<
NSObject,
NSCopying
>

/**
 * 片段实际在主轨中实际展示的时间区间。
 */
@property (nonatomic, assign, readonly) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 片段实际在主轨中实际展示的开始时间，当片段加入 MSVDraft 之后才能获取到该值。
 */
@property (nonatomic, assign, readonly) MovieousTime startTimeAtMainTrack;

/**
 * 片段实际在主轨中的时间长度，当片段类型是音视频时，durationAtMainTrack 参数和 speed 参数互相影响，调整 durationAtMainTrack 将会影响 speed，具体为：speed = timeRange.duration / durationAtMainTrack.
 * 默认为根据 timeRange 和 speed 自动计算出来的数据。
 */
@property (nonatomic, assign) MovieousTime durationAtMainTrack;

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

- (void)addObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath options:(NSKeyValueObservingOptions)options context:(nullable void *)context;
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath context:(nullable void *)context API_AVAILABLE(macos(10.7), ios(5.0), watchos(2.0), tvos(9.0));
- (void)removeObserver:(NSObject *)observer forKeyPath:(NSString *)keyPath;
- (id)copy;

@end

@protocol MSVMutableClipOrEffect
<
MSVClipOrEffect
>

/**
 * 片段实际在主轨中实际展示的时间区间。
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

/**
 * 片段实际在主轨中实际展示的开始时间，当片段加入 MSVDraft 之后才能获取到该值。
 */
@property (nonatomic, assign) MovieousTime startTimeAtMainTrack;

@end

NS_ASSUME_NONNULL_END
