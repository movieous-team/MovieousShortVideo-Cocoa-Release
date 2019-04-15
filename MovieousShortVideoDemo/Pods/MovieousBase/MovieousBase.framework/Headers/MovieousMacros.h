//
//  MovieousMacros.h
//  MovieousBase
//
//  Created by Chris Wang on 2019/3/29.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#ifndef MovieousMacros_h
#define MovieousMacros_h

#define MovieousWeakSelf  __weak typeof(self) wSelf = self;
#define MovieousStrongSelf  __strong typeof(wSelf) strongSelf = wSelf;

#endif /* MovieousMacros_h */
