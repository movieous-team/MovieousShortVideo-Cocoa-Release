//
//  MSVRenderContext.h
//  MovieousShortVideo
//
//  Created by WangSiyu on 2020/3/8.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 渲染上下文类，不同的 MSVEditor 对象，不同的 MSVSnapshotGenerator 对象，不同的 MSVExporter 对象均会使用不同的 MSVRenderContext 对象。
 */
@interface MSVRenderContext : NSObject

@end

NS_ASSUME_NONNULL_END
