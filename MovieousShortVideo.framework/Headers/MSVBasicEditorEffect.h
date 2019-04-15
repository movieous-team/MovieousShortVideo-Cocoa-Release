//
//  MSVBasicEditorEffect.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/2/22.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <MovieousBase/MovieousBase.h>

@protocol MSVBasicEditorEffect
<
NSObject
>

@required

/**
 * @brief User-defined ID field, business usage is used to distinguish objects
 */
@property (nonatomic, strong) NSString *ID;

/**
 * @brief The time interval for applying an basic effect on the main track
 */
@property (nonatomic, assign) MovieousTimeRange timeRangeAtMainTrack;

@end
