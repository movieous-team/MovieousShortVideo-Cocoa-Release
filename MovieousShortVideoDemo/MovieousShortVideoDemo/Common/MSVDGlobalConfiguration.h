//
//  MSVDGlobalConfiguration.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/29.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVDGlobalConfiguration : NSObject

@property (nonatomic, assign) CGSize resultVideoSize;

+ (instancetype)sharedGlobalConfiguration;

@end

NS_ASSUME_NONNULL_END
