//
//  MHFiltersView.m

//滤镜

#import "MHFiltersView.h"
#import "MHBeautyMenuCell.h"
#import "MHBeautyParams.h"
#import "MHBeautiesModel.h"
#define kFilterName @"kFilterName"
@interface MHFiltersView ()<UICollectionViewDelegate,UICollectionViewDataSource>
@property (nonatomic, strong) UICollectionView *collectionView;
@property (nonatomic, strong) NSMutableArray *array;
@property (nonatomic, assign) NSInteger lastIndex;

@end
@implementation MHFiltersView

- (instancetype)initWithFrame:(CGRect)frame {
    if (self = [super initWithFrame:frame]) {
        [self addSubview:self.collectionView];
        self.lastIndex = 0;
    }
    return self;
}

- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return self.array.count;
}

- (__kindof UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    MHBeautyMenuCell *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"MHFilterCell" forIndexPath:indexPath];
    cell.menuModel = self.array[indexPath.row];
    return cell;
}

- (CGSize)collectionView:(UICollectionView *)collectionView
                  layout:(UICollectionViewLayout *)collectionViewLayout
  sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    
    return CGSizeMake(([UIScreen mainScreen].bounds.size.width-20) /MHFilterItemColumn, MHFilterCellHeight);
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    if (self.lastIndex == indexPath.row) {
        return;
    }
    MHBeautiesModel *model = self.array[indexPath.row];
    model.isSelected = !model.isSelected;
    
    if ([self.delegate respondsToSelector:@selector(handleFiltersEffect: filterName:)]) {
        [self.delegate handleFiltersEffect:indexPath.row filterName:model.imgName];
    }
        
        
    MHBeautiesModel *lastModel = self.array[self.lastIndex];
    lastModel.isSelected = !lastModel.isSelected;
    
    [self.collectionView reloadData];
    self.lastIndex = indexPath.row;
}

#pragma mark - lazy
/*
 @"source",@"hudson",@"hefe",@"anitque",@"whitecat",@"amaro"
 @"lomo",@"latte",,@"sunset",@"sakura",@"romance",@"earlybird",@"emerald"
 @"freud",@"healthy"
 */

-(NSMutableArray *)array {
    if (!_array) {
        NSArray *arr = @[@"filterOrigin",@"langman2",@"qingxin2",@"weimei2",@"fennen2", @"huaijiu2", @"landiao2",@"qingliang2",@"rixi2",@"kevin",@"blackcat",@"brooklyn",@"calm", @"cool",@"blackwhite",@"romance",@"emerald",@"whitecat"];
        NSArray *filtersArr = @[@"原图",@"浪漫",@"清新",@"唯美",@"粉嫩",@"怀旧",@"蓝调",@"清凉",@"日系",@"凯文",@"黑猫",@"布鲁克林",@"平静", @"冷酷",@"黑白",@"恋爱",@"翡翠",@"简报"];
        _array = [NSMutableArray array];
        for (int i = 0; i<arr.count; i++) {
            MHBeautiesModel *model = [MHBeautiesModel new];
            model.imgName = arr[i];
            model.beautyTitle = filtersArr[i];
            model.isSelected = i == 0 ? YES : NO;
            model.type = i;
            model.menuType = MHBeautyMenuType_Filter;
            [_array addObject:model];
        }
    }
    return _array;
}

- (UICollectionView *)collectionView {
    if (!_collectionView) {
        UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
        layout.minimumLineSpacing = 0;
        layout.minimumInteritemSpacing = 15;
        layout.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        layout.sectionInset = UIEdgeInsetsMake(10, 10, 10, 10);
        _collectionView = [[UICollectionView alloc] initWithFrame:CGRectMake(0, 0, window_width,self.height) collectionViewLayout:layout];
        _collectionView.backgroundColor = [UIColor whiteColor];
        _collectionView.showsHorizontalScrollIndicator = NO;
        _collectionView.delegate = self;
        _collectionView.dataSource = self;
        [_collectionView registerClass:[MHBeautyMenuCell class] forCellWithReuseIdentifier:@"MHFilterCell"];
    }
    return _collectionView;
}

@end
