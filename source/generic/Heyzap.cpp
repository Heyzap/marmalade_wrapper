/*
Generic implementation of the Heyzap extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#include "Heyzap_internal.h"
s3eResult HeyzapInit()
{
    //Add any generic initialisation code here
    return HeyzapInit_platform();
}

void HeyzapTerminate()
{
    //Add any generic termination code here
    HeyzapTerminate_platform();
}

void HeyzapStart(const char* pubId)
{
	HeyzapStart_platform(pubId);
}

void HeyzapFetchInterstitial(const char* tag)
{
	HeyzapFetchInterstitial_platform(tag);
}

void HeyzapShowInterstitial(const char* tag)
{
	HeyzapShowInterstitial_platform(tag);
}

void HeyzapFetchVideo(const char* tag)
{
	HeyzapFetchVideo_platform(tag);
}

void HeyzapShowVideo(const char* tag)
{
	HeyzapShowVideo_platform(tag);
}

void HeyzapFetchRewarded(const char* tag)
{
	HeyzapFetchRewarded_platform(tag);
}

void HeyzapShowRewarded(const char* tag)
{
	HeyzapShowRewarded_platform(tag);
}

void HeyzapShowBanner(bool top, const char* tag)
{
	HeyzapShowBanner_platform(top, tag);
}
void HeyzapHideBanner()
{
	HeyzapHideBanner_platform();
}

void HeyzapDestroyBanner()
{
	HeyzapDestroyBanner_platform();
}

void HeyzapStartTestActivity()
{
	HeyzapStartTestActivity_platform();
}
