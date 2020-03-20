//
//  MovieousMicrophoneConfiguration.h
//  MovieousCaptureBase
//
//  Created by Chris Wang on 2018/9/26.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

/**
 * 麦克风采集配置对象。
 */
@interface MovieousMicrophoneConfiguration : NSObject

/**
 * 录制时是否静音。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL mute;

@end
