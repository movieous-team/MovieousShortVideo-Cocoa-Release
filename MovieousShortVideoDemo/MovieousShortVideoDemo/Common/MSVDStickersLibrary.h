//
//  MSVDStickersLibrary.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, MSVDStickerType) {
    MSVDStickerTypeImage = 0b001,
    MSVDStickerTypeGif = 0b010,
    MSVDStickerTypeImages = 0b100,
    MSVDStickerTypeAll = MSVDStickerTypeImage | MSVDStickerTypeGif | MSVDStickerTypeImages,
};

extern NSNotificationName const MSVDStickerUpdatedNotification;
extern NSNotificationName const MSVDStickersLibraryUpdatedNotification;

@interface MSVDSticker : NSObject

@property (nonatomic, strong) NSURL *sourceURL;
@property (nonatomic, strong) NSURL *thumbnailURL;
@property (nonatomic, assign) MSVDStickerType type;
@property (nonatomic, strong) NSMutableArray<NSString *> *localPaths;
@property (nonatomic, assign) BOOL downloading;
@property (nonatomic, assign) float progress;

- (void)download;

@end

@interface MSVDStickersLibrary : NSObject

@property (nonatomic, strong, readonly, class) NSMutableArray<MSVDSticker *> *stickers;

+ (void)refresh;

@end

NS_ASSUME_NONNULL_END
