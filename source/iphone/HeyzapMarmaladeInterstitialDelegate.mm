#import "s3eEdk.h"

#import "HeyzapMarmaladeInterstitialDelegate.h"

#import "Heyzap_internal.h"

@implementation HeyzapMarmaladeInterstitialDelegate
/** The `HZAdsDelegate` protocol provides global information about our ads. If you want to know if we had an ad to show after calling `showAd` (for example, to fallback to another ads provider). It is recommend using the `showAd:completion:` method instead. */

/**
 *  Called when we succesfully show an ad.
 *
 *  @param tag The identifier for the ad.
 */
- (void)didShowAdWithTag: (NSString *) tag {
    const char *tag_c = [(tag ? tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_SHOW, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}

/**
 *  Called when an ad fails to show
 *
 *  @param tag   The identifier for the ad.
 *  @param error An NSError describing the error
 */
- (void)didFailToShowAdWithTag: (NSString *) tag andError: (NSError *)error {
    const char *tag_c = [(tag ? tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_FAILED_TO_SHOW, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}


/**
 *  Called when a valid ad is received
 *
 *  @param tag The identifier for the ad.
 */
- (void)didReceiveAdWithTag: (NSString *) tag {
    const char *tag_c = [(tag ? tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_AVAILABLE, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}


/**
 *  Called when our server fails to send a valid ad, like when there is a 500 error.
 *
 *  @param tag The identifier for the ad.
 */
- (void)didFailToReceiveAdWithTag: (NSString *) tag {
    const char *tag_c = [(tag ? tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_FAILED_TO_FETCH, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}


/**
 *  Called when the user clicks on an ad.
 *
 *  @param tag An identifier for the ad.
 */
- (void)didClickAdWithTag: (NSString *) tag {
    const char *tag_c = [(tag ? tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_CLICK, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}


/**
 *  Called when the ad is dismissed.
 *
 *  @param tag An identifier for the ad.
 */
- (void)didHideAdWithTag: (NSString *) tag {
    const char *tag_c = [(tag ? tag : @"") UTF8String];
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_HIDE, (void *)tag_c, (strlen(tag_c) + 1 /*Include `\0`*/));
}


/**
 *  Called when an ad will use audio
 */
- (void)willStartAudio {
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_AUDIO_STARTED);
}


/**
 *  Called when an ad will finish using audio
 */
- (void) didFinishAudio {
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZINTERSTITIAL_AUDIO_FINISHED);
}

@end