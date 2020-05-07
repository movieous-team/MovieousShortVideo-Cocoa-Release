//
//  MSVDStickersLibrary.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDStickersLibrary.h"
#import <SSZipArchive/SSZipArchive.h>

NSNotificationName const MSVDStickerUpdatedNotification = @"MSVDStickerUpdatedNotification";
NSNotificationName const MSVDStickersLibraryUpdatedNotification = @"MSVDStickersLibraryUpdatedNotification";

@interface MSVDSticker ()
<
NSURLSessionDownloadDelegate,
SSZipArchiveDelegate
>

@end

@implementation MSVDSticker {
    NSURLSession *_session;
}

- (BOOL)isEqual:(MSVDSticker *)object {
    if ([object.sourceURL.absoluteString isEqualToString:_sourceURL.absoluteString] && [object.thumbnailURL.absoluteString isEqualToString:_thumbnailURL.absoluteString] && object.type == _type) {
        return YES;
    }
    return NO;
}

- (instancetype)initWithDictionary:(NSDictionary *)dictionary {
    if (self = [super init]) {
        _sourceURL = [NSURL URLWithString:dictionary[@"sourceURL"]];
        _thumbnailURL = [NSURL URLWithString:dictionary[@"thumbnailURL"]];
        NSString *typeString = dictionary[@"type"];
        if ([typeString isEqualToString:@"gif"]) {
            _type = MSVDStickerTypeGif;
        } else if ([typeString isEqualToString:@"image"]) {
            _type = MSVDStickerTypeImage;
        } else if ([typeString isEqualToString:@"images"]) {
            _type = MSVDStickerTypeImages;
        }
    }
    return self;
}

- (void)download {
    if (!_localPaths.count) {
        [[self.session downloadTaskWithURL:_sourceURL] resume];
        _downloading = YES;
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickerUpdatedNotification object:self];
}

- (NSURLSession *)session {
    if (!_session) {
        _session = [NSURLSession sessionWithConfiguration:NSURLSessionConfiguration.defaultSessionConfiguration delegate:self delegateQueue:NSOperationQueue.mainQueue];
    }
    return _session;
}

- (void)URLSession:(nonnull NSURLSession *)session downloadTask:(nonnull NSURLSessionDownloadTask *)downloadTask didFinishDownloadingToURL:(nonnull NSURL *)location {
    _downloading = NO;
    if (_type == MSVDStickerTypeImages) {
        [SSZipArchive unzipFileAtPath:location.path toDestination:[NSString stringWithFormat:@"%@/%@", MSVDGetLocalStickersDir(), _sourceURL.lastPathComponent] delegate:self];
        _localPaths = [sortAnimatedImagePaths(_localPaths) mutableCopy];
    } else {
        NSString *localPath = [NSString stringWithFormat:@"%@/%@", MSVDGetLocalStickersDir(), _sourceURL.lastPathComponent];
        NSError *error;
        [NSFileManager.defaultManager moveItemAtPath:location.path toPath:localPath error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        _localPaths = [@[localPath] mutableCopy];
    }
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickerUpdatedNotification object:self];
}

- (void)URLSession:(NSURLSession *)session downloadTask:(NSURLSessionDownloadTask *)downloadTask didWriteData:(int64_t)bytesWritten totalBytesWritten:(int64_t)totalBytesWritten totalBytesExpectedToWrite:(int64_t)totalBytesExpectedToWrite {
    _progress = (float)totalBytesWritten / (float)totalBytesExpectedToWrite;
    [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickerUpdatedNotification object:self];
}

- (void)zipArchiveDidUnzipFileAtIndex:(NSInteger)fileIndex totalFiles:(NSInteger)totalFiles archivePath:(NSString *)archivePath unzippedFilePath:(NSString *)unzippedFilePath {
    if (!_localPaths) {
        _localPaths = [NSMutableArray array];
    }
    [_localPaths addObject:unzippedFilePath];
}

@end

static NSMutableArray<MSVDSticker *> *_stickers;

@implementation MSVDStickersLibrary

+ (void)load {
    _stickers = [NSMutableArray array];
}

+ (NSMutableArray<MSVDSticker *> *)stickers {
    return _stickers;
}

+ (void)refresh {
    [[NSURLSession.sharedSession dataTaskWithURL:[NSURL URLWithString:[NSString stringWithFormat:@"%@/api/demo/stickers", MSVDGetServerHost()]] completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        NSInteger statusCode = ((NSHTTPURLResponse *)response).statusCode;
        if (statusCode != 200) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey:MSVDGenerateError(-200, @"%@: %d", NSLocalizedString(@"MSVDStickersLibrary.statusError", nil), statusCode)}];
            return;
        }
        if (!data) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey:MSVDGenerateError(-200, @"%@", NSLocalizedString(@"MSVDStickersLibrary.noData", nil))}];
            return;
        }
        NSArray *localStickerNames = [NSFileManager.defaultManager contentsOfDirectoryAtPath:MSVDGetLocalStickersDir() error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        NSArray *stickersArray = [NSJSONSerialization JSONObjectWithData:data options:0 error:&error];
        if (error) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
            return;
        }
        BOOL changed = NO;
        for (NSDictionary *stickerDic in stickersArray) {
            MSVDSticker *sticker = [[MSVDSticker alloc] initWithDictionary:stickerDic];
            if ([_stickers containsObject:sticker]) {
                continue;
            }
            if ([localStickerNames containsObject:sticker.sourceURL.lastPathComponent]) {
                if (sticker.type == MSVDStickerTypeImages) {
                    NSError *error;
                    NSString *path = [NSString stringWithFormat:@"%@/%@", MSVDGetLocalStickersDir(), sticker.sourceURL.lastPathComponent];
                    NSArray *names = [NSFileManager.defaultManager contentsOfDirectoryAtPath:path error:&error];
                    if (error) {
                        [NSNotificationCenter.defaultCenter postNotificationName:MSVDErrorNotification object:self userInfo:@{MSVDErrorKey: error}];
                        return;
                    }
                    sticker.localPaths = [NSMutableArray array];
                    for (NSString *name in names) {
                        [sticker.localPaths addObject:[NSString stringWithFormat:@"%@/%@", path, name]];
                    }
                    sticker.localPaths = [sortAnimatedImagePaths(sticker.localPaths) mutableCopy];
                } else {
                    sticker.localPaths = [NSMutableArray arrayWithObject:[NSString stringWithFormat:@"%@/%@", MSVDGetLocalStickersDir(), sticker.sourceURL.lastPathComponent]];
                }
            }
            [_stickers addObject:sticker];
            changed = YES;
        }
        if (changed) {
            [NSNotificationCenter.defaultCenter postNotificationName:MSVDStickersLibraryUpdatedNotification object:self];
        }
    }] resume];
}

@end
