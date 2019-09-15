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
 * This class contains authentication configurations.
 */
@interface MSVAuthentication : NSObject

/**
 * Register the SDK with license string.
 *
 * @param license The license string from Movieous team.
 */
+ (void)registerWithLicense:(NSString *)license;

@end

NS_ASSUME_NONNULL_END
