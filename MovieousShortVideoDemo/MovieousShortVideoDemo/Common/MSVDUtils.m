//
//  MSVDUtils.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/21.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "MSVDUtils.h"

static NSString *serverHost = @"https://demo.movieous.cn";

static NSString *localMusicsDir;
static NSString *localStickersDir;

void MSVDRunSynchronouslyOnMainQueue(void (^block)(void))
{
    if ([NSThread isMainThread])
    {
        block();
    }
    else
    {
        dispatch_sync(dispatch_get_main_queue(), block);
    }
}

void MSVDRunAsynchronouslyOnMainQueue(void (^block)(void))
{
    if ([NSThread isMainThread])
    {
        block();
    }
    else
    {
        dispatch_async(dispatch_get_main_queue(), block);
    }
}

NSString *MSVDGetLocalMusicsDir(void) {
    if (!localMusicsDir) {
        localMusicsDir = [NSString stringWithFormat:@"%@/movieous/musics", NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject];
        NSError *error;
        BOOL isDirectory;
        BOOL exist = [NSFileManager.defaultManager fileExistsAtPath:localMusicsDir isDirectory:&isDirectory];
        if (exist && !isDirectory) {
            [NSFileManager.defaultManager removeItemAtPath:localMusicsDir error:&error];
            if (error) {
                NSLog(@"remove localMusicsDir error: %@", error.localizedDescription);
            }
            exist = NO;
        }
        if (!exist) {
            [NSFileManager.defaultManager createDirectoryAtPath:localMusicsDir withIntermediateDirectories:YES attributes:nil error:&error];
            if (error) {
                NSLog(@"create localMusicsDir error: %@", error.localizedDescription);
            }
        }
    }
    return localMusicsDir;
}

NSString *MSVDGetLocalStickersDir(void) {
    if (!localStickersDir) {
        localStickersDir = [NSString stringWithFormat:@"%@/movieous/stickers", NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject];
        NSError *error;
        BOOL isDirectory;
        BOOL exist = [NSFileManager.defaultManager fileExistsAtPath:localStickersDir isDirectory:&isDirectory];
        if (exist && !isDirectory) {
            [NSFileManager.defaultManager removeItemAtPath:localStickersDir error:&error];
            if (error) {
                NSLog(@"remove localStickersDir error: %@", error.localizedDescription);
            }
            exist = NO;
        }
        if (!exist) {
            [NSFileManager.defaultManager createDirectoryAtPath:localStickersDir withIntermediateDirectories:YES attributes:nil error:&error];
            if (error) {
                NSLog(@"create localStickersDir error: %@", error.localizedDescription);
            }
        }
    }
    return localStickersDir;
}

NSString *MSVDGetServerHost(void) {
    return serverHost;
}

NSError *MSVDGenerateError(NSInteger code, NSString *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    NSString *localizedDescription = [[NSString alloc] initWithFormat:fmt arguments:args];
    va_end(args);
    return [NSError errorWithDomain:@"video.MovieousShortVideoDemo" code:-200 userInfo:@{
        NSLocalizedDescriptionKey: localizedDescription
    }];
}

CGSize MSVDGetFitSize(CGSize size, CGFloat longSide, CGFloat shortSide) {
    if (size.width >= size.height) {
        return AVMakeRectWithAspectRatioInsideRect(size, CGRectMake(0, 0, longSide, shortSide)).size;
    } else {
        return AVMakeRectWithAspectRatioInsideRect(size, CGRectMake(0, 0, shortSide, longSide)).size;
    }
}

int getImageIndex(NSString *imagePath) {
    NSArray<NSString *> *segments1 = [imagePath componentsSeparatedByString:@"_"];
    if (segments1.count < 2) {
        return 0;
    }
    NSArray<NSString *> *segments2 = [segments1[1] componentsSeparatedByString:@"."];
    if (segments2.count < 2) {
        return 0;
    }
    return [segments2[0] intValue];
}

NSArray<NSString *> *sortAnimatedImagePaths(NSArray<NSString *> * imagePaths) {
    return [imagePaths sortedArrayUsingComparator:^NSComparisonResult(NSString *  _Nonnull obj1, NSString *  _Nonnull obj2) {
        int index1 = getImageIndex(obj1);
        int index2 = getImageIndex(obj2);
        if (index1 < index2) {
            return NSOrderedAscending;
        } else if (index1 > index2) {
            return NSOrderedDescending;
        } else {
            return NSOrderedSame;
        }
    }];
}

@implementation MSVDUtils

+ (NSString *)formatTimeInterval:(MovieousTime)timeInterval {
    NSUInteger t = timeInterval / MovieousInnerTimeScale;
    NSUInteger minutes = t / 60;
    NSString *minutesString;
    if (minutes < 10) {
        minutesString = [NSString stringWithFormat:@"0%lu", (unsigned long)minutes];
    } else {
        minutesString = [NSString stringWithFormat:@"%lu", (unsigned long)minutes];
    }
    NSUInteger seconds = t - minutes * 60;
    NSString *secondsString;
    if (seconds < 10) {
        secondsString = [NSString stringWithFormat:@"0%lu", (unsigned long)seconds];
    } else {
        secondsString = [NSString stringWithFormat:@"%lu", (unsigned long)seconds];
    }
    return [NSString stringWithFormat:@"%@:%@", minutesString, secondsString];
}

+ (TZImagePickerController *)generateImagePickerControllerWithDelegate:(id<TZImagePickerControllerDelegate>)delegate maxImagesCount:(NSInteger)maxImagesCount {
    TZImagePickerController *imagePickerController = [[TZImagePickerController alloc] initWithMaxImagesCount:maxImagesCount delegate:delegate];
    imagePickerController.modalPresentationStyle = UIModalPresentationFullScreen;
    imagePickerController.allowPickingGif = YES;
    imagePickerController.allowPickingMultipleVideo = YES;
    imagePickerController.allowPickingOriginalPhoto = NO;
    imagePickerController.allowPickingImage = YES;
    imagePickerController.showSelectedIndex = YES;
    imagePickerController.onlyReturnAsset = YES;
    return imagePickerController;
}

+ (NSMutableArray<MSVMainTrackClip *> *)generateMainTrackClipsWithAssets:(NSArray<PHAsset *> *)assets videoSize:(CGSize)videoSize scalingMode:(MovieousScalingMode)scalingMode error:(NSError **)outError {
    PHImageManager *manager = [PHImageManager defaultManager];
    NSMutableArray *mainTrackClips = [NSMutableArray array];
    __block NSError *error;
    __block CGSize renderSize = videoSize;
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    for (PHAsset *asset in assets) {
        if (asset.mediaType == PHAssetMediaTypeVideo) {
            [manager requestAVAssetForVideo:asset options:nil resultHandler:^(AVAsset * _Nullable asset, AVAudioMix * _Nullable audioMix, NSDictionary * _Nullable info) {
                MSVMainTrackClip *clip = [MSVMainTrackClip mainTrackClipWithAsset:asset error:&error];
                if (!error) {
                    if (CGSizeEqualToSize(renderSize, CGSizeZero)) {
                        renderSize = clip.defaultSize;
                    }
                    [clip resetGeometryWithVideoSize:renderSize scalingMode:scalingMode];
                    [mainTrackClips addObject:clip];
                }
                dispatch_semaphore_signal(semaphore);
            }];
            dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
            if (error) {
                if (outError) {
                    *outError = error;
                }
                return nil;
            }
        } else if (asset.mediaType == PHAssetMediaTypeImage) {
            PHImageRequestOptions *option = [PHImageRequestOptions new];
            option.version = PHImageRequestOptionsVersionOriginal;
            option.deliveryMode = PHImageRequestOptionsDeliveryModeHighQualityFormat;
            option.resizeMode = PHImageRequestOptionsResizeModeNone;
            if ([[asset valueForKey:@"filename"] hasSuffix:@"GIF"]) {
                [manager requestImageDataForAsset:asset options:option resultHandler:^(NSData * _Nullable imageData, NSString * _Nullable dataUTI, UIImageOrientation orientation, NSDictionary * _Nullable info) {
                    MSVMainTrackClip *clip = [MSVMainTrackClip mainTrackClipWithAnimatedImage:[UIImage sd_imageWithGIFData:imageData] error:&error];
//                    MSVMainTrackClip *clip = [MSVMainTrackClip mainTrackClipWithAnimatedImageData:imageData error:&error];
                    if (!error) {
                        if (CGSizeEqualToSize(renderSize, CGSizeZero)) {
                            renderSize = clip.defaultSize;
                        }
                        [clip resetGeometryWithVideoSize:renderSize scalingMode:scalingMode];
                        [mainTrackClips addObject:clip];
                    }
                    dispatch_semaphore_signal(semaphore);
                }];
            } else {
                [manager requestImageForAsset:asset targetSize:PHImageManagerMaximumSize contentMode:PHImageContentModeAspectFit options:option resultHandler:^(UIImage * _Nullable result, NSDictionary * _Nullable info) {
                    MSVMainTrackClip *clip = [MSVMainTrackClip mainTrackClipWithStillImage:result duration:3 * MovieousInnerTimeScale error:&error];
                    if (!error) {
                        if (CGSizeEqualToSize(renderSize, CGSizeZero)) {
                            renderSize = clip.defaultSize;
                        }
                        [clip resetGeometryWithVideoSize:renderSize scalingMode:scalingMode];
                        [mainTrackClips addObject:clip];
                    }
                    dispatch_semaphore_signal(semaphore);
                }];
            }
            dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
            if (error) {
                if (outError) {
                    *outError = error;
                }
                return nil;
            }
        }
    }
    return mainTrackClips;
}

+ (MSVMixTrackClip *)generateMixTrackClipWithAsset:(PHAsset *)asset videoSize:(CGSize)videoSize scalingMode:(MovieousScalingMode)scalingMode startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError **)outError {
    PHImageManager *manager = [PHImageManager defaultManager];
    __block MSVMixTrackClip *mixTrackClip = nil;
    __block NSError *error;
    __block CGSize renderSize = videoSize;
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    if (asset.mediaType == PHAssetMediaTypeVideo) {
        [manager requestAVAssetForVideo:asset options:nil resultHandler:^(AVAsset * _Nullable asset, AVAudioMix * _Nullable audioMix, NSDictionary * _Nullable info) {
            mixTrackClip = [MSVMixTrackClip mixTrackClipWithAsset:asset startTimeAtMainTrack:startTimeAtMainTrack error:&error];
            if (!error) {
                if (CGSizeEqualToSize(renderSize, CGSizeZero)) {
                    renderSize = mixTrackClip.defaultSize;
                }
                [mixTrackClip resetGeometryWithVideoSize:renderSize scalingMode:scalingMode];
            }
            dispatch_semaphore_signal(semaphore);
        }];
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
        if (error) {
            if (outError) {
                *outError = error;
            }
            return nil;
        }
    } else if (asset.mediaType == PHAssetMediaTypeImage) {
        PHImageRequestOptions *option = [PHImageRequestOptions new];
        option.deliveryMode = PHImageRequestOptionsDeliveryModeHighQualityFormat;
        option.resizeMode = PHImageRequestOptionsResizeModeNone;
        [manager requestImageForAsset:asset targetSize:PHImageManagerMaximumSize contentMode:PHImageContentModeAspectFit options:option resultHandler:^(UIImage * _Nullable result, NSDictionary * _Nullable info) {
            mixTrackClip = [MSVMixTrackClip mixTrackClipWithStillImage:result duration:3 * MovieousInnerTimeScale startTimeAtMainTrack:startTimeAtMainTrack error:&error];
            if (!error) {
                if (CGSizeEqualToSize(renderSize, CGSizeZero)) {
                    renderSize = mixTrackClip.defaultSize;
                }
                [mixTrackClip resetGeometryWithVideoSize:renderSize scalingMode:scalingMode];
            }
            dispatch_semaphore_signal(semaphore);
        }];
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
        if (error) {
            if (outError) {
                *outError = error;
            }
            return nil;
        }
    }
    return mixTrackClip;
}

@end
