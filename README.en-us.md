# MovieousShortVideo-Cocoa

`MovieousShortVideo-Cocoa` is a one-stop short video composition iOS SDK developed by [Movieous](http://movieous.video), which provide easy-to-use API, compatibility for multiple devices and OS versions, it provides high performance, abundant features and support for third-party SDK including face-beaty, special-effects and sound-distortion, etc. developers can build an excellent video composition app use `MovieousShortVideo` SDK.

*Read this in other languages: [English](README.en-us.md), [简体中文](README.md).*

## Features

### recording
- [x] capture microphone audio data
- [x] import external audio data
- [x] capture camera video data
- [x] record UIVIew
- [x] import external video data
- [x] hardware encode H.264 video
- [x] software encode AAC audio
- [x] record to mp4, mov and m4v format
- [x] video resolution
- [x] embedded face beautification
- [x] LUT(look up table) filter
- [x] image sticker(watermark)
- [x] external video processing plugin
- [x] preview and encoded video mirror independently configurable
- [x] embedded touch to focus
- [x] torch mode configurable
- [x] configurable max and min capture frame rate
- [x] configurable capture resolution
- [x] switch between front and back camera
- [x] video orientation configurable
- [x] zoom factor configurable
- [x] configurable focus and exposure parameters
- [x] configurable H.264 GOP length
- [x] configurable H.264 profile level
- [x] mute
- [x] audio and video bitrate configurable
- [x] pure audio recording
- [x] pure video recording
- [x] automatically monitor recording orientation
- [x] recording speed configurable
- [x] recording volume configurable
- [x] recording to segment
- [x] discard video segment
- [x] background music configurable, you can also trim, specify volume and loop it
- [x] generate snapshot
- [x] configurable flash mode

### editing
- [x] configurable destination video duration, resolution, etc.
- [x] concatenate multiple videos
- [x] mix multiple videos
- [x] indepoendently configurable location, size, rotation, volume, speed, valid time range, etc for every video segment
- [x] embedded face beautification
- [x] LUT(look up table)
- [x] image sticker(watermark)
- [x] external video processing plugin
- [x] repeat effetc
- [x] speed effect
- [x] reverse effect
- [x] batch generate video snapshot
- [x] preview mute

### exporting
- [x] configurable export file format 
- [x] save to photo album
- [x] configurable export bitrate
- [x] configurable export channel
- [x] configurable export sample rate

## SDK Requirements

iOS 8.0 or later

## How to install
MovieousShortVideo supports multiple methods for installing the library in a project.

### Installation with CocoaPods

[CocoaPods](http://cocoapods.org/) is a dependency manager for Objective-C, which automates and simplifies the process of using 3rd-party libraries in your projects. See the [Get Started](http://cocoapods.org/#get_started) section for more details.

#### Podfile

To integrate MovieousLive into your Xcode project using CocoaPods, specify it in your `Podfile`, assume your target name is `YourTargetName`:

```ruby
target 'YourTargetName' do
    pod 'MovieousShortVideo'
end
```

Then, run the following command:

```bash
$ pod install
```

## Instructions

The documentation: [MovieousShortVideo Development Guide](https://developer.movieous.cn/#/en-uk/iOS_ShortVideo) for your reference

## Feedback and Suggestions

Please feedback the problem by submitting issues on GitHub's repo if any problems you got, describe it as clearly as possible, It would be nice if an error message or screenshot also came together, and pointed out the type of bug or other issues in Labels.

[View existing issues and submit bugs here](https://github.com/movieous-team/MovieousShortVideo-Cocoa-Release/issues).
[Submit issue](https://github.com/movieous-team/MovieousShortVideo-Cocoa-Release/issues/new)