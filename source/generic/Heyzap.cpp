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

void start(const char* pubId)
{
	start_platform(pubId);
}

void fetchInterstitial(const char* tag)
{
	fetchInterstitial_platform(tag);
}

void showInterstitial(const char* tag)
{
	showInterstitial_platform(tag);
}

void fetchVideo(const char* tag)
{
	fetchVideo_platform(tag);
}

void showVideo(const char* tag)
{
	showVideo_platform(tag);
}

void fetchRewarded(const char* tag)
{
	fetchRewarded_platform(tag);
}

void showRewarded(const char* tag)
{
	showRewarded_platform(tag);
}

void startTestActivity()
{
	startTestActivity_platform();
}
