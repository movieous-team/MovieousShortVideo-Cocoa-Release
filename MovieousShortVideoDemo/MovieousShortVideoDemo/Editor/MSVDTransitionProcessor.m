//
//  MSVDTransitionProcessor.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/19.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDTransitionProcessor.h"

@implementation MSVDTransitionProcessor

- (CVPixelBufferRef)processWithTransition:(MSVExternalMainTrackTransition *)transition disappearingPixelBuffer:(CVPixelBufferRef)disappearingPixelBuffer appearingPixelBuffer:(CVPixelBufferRef)appearingPixelBuffer time:(MovieousTime)time transitionTimeRange:(MovieousTimeRange)transitionTimeRange {
    return disappearingPixelBuffer;
}

@end
