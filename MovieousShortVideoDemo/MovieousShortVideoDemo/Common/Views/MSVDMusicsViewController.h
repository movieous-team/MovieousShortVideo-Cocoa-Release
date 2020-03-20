//
//  MSVDMusicsViewController.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MSVDMusicsLibrary.h"

NS_ASSUME_NONNULL_BEGIN

@class MSVDMusicsViewController;
@protocol MSVDMusicsViewControllerDelegate <NSObject>

- (void)musicsViewController:(MSVDMusicsViewController *)musicsViewController didSelectMusic:(MSVDMusic *)music;

@end

@interface MSVDMusicsViewController : UIViewController

@property (nonatomic, weak) id<MSVDMusicsViewControllerDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
