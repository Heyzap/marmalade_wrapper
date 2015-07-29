#include "s3e.h"
#include "IwDebug.h"
#include "Heyzap.h"

#include <string>
#include <vector>

#define CALLBACK_LOG_LIMIT 30

int32 PointerTouchEventCallback(s3ePointerTouchEvent* pEvent, void* pUserData);
std::vector<std::string> callbacks;
uint callbackCounter = 0;
bool showInter = false;
bool showVideo = false;
bool showRewarded = false;
int loopCounter = 0;

void setLastCallback(const char * callback) {
    std::string lastCallback = callback;
    callbacks.push_back(lastCallback);
    if(callbacks.size() > CALLBACK_LOG_LIMIT) {
        callbacks.erase(callbacks.begin());
    }
}

void setLastCallbackAsString(const char * callback) {
    char buff[512];
    sprintf(buff, "[%u] %s", callbackCounter++, callback);
    setLastCallback(buff);
}

void setLastCallbackAsStringWithTag(const char * callback, const char * tag) {
    char buff[512];
    sprintf(buff, "[%u] %s: %s", callbackCounter++, callback, tag);
    setLastCallback(buff);
}

void didShowAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didShowAdWithTag", tag);
    IwTrace(APP, ("didShowAdWithTag callback in heyzaptest - tag: %s strlen tag: %d", tag, strlen(tag)));
}

void didFailToShowAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didFailToShowAdWithTag", tag);
}

void didReceiveAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didReceiveAdWithTag", tag);
}

void didFailToReceiveAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didFailToReceiveAdWithTag", tag);
}

void didClickAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didClickAdWithTag", tag);
}

void didHideAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didHideAdWithTag", tag);
}

void willStartAudio(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsString("willStartAudio");
}

void didFinishAudio(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsString("didFinishAudio");
}

void didCompleteAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didCompleteAdWithTag", tag);
}

void didFailToCompleteAdWithTag(void* System, void* User)
{
    char * tag = (char *) System;
    setLastCallbackAsStringWithTag("didFailToCompleteAdWithTag", tag);
}

// Main entry point for the application
int main()
{   
    HeyzapStart("1234");

    HeyzapRegister(SHOW, (s3eCallback)didShowAdWithTag, NULL);
    HeyzapRegister(FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag, NULL);
    HeyzapRegister(AVAILABLE, (s3eCallback)didReceiveAdWithTag, NULL);
    HeyzapRegister(FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag, NULL);
    HeyzapRegister(CLICK, (s3eCallback)didClickAdWithTag, NULL);
    HeyzapRegister(HIDE, (s3eCallback)didHideAdWithTag, NULL);
    HeyzapRegister(AUDIO_STARTED, (s3eCallback)willStartAudio, NULL);
    HeyzapRegister(AUDIO_FINISHED, (s3eCallback)didFinishAudio, NULL);
    HeyzapRegister(INCENTIVE_COMPLETE, (s3eCallback)didCompleteAdWithTag, NULL);
    HeyzapRegister(INCENTIVE_INCOMPLETE, (s3eCallback)didFailToCompleteAdWithTag, NULL);

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        //Update the input systems
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        s3eSurfaceClear(0,0,0);
        int surfaceHeight = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
        int surfaceWidth = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
        

        s3eDebugPrintf(0, 20, false, (HeyzapAvailable() == S3E_TRUE) ? "Heyzap available!" : "Heyzap NOT available :(");
        if(loopCounter++ % 40 < 20) s3eDebugPrintf(surfaceWidth/2, 20, false, "Running...");
        s3eDebugPrintf(0, 60, false, "Instructions: ");
        s3eDebugPrintf(20, 90, false, "1 finger: interstitial fetch/show");
        s3eDebugPrintf(20, 120, false, "2 fingers: video fetch/show");
        s3eDebugPrintf(20, 150, false, "3 fingers: rewarded fetch/show");
        s3eDebugPrintf(20, 180, false, "4 fingers: mediation test suite");


        
        int callbacksStartHeight = 250;
        int remainingScreenHeight = surfaceHeight - callbacksStartHeight;
        int numberOfCallbacksToShow = remainingScreenHeight / 40 + 1;
        s3eDebugPrintf(0, 220, false, "Recent Callbacks: (showing %d)", numberOfCallbacksToShow );

        int callbacksShown = 0; 
        for(int index = callbacks.size() -1 ; index >= 0 && callbacksShown < numberOfCallbacksToShow; callbacksShown++, index--) {
            s3eDebugPrintf(20, 250 + 40*callbacksShown, false, "%s", callbacks.at(index).c_str());
        }

        bool processed = false;
        // Loop through all possible touch IDs
        for (int i = S3E_POINTER_TOUCH_MAX - 1; i >=0 && !processed; i--)
        {
            // Check to see if this touch ID represents a current touchscreen input
            if (s3ePointerGetTouchState(i) == S3E_POINTER_STATE_DOWN)
            {
                int32 x = s3ePointerGetTouchX(i);
                int32 y = s3ePointerGetTouchY(i);
                // Screen is being touched at x, y

                s3eDebugPrintf(surfaceWidth/4*3, 20 + 30*i, false, "#%d (%d,%d)", i+1,x,y);
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

        s3eSurfaceShow();

        // Sleep for 0ms to allow the OS to process events etc.
        s3eDeviceYield(0);
    }

    HeyzapUnRegister(SHOW, (s3eCallback)didShowAdWithTag);
    HeyzapUnRegister(FAILED_TO_SHOW, (s3eCallback)didFailToShowAdWithTag);
    HeyzapUnRegister(AVAILABLE, (s3eCallback)didReceiveAdWithTag);
    HeyzapUnRegister(FAILED_TO_FETCH, (s3eCallback)didFailToReceiveAdWithTag);
    HeyzapUnRegister(CLICK, (s3eCallback)didClickAdWithTag);
    HeyzapUnRegister(HIDE, (s3eCallback)didHideAdWithTag);
    HeyzapUnRegister(AUDIO_STARTED, (s3eCallback)willStartAudio);
    HeyzapUnRegister(AUDIO_FINISHED, (s3eCallback)didFinishAudio);
    HeyzapUnRegister(INCENTIVE_COMPLETE, (s3eCallback)didCompleteAdWithTag);
    HeyzapUnRegister(INCENTIVE_INCOMPLETE, (s3eCallback)didFailToCompleteAdWithTag);
    
    // Return
    return 0;
}