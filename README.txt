/**
 * Registers a callback to be called for an operating system event.
 *
 * The available callback types are listed in @ref HeyzapCallback.
 * @param cbid ID of the event for which to register.
 * @param fn callback function.
 * @param userdata Value to pass to the @e userdata parameter of @e NotifyFunc.
 * @return
 *  - @ref S3E_RESULT_SUCCESS if no error occurred.
 *  - @ref S3E_RESULT_ERROR if the operation failed.\n
 *
 * @see HeyzapUnRegister
 * @note For more information on the system data passed as a parameter to the callback
 * registered using this function, see the @ref HeyzapCallback enum.
 */
s3eResult HeyzapRegister(HeyzapCallback cbid, s3eCallback fn, void* userData);


/**
 * Unregister a callback for a given event.
 * @param cbid ID of the callback to unregister.
 * @param fn Callback Function.
 * @return
 * - @ref S3E_RESULT_SUCCESS if no error occurred.
 * - @ref S3E_RESULT_ERROR if the operation failed.\n
 * @note For more information on the systemData passed as a parameter to the callback
 * registered using this function, see the HeyzapCallback enum.
 * @note It is not necessary to define a return value for any registered callback.
 * @see HeyzapRegister
 */
s3eResult HeyzapUnRegister(HeyzapCallback cbid, s3eCallback fn);


/**
 * Start the Heyzap Engine
 * @param pubId your publisher id (found in our documentation)
 */
void HeyzapStart(const char* pubId);

/**
 * Fetch an interstitial ad with the given tag.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapFetchInterstitial(const char* tag);

/**
 * Show an interstitial ad with the given tag.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapShowInterstitial(const char* tag);

/**
 * Fetch a video ad with the given tag.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapFetchVideo(const char* tag);

/**
 * Show a video ad with the given tag.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapShowVideo(const char* tag);

/**
 * Fetch a rewarded video ad with the given tag.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapFetchRewarded(const char* tag);

/**
 * Show a rewarded video ad with the given tag.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapShowRewarded(const char* tag);


/**
 * Start the Heyzap Mediation Test Activity. This activity allows you to test the integration of other networks into the heyzap waterfall
 * @note This code should not be used in production, it is for testing purposes only.
 */
void HeyzapStartTestActivity();
