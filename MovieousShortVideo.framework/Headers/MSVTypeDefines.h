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
 * @brief Action to take when enter background
 */
typedef NS_ENUM(NSInteger, MSVBackgroundAction) {
    /**
     * @brief Take no action, caller is responsible to take right actions such as cancel or finish recording current clip
     */
    MSVBackgroundActionContinue,
    /**
     * @brief Finish and save clip being recording when enter background
     */
    MSVBackgroundActionFinish,
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

#pragma mark - Audio SampleRate

/**
 * @brief Audio sample rate
 */
typedef NS_ENUM(NSUInteger, MSVAudioSampleRate) {
    /**
     * @brief 48000Hz sample rate
     */
    MSVAudioSampleRate_48000Hz = 48000,
    /**
     * @brief 44100Hz sample rate
     */
    MSVAudioSampleRate_44100Hz = 44100,
    /**
     * @brief 22050Hz sample rate
     */
    MSVAudioSampleRate_22050Hz = 22050,
    /**
     * @brief 11025Hz sample rate
     */
    MSVAudioSampleRate_11025Hz = 11025,
};

#pragma mark - Audio BitRate

/**
 * @brief Audio bitrate
 */

typedef NS_ENUM(NSInteger, MSVAudioBitRate) {
    /**
     * @brief 64Kbps bitrate
     */
    MSVAudioBitRate_64Kbps = 64000,
    /**
     * @brief 96Kbps bitrate
     */
    MSVAudioBitRate_96Kbps = 96000,
    /**
     * @brief 128Kbps bitrate
     */
    MSVAudioBitRate_128Kbps = 128000,
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
    MSVFileTypeM4A, // .m4a
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
