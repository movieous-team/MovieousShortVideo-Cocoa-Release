//
//  MHFilter.h


#import <Foundation/Foundation.h>
#import <MovieousShortVideo/MovieousShortVideo.h>
#import <MHBeautySDK/MHBeautyManager.h>
NS_ASSUME_NONNULL_BEGIN

@interface MHFilter : NSObject
<
MovieousExternalFilterCaptureEffectProcessor
>

@property (nonatomic, strong)MHBeautyManager *beautyManager;

@end

NS_ASSUME_NONNULL_END
