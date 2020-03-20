//
//  MSVDMusicsViewController.m
//  MovieousShortVideoDemo
//
//  Created by Chris Wang on 2020/2/22.
//  Copyright © 2020 Movieous Team. All rights reserved.
//

#import "MSVDMusicsViewController.h"
#import <M13ProgressSuite/M13ProgressViewRing.h>

typedef NS_ENUM(NSUInteger, MSVDMusicsTableViewCellState) {
    MSVDMusicsTableViewCellStateNormal,
    MSVDMusicsTableViewCellStatePlaying,
    MSVDMusicsTableViewCellStateLoading,
};

@interface MSVDMusicsTableViewCell : UITableViewCell

@property (nonatomic, assign) MSVDMusicsTableViewCellState state;

@end

@implementation MSVDMusicsTableViewCell {
    UIImageView *_coverImageView;
    UILabel *_nameLabel;
    UILabel *_authorLabel;
    UIImageView *_playIcon;
    UIImageView *_pauseIcon;
    M13ProgressViewRing *_progressView;
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    if (self = [super initWithStyle:style reuseIdentifier:reuseIdentifier]) {
        _state = MSVDMusicsTableViewCellStateNormal;
        
        _coverImageView = [UIImageView new];
        [self.contentView addSubview:_coverImageView];
        
        _nameLabel = [UILabel new];
        _nameLabel.font = [UIFont boldSystemFontOfSize:18];
        _nameLabel.textColor = UIColor.whiteColor;
        [self.contentView addSubview:_nameLabel];
        
        _authorLabel = [UILabel new];
        _authorLabel.font = [UIFont systemFontOfSize:13];
        _authorLabel.textColor = [UIColor colorWithR:150 G:150 B:150 A:1];
        [self.contentView addSubview:_authorLabel];
        
        _playIcon = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"play_white"]];
        [_coverImageView addSubview:_playIcon];
        
        _pauseIcon = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"pause_white"]];
        [_coverImageView addSubview:_pauseIcon];
        
        _progressView = [M13ProgressViewRing new];
        _progressView.secondaryColor = UIColor.whiteColor;
        _progressView.showPercentage = NO;
        _progressView.indeterminate = YES;
        [_coverImageView addSubview:_progressView];
        
        [_coverImageView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(@20);
            make.top.equalTo(@5);
            make.bottom.equalTo(@-5);
            make.width.equalTo(_coverImageView.mas_height);
        }];
        [_nameLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_coverImageView.mas_right).offset(10);
            make.bottom.equalTo(self.contentView.mas_centerY).offset(-2);
        }];
        [_authorLabel mas_makeConstraints:^(MASConstraintMaker *make) {
            make.left.equalTo(_nameLabel.mas_left);
            make.top.equalTo(self.contentView.mas_centerY).offset(2);
        }];
        [_playIcon mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_coverImageView);
            make.size.equalTo(@20);
        }];
        [_pauseIcon mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(_coverImageView);
            make.size.equalTo(@20);
        }];
        [_progressView mas_makeConstraints:^(MASConstraintMaker *make) {
            make.center.equalTo(@0);
            make.size.equalTo(@20);
        }];
    }
    return self;
}

- (void)setState:(MSVDMusicsTableViewCellState)state {
    switch (state) {
        case MSVDMusicsTableViewCellStateNormal:
            _playIcon.hidden = NO;
            _pauseIcon.hidden = YES;
            _progressView.hidden = YES;
            break;
        case MSVDMusicsTableViewCellStatePlaying:
            _playIcon.hidden = YES;
            _pauseIcon.hidden = NO;
            _progressView.hidden = YES;
            break;
        case MSVDMusicsTableViewCellStateLoading:
            _playIcon.hidden = YES;
            _pauseIcon.hidden = YES;
            _progressView.hidden = NO;
            break;
        default:
            break;
    }
}

- (void)updateWithMusic:(MSVDMusic *)music {
    [_coverImageView sd_setImageWithURL:music.coverURL];
    _nameLabel.text = music.name;
    _authorLabel.text = music.author;
    _playIcon.hidden = NO;
    _pauseIcon.hidden = YES;
    _progressView.hidden = YES;
}

@end

@interface MSVDMusicsViewController ()
<
UINavigationBarDelegate,
UITableViewDelegate,
UITableViewDataSource
>

@end

@implementation MSVDMusicsViewController {
    UITableView *_tableView;
    UINavigationBar *_navigationBar;
    AVPlayer *_musicPlayer;
    NSIndexPath *_currentPlayingIndexPath;
    BOOL _playerLoading;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    UINavigationItem *item = [[UINavigationItem alloc] initWithTitle:NSLocalizedString(@"MSVDMusicsViewController.musics", nil)];
    item.leftBarButtonItem = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"close_white"] style:UIBarButtonItemStylePlain target:self action:@selector(closeButtonPressed:)];
    item.leftBarButtonItem.tintColor = UIColor.whiteColor;
    item.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:NSLocalizedString(@"MSVDMusicsViewController.save", nil) style:UIBarButtonItemStyleDone target:self action:@selector(saveButtonPressed:)];
    item.rightBarButtonItem.tintColor = UIColor.whiteColor;
    
    _navigationBar = [UINavigationBar new];
    [_navigationBar pushNavigationItem:item animated:NO];
    _navigationBar.delegate = self;
    [self.view addSubview:_navigationBar];
    [_navigationBar mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(self.mas_topLayoutGuideBottom);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
    }];
    
    _tableView = [UITableView new];
    _tableView.dataSource = self;
    _tableView.delegate = self;
    [_tableView registerClass:MSVDMusicsTableViewCell.class forCellReuseIdentifier:@"cell"];
    [self.view addSubview:_tableView];
    [_tableView mas_makeConstraints:^(MASConstraintMaker *make) {
        make.top.equalTo(_navigationBar.mas_bottom);
        make.left.equalTo(@0);
        make.right.equalTo(@0);
        make.bottom.equalTo(@0);
    }];
    
    _musicPlayer = [AVPlayer new];
    
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(musicLibraryRefreshDone:) name:MSVDMusicsLibraryRefreshDoneNotification object:nil];
    [NSNotificationCenter.defaultCenter addObserver:self selector:@selector(musicDidUpdated:) name:MSVDMusicDidUpdatedNotification object:nil];
    
    [MSVDMusicsLibrary refresh];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context {
    if ([keyPath isEqualToString:@"status"]) {
        if (_musicPlayer.status == AVPlayerStatusReadyToPlay) {
            _playerLoading = NO;
            dispatch_async(dispatch_get_main_queue(), ^{
                MSVDMusicsTableViewCell *cell = [self->_tableView cellForRowAtIndexPath:self->_currentPlayingIndexPath];
                cell.state = MSVDMusicsTableViewCellStatePlaying;
            });
        }
    }
}

- (void)musicLibraryRefreshDone:(NSNotification *)notification {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self->_tableView reloadData];
    });
}

- (void)musicDidUpdated:(NSNotification *)notification {
    MSVDMusic *music = notification.object;
    if (music.localPath) {
        if ([_delegate respondsToSelector:@selector(musicsViewController:didSelectMusic:)]) {
            [_delegate musicsViewController:self didSelectMusic:music];
        }
        [SVProgressHUD dismissWithCompletion:^{
            [self dismiss];
        }];
    } else {
        [SVProgressHUD showProgress:music.progress status:NSLocalizedString(@"MSVDMusicsViewController.downloading", nil)];
    }
}

- (void)saveButtonPressed:(UIButton *)sender {
    self.view.userInteractionEnabled = NO;
    if (!_currentPlayingIndexPath) {
        [self dismiss];
        return;
    }
    MSVDMusic *music = MSVDMusicsLibrary.musics[_currentPlayingIndexPath.row];
    [SVProgressHUD showWithStatus:NSLocalizedString(@"MSVDMusicsViewController.downloading", nil)];
    [music download];
}

- (void)addPlayerObservers {
    [_musicPlayer.currentItem addObserver:self forKeyPath:@"status" options:NSKeyValueObservingOptionNew context:nil];
}

- (void)removePlayerObservers {
    [_musicPlayer.currentItem removeObserver:self forKeyPath:@"status"];
}

- (UIStatusBarAnimation)preferredStatusBarUpdateAnimation {
    return UIStatusBarAnimationFade;
}

- (UIStatusBarStyle)preferredStatusBarStyle {
    return UIStatusBarStyleDefault;
}

- (UIBarPosition)positionForBar:(id<UIBarPositioning>)bar {
    return UIBarPositionTopAttached;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    MSVDMusicsTableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    if (_currentPlayingIndexPath == indexPath) {
        if (cell.state == MSVDMusicsTableViewCellStateLoading) {
            return;
        }
        if (_musicPlayer.rate == 0) {
            [_musicPlayer play];
            cell.state = MSVDMusicsTableViewCellStatePlaying;
        } else {
            [_musicPlayer pause];
            cell.state = MSVDMusicsTableViewCellStateNormal;
        }
    } else {
        MSVDMusic *music = MSVDMusicsLibrary.musics[indexPath.row];
        if (_currentPlayingIndexPath) {
            [self removePlayerObservers];
            MSVDMusicsTableViewCell *playingCell = [tableView cellForRowAtIndexPath:_currentPlayingIndexPath];
            playingCell.state = MSVDMusicsTableViewCellStateNormal;
        }
        if (music.localPath) {
            [_musicPlayer replaceCurrentItemWithPlayerItem:[AVPlayerItem playerItemWithURL:[NSURL fileURLWithPath:music.localPath]]];
        } else {
            [_musicPlayer replaceCurrentItemWithPlayerItem:[AVPlayerItem playerItemWithURL:music.sourceURL]];
        }
        [_musicPlayer play];
        [self addPlayerObservers];
        _currentPlayingIndexPath = indexPath;
        cell.state = MSVDMusicsTableViewCellStateLoading;
        _playerLoading = YES;
    }
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 90;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return MSVDMusicsLibrary.musics.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    MSVDMusicsTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    MSVDMusic *music = MSVDMusicsLibrary.musics[indexPath.row];
    [cell updateWithMusic:music];
    if (indexPath == _currentPlayingIndexPath) {
        if (_playerLoading) {
            cell.state = MSVDMusicsTableViewCellStateLoading;
        } else {
            if (_musicPlayer.rate == 0) {
                cell.state = MSVDMusicsTableViewCellStateNormal;
            } else {
                cell.state = MSVDMusicsTableViewCellStatePlaying;
            }
        }
    }
    return cell;
}

- (void)closeButtonPressed:(UIButton *)sender {
    [self dismiss];
}

- (void)dismiss {
    [self removePlayerObservers];
    [_musicPlayer pause];
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (UIModalPresentationStyle)modalPresentationStyle {
    return UIModalPresentationFullScreen;
}

@end
