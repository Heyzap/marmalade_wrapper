#import "s3eEdk.h"

#import "HeyzapMarmaladeBannerDelegate.h"

#import "Heyzap_internal.h"

@implementation HeyzapMarmaladeBannerDelegate

/**
 *  Called when the banner ad is loaded.
 */
- (void)bannerDidReceiveAd:(HZBannerAd *)banner {
    const char *tag_c = [(banner.options.tag ? banner.options.tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZBANNER_LOADED, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}

/**
 *  Called when the banner ad fails to load.
 *
 *  @param error An error describing the failure. 
 *
 *  If the underlying ad network provided an `NSError` object, it will be accessible in the `userInfo` dictionary
 *  with the `NSUnderlyingErrorKey`.
 */
- (void)bannerDidFailToReceiveAd:(HZBannerAd *)banner error:(NSError *)error {
    const char *tag_c = [(banner && banner.options.tag ? banner.options.tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZBANNER_ERROR, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}


/// @name Click-time Notifications

/**
 *  Called when the user clicks the banner ad.
 */
- (void)bannerWasClicked:(HZBannerAd *)banner {
    const char *tag_c = [(banner.options.tag ? banner.options.tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZBANNER_CLICKED, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}

@end