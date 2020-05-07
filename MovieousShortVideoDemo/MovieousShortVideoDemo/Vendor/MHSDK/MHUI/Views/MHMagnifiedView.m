//
//  MHMagnifiedView.m

//哈哈镜

#import "MHMagnifiedView.h"
#import "MHMagnifiedEffectCell.h"
#import "MHBeautiesModel.h"
#import "MHBeautyParams.h"

@interface MHMagnifiedView ()<UICollectionViewDelegate,UICollectionViewDataSource>
@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) NSMutableArray *array;
@property (nonatomic, assign) NSInteger lastIndex;
@end
@implementation MHMagnifiedView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self addSubview:self.collectionView];
    }
    return self;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.array.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    MHMagnifiedEffectCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"MHMagnifiedEffectCell" forIndexPath:indexPath];
    cell.model = self.array[indexPath.row];
    return cell;
}

- (CGSize)collectionView:(UICollectionView *)collectionView
                  layout:(UICollectionViewLayout *)collectionViewLayout
  sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    return CGSizeMake((window_width-20)/4.5, MHMagnifyViewHeight-20);
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    if (self.lastIndex == indexPath.row) {
        return;
    }
    MHBeautiesModel *model = self.array[indexPath.row];
    model.isSelected = !model.isSelected;
    if (self.lastIndex >= 0) {
        MHBeautiesModel *lastModel = self.array[self.lastIndex];
        lastModel.isSelected = !lastModel.isSelected;
    }
    [self.collectionView reloadData];
    self.lastIndex = indexPath.row;
    if ([self.delegate respondsToSelector:@selector(handleMagnify:)]) {
        [self.delegate handleMagnify:indexPath.row];
    }
}

#pragma mark - lazy
-(NSMutableArray *)array {
    if (!_array) {
        NSArray *arr = @[@"无", @"外星人", @"梨梨脸", @"瘦瘦脸", @"镜像脸", @"片段脸", @"水面倒影", @"螺旋镜面", @"鱼眼相机",@"左右镜像"];
        NSArray *imgs = @[@"haha_cancel",@"waixingren",@"lilian",@"shoushou",@"shangxia",@"pianduanlian",@"daoying",@"luoxuan",@"yuyan",@"zuoyou"];
        _array = [NSMutableArray array];
        for (int i = 0; i<arr.count; i++) {
            MHBeautiesModel *model = [MHBeautiesModel new];
            model.beautyTitle = arr[i];
            model.imgName = imgs[i];
            model.isSelected = i == 0 ? YES : NO;
            model.menuType = MHBeautyMenuType_Magnify;
            model.type = i;
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
        layout.sectionInset = UIEdgeInsetsMake(10, 10, 0, 10);
        layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, 0, window_width, self.height) collectionViewLayout:layout];
        _collectionView.backgroundColor = [UIColor whiteColor];
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [_collectionView registerClass:[MHMagnifiedEffectCell class] forCellWithReuseIdentifier:@"MHMagnifiedEffectCell"];
    }
    return _collectionView;
}
@end
