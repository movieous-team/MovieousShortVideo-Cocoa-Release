//
//  MHBeautyManager.h


#import <Foundation/Foundation.h>
#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#import <CoreVideo/CoreVideo.h>
#import <CoreMedia/CoreMedia.h>
#import "MHFiltersContants.h"
NS_ASSUME_NONNULL_BEGIN

@interface MHBeautyManager : NSObject

/**
 处理纹理数据
 
 @param texture 纹理数据
 @param width 宽度
 @param height 高度
 */

- (void)processWithTexture:(GLuint)texture width:(GLint)width height:(GLint)height;
 
/**
 处理iOS封装的数据
 
 @param pixelBuffer BGRA格式数据
 @param formatType 只支持kCVPixelFormatType_420YpCbCr8BiPlanarFullRange 和 kCVPixelFormatType_32BGRA
 */

- (void)processWithPixelBuffer:(CVPixelBufferRef)pixelBuffer formatType:(OSType)formatType;

- (CVPixelBufferRef)processPixelBuffer:(CVPixelBufferRef)pixelBuffer sampleTimingInfo:(CMSampleTimingInfo)sampleTimingInfo;
/**
 清空所有资源，为防止内存泄露，退出页面销毁时请调用此接口
 */
- (void)destroy;

/// 美白
/// @param skinWhiting 美白参数，参数0.0到100.0，0是正常值
- (void)setSkinWhiting:(int)skinWhiting;

/// 磨皮
/// @param buffing 磨皮参数，参数0.0到100.0，0是正常值
- (void)setBuffing:(int)buffing;

/// 红润
/// @param ruddiness 红润参数，参数0.0到100.0，0是正常值
- (void)setRuddiness:(int)ruddiness;

/**
 大眼

 @param bigEye 参数0.0到100.0，0是正常值
 */
- (void)setBigEye:(int)bigEye;

/**
 瘦脸

 @param faceLift 参数0.0到100.0，0是正常值
 */
- (void)setFaceLift:(int)faceLift;

/**
 瘦鼻

 @param noseLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setNoseLift:(int)noseLift;

/**
 嘴型

 @param mouthLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setMouthLift:(int)mouthLift;

/**
 下巴

 @param chinLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
-(void)setChinLift:(int)chinLift;

/**
 额头

 @param foreheadLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setForeheadLift:(int)foreheadLift;

/**
 长鼻

 @param lengthenNoseLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setLengthenNoseLift:(int)lengthenNoseLift;


/**
 眉毛

 @param eyeBrownLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setEyeBrownLift:(int)eyeBrownLift;

/**
 眼角

 @param eyeAngleLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setEyeAngleLift:(int)eyeAngleLift;

/**
 开眼角

 @param eyeAlaeLift 参数0.0到100.0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setEyeAlaeLift:(int)eyeAlaeLift;

/**
 眼距

 @param eyeDistanceLift 参数0.0到100.0，0是不设置，50为默认值。0-50为缩小，50-100为放大
 */
- (void)setEyeDistanceLift:(int)eyeDistanceLift;

/**
 削脸

 @param shaveFaceLift ，参数0.0到100.0，0是正常值。
 */
- (void)setShaveFaceLift:(int)shaveFaceLift;

/**
 贴纸

 @param stickerContent stickerContent
 */
- (void)setSticker:(NSString *)stickerContent;


/**
 特效

 @param jitter MHJitterType，详情参见MHFiltersContants.h
 */
- (void)setJitterType:(MHJitterType)jitter;

/**
 哈哈镜

 @param distort MHDistortType，详情参见MHFiltersContants.h
 */
- (void)setDistortType:(MHDistortType)distort;

/**
 滤镜

 @param filterType MHFilterType，详情参见MHFiltersContants.h
 newFilterInfo 新滤镜信息
 */
- (void)setFilterType:(NSInteger)filterType newFilterInfo:(NSDictionary *)info;


/**
 亮度

 @param brightnessLift 亮度 0 to 100.0,  50.0 as the normal level
 */
- (void)setBrightnessLift:(int)brightnessLift;

/**
 水印
 
 @param watermark 图片名称
 @param alignment 水印位置 详情参见MHFiltersContants.h
 */
- (void)setWatermark:(NSString *)watermark alignment:(MHWatermarkAlign)alignment;
@end

NS_ASSUME_NONNULL_END

