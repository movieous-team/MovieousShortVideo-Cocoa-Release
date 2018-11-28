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
 * 视频输入源类型
 */
typedef NS_ENUM(NSInteger, MSVVideoSource) {
    /**
     * @brief 不录制视频，请不要同时使 video source 和 audio source 都为 none
     */
    MSVVideoSourceNone,
    /**
     * @brief 摄像头输入源
     */
    MSVVideoSourceCamera,
    /**
     * @brief UIView 输入源，当使用此输入源时请在 MSVRecorder 的 `startRecordingWithClipConfiguration:error:` 中指定 viewForRecording 对象
     */
    MSVVideoSourceUIView,
    /**
     * @brief 外部视频源
     * @warning 使用此输入源时请使用 `writeVideoData:error:` 方法输入视频数据，如果选择外部数据源又不导入视频会导致未知问题
     */
    MSVVideoSourceExtern,
};

/**
 * @brief 音频输入源类型
 */
typedef NS_ENUM(NSInteger, MSVAudioSource) {
    /**
    * @brief 不录制音频，请不要同时使 video source 和 audio source 都为 none
     */
    MSVAudioSourceNone,
    /**
     * @brief 麦克风输入源
     */
    MSVAudioSourceMicrophone,
    /**
     * @brief 外部输入源
     * @warning 使用此输入源时请使用 `writeAudioData:error:` 方法输入音频数据，如果选择外部数据源又不导入视频会导致未知问题
     */
    MSVAudioSourceExtern,
};

/**
 * @brief 录制进入后台时采取的操作类型
 */
typedef NS_ENUM(NSInteger, MSVBackgroundAction) {
    /**
     * @brief 退出到后台之后不做任何操作，调用者需要负责进行正确的操作，一般是取消或结束当前片段的录制
     */
    MSVBackgroundActionContinue,
    /**
     * @brief 退出到后台之后结束并保存当前录制的片段
     */
    MSVBackgroundActionFinish,
};

/**
 * @brief 预览视图的方向
 */
typedef NS_ENUM(NSInteger, MSVPreviewOrientation) {
    /**
     * @brief 正立方向
     */
    MSVPreviewOrientationPortrait = 0,
    /**
     * @brief 倒立方向
     */
    MSVPreviewOrientationPortraitUpsideDown = 1,
    /**
     * @brief 横置并且 Home 键位于右侧
     */
    MSVPreviewOrientationLandscapeRight = 2,
    /**
     * @brief 横置并且 Home 键位于左侧
     */
    MSVPreviewOrientationLandscapeLeft = 3,
};

#pragma mark - Audio SampleRate

/**
 * @brief 音频编码采样率
 */
typedef NS_ENUM(NSUInteger, MSVAudioSampleRate) {
    /**
     * @brief 48000Hz 音频编码采样率
     */
    MSVAudioSampleRate_48000Hz = 48000,
    /**
     * @brief 44100Hz 音频编码采样率
     */
    MSVAudioSampleRate_44100Hz = 44100,
    /**
     * @brief 22050Hz 音频编码采样率
     */
    MSVAudioSampleRate_22050Hz = 22050,
    /**
     * @brief 11025Hz 音频编码采样率
     */
    MSVAudioSampleRate_11025Hz = 11025,
};

#pragma mark - Audio BitRate

/**
 * @brief 音频编码码率
 */

typedef NS_ENUM(NSInteger, MSVAudioBitRate) {
    /**
     * @brief 64Kbps 音频码率
     */
    MSVAudioBitRate_64Kbps = 64000,
    /**
     * @brief 96Kbps 音频码率
     */
    MSVAudioBitRate_96Kbps = 96000,
    /**
     * @brief 128Kbps 音频码率
     */
    MSVAudioBitRate_128Kbps = 128000,
};

#pragma mark - Video File Type

/**
 * @brief 录制目标文件类型
 */
typedef NS_ENUM(NSUInteger, MSVFileType) {
    /**
     * @brief mp4 文件，一般以 .mp4 为后缀
     */
    MSVFileTypeMPEG4,
    /**
     * @brief QuickTime Movie 文件，一般以 .mov 为后缀
     */
    MSVFileTypeQuickTimeMovie, // .mov
    /**
     * @brief m4a 文件，一般以 .m4a 为后缀
     */
    MSVFileTypeM4A, // .m4a
};

/**
 * @brief 视频转场类型
 */
typedef NS_ENUM(NSInteger, MSVVideoTransitionType) {
    /**
     * @brief 溶解转场效果
     */
    MSVVideoTransitionTypeDissolve,
    /**
     * @brief 向右扫入转场效果
     */
    MSVVideoTransitionTypeWipeRight,
    /**
     * @brief 向左扫入转场效果
     */
    MSVVideoTransitionTypeWipeLeft,
    /**
     * @brief 向上扫入转场效果
     */
    MSVVideoTransitionTypeWipeUp,
    /**
     * @brief 向下扫入转场效果
     */
    MSVVideoTransitionTypeWipeDown,
    /**
     * @brief 向右划入转场效果
     */
    MSVVideoTransitionTypeSlideRight,
    /**
     * @brief 向左划入转场效果
     */
    MSVVideoTransitionTypeSlideLeft,
    /**
     * @brief 向上划入转场效果
     */
    MSVVideoTransitionTypeSlideUp,
    /**
     * @brief 向下划入转场效果
     */
    MSVVideoTransitionTypeSlideDown,
    /**
     * @brief 渐隐渐现转场效果
     */
    MSVVideoTransitionTypeFade
};
