//
//  MHFiltersContants.h

#import <Foundation/Foundation.h>

#import <OpenGLES/ES2/gl.h>
#ifndef MHFiltersContants_h
#define MHFiltersContants_h

typedef NS_ENUM(NSInteger,MHFilterType) {
    //MHFilterType_None         = 0,
    MHFilterType_biaozhun = 0    ,   //标准滤镜
    MHFilterType_langman  = 1       ,   //浪漫滤镜
    MHFilterType_qingxin         ,   //清新滤镜
    MHFilterType_weimei         ,   //唯美滤镜
    MHFilterType_fennen         ,   //粉嫩滤镜
    MHFilterType_huaijiu         ,   //怀旧滤镜
    MHFilterType_landiao         ,   //蓝调滤镜
    MHFilterType_qingliang    ,   //清凉滤镜
    MHFilterType_rixi         ,   //日系滤镜
    MHFilterType_yinghong     ,   //樱红滤镜
    MHFilterType_yunshang     ,   //云裳滤镜
    MHFilterType_chunzhen     ,   //纯真滤镜
    MHFilterType_bailan       ,   //白兰滤镜
    MHFilterType_yuanqi       ,   //元气滤镜
    MHFilterType_chaotuo      ,   //超脱滤镜
    MHFilterType_xiangfen     ,   //香氛滤镜
    MHFilterType_white        ,   //美白滤镜
    
};

typedef NS_ENUM(NSInteger,MHJitterType) {
    
    MHJitterType_NONE = 0,
    MHJitterType_SOULOUT  = 1   ,   //灵魂出窍
    MHJitterType_SHAKE  = 2      ,   //抖动
    MHJitterType_SHINEWHITE  = 3  ,   //闪白
    MHJitterType_GLITCH   = 4    ,   //毛刺
    MHJitterType_VERTIGO   = 5    ,   //幻觉
    MHJitterType_FRAGMOSAIC = 6,//马赛克
    MHJitterType_CIRCLEMOSAIC = 7,//圆形马赛克
    MHJitterType_TRIANGLEMOSAIC = 8,//三角马赛克
    MHJitterType_HEXAGOMOSAIC = 9 //六边马赛克
};

typedef NS_ENUM(NSInteger,MHDistortType) {
    
    MHDistortType_NONE = 0,
    MHDistortType_ALIEN  = 1   ,     //外星人
    MHDistortType_PEAR  = 2    ,     //梨梨脸
    MHDistortType_THIN  = 3    ,     //瘦瘦脸
    MHDistortType_MIRROR  = 4,        //镜像脸
    MHDistortType_FRAGMENT_MIRROR = 5  , // 片段脸
    MHDistortType_WATER_REFLECTION = 6, // 水面
    MHDistortType_SPIRIAL =   7 ,  // 螺旋镜面
    MHDistortType_FISHEYE = 8, //鱼眼相机
    MHDistortType_LeftMIRROR = 9 //左右镜像
};
//水印
typedef NS_ENUM(NSInteger,MHWatermarkAlign) {
    
    MHWatermarkAlign_NONE = 0,
    MHWatermarkAlign_TOP_LEFT  =  1,
    MHWatermarkAlign_TOP_RIGHT  =  2,
    MHWatermarkAlign_BOTTOM_LEFT  = 3,
    MHWatermarkAlign_BOTTOM_RIGHT  = 4
};

typedef struct MHGPUTextureOptions {
    GLenum minFilter;
    GLenum magFilter;
    GLenum wrapS;
    GLenum wrapT;
    GLenum internalFormat;
    GLenum format;
    GLenum type;
} MHGPUTextureOptions;

typedef struct MHGPUVector4 {
    GLfloat one;
    GLfloat two;
    GLfloat three;
    GLfloat four;
} MHGPUVector4;

typedef struct MHGPUVector3 {
    GLfloat one;
    GLfloat two;
    GLfloat three;
} MHGPUVector3;

typedef struct MHGPUMatrix4x4 {
    MHGPUVector4 one;
    MHGPUVector4 two;
    MHGPUVector4 three;
    MHGPUVector4 four;
} MHGPUMatrix4x4;

typedef struct MHGPUMatrix3x3 {
    MHGPUVector3 one;
    MHGPUVector3 two;
    MHGPUVector3 three;
} MHGPUMatrix3x3;

typedef NS_ENUM(NSUInteger, MHGPUImageRotationMode) {
    kMHGPUImageNoRotation,
    kMHGPUImageRotateLeft,
    kMHGPUImageRotateRight,
    kMHGPUImageFlipVertical,
    kMHGPUImageFlipHorizonal,
    kMHGPUImageRotateRightFlipVertical,
    kMHGPUImageRotateRightFlipHorizontal,
    kMHGPUImageRotate180
};

#endif /* MHFiltersContants_h */

