//
//  MSVDGlobalConfiguration.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/29.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDGlobalConfiguration.h"

@implementation MSVDGlobalConfiguration

+ (instancetype)sharedGlobalConfiguration {
    static MSVDGlobalConfiguration *instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [MSVDGlobalConfiguration new];
    });
    return instance;
}

- (instancetype)init {
    if (self = [super init]) {
        _resultVideoSize = CGSizeMake(720, 1280);
    }
    return self;
}

@end
