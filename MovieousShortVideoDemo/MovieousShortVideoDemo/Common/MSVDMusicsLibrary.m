//
//  MSVDMusicsLibrary.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDMusicsLibrary.h"

@interface MSVDMusic ()
<
NSURLSessionDownloadDelegate
>

@end

@implementation MSVDMusic {
    NSURLSession *_session;
}

- (BOOL)isEqual:(MSVDMusic *)object {
    if ([object.sourceURL.absoluteString isEqualToString:_sourceURL.absoluteString] && [object.coverURL.absoluteString isEqualToString:_coverURL.absoluteString] && [object.name isEqualToString:_name] && [object.author isEqualToString:_author]) {
        return YES;
    }
    return NO;
}

- (instancetype)initWithDictionary:(NSDictionary *)dictionary {
    if (self = [super init]) {
        _sourceURL = [NSURL URLWithString:dictionary[@"sourceURL"]];
        _coverURL = [NSURL URLWithString:dictionary[@"coverURL"]];
        _name = dictionary[@"name"];
        _author = dictionary[@"author"];
    }
    return self;
}

- (instancetype)initWithSourceURL:(NSURL *)sourceURL coverURL:(NSURL *)coverURL name:(NSString *)name author:(NSString *)author localPath:(NSString *)localPath {
    if (self = [super init]) {
        _sourceURL = sourceURL;
        _coverURL = coverURL;
        _name = name;
        _author = author;
        _localPath = localPath;
    }
    return self;
}

- (void)download {
    if (!_localPath) {
        [[self.session downloadTaskWithURL:_sourceURL] resume];
        _downloading = YES;
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDMusicDidUpdatedNotification object:self];
}

- (NSURLSession *)session {
    if (!_session) {
        _session = [NSURLSession sessionWithConfiguration:NSURLSessionConfiguration.defaultSessionConfiguration delegate:self delegateQueue:NSOperationQueue.mainQueue];
    }
    return _session;
}

- (void)URLSession:(nonnull NSURLSession *)session downloadTask:(nonnull NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(nonnull NSURL *)location {
    _downloading = NO;
    NSString *localPath = [NSString stringWithFormat:@"%@/%@", MSVDGetLocalMusicsDir(), _sourceURL.lastPathComponent];
    NSError *error;
    [NSFileManager.defaultManager moveItemAtPath:location.path toPath:localPath error:&error];
    if (error) {
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
        return;
    }
    _localPath = localPath;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDMusicDidUpdatedNotification object:self];
}

- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite {
    _progress = (float)totalBytesWritten / (float)totalBytesExpectedToWrite;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDMusicDidUpdatedNotification object:self];
}

@end

static NSMutableArray<MSVDMusic *> *_musics;

@implementation MSVDMusicsLibrary

+ (void)load {
    _musics = [NSMutableArray array];
}

+ (NSMutableArray<MSVDMusic *> *)musics {
    return _musics;
}

+ (void)refresh {
    [[NSURLSession.sharedSession dataTaskWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/api/demo/musics", MSVDGetServerHost()]] completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        NSInteger statusCode = ((NSHTTPURLResponse *)response).statusCode;
        if (statusCode != 200) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey:MSVDGenerateError(-200, @"%@: %d", NSLocalizedString(@"MSVDMusicsLibrary.statusError", nil), statusCode)}];
            return;
        }
        if (!data) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey:MSVDGenerateError(-200, @"%@", NSLocalizedString(@"MSVDMusicsLibrary.noData", nil))}];
            return;
        }
        NSArray *localMusicNames = [NSFileManager.defaultManager contentsOfDirectoryAtPath:MSVDGetLocalMusicsDir() error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        NSArray *musicsArray = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        for (NSDictionary *musicDic in musicsArray) {
            MSVDMusic *music = [[MSVDMusic alloc] initWithDictionary:musicDic];
            if ([_musics containsObject:music]) {
                continue;
            }
            if ([localMusicNames containsObject:music.sourceURL.lastPathComponent]) {
                music.localPath = [NSString stringWithFormat:@"%@/%@", MSVDGetLocalMusicsDir(), music.sourceURL.lastPathComponent];
            }
            [_musics addObject:music];
        }
        [NSNotificationCenter.defaultCenter postNotificationName:MSVDMusicsLibraryRefreshDoneNotification object:self];
    }] resume];
}

@end
