*Read this in other languages: [English](CHANGELOG.md), [简体中文](CHANGELOG.zh-cn.md).*

# v2.2.4(2019-5-4)
## Fixes
- fix timeout error happend when `-snapshotWithCompletion:` is called.
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
- fix crash happens when `-copy` is called by `MSVDraft`.
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