//
//  MSVDFiltersLibrary.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/23.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVDFilter : NSObject

@property (nonatomic, strong) UIImage *image;
@property (nonatomic, strong) UIImage *cover;
@property (nonatomic, strong) NSString *name;

@end

@interface MSVDFiltersLibrary : NSObject

@property (nonatomic, strong, class, readonly) NSArray<MSVDFilter *> *filters;

@end

NS_ASSUME_NONNULL_END
