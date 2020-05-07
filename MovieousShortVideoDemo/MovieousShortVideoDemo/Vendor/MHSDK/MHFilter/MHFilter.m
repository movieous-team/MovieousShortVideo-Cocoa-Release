//
//  MHFilter.m
//  MovieousDemo
//
//  Created by apple on 2020/1/6.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MHFilter.h"

@implementation MHFilter

- (CVPixelBufferRef)externalFilterCaptureEffect:(MovieousExternalFilterCaptureEffect *)externalFilterCaptureEffect shouldProcessPixelBuffer:(CVPixelBufferRef)pixelBuffer time:(MovieousTime)time {
    pixelBuffer = [self.beautyManager processPixelBuffer:pixelBuffer sampleTimingInfo:(CMSampleTimingInfo){kCMTimeZero, CMTimeMakeWithMovieousTime(time), kCMTimeZero}];
    return pixelBuffer;
}

@end
