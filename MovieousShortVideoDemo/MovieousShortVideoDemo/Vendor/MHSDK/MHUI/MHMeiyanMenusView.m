//
//  MHMeiyanMenusView.m

#import "MHMeiyanMenusView.h"
#import "MHBeautyMenuCell.h"
#import "MHStickersView.h"
#import "MHBeautyParams.h"
#import "StickerDataListModel.h"
#import "StickerManager.h"
#import "MHMagnifiedView.h"
#import "MHBeautyAssembleView.h"
#import "MHSpecificAssembleView.h"
#import "MHBeautiesModel.h"
#import "MHFilterModel.h"

#define kBasicStickerURL @"aHR0cHM6Ly9kYXRhLmZhY2VnbC5jb20vYXBwYXBpL1N0aWNrZXIvaW5kZXg="
static NSString *StickerImg = @"stickerFace";
static NSString *BeautyImg = @"beauty1";
static NSString *FaceImg = @"face";
static NSString *CameraImg = @"beautyCamera";
static NSString *FilterImg = @"filter";
static NSString *SpecificImg = @"specific";
static NSString *HahaImg = @"haha";


@interface MHMeiyanMenusView()<UICollectionViewDelegate,UICollectionViewDataSource,MHBeautyAssembleViewDelegate,MHStickersViewDelegate,MHMagnifiedViewDelegate,MHSpecificAssembleViewDelegate>
@property (nonatomic, strong) MHBeautyManager *beautyManager;//美型特性管理器，必须传入
@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) NSMutableArray *array;
@property (nonatomic, strong) UIView *currentView;
@property (nonatomic, assign) NSInteger lastIndex;//上一个index
@property (nonatomic, strong) UIView *superView;
@property (nonatomic, strong) NSMutableArray *viewsArr;
@property (nonatomic, strong) MHMagnifiedView *magnifiedView;//哈哈镜
@property (nonatomic, strong) MHBeautyAssembleView *beautyAssembleView;//美颜集合
@property (nonatomic, strong) MHSpecificAssembleView *specificAssembleView;//特效集合
@property (nonatomic, strong) MHStickersView *stickersView;//贴纸

@end
@implementation MHMeiyanMenusView

- (void)setupDefaultBeautyAndFaceValueWithIsTX:(BOOL)isTX{
    //设置美型默认数据，按照数组的名称设置初始值，不要换顺序
    /*
    NSArray *originalValuesArr = @[@"0",@"大眼",@"瘦脸",
    @"嘴型",
    @"瘦鼻",
    @"下巴",
    @"额头",
    @"眉毛",
    @"眼角",
    @"眼距",
    @"开眼角",
    @"削脸",
    @"长鼻"];
    for (int i = 0; i<originalValuesArr.count; i++) {
        if (i != 0) {
            NSInteger value = (NSInteger)originalValuesArr[i];
            [self handleFaceBeautyWithType:i sliderValue:value];
        }
    }
    //设置美颜参数
    NSArray *beautyArr = @[@"磨皮数值",@"美白数值",@"红润数值"];
    if (isTX) {
        [self beautyLevel:(NSInteger)[beautyArr objectAtIndex:0] whitenessLevel:(NSInteger)[beautyArr objectAtIndex:1] ruddinessLevel:(NSInteger)[beautyArr objectAtIndex:2] brightnessLevel:50];
    } else {
        [_beautyManager setBuffing:(int)[beautyArr objectAtIndex:0]];
        [_beautyManager setSkinWhiting:(int)[beautyArr objectAtIndex:1]];
        [_beautyManager setRuddiness:(int)[beautyArr objectAtIndex:2]];
    }
     */
}
- (instancetype)initWithFrame:(CGRect)frame superView:(UIView *)superView delegate:(id<MHMeiyanMenusViewDelegate>)delegate beautyManager:(MHBeautyManager *)manager isTXSDK:(BOOL)isTx {
    if (self = [super initWithFrame:frame]) {
        self.superView = superView;
        self.delegate = delegate;
        self.isTX = isTx;
        self.beautyManager = manager;
        [self addSubview:self.collectionView];
        self.lastIndex = -1;
        [self getSticks];
    }
    return self;
}

- (void)showMenuView:(BOOL)show {
    if (self.currentView) {
        [self.currentView removeFromSuperview];
        self.show = YES;
        self.currentView = nil;
    }
    if (show) {
        if (![self isDescendantOfView:self.superView]) {
               [self.superView addSubview:self];
        }
    } else {
        [self removeFromSuperview];
    }
    self.show = show;
}

- (void)setIsTX:(BOOL)isTX {
    _isTX = isTX;
    self.beautyAssembleView.isTXSDK = isTX;
}

#pragma mark - delegate
//美颜-腾讯直播SDK使用
- (void)beautyLevel:(NSInteger)beauty whitenessLevel:(NSInteger)white ruddinessLevel:(NSInteger)ruddiness brightnessLevel:(NSInteger)brightness{
    if ([self.delegate respondsToSelector:@selector(beautyEffectWithLevel:whitenessLevel:ruddinessLevel:)]) {
        [self.delegate beautyEffectWithLevel:beauty whitenessLevel:white ruddinessLevel:ruddiness];
    }
    [_beautyManager setBrightnessLift:(int)brightness];
}

//美颜-非腾讯直播SDK使用
- (void)handleBeautyWithType:(NSInteger)type level:(NSInteger)beautyLevel {
    switch (type) {
            case MHBeautyType_Original:{
                [_beautyManager setRuddiness:0];
                [_beautyManager setSkinWhiting:0];
                [_beautyManager setBuffing:0];
            }
                break;
            
            case MHBeautyType_Mopi:
            [_beautyManager setBuffing:(int)beautyLevel];
           
            break;
            case MHBeautyType_White:
            [_beautyManager setSkinWhiting:(int)beautyLevel];
            break;
            case MHBeautyType_Ruddiess:
            [_beautyManager setRuddiness:(int)beautyLevel];
            break;
            case MHBeautyType_Brightness:
            [_beautyManager setBrightnessLift:(int)beautyLevel];
            break;
            
        default:
            break;
    }
}

//美型
-(void)handleFaceBeautyWithType:(NSInteger)type sliderValue:(NSInteger)value {
    switch (type) {
        case MHBeautyFaceType_Original:{
            [self.beautyManager setFaceLift:0];
            [self.beautyManager setBigEye:0];
            [self.beautyManager setMouthLift:0];
            [self.beautyManager setNoseLift:0];
            [self.beautyManager setChinLift:0];
            [self.beautyManager setForeheadLift:0];
            [self.beautyManager setEyeBrownLift:0];
            [self.beautyManager setEyeAngleLift:0];
            [self.beautyManager setEyeAlaeLift:0];
            [self.beautyManager setShaveFaceLift:0];
            [self.beautyManager setEyeDistanceLift:0];
        }
            break;
        case MHBeautyFaceType_ThinFace:
            [self.beautyManager setFaceLift:(int)value];
            break;
        case MHBeautyFaceType_BigEyes:
            [self.beautyManager setBigEye:(int)value];
            break;
        case MHBeautyFaceType_Mouth:
            [self.beautyManager setMouthLift:(int)value];
            break;
        case MHBeautyFaceType_Nose:
            [self.beautyManager setNoseLift:(int)value];
            break;
        case MHBeautyFaceType_Chin:
            [self.beautyManager setChinLift:(int)value];
            break;
        case MHBeautyFaceType_Forehead:
            [self.beautyManager setForeheadLift:(int)value];
            break;
        case MHBeautyFaceType_Eyebrow:
            [self.beautyManager setEyeBrownLift:(int)value];
            break;
        case MHBeautyFaceType_Canthus:
            [self.beautyManager setEyeAngleLift:(int)value];
            break;
        case MHBeautyFaceType_EyeAlae:
            [self.beautyManager setEyeAlaeLift:(int)value];
            break;
        case MHBeautyFaceType_EyeDistance:
            [self.beautyManager setEyeDistanceLift:(int)value];
            break;
        case MHBeautyFaceType_ShaveFace:
            [self.beautyManager setShaveFaceLift:(int)value];
            break;
        case MHBeautyFaceType_LongNose:
            [self.beautyManager setLengthenNoseLift:(int)value];
            break;
        default:
            break;
    }
   
}

//一键美颜
- (void)handleQuickBeautyValue:(MHBeautiesModel *)model {
    [self.beautyManager setFaceLift:model.face_defaultValue.intValue];
    [self.beautyManager setBigEye:model.bigEye_defaultValue.intValue];
    [self.beautyManager setMouthLift:model.mouth_defaultValue.intValue];
    [self.beautyManager setNoseLift:model.nose_defaultValue.intValue];
    [self.beautyManager setChinLift:model.chin_defaultValue.intValue];
    [self.beautyManager setForeheadLift:model.forehead_defaultValue.intValue];
    [self.beautyManager setEyeBrownLift:model.eyeBrown_defaultValue.intValue];
    [self.beautyManager setEyeAngleLift:model.eyeAngle_defaultValue.intValue];
    [self.beautyManager setEyeAlaeLift:model.eyeAlae_defaultValue.intValue];
    [self.beautyManager setShaveFaceLift:model.shaveFace_defaultValue.intValue];
    [self.beautyManager setEyeDistanceLift:model.eyeDistance_defaultValue.intValue];
    if (self.isTX) {
        if ([self.delegate respondsToSelector:@selector(beautyEffectWithLevel:whitenessLevel:ruddinessLevel:)]) {
            
            [self.delegate beautyEffectWithLevel:model.buffingValue.integerValue whitenessLevel:model.whiteValue.integerValue ruddinessLevel:model.ruddinessValue.integerValue];
        }
    } else {
            [_beautyManager setRuddiness:(model.ruddinessValue.intValue)*100/9.0];
            [_beautyManager setSkinWhiting:(model.whiteValue.intValue)*100/9.0];
            [_beautyManager setBuffing:(model.buffingValue.intValue)*100/9.0];

    }
}


- (void)handleQuickBeautyWithSliderValue:(NSInteger)value quickBeautyModel:(nonnull MHBeautiesModel *)model{
    if (!model) {
        return;
    }
    if (value >= model.bigEye_minValue.integerValue && value <= model.bigEye_maxValue.integerValue) {
        [self.beautyManager setBigEye:(int)value];
        
    }
    if (value >= model.face_minValue.integerValue && value <= model.face_minValue.integerValue) {
        [self.beautyManager setFaceLift:(int)value];
        
    }
    if (value >= model.mouth_minValue.integerValue && value <= model.mouth_maxValue.integerValue) {
        [self.beautyManager setMouthLift:(int)value];
        
    }
    if (value >= model.shaveFace_minValue.integerValue && value <= model.shaveFace_maxValue.integerValue) {
        [self.beautyManager setShaveFaceLift:(int)value];
        
    }
    if (value >= model.eyeAlae_minValue.integerValue && value <= model.eyeAlae_maxValue.integerValue) {
        [self.beautyManager setEyeAlaeLift:(int)value];
        
    }
    if (value >= model.eyeAngle_minValue.integerValue && value <= model.eyeAngle_maxValue.integerValue) {
        [self.beautyManager setEyeAngleLift:(int)value];
        
    }
    if (value >= model.eyeBrown_minValue.integerValue && value <= model.eyeBrown_maxValue.integerValue) {
        [self.beautyManager setEyeBrownLift:(int)value];
        
    }
    if (value >= model.forehead_minValue.integerValue && value <= model.forehead_maxValue.integerValue) {
        [self.beautyManager setForeheadLift:(int)value];
        
    }
    if (value >= model.chin_minValue.integerValue && value <= model.chin_maxValue.integerValue) {
        [self.beautyManager setChinLift:(int)value];
        
    }
    if (value >= model.nose_minValue.integerValue && value <= model.nose_maxValue.integerValue) {
        [self.beautyManager setNoseLift:(int)value];
        
    }
    if (value >= model.eyeDistance_minValue.integerValue && value <= model.eyeDistance_maxValue.integerValue) {
        [self.beautyManager setEyeDistanceLift:(int)value];
        
    }
}
//滤镜
- (void)handleFiltersEffectWithType:(NSInteger)filter  withFilterName:(nonnull NSString *)filterName{
    MHFilterModel *model = [MHFilterModel unzipFiltersFile:filterName];
    if (model) {
        NSDictionary *dic = @{@"kUniformList":model.uniformList,
              @"kUniformData":model.uniformData,
              @"kUnzipDesPath":model.unzipDesPath,
              @"kName":model.name,
              @"kFragmentShader":model.fragmentShader
        };
        [_beautyManager setFilterType:filter newFilterInfo:dic];
    } else {
        [_beautyManager setFilterType:filter newFilterInfo:[NSDictionary dictionary]];
    }
}

//水印
- (void)handleWatermarkWithModel:(MHBeautiesModel *)model {
    [self.beautyManager setWatermark:model.imgName alignment:model.aliment];
}
//特效
- (void)handleSpecificWithType:(NSInteger)type {
    [self.beautyManager setJitterType:type];
}

//哈哈镜
-(void)handleMagnify:(NSInteger)type {
    [_beautyManager setDistortType:type];
}

//贴纸
- (void)handleStickerEffect:(NSString *)stickerContent sticker:(StickerDataListModel *)model{
    [self.beautyManager setSticker:stickerContent];
    if (!model || model.beauty.length ==0 || !model.beauty) {
        return;
    }
    
        //高级版本贴纸
        if (model.face_lift.integerValue >= 0) {
            [self.beautyManager setFaceLift:(int)model.face_lift.integerValue];
        }
        if (model.big_eye.integerValue >= 0) {
            [self.beautyManager setBigEye:(int)model.big_eye.integerValue];
        }
        
        if (model.lengthen_noseLift.integerValue >= 0) {
            [self.beautyManager setLengthenNoseLift:(int)model.lengthen_noseLift.integerValue];
            
        }
        if (model.eye_length.integerValue >= 0) {
            [self.beautyManager setEyeDistanceLift:(int)model.eye_length.integerValue];
        }
        
        if (model.face_shave.integerValue >= 0) {
            [self.beautyManager setShaveFaceLift:(int)model.face_shave.integerValue];
        }
        
        if (model.eye_alat.integerValue >= 0) {
            [self.beautyManager setEyeAlaeLift:(int)model.eye_alat.integerValue];
        }
        
        if (model.eye_corner.integerValue >= 0) {
            [self.beautyManager setEyeAngleLift:(int)model.eye_corner.integerValue];
        }
        
        if (model.eye_brow.integerValue >= 0) {
            [self.beautyManager setEyeBrownLift:(int)model.eye_brow.integerValue];
        }
        
        if (model.forehead_lift.integerValue >= 0) {
            [self.beautyManager setForeheadLift:(int)model.forehead_lift.integerValue];
        }
        
        if (model.chin_lift.integerValue >= 0) {
            [self.beautyManager setChinLift:(int)model.chin_lift.integerValue];
        }
        
        if (model.nose_lift.integerValue >= 0) {
            [self.beautyManager setNoseLift:(int)model.nose_lift.integerValue];
        }
        
        if (model.mouse_lift.integerValue >= 0) {
            [self.beautyManager setMouthLift:(int)model.mouse_lift.integerValue];
            
        }
        
        if (self.isTX) {
            if ([self.delegate respondsToSelector:@selector(beautyEffectWithLevel:whitenessLevel:ruddinessLevel:)]) {
                [self.delegate beautyEffectWithLevel:model.mopi.integerValue whitenessLevel:model.white.integerValue ruddinessLevel:model.ruddies.integerValue];
            }
        } else {
            [self.beautyManager setRuddiness:(model.mopi.intValue)*100/9.0];
            [self.beautyManager setSkinWhiting:(model.white.intValue)*100/9.0];
            [self.beautyManager setBuffing:(model.ruddies.intValue)*100/9.0];

        }
    
}

#pragma mark - 贴纸解析
- (void)getSticks {
     __weak typeof(self) weakSelf = self;
    dispatch_async(dispatch_queue_create("com.suory.stickers", DISPATCH_QUEUE_SERIAL), ^{
        [[StickerManager sharedManager] requestStickersListWithUrl:kBasicStickerURL Success:^(NSArray<StickerDataListModel *> * _Nonnull stickerArray) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf.stickersView configureStickers:stickerArray];
            });
        } Failed:^{
            
        }];
    });
}


#pragma mark - collectionView
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.array.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    MHBeautyMenuCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"MHBeautyMenuCell" forIndexPath:indexPath];
    cell.menuModel = self.array[indexPath.row];
    return cell;
}

- (CGSize)collectionView:(UICollectionView *)collectionView
                  layout:(UICollectionViewLayout *)collectionViewLayout
  sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    return CGSizeMake((window_width-40)/self.array.count, MHMeiyanMenusCellHeight);
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    
    MHBeautyMenuCell *cell = (MHBeautyMenuCell *)[collectionView cellForItemAtIndexPath:indexPath];
    MHBeautiesModel *currentModel = self.array[indexPath.row];
    currentModel.isSelected = YES;
    if (self.lastIndex >= 0) {
        MHBeautiesModel *lastModel = self.array[self.lastIndex];
        lastModel.isSelected = NO;
    }
    
    self.lastIndex = indexPath.row;
    [self.collectionView reloadData];
    [self showBeautyViews:self.viewsArr[indexPath.row]];
   
}

#pragma mark - 切换美颜效果分类
- (void)showBeautyViews:(UIView *)currentView {
    [self.superView addSubview:currentView];
    [currentView setY:window_height - currentView.frame.size.height - BottomIndicatorHeight];
    self.currentView = currentView;
}

#pragma mark - lazy
- (NSMutableArray *)viewsArr {
    if (!_viewsArr) {
        _viewsArr = [NSMutableArray arrayWithObjects:self.stickersView,self.beautyAssembleView,self.specificAssembleView,self.magnifiedView, nil];
    }
    return _viewsArr;
}

- (MHBeautyAssembleView *)beautyAssembleView {
    if (!_beautyAssembleView) {
        _beautyAssembleView = [[MHBeautyAssembleView alloc] initWithFrame:CGRectMake(0, window_height-MHBeautyAssembleViewHeight-BottomIndicatorHeight, window_width, MHBeautyAssembleViewHeight)];
        _beautyAssembleView.delegate = self;
       
    }
    return _beautyAssembleView;
}

- (MHSpecificAssembleView *)specificAssembleView {
    if (!_specificAssembleView) {
        _specificAssembleView = [[MHSpecificAssembleView alloc] initWithFrame:CGRectMake(0, window_height-MHSpecificAssembleViewHeight-BottomIndicatorHeight, window_width, MHSpecificAssembleViewHeight)];
        _specificAssembleView.delegate = self;
    }
    return _specificAssembleView;
}
- (MHMagnifiedView *)magnifiedView {
    if (!_magnifiedView) {
        _magnifiedView = [[MHMagnifiedView alloc] initWithFrame:CGRectMake(0, window_height-MHMagnifyViewHeight-BottomIndicatorHeight, window_width, MHMagnifyViewHeight)];
        _magnifiedView.delegate = self;
    }
    return _magnifiedView;
}

- (MHStickersView *)stickersView {
    if (!_stickersView) {
        _stickersView = [[MHStickersView alloc] initWithFrame:CGRectMake(0, window_height-MHStickersViewHeight-BottomIndicatorHeight , window_width, MHStickersViewHeight)];
        _stickersView.delegate = self;
    }
    return _stickersView;
}

-(NSMutableArray *)array {
    if (!_array) {
        NSArray *arr = @[@"贴纸",@"美颜",@"特效",@"哈哈镜"];
        NSArray *imgArr = @[StickerImg,BeautyImg,SpecificImg,HahaImg];
        _array = [NSMutableArray array];
        for (int i = 0; i<arr.count; i++) {
           MHBeautiesModel *model = [[MHBeautiesModel alloc] init];
            model.imgName = imgArr[i];
            model.beautyTitle = arr[i];
            model.menuType = MHBeautyMenuType_Menu;
            [_array addObject:model];
        }
    }
    return _array;
}

- (UICollectionView *)collectionView {
    if (!_collectionView) {
        UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
        layout.minimumLineSpacing = 0;
        layout.minimumInteritemSpacing = 10;
        layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        layout.sectionInset = UIEdgeInsetsMake(0, 20, 0,20);
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, 0, window_width, self.height) collectionViewLayout:layout];
        _collectionView.backgroundColor = [UIColor clearColor];
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [_collectionView registerClass:[MHBeautyMenuCell class] forCellWithReuseIdentifier:@"MHBeautyMenuCell"];
    }
    return _collectionView;
}


@end
