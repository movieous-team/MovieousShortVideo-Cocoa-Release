//
//  MovieousMicrophoneConfiguration.h
//  Movieous
//
//  Created by Chris Wang on 2018/9/26.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>

@protocol MovieousMicrophoneConfiguration <NSObject>

/*!
 * Whether to allow to compromise some parameters which are not supported by the current device to ensure component initialization's success. Default to YES
 */
@property (nonatomic, assign) BOOL compromise;

@end
