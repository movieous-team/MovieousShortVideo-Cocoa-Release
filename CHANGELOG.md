*其他语言版本: [English](CHANGELOG.en-us.md), [简体中文](CHANGELOG.md).*

# v2.2.14(2019-7-27)
## 修复
- 修复 `MSVImageGenerator` 释放时可能出现 crash 的问题。

# v2.2.13(2019-7-23)
## 修复
- 修复自动生成的 gif 路径扩展名错误的问题。

# v2.2.12(2019-7-16)
## 功能
- 将 `MovieousBase` 升级到 v1.1.1。
- 支持切换摄像头时模糊化过渡。
- gif 生成支持。
## 优化
- 优化默认的拍摄文件，导出文件等的存储路径。

# v2.2.11(2019-7-9)
## 功能
- `MSVRecorder` 支持 `m4a` 类型录制
## 修复
- 修复 `MSVRecorder` 回调的当前片段时长不正确的问题。
- 减少 `MSVRecorder` 录制过程中频繁报错的情况。
- 修复 `MSVRecorder` 在调用 `stopCapturing` 方法后调用其他方法可能被卡住的问题。 

# v2.2.10(2019-6-30)
## 修复
- 修复 `MSVRecorder` 使用过程中 `MSVCamera` 内存泄露的问题。
- 修复 `-switchCamera` 时可能出现旋转方向不正确的图像的问题。
- 修复 `MSVRecorder` 在录制过程中经常报错的问题。

# v2.2.9(2019-5-16)
## 修复
- 修复 `-updateDraft:error:` 使用新的资源可能导致视频无法刷新的问题。
- 修复 `MSVRecorder` 在 `-dealloc` 时可能发生 crash 的问题。
- 修复 `MSVRecorder` 在发生错误后未正确恢复状态的问题。

# v2.2.8(2019-5-14)
## 修复
- 修复  `-updateDraft:error:` 可能导致 `editor` 无法正常播放视频的问题。

# v2.2.7(2019-5-14)
## 修复
- 修复释放对象时有可能触发 crash 的问题。
- 修复偶现的音量同步问题。
- 修复 `-seekToTime:accurate:` 时间基准未添加 `timeRange` 影响的问题。

# v2.2.6(2019-5-7)
## 修复
- 修复 `-startCapturingWithCompletion` 调用时会短暂卡住主线程的问题。

# v2.2.5(2019-5-5)
## 修复
- 修复 `preferredVideoOrientation` 在切换摄像头之后不生效的问题。

# v2.2.4(2019-5-4)
## 修复
- 修复 `-snapshotWithCompletion:` 接口可能发生 timeout 的错误。
- 优化编码器。

# v2.2.3(2019-4-29)
## 功能
- 使用 `AVCaptureStillImageOutput` 来生成录制器的快照。
- 录制器添加 `flashMode` 属性。
## 修复
- 修复图片处理管道中 `videoSize` 转向的问题。

# v2.2.2(2019-4-28)
## 功能
- 给 `MSVEditor` 添加 `volume` 属性。

# v2.2.1(2019-4-25)
## 其他
- 更新头文件文档。

# v2.2.0(2019-4-24)
## 功能
- 添加 `MSVDraft.videoSize` 设置的错误返回。
- 将更多的摄像头和麦克风配置项加入 `MSVRecorderAudioConfiguration` 和 `MSVRecorderVideoConfiguration` 中。
## 修复
- 修复 `MSVDraft` 进行 `-copy` 时会 crash 的问题。
## 其他
- 将 `MSVVideoExporter` 重命名为 `MSVExporter`。
- 将 `MSVRecorderVideoConfiguration.scalingMode` 重命名为 `MSVRecorderVideoConfiguration.previewScalingMode`。

# v2.1.0(2019-4-15)
## 功能
- 将 `MSVAudioClip` 和 `MSVVideoClip` 合并为 `MSVMixTrackClip`。
- 添加 `MSVAuthentication` 来对 SDK 进行授权。
- 添加 `MSVImageGenerator` 来管理视频快照。
- 给 `MSVRecorder` 添加内置美颜和其他滤镜。
- 添加包括曝光模式，手电筒模式等更多的摄像头控制操作。
- 给 `MSVTimeEffect` 添加 `scope` 配置项。

# v2.0.1(2019-3-21)
## 功能
- 添加涂鸦功能。

# v2.0.0(2019-3-19)
## 功能
- 添加大小、位置、旋转方向、背景颜色等配置项到 `MSVMainTrackClip` 中
- 添加视频混合功能。
- 将 `effects` 分为 `basicEffects` 和 `timeEffects`。
- 给 `MSVEditor` 添加当前播放位置的通知。
- 重命名部分接口。
- `MSVRecorder` 中移除多长录制时长配置项，你可以实现自己的录制时长控制逻辑来实现录制时长控制。
## 修复
- 修复视频旋转的 bug。

# v1.0.3(2019-1-15)
## 功能
- 修复视频转向的 bug。

# v1.0.2(2018-12-27)
## 其他
- 重命名 `MSVImagePasterEffect` 为 `MSVImageStickerEffect`。
- 接口文档调整为英文版。

# v1.0.1(2018-12-3)
## 功能
- 添加鉴权支持。
## 修复
- 修复频繁切换背景音乐等操作可能导致的音频服务被重置，无法正常预览的问题。

# v1.0.0(2018-11-28)
- 发布初版。
