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
 * Video input souce type
 */
typedef NS_ENUM(NSInteger, MSVVideoSource) {
    /**
     * @brief No video，please don't set both video source and audio source to none.
     */
    MSVVideoSourceNone,
    /**
     * @brief Camera input source
     */
    MSVVideoSourceCamera,
    /**
     * @brief UIView input source, when you use this input source please specify viewForRecording property in `startRecordingWithClipConfiguration:error:` method
     */
    MSVVideoSourceUIView,
    /**
     * @brief External video source
     * @warning When you use this input source, please use `writeVideoData:error:` to write video data, if you choose external video source but don't input video data, unknown error may come out
     */
    MSVVideoSourceExtern,
};

/**
 * @brief Audio input source
 */
typedef NS_ENUM(NSInteger, MSVAudioSource) {
    /**
     * @brief No audio，please don't set both video source and audio source to none.
     */
    MSVAudioSourceNone,
    /**
     * @brief Microphone input source.
     */
    MSVAudioSourceMicrophone,
    /**
     * @brief External input source
     * @warning You must use `writeAudioData:error:` method to input audio data when use this input source, if you choose external audio source but don't input audio data, unknown error may come out
     */
    MSVAudioSourceExtern,
};

/**
 * @brief Orientation of preview
 */
typedef NS_ENUM(NSInteger, MSVPreviewOrientation) {
    /**
     * @brief Portrait orientation
     */
    MSVPreviewOrientationPortrait = 0,
    /**
     * @brief Upside down orientation
     */
    MSVPreviewOrientationPortraitUpsideDown = 1,
    /**
     * @brief LandscapeRight orientation
     */
    MSVPreviewOrientationLandscapeRight = 2,
    /**
     * @brief LandscapeLeft orientation
     */
    MSVPreviewOrientationLandscapeLeft = 3,
};

#pragma mark - Video File Type

/**
 * @brief Destination file type for recording
 */
typedef NS_ENUM(NSUInteger, MSVFileType) {
    /**
     * @brief mp4 file type，suffixed .mp4
     */
    MSVFileTypeMPEG4,
    /**
     * @brief QuickTime Movie file type，suffixed .mov
     */
    MSVFileTypeQuickTimeMovie, // .mov
    /**
     * @brief m4a file type，suffixed .m4a
     */
    MSVFileTypeM4V, // .m4v
};

/**
 * @brief Video transition type
 */
typedef NS_ENUM(NSInteger, MSVVideoTransitionType) {
    /**
     * @brief Dissolve transition type
     */
    MSVVideoTransitionTypeDissolve,
    /**
     * @brief Wipe right transition type
     */
    MSVVideoTransitionTypeWipeRight,
    /**
     * @brief Wipe left transition type
     */
    MSVVideoTransitionTypeWipeLeft,
    /**
     * @brief Wipe up transition type
     */
    MSVVideoTransitionTypeWipeUp,
    /**
     * @brief Wipe down transition type
     */
    MSVVideoTransitionTypeWipeDown,
    /**
     * @brief Slide right transition type
     */
    MSVVideoTransitionTypeSlideRight,
    /**
     * @brief Slide left transition type
     */
    MSVVideoTransitionTypeSlideLeft,
    /**
     * @brief Slide up transition type
     */
    MSVVideoTransitionTypeSlideUp,
    /**
     * @brief Slide down transition type
     */
    MSVVideoTransitionTypeSlideDown,
    /**
     * @brief Fade transition type
     */
    MSVVideoTransitionTypeFade
};

/**
 * @brief Type of a clip
 */
typedef NS_ENUM(NSInteger, MSVClipType) {
    /**
     * Audio and video media resource type
     */
    MSVClipTypeAV,
    /**
     * Image resource type
     */
    MSVClipTypeImage
};

/**
 * @brief The effective scope for MSVTimeEffect
 */
typedef NS_ENUM(NSInteger, MSVTimeEffectScope) {
    /**
     * @brief The effective scope is main track
     */
    MSVTimeEffectScopeMainTracks = 1 << 0,
    /**
     * @brief The effective scope is mix track
     */
    MSVTimeEffectScopeMixTracks = 1 << 1,
    /**
     * @brief The effective scope is all track
     */
    MSVTimeEffectScopeAllTracks = MSVTimeEffectScopeMainTracks | MSVTimeEffectScopeMixTracks,
};

/**
 * @brief Notify that the media service has reset, you should do neccessary restart on your audio services;
 */
extern NSString *kMediaServiceResetNotification;
