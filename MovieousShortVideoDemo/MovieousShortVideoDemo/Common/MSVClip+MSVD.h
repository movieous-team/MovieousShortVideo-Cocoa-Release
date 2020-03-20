//
//  MSVClip+MSVD.h
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/23.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import <MovieousShortVideo/MovieousShortVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface MSVClip(MSVD)

- (BOOL)isSameSourceWithClip:(MSVClip *)clip;

@end

NS_ASSUME_NONNULL_END
