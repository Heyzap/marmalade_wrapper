#include "../../incoming/HeyzapAds.framework/Headers/HZBannerAd.h"
#include "../../incoming/HeyzapAds.framework/Headers/HZBannerAdOptions.h"

@interface HeyzapMarmaladeBannerDelegate : NSObject <HZBannerAdDelegate>

/**
 *  Called when the banner ad is loaded.
 */
- (void)bannerDidReceiveAd:(HZBannerAd *)banner;

/**
 *  Called when the banner ad fails to load.
 *
 *  @param error An error describing the failure. 
 *
 *  If the underlying ad network provided an `NSError` object, it will be accessible in the `userInfo` dictionary
 *  with the `NSUnderlyingErrorKey`.
 */
- (void)bannerDidFailToReceiveAd:(HZBannerAd *)banner error:(NSError *)error;


/// @name Click-time Notifications

/**
 *  Called when the user clicks the banner ad.
 */
- (void)bannerWasClicked:(HZBannerAd *)banner;

@end