//
//  MSVSnapshotGenerator.h
//  MovieousShortVideo
//
//  Created by Chris Wang on 2019/3/31.
//  Copyright © 2019 Movieous Team. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <MovieousBase/MovieousBase.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Video snapshot result code.
 */
typedef NS_ENUM(NSInteger, MSVSnapshotGeneratorResult) {
    /**
     * Snapshot generator succeeded.
     */
    MSVSnapshotGeneratorSucceeded   = 0,
    /**
     * Snapshot generator failed.
     */
    MSVSnapshotGeneratorFailed      = 1,
    /**
     * Snapshot generator cancelled.
     */
    MSVSnapshotGeneratorCancelled   = 2,
};

/**
 * The type of an aperture mode.
 */
typedef NS_ENUM(NSInteger, MSVSnapshotGeneratorApertureMode) {
    /**
     * Both pixel aspect ratio and clean aperture will be applied.
     * An image's clean aperture is a region of video free from transition artifacts caused by the encoding of the signal.
     */
    MSVSnapshotGeneratorApertureModeCleanAperture       = 0,
    /**
     * Only pixel aspect ratio will be applied.
     * The image is not cropped to the clean aperture region, but it is scaled according to the pixel aspect ratio. Use this option when you want to see all the pixels in your video, including the edges.
     */
    MSVSnapshotGeneratorApertureModeProductionAperture  = 1,
    /**
     * Neither pixel aspect ratio nor clean aperture will be applied.
     * The image is not cropped to the clean aperture region and is not scaled according to the pixel aspect ratio. The encoded dimensions of the image description are displayed.
     */
    MSVSnapshotGeneratorApertureModeEncodedPixels       = 2,
};


/**
 * A block that you use to receive thumbnail images generated from an asset.Pass a block of this type to generateCGImagesAsynchronouslyForTimes:completionHandler:, and use that block to receive the generated images. The generateCGImagesAsynchronously(forTimes:completionHandler:) method executes this handler once for each time value you specified.
The block takes five arguments:
 *
 * @param requestedTime The time for which you requested an image.
 * @param image The image that was generated, or NULL if the image could not be generated.
 * @param actualTime The time at which the image was actually generated.
 * @param result A result code indicating whether the image generation process succeeded, failed, or was cancelled.
 * @param error If result is AVAssetImageGeneratorFailed, an error object that describes the problem.
 */
typedef void (^MSVSnapshotGeneratorCompletionHandler)(NSTimeInterval requestedTime, UIImage *_Nullable image, NSTimeInterval actualTime, MSVSnapshotGeneratorResult result, NSError * _Nullable error);

/**
 * Snapshot generator.
 */
@interface MSVSnapshotGenerator : NSObject
<
NSCopying
>

/* Specifies the maximum dimensions for generated image.  Default (CGSizeZero) is the asset's unscaled dimensions.
   AVAssetImageGenerator will scale images such that they fit within the defined bounding box.
   Images will never be scaled up.  The aspect ratio of the scaled image will be defined by the apertureMode property. */
@property (nonatomic, assign) CGSize maximumSize;

/* Specifies the aperture mode for the generated image.  Default is AVAssetImageGeneratorApertureModeCleanAperture. */
@property (nonatomic, assign) MSVSnapshotGeneratorApertureMode apertureMode;

/**
 * The maximum amount of time before a requested time you can generate an image.
 * The default value is kCMTimePositiveInfinity. Set the values of requestedTimeToleranceBefore and requestedTimeToleranceAfter to kCMTimeZero to request frame-accurate image generation; this may incur additional decoding delay.
 */
@property (nonatomic, assign) NSTimeInterval requestedTimeToleranceBefore;

/**
 * The maximum length of time after a requested time you can generate an image.
 * The default value is kCMTimePositiveInfinity. Set the values of requestedTimeToleranceBefore and requestedTimeToleranceAfter to kCMTimeZero to request frame-accurate image generation; this may incur additional decoding delay.
 */
@property (nonatomic, assign) NSTimeInterval requestedTimeToleranceAfter;

/**
 * Returns a CFRetained CGImageRef for an asset at or near the specified time.
 *
 * @param requestedTime The time at which the image of the asset is to be created.
 * @param actualTime A pointer to a CMTime to receive the time at which the image was actually generated. If you are not interested in this information, pass NULL.
 * @param outError An error object describing the reason for failure, in the event that this method returns NULL.
 *
 * @return The generated image object.
 */
- (UIImage *_Nullable)generateSnapshotAtTime:(NSTimeInterval)requestedTime actualTime:(nullable NSTimeInterval *)actualTime error:(NSError * _Nullable * _Nullable)outError;

/**
 * @abstract Returns a series of CGImageRefs for an asset at or near the specified times.
 * @discussion Employs an efficient "batch mode" for getting images in time order.The client will receive exactly one handler callback for each requested time in requestedTimes.Changes to generator properties (snap behavior, maximum size, etc...) will not affect outstanding asynchronous image generation requests.The generated image is not retained.  Clients should retain the image if they wish it to persist after the completion handler returns.
 *
 * @param requestedTimes An NSArray of NSValues, each containing a CMTime, specifying the asset times at which an image is requested.
 * @param handler A block that will be called when an image request is complete.
 */
- (void)generateSnapshotsAsynchronouslyForTimes:(NSArray<NSNumber *> *)requestedTimes completionHandler:(MSVSnapshotGeneratorCompletionHandler)handler;

/**
 * Cancels all outstanding image generation requests.Calls the handler block with AVAssetImageGeneratorCancelled for each image time in every previous invocation of -generateCGImagesAsynchronouslyForTimes:completionHandler:for which images have not yet been supplied.
 */
- (void)cancelAllSnapshotGeneration;

@end

NS_ASSUME_NONNULL_END
