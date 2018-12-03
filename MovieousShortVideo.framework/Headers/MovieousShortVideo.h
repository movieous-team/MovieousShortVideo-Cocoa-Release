//
//  MovieousShortVideo.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/11.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for MovieousShortVideo.
FOUNDATION_EXPORT double MovieousShortVideoVersionNumber;

//! Project version string for MovieousShortVideo.
FOUNDATION_EXPORT const unsigned char MovieousShortVideoVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <MovieousShortVideo/PublicHeader.h>

#import <MovieousShortVideo/MSVRecorder.h>
#import <MovieousShortVideo/MSVEditor.h>
#import <MovieousShortVideo/MSVVideoExporter.h>
#import <MovieousShortVideo/MSVRepeatEffect.h>
#import <MovieousShortVideo/MSVSpeedEffect.h>

@interface MovieousShortVideo : NSObject

@property (nonatomic, assign, readonly, class) BOOL registered;

+ (void)registerWithLicense:(NSString *)license;

+ (BOOL)checkAuthState;

@end
