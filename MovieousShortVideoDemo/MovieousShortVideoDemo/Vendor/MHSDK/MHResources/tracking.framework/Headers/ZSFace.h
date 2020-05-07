//
//  ZSFace.h
//  zeuseefacenet
//
//  Created by flora on 2019/4/9.
//  Copyright © 2019 zeusee. All rights reserved.
//
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ZSFace : NSObject

@property (nonatomic, assign) int ID;
@property (nonatomic, assign) int left;
@property (nonatomic, assign) int top;
@property (nonatomic, assign) int right;
@property (nonatomic, assign) int bottom;
@property (nonatomic, assign) int height;
@property (nonatomic, assign) int width;
@property (nonatomic, assign) int* landmarks;
@property (nonatomic, assign) int monthState;
@property (nonatomic, assign) int eyeState;
@property (nonatomic, assign) int shakeState;
@property (nonatomic, assign) int riseState;
@property (nonatomic, assign) float pitch;
@property (nonatomic, assign) float yaw;
@property (nonatomic, assign) float roll;

- (instancetype)initWithLeft:(int)x1 top:(int)y1 right:(int)x2 bottom:(int)y2;

- (instancetype)initWithLeft:(int)x1 top:(int)y1 width:(int)width height:(int)height landmark:(int *)landmark id:(int)iid;

@end

NS_ASSUME_NONNULL_END

