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
static jmethodID g_HeyzapStartTestActivity;


// todo: we should return tags here (see this and Heyzap.java)
void JNICALL Heyzap_nativeCallback(JNIEnv* env, jobject obj, jint status)
{
    switch(status){
        case 0:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, SHOW, NULL, 0);
        break;
        case 1:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, CLICK, NULL, 0);
        break;
        case 2:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, HIDE, NULL, 0);
        break;
        case 3:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, FAILED_TO_SHOW, NULL, 0);   
        break;
        case 4:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, AVAILABLE, NULL, 0);
        break;
        case 5:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, FAILED_TO_FETCH, NULL, 0);
        break;
        case 6:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, AUDIO_STARTED, NULL, 0);
        break;
        case 7:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, AUDIO_FINISHED, NULL, 0);
        break;
        case 8:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, INCENTIVE_COMPLETE, NULL, 0);
        break;
        case 9:
        s3eEdkCallbacksEnqueue(S3E_EXT_HEYZAP_HASH, INCENTIVE_INCOMPLETE, NULL, 0);
        break;
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

    g_HeyzapStartTestActivity = env->GetMethodID(cls, "HeyzapStartTestActivity", "()V");
    if (!g_HeyzapStartTestActivity)
        goto fail;

    static const JNINativeMethod methods[] =
    {
        {"nativeCallback","(I)V",(void*)&Heyzap_nativeCallback}
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

void HeyzapStartTestActivity_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_HeyzapStartTestActivity);
}
