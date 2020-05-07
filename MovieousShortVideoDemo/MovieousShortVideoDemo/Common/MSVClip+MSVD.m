//
//  MSVClip+MSVD.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/23.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVClip+MSVD.h"

@implementation MSVClip(MSVD)

- (BOOL)isSameSourceWithClip:(MSVClip *)clip {
    if (self.path) {
        if ([self.path isEqualToString:clip.path]) {
            return YES;
        }
    } else if (self.asset) {
        if (self.asset == clip.asset) {
            return YES;
        }
        if ([self.asset isKindOfClass:AVURLAsset.class] && [clip.asset isKindOfClass:AVURLAsset.class]) {
            if (((AVURLAsset *)self.asset).URL.absoluteString && [((AVURLAsset *)self.asset).URL.absoluteString isEqualToString:((AVURLAsset *)clip.asset).URL.absoluteString]) {
                return YES;
            }
        }
    }
    return NO;
}

@end
