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
 * @brief This class contains authentication configurations
 */
@interface MSVAuthentication : NSObject

/**
 * @brief Is `-registerWithLicense` been called before
 */
@property (nonatomic, assign, readonly, class) BOOL registered;

/**
 * @brief Register the SDK with license string
 * @param license The license string from Movieous team
 */
+ (void)registerWithLicense:(NSString *)license;

/**
 * @brief Return the auth state for the SDK
 */
+ (BOOL)checkAuthState;

@end

NS_ASSUME_NONNULL_END
