/*
 * Internal header for the Heyzap extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 */

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */


#ifndef HEYZAP_INTERNAL_H
#define HEYZAP_INTERNAL_H

#include "s3eTypes.h"
#include "Heyzap.h"
#include "Heyzap_autodefs.h"


/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult HeyzapInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult HeyzapInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void HeyzapTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void HeyzapTerminate_platform();
void start_platform(const char* pubId);

void fetchInterstitial_platform(const char* tag);

void showInterstitial_platform(const char* tag);

void fetchVideo_platform(const char* tag);

void showVideo_platform(const char* tag);

void fetchRewarded_platform(const char* tag);

void showRewarded_platform(const char* tag);

void startTestActivity_platform();


#endif /* !HEYZAP_INTERNAL_H */