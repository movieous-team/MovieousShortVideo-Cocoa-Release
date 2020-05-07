//
//  AppDelegate.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "AppDelegate.h"
#import "MSVDHomeViewController.h"
#import <MHBeautySDK/MHBeautySDK.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    self.window = [UIWindow new];
    [self.window makeKeyAndVisible];
    self.window.rootViewController = [MSVDHomeViewController new];
    [MSVAuthentication registerWithLicense:@"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJhcHBpZCI6InZpZGVvLm1vdmllb3VzLk1vdmllb3VzU2hvcnRWaWRlb0RlbW8iLCJsb2NhbGF1dGgiOnRydWV9.qfY35jrCd9qb3X6p04Bus-reLTaWQvkrNDJyvDyzqNA"];
    [MHSDK.shareInstance init:@"f5fe7ecab78ae9a67f66c04c3d0f988d"];
    return YES;
}

@end
