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
#import <MovieousShortVideo/MSVTranscoder.h>
#import <MovieousShortVideo/MSVBrush.h>
#import <MovieousShortVideo/MSVGraffitiView.h>

/**
 * @brief This class contains common configurations
 */
@interface MovieousShortVideo : NSObject

/**
 * @brief Is `-registerWithLicense` been called before
 */
@property (nonatomic, assign, readonly, class) BOOL registered;

/**
 * @brief Register the SDK with license string
 * @param license The license string from Movieous team
 */
+ (void)registerWithLicense:(NSString *)license;

/**
 * @brief Return the auth state for the SDK
 */
+ (BOOL)checkAuthState;

@end
