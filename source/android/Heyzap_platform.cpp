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
static jmethodID g_start;
static jmethodID g_fetchInterstitial;
static jmethodID g_showInterstitial;
static jmethodID g_fetchVideo;
static jmethodID g_showVideo;
static jmethodID g_fetchRewarded;
static jmethodID g_showRewarded;
static jmethodID g_startTestActivity;

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
    g_start = env->GetMethodID(cls, "start", "(Ljava/lang/String;)V");
    if (!g_start)
        goto fail;

    g_fetchInterstitial = env->GetMethodID(cls, "fetchInterstitial", "(Ljava/lang/String;)V");
    if (!g_fetchInterstitial)
        goto fail;

    g_showInterstitial = env->GetMethodID(cls, "showInterstitial", "(Ljava/lang/String;)V");
    if (!g_showInterstitial)
        goto fail;

    g_fetchVideo = env->GetMethodID(cls, "fetchVideo", "(Ljava/lang/String;)V");
    if (!g_fetchVideo)
        goto fail;

    g_showVideo = env->GetMethodID(cls, "showVideo", "(Ljava/lang/String;)V");
    if (!g_showVideo)
        goto fail;

    g_fetchRewarded = env->GetMethodID(cls, "fetchRewarded", "(Ljava/lang/String;)V");
    if (!g_fetchRewarded)
        goto fail;

    g_showRewarded = env->GetMethodID(cls, "showRewarded", "(Ljava/lang/String;)V");
    if (!g_showRewarded)
        goto fail;

    g_startTestActivity = env->GetMethodID(cls, "startTestActivity", "()V");
    if (!g_startTestActivity)
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

void start_platform(const char* pubId)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring pubId_jstr = env->NewStringUTF(pubId);
    env->CallVoidMethod(g_Obj, g_start, pubId_jstr);
}

void fetchInterstitial_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_fetchInterstitial, tag_jstr);
}

void showInterstitial_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_showInterstitial, tag_jstr);
}

void fetchVideo_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_fetchVideo, tag_jstr);
}

void showVideo_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_showVideo, tag_jstr);
}

void fetchRewarded_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_fetchRewarded, tag_jstr);
}

void showRewarded_platform(const char* tag)
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    jstring tag_jstr = env->NewStringUTF(tag);
    env->CallVoidMethod(g_Obj, g_showRewarded, tag_jstr);
}

void startTestActivity_platform()
{
    JNIEnv* env = s3eEdkJNIGetEnv();
    env->CallVoidMethod(g_Obj, g_startTestActivity);
}
