/*
 * iphone-specific implementation of the Heyzap extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#include "s3eEdk.h"

#include "Heyzap_internal.h"
#include "../../incoming/Headers/HeyzapAds.h"
#include "../../incoming/Headers/HZLog.h"

#include "HeyzapMarmaladeInterstitialDelegate.h"
#include "HeyzapMarmaladeVideoDelegate.h"
#include "HeyzapMarmaladeIncentivizedDelegate.h"

 #define HZ_FRAMEWORK_MARMALADE @"marmalade"

HeyzapMarmaladeInterstitialDelegate * interstitialDelegate;
HeyzapMarmaladeVideoDelegate * videoDelegate;
HeyzapMarmaladeIncentivizedDelegate * incentivizedDelegate;


s3eResult HeyzapInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void HeyzapTerminate_platform()
{ 
}

//todo: only run this code once
void HeyzapStart_platform(const char* pubId)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        interstitialDelegate = [[HeyzapMarmaladeInterstitialDelegate alloc] init];
        videoDelegate = [[HeyzapMarmaladeVideoDelegate alloc] init];
        incentivizedDelegate = [[HeyzapMarmaladeIncentivizedDelegate alloc] init];

        [HZInterstitialAd setDelegate: interstitialDelegate];
        [HZVideoAd setDelegate: videoDelegate];
        [HZIncentivizedAd setDelegate: incentivizedDelegate];

        [HeyzapAds networkCallbackWithBlock:^(NSString *network, NSString *callback) {
            const char *value = [[NSString stringWithFormat:@"%@,%@", network, callback] UTF8String]; // callback can be parsed as "network,callback" on the other side
            s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HZ_NETWORK_CALLBACK, (void *)value, strlen(value));
        }];

        [HeyzapAds setDebugLevel:HZDebugLevelVerbose];
        [HeyzapAds startWithPublisherID:[[NSString alloc] initWithUTF8String:pubId] andOptions:nil andFramework:HZ_FRAMEWORK_MARMALADE];
    });
}

void HeyzapFetchInterstitial_platform(const char* tag)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HZInterstitialAd fetchForTag:[[NSString alloc] initWithUTF8String:tag]];
    });
}

void HeyzapShowInterstitial_platform(const char* tag)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HZInterstitialAd showForTag:[[NSString alloc] initWithUTF8String:tag]];
    });
}

void HeyzapFetchVideo_platform(const char* tag)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HZVideoAd fetchForTag:[[NSString alloc] initWithUTF8String:tag]];
    });
}

void HeyzapShowVideo_platform(const char* tag)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HZVideoAd showForTag:[[NSString alloc] initWithUTF8String:tag]];
    });
}

void HeyzapFetchRewarded_platform(const char* tag)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HZIncentivizedAd fetchForTag:[[NSString alloc] initWithUTF8String:tag]];
    });
}

void HeyzapShowRewarded_platform(const char* tag)
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HZIncentivizedAd showForTag:[[NSString alloc] initWithUTF8String:tag]];
    });
}

void HeyzapStartTestActivity_platform()
{
    dispatch_sync(dispatch_get_main_queue(), ^{
        [HeyzapAds presentMediationDebugViewController];
    });
}
