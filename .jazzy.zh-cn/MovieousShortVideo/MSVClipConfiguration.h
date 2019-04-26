//
//  MSVRecordingConfiguration.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/29.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MSVTypeDefines.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Recorder clip configuration class, used to configure current recording clip.
 */
@interface MSVClipConfiguration : NSObject

/**
 * Clip file URL, the default is auto generated URL.
 */
@property (nonatomic, strong) NSURL *URL;

/**
 * Media file type of the clip to be recorded, the default is MSVFileTypeMPEG4.
 */
@property (nonatomic, assign) MSVFileType fileType;

/**
 * Clip speed of the clip to be recorded, the default is 1.0.
 *
 * @discussion
 * Recommend configurations:
 * very fast：2.0.
 * fast：1.5.
 * normal：1.0.
 * slow：0.75.
 * very slow：0.5.
 */
@property (nonatomic, assign) CGFloat speed;

/**
 * Original sound volume of the clip to be recorded.
 * The default is 1.
 */
@property (nonatomic, assign) float volume;

/**
 * View used for recording, only valid when videoConfiguration.source = MSVVideoSourceUIView.
 * The default is nil.
 */
@property (nonatomic, strong) UIView *viewForRecording;

/**
 * Create a default configuration instance
 * 
 * @return Created instance
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
