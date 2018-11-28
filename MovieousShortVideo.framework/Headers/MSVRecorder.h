//
//  MSVRecorder.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2018/9/26.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>
#import <AVFoundation/AVFoundation.h>
#import "MSVRecorderAudioConfiguration.h"
#import "MSVRecorderVideoConfiguration.h"
#import "MSVClipConfiguration.h"
#import "MSVClip.h"
#import "MSVMainTrackClip.h"
#import "MSVDraft.h"
#import "MSVBackgroundAudioConfiguration.h"
#import "MSVExternalFilter.h"

@class MSVRecorder;

/**
 * @brief 录制器代理接口
 */
@protocol MSVRecorderDelegate <NSObject>

@optional
/**
 * @brief 当用户点击预览界面对焦时回调
 * @param recorder 产生事件的录制器对象
 * @param point 用户点击的位置
 */
- (void)recorder:(MSVRecorder *)recorder didFocusAtPoint:(CGPoint)point;

/**
 * @brief 录制器到达配置的最大时长
 * @param recorder 产生事件的录制器对象
 */
- (void)recorderDidReachMaxDuration:(MSVRecorder *)recorder;

/**
 * @brief 录制器播放背景音乐时发生错误
 * @param recorder 产生事件的录制器对象
 * @param error 产生的具体错误
 */
- (void)recorder:(MSVRecorder *)recorder didPlayBackgroundAudioError:(NSError *)error;

/**
 * @brief 当前录制片段的时长发生更新的回调，调用者可以在此回调当中更新 UI 反馈录制进度
 * @param recorder 产生事件的录制器对象
 * @param currentClipDuration 当前片段的时长
 */
- (void)recorder:(MSVRecorder *)recorder currentClipDurationDidUpdated:(NSTimeInterval)currentClipDuration;

/**
 * @brief 摄像头获取到视频数据的回调，调用者可以实现该方法来对视频数据进行自定义处理，处理后的数据将会反馈在预览图像并编码到生成的片段当中
 * @param recorder 产生事件的录制器对象
 * @param pixelBuffer 待处理的视频数据
 * @return 处理完成的视频数据
 */
- (CVPixelBufferRef)recorder:(MSVRecorder *)recorder didGetPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

/**
 * @brief 录制器
 */
@interface MSVRecorder : NSObject

/**
 * @brief Recorder 自动生成的草稿对象，可以通过此属性获取草稿对象用于编辑或导出
 */
@property (nonatomic, strong, readonly) MSVDraft *draft;

/**
 * @brief 视频参数配置对象
 * @warning 请不要修改获取到的 videoConfiguration 对象，否则会出现未定义的错误，更新参数请使用相关运行时属性更新接口或销毁当前 Recorder 重新生成
 */
@property (nonatomic, strong, readonly) MSVRecorderVideoConfiguration *videoConfiguration;

/**
 * @brief 音频参数配置对象
 * @warning 请不要修改获取到的 videoConfiguration 对象，否则会出现未定义的错误，更新参数请使用相关运行时属性更新接口或销毁当前 Recorder 重新生成
 */
@property (nonatomic, strong, readonly) MSVRecorderAudioConfiguration *audioConfiguration;

/**
 * @brief 当前片段已经录制的时间长度
 */
@property (nonatomic, assign, readonly) NSTimeInterval currentClipDuration;

/**
 * @brief 所有已经保存的片段的时间长度
 */
@property (nonatomic, assign, readonly) NSTimeInterval recordedClipsDuration;

/**
 * @brief 最大的录制长度，这里的录制长度指的是所有片段长度的总和，当录制长度到达最大值时，delegate 的 `recorderDidReachMaxDuration` 方法将被调用，如果该值小于或等于 0 则表示没有最大长度限制
 */
@property (nonatomic, assign) NSTimeInterval maxDuration;

/**
 * @brief 预览视图
 */
@property (nonatomic, strong, readonly) UIView *preview;

/**
 * @brief 代理对象，用于接收事件回调
 */
@property (nonatomic, weak) id<MSVRecorderDelegate> delegate;

/**
 * @brief 代理方法回调使用的队列，如果未指定将在主线程回调
 */
@property (nonatomic, strong) dispatch_queue_t delegateQueue;

/**
 * @brief 当预览视窗与配置的 videoSize 比例不一致时使用的填充模式，默认为 MovieousScalingModeAspectFit
 */
@property (nonatomic, assign) MovieousScalingMode previewScalingMode;

/**
 * @brief 当前是否处于正在录制的状态
 */
@property (nonatomic, assign) BOOL recording;

/**
 * @brief 是否对前置摄像头预览进行镜像处理，默认为 YES
 */
@property (nonatomic, assign) BOOL mirrorFrontPreview;

/**
 * @brief 是否对后置摄像头预览进行镜像处理，默认为 NO
 */
@property (nonatomic, assign) BOOL mirrorBackPreview;

/**
 * @brief 是否对前置摄像头编码的视频进行镜像处理，默认为 NO
 */
@property (nonatomic, assign) BOOL mirrorFrontEncoded;

/**
 * @brief 是否对后置摄像头编码的视频进行镜像处理，默认为 NO
 */
@property (nonatomic, assign) BOOL mirrorBackEncoded;

/**
 * @brief 是否开启内部的聚焦视图，默认为 NO
 */
@property (nonatomic, assign) BOOL innerFocusView;

/**
 * @brief 获取截图
 */
@property (nonatomic, strong, readonly) UIImage *snapshot;

/**
 * @brief 录制进入后台时自动采取的操作，如果不自动进行操作那调用方需要自行进行适当的处理（完成或取消当前片段的录制），默认为 MSVBackgroundActionContinue
 */
@property (nonatomic, assign) MSVBackgroundAction backgroundAction;

/**
 * @brief 是否开启了手电筒，默认为 NO
 */
@property (nonatomic, assign, readonly) BOOL torchOn;

/**
 * @brief 开关手电筒接口
 * @param torchOn 开启或关闭
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setTorchOn:(BOOL)torchOn error:(NSError **)outError;

/**
 * @brief 采集视频的帧率
 */
@property (nonatomic, assign, readonly) NSUInteger frameRate;

/**
 * @brief 设置采集视频的帧率
 * @param frameRate 新的帧率
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setFrameRate:(NSUInteger)frameRate error:(NSError **)outError;

/**
 * @brief 相机采集的分辨率，默认为 AVCaptureSessionPresetHigh
 */
@property (nonatomic, strong, readonly) AVCaptureSessionPreset cameraResolution;

/**
 * @brief 设置相机采集的分辨率
 * @param cameraResolution 新的分辨率
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setCameraResolution:(AVCaptureSessionPreset)cameraResolution error:(NSError **)outError;

/**
 * @brief 摄像头的位置，默认为 AVCaptureDevicePositionBack
 */
@property (nonatomic, assign, readonly) AVCaptureDevicePosition cameraPosition;

/**
 * @brief 设置摄像头的位置
 * @param cameraPosition 新的摄像头位置
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setCameraPosition:(AVCaptureDevicePosition)cameraPosition error:(NSError **)outError;

/**
 * @brief 摄像头的旋转方向，默认为 AVCaptureVideoOrientationPortrait
 */
@property (nonatomic, assign, readonly) AVCaptureVideoOrientation cameraOrientation;

/**
 * @brief 设置摄像头的旋转方向
 * @param cameraOrientation 新的摄像头旋转方向
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setCameraOrientation:(AVCaptureVideoOrientation)cameraOrientation error:(NSError **)outError;

/**
 * @brief 摄像头变焦系数，默认为 1
 */
@property (nonatomic, assign, readonly) CGFloat cameraZoomFactor;

/**
 * @brief 设置摄像头变焦系数
 * @param cameraZoomFactor 新的摄像头变焦系数
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setCameraZoomFactor:(CGFloat)cameraZoomFactor error:(NSError **)outError;

/**
 * @brief 对焦和曝光参考点（点的位置以 cameraResolution 指定的采集分辨率为参考系，左上角为原点，朝右和朝下分别为 x 值和 y 值递增的方向）
 */
@property (nonatomic, assign, readonly) CGPoint pointOfInterest;

/**
 * @brief 设置对焦和曝光的参考点
 * @param pointOfInterest 新的对焦曝光参考点
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setPointOfInterest:(CGPoint)pointOfInterest error:(NSError **)outError;

/**
 * @brief 初始化一个空的录制器
 * @param audioConfiguration 音频配置，传入 nil 将使用默认配置
 * @param videoConfiguration 视频配置，传入 nil 将使用默认配置
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功返回初始化后的对象，否则返回 nil
 */
- (instancetype)initWithAudioConfiguration:(MSVRecorderAudioConfiguration *)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *)videoConfiguration error:(NSError **)outError;

/**
 * @brief 使用保存的草稿初始化一个录制器，使用此方法创建的录制器后续所有录制的片段和背景音乐都将添加到初始化使用的草稿对象中
 * @param draft 初始化使用的草稿对象
 * @param audioConfiguration 音频配置，传入 nil 将使用默认配置
 * @param videoConfiguration 视频配置，传入 nil 将使用默认配置
 * @param outError 如果发生错误，返回发生的错误
 * @return 初始化成功返回初始化后的对象，否则返回 nil
 */
- (instancetype)initWithDraft:(MSVDraft *)draft AudioConfiguration:(MSVRecorderAudioConfiguration *)audioConfiguration videoConfiguration:(MSVRecorderVideoConfiguration *)videoConfiguration error:(NSError **)outError;

/**
 * @brief 开始采集音视频，调用此方法将请求音视频的使用权限（如果指定音视频数据源为摄像头或麦克风的话）
 * @param completionHandler 调用完成的回调，audioGranted：是否获得音频权限，audioError：音频组件初始化发生的错误，videoGranted：是否获得了视频的采集权限，videoError：视频组件初始化发生的错误
 */
- (void)startCapturingWithCompletionHandler:(void(^)(BOOL audioGranted, NSError *audioError, BOOL videoGranted, NSError *videoError))completionHandler;

/**
 * @brief 开始采集音视频，调用此方法将请求音视频的使用权限（如果指定音视频数据源为摄像头或麦克风的话）
 * @param compromise 是否允许妥协部分不受当前设备支持的参数以保证尽最大努力使组件初始化成功
 * @param completionHandler 调用完成的回调，audioGranted：是否获得音频权限，audioError：音频组件初始化发生的错误，videoGranted：是否获得了视频的采集权限，videoError：视频组件初始化发生的错误
 */
- (void)startCapturingWithCompromise:(BOOL)compromise completionHandler:(void(^)(BOOL audioGranted, NSError *audioError, BOOL videoGranted, NSError *videoError))completionHandler;

/**
 * @brief 停止采集
 */
- (void)stopCapturing;

/**
 * @brief 使用默认配置开始录制
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)startRecordingWithError:(NSError **)outError;

/**
 * @brief 使用指定配置开始录制
 * @param clipConfiguration 录制使用的配置，传入 nil 将使用默认配置
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)startRecordingWithClipConfiguration:(MSVClipConfiguration *)clipConfiguration error:(NSError **)outError;

/**
 * @brief 完成录制
 * @param completionHandler 停止成功的回调，clip：录制产生的主轨道片段对象，error：发生的错误
 */
- (void)finishRecordingWithCompletionHandler:(void(^)(MSVMainTrackClip *clip, NSError *error))completionHandler;

/**
 * @brief 删除上一段录制的片段
 */
- (void)discardLastClip;

/**
 * @brief 删除指定索引的片段
 * @param index 需要删除的片段的索引
 */
- (void)discardClipAtIndex:(NSUInteger)index;

/**
 * @brief 删除所有录制的片段
 */
- (void)discardAllClips;

/**
 * @brief 切换摄像头
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)switchCameraWithError:(NSError **)outError;

/**
 * @brief 设置水印
 * @param waterMark 水印使用的图片
 * @param position 水印的位置
 */
- (void)setWaterMark:(UIImage *)waterMark position:(CGPoint)position;

/**
 * @brief 清除水印
 */
- (void)clearWaterMark;

/**
 * @brief 开启设备朝向自动检测
 * @param orientationUpdatedBlock 设备旋转方向改变时的回调
 */
- (void)enableAutoOrientationAdaptionWithOrientationUpdatedBlock:(void(^)(UIDeviceOrientation))orientationUpdatedBlock;

/**
 * @brief 关闭设备朝向自动检测
 */
- (void)disableAutoOrientationAdaption;

/**
 * @brief 更新录制器使用的草稿对象
 * @param draft 新的草稿对象
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)updateDraft:(MSVDraft *)draft error:(NSError **)outError;

/**
 * @brief 背景音效配置对象
 */
@property(nonatomic, strong, readonly) MSVBackgroundAudioConfiguration *backgroundAudioConfiguration;

/**
 * @brief 只有在未开始录制或者已经删除所有已录制的片段之后才能设置或取消背景音乐，设置的背景音乐信息会体现在 draft.audioClips 中而不会直接编码到生成的录制文件当中，以便在编辑阶段可以随时替换背景音乐
 * @param configuration 背景音效配置对象，传入 nil 清空背景音效
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)setBackgroundAudioWithConfiguration:(MSVBackgroundAudioConfiguration *)configuration error:(NSError **)outError;

/**
 * @brief 外部写入视频数据接口，使用该接口导入视频数据请保证配置 videoConfiguration.source = MSVVideoSourceExtern
 * @param videoData 待写入的视频数据
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)writeVideoData:(CMSampleBufferRef)videoData error:(NSError **)outError;

/**
 * @brief 外部写入音频数据接口，使用该接口导入视频数据请保证配置 audioConfiguration.source = MSVAudioSourceExtern
 * @param audioData 待写入的音频数据
 * @param outError 如果发生错误，返回发生的错误
 * @return 设置成功返回 YES，否则返回 NO
 */
- (BOOL)writeAudioData:(CMSampleBufferRef)audioData error:(NSError **)outError;

@end
