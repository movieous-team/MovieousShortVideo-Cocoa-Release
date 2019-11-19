//
//  MSVTypeDefines.h
//  MSVShortVideoKit
//
//  Created by Chris Wang on 18/3/1.
//  Copyright © 2018年 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 * Video input souce type.
 */
typedef NS_ENUM(NSInteger, MSVVideoSource) {
    /**
     * No video，please don't set both video source and audio source to none.
     */
    MSVVideoSourceNone,
    /**
     * Camera input source.
     */
    MSVVideoSourceCamera,
    /**
     * UIView input source, when you use this input source please specify viewForRecording property in `startRecordingWithClipConfiguration:error:` method.
     */
    MSVVideoSourceUIView,
    /**
     * External video source.
     *
     * @warning When you use this input source, please use `writeVideoData:error:` to write video data, if you choose external video source but don't input video data, unknown error may come out.
     */
    MSVVideoSourceExtern,
};

/**
 * Audio input source
 */
typedef NS_ENUM(NSInteger, MSVAudioSource) {
    /**
     * No audio，please don't set both video source and audio source to none.
     */
    MSVAudioSourceNone,
    /**
     * Microphone input source.
     */
    MSVAudioSourceMicrophone,
    /**
     * External input source.
     *
     * @warning You must use `writeAudioData:error:` method to input audio data when use this input source, if you choose external audio source but don't input audio data, unknown error may come out.
     */
    MSVAudioSourceExtern,
};

#pragma mark - Video File Type

/**
 * Destination file type for recording.
 */
typedef NS_ENUM(NSUInteger, MSVFileType) {
    /**
     * QuickTime Movie file type，suffixed .mov.
     */
    MSVFileTypeQuickTimeMovie,
    /**
     * mp4 file type，suffixed .mp4.
     */
    MSVFileTypeMPEG4,
    /**
     * m4v file type，suffixed .m4v.
     */
    MSVFileTypeAppleM4V,
    /**
     * m4a file type，suffixed .m4a, audio only.
     */
    MSVFileTypeAppleM4A
};

/**
 * Video transition type.
 */
typedef NS_ENUM(NSInteger, MSVVideoTransitionType) {
    /**
     * Dissolve transition type.
     */
    MSVVideoTransitionTypeDissolve,
    /**
     * Wipe right transition type.
     */
    MSVVideoTransitionTypeWipeRight,
    /**
     * Wipe left transition type.
     */
    MSVVideoTransitionTypeWipeLeft,
    /**
     * Wipe up transition type.
     */
    MSVVideoTransitionTypeWipeUp,
    /**
     * Wipe down transition type.
     */
    MSVVideoTransitionTypeWipeDown,
    /**
     * Slide right transition type.
     */
    MSVVideoTransitionTypeSlideRight,
    /**
     * Slide left transition type.
     */
    MSVVideoTransitionTypeSlideLeft,
    /**
     * Slide up transition type.
     */
    MSVVideoTransitionTypeSlideUp,
    /**
     * Slide down transition type.
     */
    MSVVideoTransitionTypeSlideDown,
    /**
     * Fade transition type.
     */
    MSVVideoTransitionTypeFade
};

/**
 * Type of a clip.
 */
typedef NS_ENUM(NSInteger, MSVClipType) {
    /**
     * Audio and video media resource type.
     */
    MSVClipTypeAV,
    /**
     * Image resource type.
     */
    MSVClipTypeImage
};

/**
 * Notify that the media service has reset, you should do neccessary restart on your audio services.
 */
extern NSString *kMediaServiceResetNotification;
