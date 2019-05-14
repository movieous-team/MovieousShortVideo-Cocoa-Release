*其他语言版本: [English](CHANGELOG.md), [简体中文](CHANGELOG.zh-cn.md).*

# v2.2.6(2019-5-14)
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