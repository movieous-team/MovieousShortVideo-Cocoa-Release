# v2.1.0
## Feature
- merge `MSVAudioClip` & `MSVVideoClip` to `MSVMixTrackClip`
- add `MSVAuthentication` to authenticate SDK
- add `MSVImageGenerator` to manage snapshots
- add inner beautify and other filters to `MSVRecorder`
- add more camera controll operations including exposure mode, torch mode, etc.
- add scope for `MSVTimeEffect`

# v2.0.1
## Features
- add graffiti feature

# v2.0.0
## Features
- add size, location, rotation and background color configuration for `MSVMainTrackClip`
- add video mix feature
- separate effects to basicEffects and timeEffects
- add current time notification for `MSVEditor`
- rename some interfaces
- remove max duration configuration for `MSVRecorder`, you can implement your own recorded time controll

## Fixes
- fix many bugs found in v1.x.x

# v1.0.3(2019-1-15)
## Features
- fix video transform bug

# v1.0.2(2018-12-27)
## Miscs
- rename `MSVImagePasterEffect` to `MSVImageStickerEffect`
- change interface documentation language to English

# v1.0.1(2018-12-3)
## Features
- support license authentication
## Fixes
- fix preview error when media service is resetted because of frequent backgroud audio switch operations, etc.

# v1.0.0(2018-11-28)
## Features
- Audio/Video Acquisition
- Audio/Video encoding（H.264 + AAC）
- Real-time beautificaion, Filter
- Support beatification and Filter from the third part 
- Customized recording duration, bitrate, resolution
- Support recording size as 1:1
- Breakpoint recording
- Delete the recorded clip
- Place effects
- Background replacement
- Gesture recognition
- Expression recognition
- Video format save as Mp4
- Support core system framework as  arm64, i386, x86_64 