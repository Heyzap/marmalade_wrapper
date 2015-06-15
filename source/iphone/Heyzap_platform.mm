/*
 * iphone-specific implementation of the Heyzap extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "Heyzap_internal.h"

s3eResult HeyzapInit_platform()
{
    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void HeyzapTerminate_platform()
{ 
}

void HeyzapStart_platform(const char* pubId)
{
}

void HeyzapFetchInterstitial_platform(const char* tag)
{
}

void HeyzapShowInterstitial_platform(const char* tag)
{
}

void HeyzapFetchVideo_platform(const char* tag)
{
}

void HeyzapShowVideo_platform(const char* tag)
{
}

void HeyzapFetchRewarded_platform(const char* tag)
{
}

void HeyzapShowRewarded_platform(const char* tag)
{
}

void HeyzapStartTestActivity_platform()
{
}
