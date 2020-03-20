//
//  AppDelegate.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2019/12/9.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import "AppDelegate.h"
#import "MSVDHomeViewController.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    self.window = [UIWindow new];
    [self.window makeKeyAndVisible];
    self.window.rootViewController = [MSVDHomeViewController new];
    [MSVAuthentication registerWithLicense:@"test"];
    return YES;
}

@end
