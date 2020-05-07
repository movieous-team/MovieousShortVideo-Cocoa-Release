//
//  MSVDMusicsLibrary.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSNotificationName const MSVDMusicDidUpdatedNotification;
extern NSNotificationName const MSVDMusicsLibraryRefreshDoneNotification;

@interface MSVDMusic : NSObject

@property (nonatomic, strong) NSURL *sourceURL;
@property (nonatomic, strong) NSURL *coverURL;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *author;
@property (nonatomic, strong) NSString *localPath;
@property (nonatomic, assign) BOOL downloading;
@property (nonatomic, assign) float progress;

- (void)download;

@end

@interface MSVDMusicsLibrary : NSObject

@property (nonatomic, strong, readonly, class) NSMutableArray<MSVDMusic *> *musics;

+ (void)refresh;

@end

NS_ASSUME_NONNULL_END
