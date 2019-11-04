//
//  MSVAuthentication.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/4/13.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * 这个类包含鉴权相关配置。
 */
@interface MSVAuthentication : NSObject

/**
 * 使用证书字符串来注册 SDK。
 *
 * @param license 从 Movieous 团队获取到的证书字符串。
 */
+ (void)registerWithLicense:(NSString *)license;

@end

NS_ASSUME_NONNULL_END
