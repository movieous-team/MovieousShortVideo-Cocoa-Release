//
//  MHSpecificEffectView.m


#import "MHSpecificEffectView.h"
#import "MHBeautyParams.h"
#import "MHBeautiesModel.h"
#import "MHBeautyMenuCell.h"
@interface MHSpecificEffectView ()<UICollectionViewDelegate,UICollectionViewDataSource>
@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) NSMutableArray *specificArr;//存特效数据模型
@property (nonatomic, assign) NSInteger lastIndex;

@end
@implementation MHSpecificEffectView
- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self addSubview:self.collectionView];
        self.lastIndex = 0;
    }
    return self;
}
#pragma mark - dataSource
- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.specificArr.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    MHBeautyMenuCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"MHSpecificCell" forIndexPath:indexPath];
    cell.menuModel = self.specificArr[indexPath.row];
    return cell;
}

- (CGSize)collectionView:(UICollectionView *)collectionView
                  layout:(UICollectionViewLayout *)collectionViewLayout
  sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    return CGSizeMake(([UIScreen mainScreen].bounds.size.width-20) /6, MHSpecificCellHeight);
}
#pragma mark - delegate
- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    if (self.lastIndex == indexPath.row) {
        return;
    }
    MHBeautiesModel *model = self.specificArr[indexPath.row];
    model.isSelected = !model.isSelected;

    if ([self.delegate respondsToSelector:@selector(handleSpecific:)]) {
            [self.delegate handleSpecific:indexPath.row];
        }
    MHBeautiesModel *lastModel = self.specificArr[self.lastIndex];
    lastModel.isSelected = !lastModel.isSelected;
    
    [self.collectionView reloadData];
    self.lastIndex = indexPath.row;
}
#pragma mark - lazy
//@"马赛克",@"圆形马赛克",@"三角马赛克",@"六边马赛克"
//@"mosaic",@"mosaic_circle",@"mosaic_sanjiao",@"mosaic_liubian"
-(NSMutableArray *)specificArr {
    if (!_specificArr) {
        NSArray *arr = @[@"noSpecific",@"chuqiao",@"doudong",@"shanbai",@"maoci", @"huanjue",@"mosaic",@"mosaic_circle",@"mosaic_sanjiao",@"mosaic_liubian"];
        NSArray *filtersArr = @[@"无",@"灵魂出窍",@"抖动",@"闪白",@"毛刺",@"幻觉",@"马赛克",@"圆形马赛克",@"三角马赛克",@"六边马赛克"];
        _specificArr = [NSMutableArray array];
        for (int i = 0; i<arr.count; i++) {
            MHBeautiesModel *model = [[MHBeautiesModel alloc] init];
            model.imgName = arr[i];
            model.beautyTitle = filtersArr[i];
            model.isSelected = i == 0 ? YES : NO;
            model.type = i;
            model.menuType = MHBeautyMenuType_Specify;
            [_specificArr addObject:model];
        }
    }
    return _specificArr;
}

- (UICollectionView *)collectionView {
    if (!_collectionView) {
        UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
        layout.minimumLineSpacing = 0;
        layout.minimumInteritemSpacing = 0;
        layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        layout.sectionInset = UIEdgeInsetsMake(20, 10, 0, 10);
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, 0, window_width,self.height) collectionViewLayout:layout];
        _collectionView.backgroundColor = [UIColor whiteColor];
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [_collectionView registerClass:[MHBeautyMenuCell class] forCellWithReuseIdentifier:@"MHSpecificCell"];
    }
    return _collectionView;
}

@end
