#include "s3e.h"
#include "IwDebug.h"
#include "Heyzap.h"

#include <string>
#include <vector>
#include <sstream>


#define CALLBACK_LOG_LIMIT 30

int32 PointerTouchEventCallback(s3ePointerTouchEvent* pEvent, void* pUserData);
std::vector<std::string> callbacks;
uint callbackCounter = 0;
bool showInter = false;
bool showVideo = false;
bool showRewarded = false;
int loopCounter = 0;

// these are used to identify the type of ad in a callback so we can reuse the methods that log them
void * INTERSTITIAL = &INTERSTITIAL;
void * VIDEO = &VIDEO;
void * INCENTIVIZED = &INCENTIVIZED;
void * NETWORK = &NETWORK;

/* Utility methods */
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}
/* End utility methods */

const char * callbackType(void * type) {
    if(type == INTERSTITIAL) {
        return "Interstitial";
    }

    if(type == VIDEO) {
        return "Video";
    }

    if(type == INCENTIVIZED) {
        return "Incentivized";
    }

    return "Network";
}

void setLastCallback(const char * callback) {
    std::string lastCallback = callback;
    callbacks.push_back(lastCallback);
    if(callbacks.size() > CALLBACK_LOG_LIMIT) {
        callbacks.erase(callbacks.begin());
    }
}

void setLastCallbackAsString(const char * callback, void * adType) {
    char buff[512];
    sprintf(buff, "[%u][%s] %s", callbackCounter++, callbackType(adType), callback);
    setLastCallback(buff);
}

void setLastCallbackAsStringWithTag(const char * callback, const char * tag, void * adType) {
    char buff[512];
    sprintf(buff, "[%u][%s] %s: %s", callbackCounter++, callbackType(adType), callback, tag);
    setLastCallback(buff);
}

void didShowAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didShowAdWithTag", tag, User);
    IwTrace(APP, ("didShowAdWithTag callback in heyzaptest - tag: %s strlen tag: %d", tag, strlen(tag)));
}

void didFailToShowAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didFailToShowAdWithTag", tag, User);
}

void didReceiveAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didReceiveAdWithTag", tag, User);
}

void didFailToReceiveAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didFailToReceiveAdWithTag", tag, User);
}

void didClickAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didClickAdWithTag", tag, User);
}

void didHideAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didHideAdWithTag", tag, User);
}

void willStartAudio(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsString("willStartAudio", User);
}

void didFinishAudio(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsString("didFinishAudio", User);
}

void didCompleteAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didCompleteAdWithTag", tag, User);
}

void didFailToCompleteAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didFailToCompleteAdWithTag", tag, User);
}

void didReceiveNetworkCallback(void* System, void* User) 
{
    std::string str = (char *) System;
    std::vector<std::string> networkAndCallback = split(str, ',');
    if(networkAndCallback.size() == 2) {
        setLastCallbackAsStringWithTag(networkAndCallback[0].c_str(), networkAndCallback[1].c_str(), User);
    } else {
        setLastCallbackAsStringWithTag("unknown", (char *)System, User);
    }
     
}
// Main entry point for the application
int main()
{   
    HeyzapStart("1234");

    HeyzapRegister(HZINTERSTITIAL_SHOW, (s3eCallback)didShowAdWithTag, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_AVAILABLE, (s3eCallback)didReceiveAdWithTag, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_CLICK, (s3eCallback)didClickAdWithTag, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_HIDE, (s3eCallback)didHideAdWithTag, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_AUDIO_STARTED, (s3eCallback)willStartAudio, INTERSTITIAL);
    HeyzapRegister(HZINTERSTITIAL_AUDIO_FINISHED, (s3eCallback)didFinishAudio, INTERSTITIAL);

    HeyzapRegister(HZVIDEO_SHOW, (s3eCallback)didShowAdWithTag, VIDEO);
    HeyzapRegister(HZVIDEO_FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag, VIDEO);
    HeyzapRegister(HZVIDEO_AVAILABLE, (s3eCallback)didReceiveAdWithTag, VIDEO);
    HeyzapRegister(HZVIDEO_FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag, VIDEO);
    HeyzapRegister(HZVIDEO_CLICK, (s3eCallback)didClickAdWithTag, VIDEO);
    HeyzapRegister(HZVIDEO_HIDE, (s3eCallback)didHideAdWithTag, VIDEO);
    HeyzapRegister(HZVIDEO_AUDIO_STARTED, (s3eCallback)willStartAudio, VIDEO);
    HeyzapRegister(HZVIDEO_AUDIO_FINISHED, (s3eCallback)didFinishAudio, VIDEO);

    HeyzapRegister(HZINCENTIVIZED_SHOW, (s3eCallback)didShowAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_AVAILABLE, (s3eCallback)didReceiveAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_CLICK, (s3eCallback)didClickAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_HIDE, (s3eCallback)didHideAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_AUDIO_STARTED, (s3eCallback)willStartAudio, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_AUDIO_FINISHED, (s3eCallback)didFinishAudio, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_COMPLETE, (s3eCallback)didCompleteAdWithTag, INCENTIVIZED);
    HeyzapRegister(HZINCENTIVIZED_INCOMPLETE, (s3eCallback)didFailToCompleteAdWithTag, INCENTIVIZED);

    HeyzapRegister(HZ_NETWORK_CALLBACK, (s3eCallback)didReceiveNetworkCallback, NETWORK);


    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        s3eSurfaceClear(0,0,0);
        int surfaceHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT); //pixels
        int surfaceWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH); //pixels
        int surfacePitch = s3eSurfaceGetInt(S3E_SURFACE_PITCH); //number of bytes in a single horizontal row of the screen display
        

        s3eDebugPrintf(0, 20, false, (HeyzapAvailable() == S3E_TRUE) ? "Heyzap available!" : "Heyzap NOT available :(");
        if(loopCounter++ % 40 < 20) s3eDebugPrintf(surfaceWidth/2, 20, false, "Running...");

        bool processed = false;
        bool showPressedUI = false;
        // Loop through all possible touch IDs
        for (int i = S3E_POINTER_TOUCH_MAX - 1; i >=0 && !processed; i--)
        {
            // Check to see if this touch ID represents a current touchscreen input
            if (s3ePointerGetTouchState(i) == S3E_POINTER_STATE_DOWN)
            {
                showPressedUI = true;
                int32 x = s3ePointerGetTouchX(i);
                int32 y = s3ePointerGetTouchY(i);
                // Screen is being touched at x, y

                s3eDebugPrintf(surfaceWidth/4*3, 20 + 30*i, false, "#%d (%d,%d)", i+1,x,y);

                // use height of first finger touch to determine if fetching/showing
                if(i == 0 && y < surfaceHeight/2) {
                    showInter = showVideo = showRewarded = false;
                } else {
                    showInter = showVideo = showRewarded = true;
                }
            }

            switch(i){
                case 0:
                    if (s3ePointerGetTouchState(i) & S3E_POINTER_STATE_RELEASED)
                    {
                        processed = true;
                        if(showInter) {
                            HeyzapShowInterstitial("this_tag_is_on");
                        } else {
                            HeyzapFetchInterstitial("this_tag_is_on");
                        }
                        showInter = !showInter;
                    }
                break;
                case 1:
                    if (s3ePointerGetTouchState(i) & S3E_POINTER_STATE_RELEASED)
                    {
                        processed = true;
                        if(showVideo) {
                            HeyzapShowVideo("this_tag_is_on");
                        } else {
                            HeyzapFetchVideo("this_tag_is_on");
                        }
                        showVideo = !showVideo;
                    }
                break;
                case 2:
                    if (s3ePointerGetTouchState(i) & S3E_POINTER_STATE_RELEASED)
                    {
                        processed = true;
                        if(showRewarded) {
                            HeyzapShowRewarded("this_tag_is_on");
                        } else {
                            HeyzapFetchRewarded("this_tag_is_on");
                        }
                        showRewarded = !showRewarded;
                    }
                break;
                case 3:
                if (s3ePointerGetTouchState(i) & S3E_POINTER_STATE_RELEASED)
                    {
                        processed = true;
                        HeyzapStartTestActivity();
                    }
                break;
            }
        }

        if(showPressedUI) {
            // Loop through the y coordinates
            uint32 yStart = surfaceHeight / 2;
            uint32 xStart = 0;

            for (uint32 y = 0; y < 5; y++)
            {
                // Calculate a pointer for the first pixel to modify on the current line
                // Note that the pointer is first cast to a uint32 since we want to ensure a byte offset is calculated
                uint32* p = (uint32*) ((uint32) s3eSurfacePtr() + ((yStart + y) * surfacePitch) + (xStart * sizeof(uint32)));
         
                // Loop through the x coordinates
                for (uint32 x = 0; x < surfaceWidth; x++)
                {
                    // Calculate a colour and set the current pixel
                    *p++ = s3eSurfaceConvertRGB(0xFF, 0xFF, 0xFF);
                }
            }

            s3eDebugPrintf(surfaceWidth / 2 - 100, surfaceHeight / 4, false, "RELEASE HERE TO FETCH");
            s3eDebugPrintf(surfaceWidth / 2 - 100, surfaceHeight / 4 * 3, false, "RELEASE HERE TO SHOW");
        } else {
            // screen not pressed. show instructions and callbacks

            s3eDebugPrintf(0, 60, false, "Instructions: (Top half = fetch, bottom = show)");
            s3eDebugPrintf(20, 90, false, "1 finger: interstitial");
            s3eDebugPrintf(20, 120, false, "2 fingers: video");
            s3eDebugPrintf(20, 150, false, "3 fingers: rewarded");
            s3eDebugPrintf(20, 180, false, "4 fingers: mediation test suite");

            int callbacksStartHeight = 250;
            int remainingScreenHeight = surfaceHeight - callbacksStartHeight;
            int numberOfCallbacksToShow = remainingScreenHeight / 40 + 1;
            s3eDebugPrintf(0, 220, false, "Recent Callbacks: (showing %d)", numberOfCallbacksToShow );

            int callbacksShown = 0; 
            for(int index = callbacks.size() -1 ; index >= 0 && callbacksShown < numberOfCallbacksToShow; callbacksShown++, index--) {
                s3eDebugPrintf(20, 250 + 40*callbacksShown, false, "%s", callbacks.at(index).c_str());
            }
        }

        s3eSurfaceShow();

        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    HeyzapUnRegister(HZINTERSTITIAL_SHOW, (s3eCallback)didShowAdWithTag);
    HeyzapUnRegister(HZINTERSTITIAL_FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag);
    HeyzapUnRegister(HZINTERSTITIAL_AVAILABLE, (s3eCallback)didReceiveAdWithTag);
    HeyzapUnRegister(HZINTERSTITIAL_FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag);
    HeyzapUnRegister(HZINTERSTITIAL_CLICK, (s3eCallback)didClickAdWithTag);
    HeyzapUnRegister(HZINTERSTITIAL_HIDE, (s3eCallback)didHideAdWithTag);
    HeyzapUnRegister(HZINTERSTITIAL_AUDIO_STARTED, (s3eCallback)willStartAudio);
    HeyzapUnRegister(HZINTERSTITIAL_AUDIO_FINISHED, (s3eCallback)didFinishAudio);

    HeyzapUnRegister(HZVIDEO_SHOW, (s3eCallback)didShowAdWithTag);
    HeyzapUnRegister(HZVIDEO_FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag);
    HeyzapUnRegister(HZVIDEO_AVAILABLE, (s3eCallback)didReceiveAdWithTag);
    HeyzapUnRegister(HZVIDEO_FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag);
    HeyzapUnRegister(HZVIDEO_CLICK, (s3eCallback)didClickAdWithTag);
    HeyzapUnRegister(HZVIDEO_HIDE, (s3eCallback)didHideAdWithTag);
    HeyzapUnRegister(HZVIDEO_AUDIO_STARTED, (s3eCallback)willStartAudio);
    HeyzapUnRegister(HZVIDEO_AUDIO_FINISHED, (s3eCallback)didFinishAudio);

    HeyzapUnRegister(HZINCENTIVIZED_SHOW, (s3eCallback)didShowAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_AVAILABLE, (s3eCallback)didReceiveAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_CLICK, (s3eCallback)didClickAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_HIDE, (s3eCallback)didHideAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_AUDIO_STARTED, (s3eCallback)willStartAudio);
    HeyzapUnRegister(HZINCENTIVIZED_AUDIO_FINISHED, (s3eCallback)didFinishAudio);
    HeyzapUnRegister(HZINCENTIVIZED_COMPLETE, (s3eCallback)didCompleteAdWithTag);
    HeyzapUnRegister(HZINCENTIVIZED_INCOMPLETE, (s3eCallback)didFailToCompleteAdWithTag);

    HeyzapUnRegister(HZ_NETWORK_CALLBACK, (s3eCallback)didReceiveNetworkCallback);

    
    // Return
    return 0;
}