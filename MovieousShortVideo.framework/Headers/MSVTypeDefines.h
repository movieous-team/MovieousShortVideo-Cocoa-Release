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
 * 视频输入源类型。
 */
typedef NS_ENUM(NSInteger, MSVVideoSource) {
    /**
     * 无视频源，请不要同时将视频和音频源设置为无。
     */
    MSVVideoSourceNone,
    /**
     * 摄像头视频源。
     */
    MSVVideoSourceCamera,
    /**
     * UIView 输入源，当你使用此输入源时，请在 `startRecordingWithClipConfiguration:error:` 调用时指定 `viewForRecording` 属性。
     */
    MSVVideoSourceUIView,
    /**
     * 外部视频源
     *
     * @warning 当你使用此输入源时，请使用 `writeVideoData:error:` 方法来写入视频数据，如果你使用 MSVVideoSourceExtern 但是又不写入视频数据，未知的错误将会产生。
     */
    MSVVideoSourceExtern,
};

/**
 * 音频输入源。
 */
typedef NS_ENUM(NSInteger, MSVAudioSource) {
    /**
     * 无音频输入源，请不要同时将视频和音频源设置为无。
     */
    MSVAudioSourceNone,
    /**
     * 麦克风音频输入源。
     */
    MSVAudioSourceMicrophone,
    /**
     * 外部音频输入源。
     *
     * @warning 当你使用此输入源时，请使用 `writeAudioData:error:` 方法来写入音频数据，如果你使用 MSVAudioSourceExtern 但是又不写入音频数据，未知的错误将会产生。
     */
    MSVAudioSourceExtern,
};

#pragma mark - Video File Type

/**
 * 录制的目标文件类型。
 */
typedef NS_ENUM(NSUInteger, MSVFileType) {
    /**
     * QuickTime Movie 文件类型，以 .mov 为后缀。
     */
    MSVFileTypeQuickTimeMovie,
    /**
     * mp4 文件类型，以 .mp4 为后缀。
     */
    MSVFileTypeMPEG4,
    /**
     * M4V 文件类型，以 .m4v 为后缀。
     */
    MSVFileTypeAppleM4V,
    /**
     * M4A 文件类型，以 .m4a 为后缀，仅支持音频。
     */
    MSVFileTypeAppleM4A
};

/**
 * 视频转场类型。
 */
typedef NS_ENUM(NSInteger, MSVVideoTransitionType) {
    /**
     * 溶解转场。
     */
    MSVVideoTransitionTypeDissolve,
    /**
     * 向右扫动转场。
     */
    MSVVideoTransitionTypeWipeRight,
    /**
     * 向左扫动转场。
     */
    MSVVideoTransitionTypeWipeLeft,
    /**
     * 向上扫动转场。
     */
    MSVVideoTransitionTypeWipeUp,
    /**
     * 向下扫动转场。
     */
    MSVVideoTransitionTypeWipeDown,
    /**
     * 向右滑动转场。
     */
    MSVVideoTransitionTypeSlideRight,
    /**
     * 向左滑动转场。
     */
    MSVVideoTransitionTypeSlideLeft,
    /**
     * 向上滑动转场。
     */
    MSVVideoTransitionTypeSlideUp,
    /**
     * 向下滑动转场。
     */
    MSVVideoTransitionTypeSlideDown,
    /**
     * 渐隐渐现转场。
     */
    MSVVideoTransitionTypeFade
};

/**
 * 媒体片段的类型。
 */
typedef NS_ENUM(NSInteger, MSVClipType) {
    /**
     * 音视频媒体类型的片段。
     */
    MSVClipTypeAV,
    /**
     * 图片类型的片段。
     */
    MSVClipTypeImage
};

/**
 * Notify that the media service has reset, you should do neccessary restart on your audio services.
 */
extern NSString *kMediaServiceResetNotification;
