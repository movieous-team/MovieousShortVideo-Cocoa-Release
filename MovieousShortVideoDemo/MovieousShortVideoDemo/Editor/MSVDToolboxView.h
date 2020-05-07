//
//  MSVDToolboxView.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/10.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousShortVideo/MovieousShortVideo.h>

NS_ASSUME_NONNULL_BEGIN

extern NSNotificationName const MSVDToolboxViewToolSelectedNotification;
extern NSNotificationName const MSVDToolboxViewChangeToToolboxNotification;
extern NSNotificationName const MSVDToolboxViewSelectedClipGeoUpdatedNotification;
extern NSNotificationName const MSVDToolboxViewShouldSelectClipOrEffectNotification;
extern NSString *const MSVDToolboxViewSelectedToolKey;
extern NSString *const MSVDToolboxViewConfigurationKey;
extern NSString *const MSVDToolboxViewClipOrEffectKey;

@interface MSVDToolboxView : UIView

- (instancetype)initWithEditor:(MSVEditor *)editor;

@end

NS_ASSUME_NONNULL_END
