//
//  MHFilterModel.m

//

#import "MHFilterModel.h"
#import "SSZipArchive.h"
@interface MHFilterModel()
@end

@implementation MHFilterModel

- (MHFilterModel *)modelWithConfigJson:(NSString *)json {
    MHFilterModel *model = [MHFilterModel initWithModel];
    NSDictionary *mainDic = [model dictionaryWithJsonString:json];
    NSArray *arr = mainDic[@"filterList"];
    NSDictionary *info = arr.firstObject;
    model.type = [info objectForKey:@"type"];
    model.name = [info objectForKey:@"name"];
    model.vertexShader = [info objectForKey:@"vertexShader"];
    model.fragmentShader = [info objectForKey:@"fragmentShader"];
    model.uniformList = [info objectForKey:@"uniformList"];
    model.uniformData = [info objectForKey:@"uniformData"];
    model.strength = [info objectForKey:@"strength"];
    model.texelOffset = [info objectForKey:@"texelOffset"];
    model.audioPath = [info objectForKey:@"audioPath"];
    model.audioLooping = [info objectForKey:@"audioLooping"];
    return model;
}

+ (instancetype)initWithModel {
    return [[self alloc] init];
}

+ (MHFilterModel *)unzipFiltersFile:(NSString *)filterFileName {
    NSString *desPath = [[MHFilterModel initWithModel] getUnzipPath];
    
    NSString *mainPath =  [[NSBundle mainBundle] pathForResource:@"MHSDK" ofType:@"bundle"];
    NSBundle *bundle = [NSBundle bundleWithPath:mainPath];
    NSString *path = [bundle pathForResource:@"filterFile" ofType:@"zip"];

    BOOL unZipSuccess = [SSZipArchive unzipFileAtPath:path toDestination:desPath];
    if (unZipSuccess) {
        NSString *filterPath = [NSString stringWithFormat:@"%@/filterFile/%@.zip",desPath,filterFileName];
        NSLog(@"filterPath==%@",filterPath);
        BOOL unZipSuccess2 = [SSZipArchive unzipFileAtPath:filterPath toDestination:desPath];
        if (unZipSuccess2) {
            NSString *filterPath2 = [NSString stringWithFormat:@"%@/%@/config.json",desPath,filterFileName];
            NSString *content = [NSString stringWithContentsOfFile:filterPath2 encoding:NSUTF8StringEncoding error:nil];
            MHFilterModel *model = [[MHFilterModel initWithModel] modelWithConfigJson:content];
            NSString *shaderPath = [NSString stringWithFormat:@"%@/%@/fragment.glsl",desPath,filterFileName];
            NSString *shader = [NSString stringWithContentsOfFile:shaderPath encoding:NSUTF8StringEncoding error:nil];
            NSLog(@"shader==%@",shader);
            model.fragmentShader = shader;
            model.unzipDesPath = desPath;
            NSLog(@"model.fragmentShader---%@",model.fragmentShader);
           return model;
        }
//          // 读取文件夹内容
//          NSError *error = nil;
//          NSMutableArray*items = [[[NSFileManager defaultManager]
//                                   contentsOfDirectoryAtPath:desPath
//                                   error:&error] mutableCopy];
//          if (error) {
//              return;
//          }
//
//          for (NSString * item_str in items) {
//              NSLog(@"文件名:%@",item_str);
//          }
    }
    return nil;
}

- (NSString *)getUnzipPath {
    NSString *path = [[NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject] stringByAppendingPathComponent:@"filtersFile"];
    
    if (![[NSFileManager defaultManager] fileExistsAtPath:path]) {
        [[NSFileManager defaultManager] createDirectoryAtPath:path withIntermediateDirectories:NO attributes:nil error:nil];
    }
    return path;
}

- (NSDictionary *)dictionaryWithJsonString:(NSString *)jsonString
{
    if (jsonString == nil) {
        return nil;
    }
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSError *err;
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:jsonData
                                                        options:NSJSONReadingMutableContainers
                                                          error:&err];
    if(err) {
        return nil;
    }
    return dic;
}
@end
