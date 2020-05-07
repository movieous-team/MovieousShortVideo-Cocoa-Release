//
//  MSVDClipsAndEeffectsView.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/10.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSNotificationName const MSVDAddMainTrackClipButtonPressedNotification;
extern NSNotificationName const MSVDDidSelectClipOrEffectNotification;
extern NSNotificationName const MSVDDidSelectTransitionNotification;

@interface MSVDClipsAndEeffectsView : UIView

@property (nonatomic, strong, readonly) id<MSVClipOrEffect> selectedClipOrEffect;
@property (nonatomic, assign, readonly) NSInteger selectedMainTrackClipIndex;
@property (nonatomic, assign, readonly) NSInteger selectedMainTrackTransitionIndex;

- (instancetype)initWithEditor:(MSVEditor *)editor;
- (void)selectClipOrEffect:(id)clipOrEffect;

@end
