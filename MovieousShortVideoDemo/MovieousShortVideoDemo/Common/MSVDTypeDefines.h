//
//  MSVDTypeDefines.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/29.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
#define MSVDSnapshotBarKey  @"MSVDSnapshotBarKey"

#define MinDurationPerClip  1

extern NSNotificationName const MSVDErrorNotification;
extern NSString *const MSVDErrorKey;

extern NSNotificationName const MSVDMusicDidUpdatedNotification;
extern NSNotificationName const MSVDMusicsLibraryRefreshDoneNotification;

extern NSNotificationName const MSVDStickerUpdatedNotification;
extern NSNotificationName const MSVDStickersLibraryUpdatedNotification;

extern NSNotificationName const MSVDAddMainTrackClipButtonPressedNotification;

extern NSNotificationName const MSVDDidSelectClipOrEffectNotification;
extern NSNotificationName const MSVDDidDeselectClipOrEffectNotification;

extern NSNotificationName const MSVDToolboxViewToolSelectedNotification;
extern NSNotificationName const MSVDToolboxViewChangeToToolboxNotification;
extern NSString *const MSVDToolboxViewSelectedToolKey;
extern NSString *const MSVDToolboxViewToolboxConfigurationKey;

extern NSNotificationName const MSVDStickersViewSelectStickerNotification;
extern NSString *const MSVDStickersViewSelectedStickerKey;

NS_ASSUME_NONNULL_END
