# MovieousShortVideo-Cocoa

`Movieous 短视频 SDK` 是 [Movieous](https://movieous.cn/) 研发的使用于 iOS 平台的一站式视频制作 SDK。它通过提供极致简单易用并且具有高度灵活性的 API 提供包括录制，编辑，上传、滤镜，特效，背景音乐等丰富功能。`Movieous 短视频 SDK` 拥有超强的机型及版本兼容性，极致的性能表现，丰富的功能以及众多的三方生态支持。集成 `Movieous 短视频 SDK` 能够让开发者快速赋予 app 短视频能力。

*其他语言版本: [English](README.md), [简体中文](README.zh-cn.md).*

## 功能

| 功能点                          | 版本       | 备注       |
| ---------------------------- | -------- | -------------- |
| 摄像头采集                        | 1.0.0(+) | 无 |
| 麦克风采集                        | 1.0.0(+) | 无 |
| 静音功能                         | 1.0.0(+) | 无 |
| 纯音频录制                        | 1.0.0(+) | 无 |
| 手动对焦                         | 1.0.0(+) | 无 |
| 自动对焦                         | 1.0.0(+) | 无 |
| 曝光调节                         | 1.0.0(+) | 无 |
| 闪光灯开关                        | 1.0.0(+) | 无 |
| 横屏拍摄                         | 1.0.0(+) | 无 |
| 变速拍摄                         | 1.0.0(+) | 无 |
| 自定义拍摄时长                      | 1.0.0(+) | 无 |
| 自定义分辨率                       | 1.0.0(+) | 无 |
| 自定义视频帧率                      | 1.0.0(+) | 无 |
| 自定义视频码率                      | 1.0.0(+) | 无 |
| 支持 1:1 等比例录制                 | 1.0.0(+) | 无 |
| 分段录制                         | 1.0.0(+) | 无 |
| 回删视频                         | 1.0.0(+) | 无 |
| H.264 硬编                     | 1.0.0(+) | 无 |
| AAC 硬编                       | 1.0.0(+) | 无 |
| 视频拼接                         | 1.0.0(+) | 无 |
| 输出 MP4 文件                    | 1.0.0(+) | 无 |
| 实时水印                         | 1.0.0(+) | 无 |
| 实时美颜/滤镜                    | 1.0.0(+) | 无 |
| 关键帧/非关键帧预览               | 1.0.0(+) | 无 |
| 视频片段剪辑                     | 1.0.0(+) | 无 |
| 制作 GIF 动画封面                | 1.0.0(+) | 无 |
| 制作过场字幕                      | 1.0.0(+) | 无 |
| 文字特效                        | 1.0.0(+) | 无|
| 配音                            | 1.0.0(+) | 无 |
| 调节原声/背景声音量               | 1.0.0(+) | 无 |
| 片头片尾                         | 1.0.0    | 无 |
| 图片合成 MP4                     | 1.0.0(+) | 无 |
| 第三方美颜接口                    | 1.0.0(+) | 无 |
| 第三方滤镜接口                    | 1.0.0(+) | 无 |
| 大眼/瘦脸                        | 1.0.0(+) | 联系商务 |
| 贴纸特效                         | 1.0.0(+) | 联系商务 |
| 抖音滤镜                         | 1.0.0(+) | 联系商务 |
| 背景替换                         | 1.0.0(+) | 联系商务 |
| 表情特效                         | 1.0.0(+) | 联系商务 |
| 手势识别                         | 1.0.0(+) | 联系商务 |
| 支持主流架构（armv7、arm64、x86）  | 1.0.0(+) | 无 |
| 上传云端                         | 1.0.1(+) | 无 |
| 断点续传                         | 1.0.1(+) | 无 |

## 版本要求

iOS 8.0 及其以上

## 如何安装

### Cocoapods 集成

#### 安装 Cocoapods

如果您已安装 Cocoapods，则请直接跳过该步骤，直接进入下一步骤。
如果你未接触过 Cocoapods ，我们推荐您阅读 [唐巧的博客-用CocoaPods做iOS程序的依赖管理](https://blog.devtang.com/2014/05/25/use-cocoapod-to-manage-ios-lib-dependency/ "用CocoaPods做iOS程序的依赖管理") ，了解我们为何使用 Cocoapods 。另外文章中提及的淘宝源已经不再维护，需要使用 [Ruby-China RubyGems 镜像](https://gems.ruby-china.com/)替换。

如果觉得上面两个文章比较繁琐，可以直接根据我们提供的简要步骤，进行安装。
* 简要步骤：打开mac自带的 终端(terminal)，然后输入依次执行下述命令。

```bash
# 注释：Ruby-China 推荐2.6.x，实际 mac 自带的 ruby 也能用了
gem sources --add https://gems.ruby-china.com/ --remove https://rubygems.org/
gem sources -l
# 注释：上面的命令，应该会输出以下内容，>>> 代表此处为输出
>>> https://gems.ruby-china.com
# 注释：确保只有 gems.ruby-china.com

sudo gem install cocoapods
# 注释：由于我们不需要使用官方库，所以可以不执行 pod setup。
```

#### 使用Podfile集成

通过 [CocoaPods](https://cocoapods.org/) 安装可以最大化地简化安装过程。
首先，在项目根目录下的 Podfile 文件中添加以下 pods（我们假设您的项目 target 名称为 `iOSDemo`）：

```ruby
target 'iOSDemo' do
    pod 'MovieousShortVideo'
end
```

<span data-type="color" style="color:rgb(51, 51, 51)"><span data-type="background" style="background-color:rgb(255, 255, 255)">然后在项目根目录执行 </span></span>`pod install`<span data-type="color" style="color:rgb(51, 51, 51)"><span data-type="background" style="background-color:rgb(255, 255, 255)"> </span></span>命令，执行成功后，SDK 就集成到项目中了。
<em>如果长时间没有拉取过pod 仓库，可能出现无法找到我们的repo的情况，此时建议先使用 </em><code><em>pod repo update</em></code><em> 更新pod仓库。</em>

## 使用方法

请参考开发者文档：[MovieousShortVideo 开发指南](https://developer.movieous.cn/#/iOS_ShortVideo)

## 反馈及意见

当你遇到任何问题时，可以向我们提交 issue 来反馈。

[提交 issue](https://github.com/movieous-team/MovieousShortVideo-Cocoa-Release/issues)。