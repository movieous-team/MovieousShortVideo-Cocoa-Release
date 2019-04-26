//
//  MovieousMicrophoneConfiguration.h
//  MovieousBase
//
//  Created by Chris Wang on 2018/9/26.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

@protocol MovieousMicrophoneConfiguration <NSObject>

/**
 * 录制时是否静音。
 * 默认为 NO。
 */
@property (nonatomic, assign) BOOL mute;

@end
