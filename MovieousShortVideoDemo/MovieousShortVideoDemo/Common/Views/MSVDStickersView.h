//
//  MSVDStickersView.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/3/1.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MSVDStickersLibrary.h"

NS_ASSUME_NONNULL_BEGIN

extern NSNotificationName const MSVDStickersViewSelectStickerNotification;
extern NSNotificationName const MSVDStickersViewDoneNotification;
extern NSString *const MSVDStickersViewSelectedStickerKey;

@interface MSVDStickersView : UIView

@end

NS_ASSUME_NONNULL_END
