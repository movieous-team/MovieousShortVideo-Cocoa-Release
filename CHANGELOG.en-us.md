*Read this in other languages: [English](CHANGELOG.en-us.md), [简体中文](CHANGELOG.md).*

# v2.2.28(2020-1-16)
## Fixes
- fix issue that video will still show background blur when `blurBackground` is on and `scalingMode` is not `MovieousScalingModeAspectFit`.

# v2.2.26(2020-1-2)
## Features
- add blur canvas with first video frame.

# v2.2.25(2019-12-26)
## Fixes
- avoid accasional crash when correct `videoSize` of `EffectPipeline` can not be found.

# v2.2.24(2019-12-20)
## Features
- add blur feature for editor canvas.
## Fixes
- fix issue that progress callback won't be called when `[MSVExporter startExport]` is not called main thread.
- fix issue that `MSVExporter` may won't call error callback when error occurs.
- fix issue that orientation may be error when you use image to init `MSVMainTrackClip`.

# v2.2.23(2019-11-21)
## Fixes
- fix issue that valid video region is not in the center of the whole video when export aspect ratio is not equal to that of original video.

# v2.2.21(2019-10-31)
## Features
- add `MSVExporter.maxKeyFrameInterval` property to specify max key frame interval.
- add `MSVRecorder.finishing` so that you can check if the recorder is finishing.
## Fixes
- fix issue that call `-startRecordingWithError:`, `-startRecordingWithClipConfiguration:error:` or `-finishRecordingWithCompletionHandler:` before callback of `-finishRecordingWithCompletionHandler:` can lead to unknown error without returning error.
- fix issue that `-snapshotWithCompletion:` may failed to callback.

# v2.2.20(2019-8-27)
## Fixes
- fix issue that framework can not be compiled on XCode 10 and older.

# v2.2.19(2019-8-27)
## Fixes
- fix issue that some components would retrieve UI parameters.
- fix error when export pure audio assets.

# v2.2.18(2019-9-15)
## Features
- update `MovieousBase` to v1.1.6.
    - add `averagePowerLevel` property.
## Fixes
- fix encoding error incidentally happen while recording.
- update authentication mechanism, won't throw exception if failed.
- split `MSVRecorder.currentClipDuration` to `MSVRecorder.currentClipOriginalDuration` and `MSVRecorder.currentClipRealDuration`.
- fix music duration error when configure background music in `MSVRecorder`.
- fix failing to update progress of background music after operations like `cancelRecording`.

# v2.2.17(2019-8-26)
## Features
- update `MovieousBase` to v1.1.5.
    - fix color error when export video.
## Improvements
- improve sensitivity of volume param.
## Fixes
- fix error when retrieve `MSVDraft.videoSize` of rotated video.

# v2.2.16(2019-8-22)
## Features
- support greater than 1 value for `volume` property of `MSVClip` and it's subclasses.
- 允许 `MSVClip` 及其子类的 `volume` 属性大于1。

# v2.2.15(2019-8-1)
## Features
- Add `loopCount` property to `MSVGifGenerator` to adjust play count.
## Fixes
- Fix failing to apply `timeRange` property.

# v2.2.14(2019-7-27)
## Fixes
- Fix crash problem encountered when `MSVImageGenerator` dealloc.

# v2.2.13(2019-7-23)
## Fixes
- Fix auto generated gif file path extension error.

# v2.2.12(2019-7-16)
## Features
- update `MovieousBase` to v1.1.1.
- support blur while switching camera position.
- support generating gif files.
## Improvements
- refine default storage path for recorder and exporter files.

# v2.2.11(2019-7-9)
## Features
- support `m4a` for `MSVRecorder`.
## Fixes
- fix clip duration problem in `MSVRecorder` callback.
- reduce error occured when use `MSVRecorder` to record
- fix stuck when calling other method after `stopCapturing` of `MSVRecorder`

# v2.2.10(2019-6-30)
## Fixes
- fix memory leak of `MSVCamera` while using `MSVRecorder`.
- fix wrong orientation issue while using `-switchCamera`.
- fix error constantly occur while using `MSVRecorder`.

# v2.2.9(2019-5-16)
## Fixes
- fix issue that `-updateDraft:error:` called with new resources can lead to unable to refresh video.
- fix crash issue that may happen during `-dealloc` of `MSVRecorder`.
- fix incorrect state after error happend for `MSVRecorder`.

# v2.2.8(2019-5-14)
## Fixes
- fix issue that `-updateDraft:error:` may lead to abnormal video play for `editor`.

# v2.2.7(2019-5-14)
## Fixes
- fix crash issue may happen when release objects.
- fix volume synchronization issue happens occasionally.
- fix issue that `-seekToTime:accurate:` hasn't add `timeRange` as time base.

# v2.2.6(2019-5-7)
## Fixes
- fix main thread been block after `-startCapturingWithCompletion` being called.

# v2.2.5(2019-5-5)
## Fixes
- fix `preferredVideoOrientation` becoming invalid after switching camera.

# v2.2.4(2019-5-4)
## Fixes
- fix timeout error happening when `-snapshotWithCompletion:` is called.
- refine encoder.

# v2.2.3(2019-4-29)
## Features
- use `AVCaptureStillImageOutput` for recorder snapshot.
- add `flashMode` to recorder.
## Fixes
- fix `videoSize` orientation bug for image processing pipeline.

# v2.2.2(2019-4-28)
## Features
- add `volume` property for `MSVEditor`.

# v2.2.1(2019-4-25)
## Others
- update header documentations.

# v2.2.0(2019-4-24)
## Features
- add error return when set `MSVDraft.videoSize`.
- add more camera and microphone configuration to `MSVRecorderAudioConfiguration` and `MSVRecorderVideoConfiguration`.
## Fixes
- fix crash happening when `-copy` is called by `MSVDraft`.
## Others
- rename `MSVVideoExporter` to `MSVExporter`.
- rename `MSVRecorderVideoConfiguration.scalingMode` to `MSVRecorderVideoConfiguration.previewScalingMode`.

# v2.1.0(2019-4-15)
## Features
- merge `MSVAudioClip` & `MSVVideoClip` to `MSVMixTrackClip`.
- add `MSVAuthentication` to authenticate SDK.
- add `MSVImageGenerator` to manage snapshots.
- add embedded beautification and other filters to `MSVRecorder`.
- add more camera controll operations including exposure mode, torch mode, etc.
- add `scope` configuration for `MSVTimeEffect`.

# v2.0.1(2019-3-21)
## Features
- add graffiti feature.

# v2.0.0(2019-3-19)
## Features
- add size, location, rotation and background color configuration for `MSVMainTrackClip`.
- add video mix feature.
- separate `effects` to `basicEffects` and `timeEffects`.
- add current time notification for `MSVEditor`.
- rename some interfaces.
- remove max duration configuration for `MSVRecorder`, you can implement your own recorded time controll.
## Fixes
- fix many bugs found in v1.x.x.

# v1.0.3(2019-1-15)
## Features
- fix video transform bug.

# v1.0.2(2018-12-27)
## Others
- rename `MSVImagePasterEffect` to `MSVImageStickerEffect`.
- change interface documentation language to English.

# v1.0.1(2018-12-3)
## Features
- support license authentication.
## Fixes
- fix preview error when media service is resetted because of frequent backgroud audio switch operations, etc.

# v1.0.0(2018-11-28)
- initial release.
