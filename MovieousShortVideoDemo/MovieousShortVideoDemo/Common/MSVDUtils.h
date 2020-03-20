//
//  MSVDUtils.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/21.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <TZImagePickerController/TZImagePickerController.h>

NS_ASSUME_NONNULL_BEGIN

void MSVDRunSynchronouslyOnMainQueue(void (^block)(void));
void MSVDRunAsynchronouslyOnMainQueue(void (^block)(void));
NSString *MSVDGetLocalMusicsDir(void);
NSString *MSVDGetLocalStickersDir(void);
NSString *MSVDGetServerHost(void);
NSError *MSVDGenerateError(NSInteger code, NSString *fmt, ...);
CGSize MSVDGetFitSize(CGSize size, CGFloat longSide, CGFloat shortSide);
NSArray<NSString *> *sortAnimatedImagePaths(NSArray<NSString *> * imagePaths);

@interface MSVDUtils : NSObject

+ (NSString *)formatTimeInterval:(MovieousTime)timeInterval;
+ (TZImagePickerController *)generateImagePickerControllerWithDelegate:(id<TZImagePickerControllerDelegate>)delegate maxImagesCount:(NSInteger)maxImagesCount;
+ (NSMutableArray<MSVMainTrackClip *> *)generateMainTrackClipsWithAssets:(NSArray<PHAsset *> *)assets videoSize:(CGSize)videoSize scalingMode:(MovieousScalingMode)scalingMode error:(NSError **)outError;
+ (MSVMixTrackClip *)generateMixTrackClipWithAsset:(PHAsset *)asset videoSize:(CGSize)videoSize scalingMode:(MovieousScalingMode)scalingMode startTimeAtMainTrack:(MovieousTime)startTimeAtMainTrack error:(NSError **)outError;

@end

NS_ASSUME_NONNULL_END
