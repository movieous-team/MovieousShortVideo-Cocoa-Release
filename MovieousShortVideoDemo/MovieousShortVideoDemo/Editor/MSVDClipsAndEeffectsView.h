//
//  MSVDClipsAndEeffectsView.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/10.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVDClipsAndEeffectsView : UIView

@property (nonatomic, strong) id selectedClipOrEffect;

- (instancetype)initWithEditor:(MSVEditor *)editor;
- (void)deselectClipOrEffect;

@end

NS_ASSUME_NONNULL_END
