//
//  MSVDFiltersLibrary.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/23.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDFiltersLibrary.h"

@implementation MSVDFilter

@end

static NSMutableArray<MSVDFilter *> *_filters;

@implementation MSVDFiltersLibrary

+ (NSArray<MSVDFilter *> *)filters {
    if (!_filters) {
        _filters = [NSMutableArray array];
        NSString *filterBundlePath = [NSBundle.mainBundle pathForResource:@"Filters" ofType:@"bundle"];
        NSError *error;
        NSArray *names = [NSFileManager.defaultManager contentsOfDirectoryAtPath:filterBundlePath error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return nil;
        }
        UIImage *cover = [UIImage imageNamed:@"filter_template.jpg"];
        for (NSString *name in names) {
            MSVDFilter *filter = [MSVDFilter new];
            filter.image = [UIImage imageWithContentsOfFile:[NSString stringWithFormat:@"%@/%@", filterBundlePath, name]];
            filter.name = name;
            filter.cover = cover;
            [_filters addObject:filter];
        }
    }
    return _filters;
}

@end
