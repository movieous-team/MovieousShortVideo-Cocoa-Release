//
//  MSVDTypeDefines.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/29.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

#define VideoFrameRate              30
// 一帧
#define MinDurationPerClip          33333
#define DefaultTransitionDuration   5e6
#define MinTransitionDuration       0.1
#define IsEmptyStringKey            @"IsEmptyStringKey"

extern NSNotificationName const MSVDErrorNotification;
extern NSString *const MSVDErrorKey;

NS_ASSUME_NONNULL_END
