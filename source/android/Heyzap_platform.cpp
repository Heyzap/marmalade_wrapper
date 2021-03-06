/*
 * android-specific implementation of the Heyzap extension.
 * Add any platform-specific functionality here.
 */
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#include "Heyzap_internal.h"

#include "s3eEdk.h"
#include "s3eEdk_android.h"
#include <jni.h>
#include "IwDebug.h"

static jobject g_Obj;
static jmethodID g_HeyzapStart;
static jmethodID g_HeyzapFetchInterstitial;
static jmethodID g_HeyzapShowInterstitial;
static jmethodID g_HeyzapFetchVideo;
static jmethodID g_HeyzapShowVideo;
static jmethodID g_HeyzapFetchRewarded;
static jmethodID g_HeyzapShowRewarded;
static jmethodID g_HeyzapShowBanner;
static jmethodID g_HeyzapHideBanner;
static jmethodID g_HeyzapDestroyBanner;
static jmethodID g_HeyzapStartTestActivity;


void JNICALL Heyzap_nativeCallback(JNIEnv* env, jobject obj, jint callbackIndex, jstring callbackData)
{
    const char *callbackDataChars;
    int callbackDataLength;

    if(callbackData == NULL)
    {
        callbackDataChars = NULL;
        callbackDataLength = 0;
    }
    else
    {
        callbackDataChars = env->GetStringUTFChars(callbackData, NULL);
        callbackDataLength = env->GetStringUTFLength(callbackData) + 1; // Include \0
    }
    
    // the callbackIndex sent in Heyzap.java is the ordinal from the same enum used for the callbacks in C here
    s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, (HeyzapCallback)callbackIndex, (void  *)callbackDataChars, callbackDataLength);

    if(callbackData != NULL)
    {
        env->ReleaseStringUTFChars(callbackData, callbackDataChars);
    }
}

s3eResult HeyzapInit_platform()
{
    // Get the environment from the pointer
    JNIEnv* env = s3eEdkJNIGetEnv();
    jobject obj = NULL;
    jmethodID cons = NULL;

    // Get the extension class
    jclass cls = s3eEdkAndroidFindClass("Heyzap");
    if (!cls)
        goto fail;

    // Get its constructor
    cons = env->GetMethodID(cls, "<init>", "()V");
    if (!cons)
        goto fail;

    // Construct the java class
    obj = env->NewObject(cls, cons);
    if (!obj)
        goto fail;

    // Get all the extension methods
    g_HeyzapStart = env->GetMethodID(cls, "HeyzapStart", "(Ljava/lang/String;)V");
    if (!g_HeyzapStart)
        goto fail;

    g_HeyzapFetchInterstitial = env->GetMethodID(cls, "HeyzapFetchInterstitial", "(Ljava/lang/String;)V");
    if (!g_HeyzapFetchInterstitial)
        goto fail;

    g_HeyzapShowInterstitial = env->GetMethodID(cls, "HeyzapShowInterstitial", "(Ljava/lang/String;)V");
    if (!g_HeyzapShowInterstitial)
        goto fail;

    g_HeyzapFetchVideo = env->GetMethodID(cls, "HeyzapFetchVideo", "(Ljava/lang/String;)V");
    if (!g_HeyzapFetchVideo)
        goto fail;

    g_HeyzapShowVideo = env->GetMethodID(cls, "HeyzapShowVideo", "(Ljava/lang/String;)V");
    if (!g_HeyzapShowVideo)
        goto fail;

    g_HeyzapFetchRewarded = env->GetMethodID(cls, "HeyzapFetchRewarded", "(Ljava/lang/String;)V");
    if (!g_HeyzapFetchRewarded)
        goto fail;

    g_HeyzapShowRewarded = env->GetMethodID(cls, "HeyzapShowRewarded", "(Ljava/lang/String;)V");
    if (!g_HeyzapShowRewarded)
        goto fail;

    g_HeyzapShowBanner = env->GetMethodID(cls, "HeyzapShowBanner", "(ZLjava/lang/String;)V");
    if (!g_HeyzapShowBanner)
        goto fail;

    g_HeyzapHideBanner= env->GetMethodID(cls, "HeyzapHideBanner", "()V");
    if (!g_HeyzapHideBanner)
        goto fail;

    g_HeyzapDestroyBanner = env->GetMethodID(cls, "HeyzapDestroyBanner", "()V");
    if (!g_HeyzapDestroyBanner)
        goto fail;

    g_HeyzapStartTestActivity = env->GetMethodID(cls, "HeyzapStartTestActivity", "()V");
    if (!g_HeyzapStartTestActivity)
        goto fail;

    static const JNINativeMethod methods[] =
    {
        {"nativeCallback","(ILjava/lang/String;)V",(void*)&Heyzap_nativeCallback}
    };

    // Register the native hooks
    if (env->RegisterNatives(cls, methods,sizeof(methods)/sizeof(methods[0])))
        goto fail;


    IwTrace(HEYZAP, ("HEYZAP init success"));
    g_Obj = env->NewGlobalRef(obj);
    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);

    // Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;

fail:
    jthrowable exc = env->ExceptionOccurred();
    if (exc)
    {
        env->ExceptionDescribe();
        env->ExceptionClear();
        IwTrace(Heyzap, ("One or more java methods could not be found"));
    }

    env->DeleteLocalRef(obj);
    env->DeleteGlobalRef(cls);
    return S3E_RESULT_ERROR;

}

void HeyzapTerminate_platform()
{ 
    // Add any platform-specific termination code here
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->DeleteGlobalRef(g_Obj);
    g_Obj = NULL;
}

void HeyzapStart_platform(const char* pubId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring pubId_jstr = env->NewStringUTF(pubId);
    env->CallVoidMethod(g_Obj, g_HeyzapStart, pubId_jstr);
}

void HeyzapFetchInterstitial_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapFetchInterstitial, tag_jstr);
}

void HeyzapShowInterstitial_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapShowInterstitial, tag_jstr);
}

void HeyzapFetchVideo_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapFetchVideo, tag_jstr);
}

void HeyzapShowVideo_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapShowVideo, tag_jstr);
}

void HeyzapFetchRewarded_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapFetchRewarded, tag_jstr);
}

void HeyzapShowRewarded_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapShowRewarded, tag_jstr);
}

void HeyzapShowBanner_platform(bool top, const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_HeyzapShowBanner, (jboolean)top, tag_jstr);
}

void HeyzapHideBanner_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_HeyzapHideBanner);
}

void HeyzapDestroyBanner_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_HeyzapDestroyBanner);
}

void HeyzapStartTestActivity_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_HeyzapStartTestActivity);
}
