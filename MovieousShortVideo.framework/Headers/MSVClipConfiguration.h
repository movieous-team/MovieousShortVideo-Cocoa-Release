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
 * Recorder clip configuration class, used to configure current recording clip
 */
@interface MSVClipConfiguration : NSObject

/**
 * @brief Clip file URL, default to auto generated URL
 */
@property (nonatomic, strong) NSURL *URL;

/**
 * @brief Media file type of the clip to be recorded, default to MSVFileTypeMPEG4
 */
@property (nonatomic, assign) MSVFileType fileType;

/**
 * @brief Clip speed of the clip to be recorded, default to 1.0
 * Recommend configurations:
 * very fast：2.0
 * fast：1.5
 * normal：1.0
 * slow：0.75
 * very slow：0.5
 */
@property (nonatomic, assign) CGFloat speed;

/**
 * @brief Original sound volume of the clip to be recorded, default to 1.0
 */
@property (nonatomic, assign) float volume;

/**
 * @brief View used for recording, only valid when videoConfiguration.source = MSVVideoSourceUIView
 * Default to nil
 */
@property (nonatomic, strong) UIView *viewForRecording;

/**
 * @brief Create a default configuration instance
 * @return Created instance
 */
+ (instancetype)defaultConfiguration;

@end

NS_ASSUME_NONNULL_END
