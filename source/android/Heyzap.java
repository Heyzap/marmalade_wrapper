/*
java implementation of the Heyzap extension.

Add android-specific functionality here.

These functions are called via JNI from native code.
*/
/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
import com.ideaworks3d.marmalade.LoaderAPI;

import android.view.Gravity;

import com.heyzap.sdk.ads.*;
import com.heyzap.internal.*;

// Comment in the following line if you want to use ResourceUtility
// import com.ideaworks3d.marmalade.ResourceUtility;

class Heyzap
{
    final private static String MARMALADE_FRAMEWORK = "marmalade";

    /* Be careful modifying this enum. The ordinal values here correlate to the values expected in Heyzap_platform.cpp (via Heyzap.h). This enum was copied from Heyzap.s4e, if you change it there you should copy and paste the changes here, too. */
    private enum HeyzapCallback{
        HZINTERSTITIAL_SHOW, HZINTERSTITIAL_CLICK, HZINTERSTITIAL_HIDE, HZINTERSTITIAL_FAILED_TO_SHOW, HZINTERSTITIAL_AVAILABLE, HZINTERSTITIAL_FAILED_TO_FETCH, HZINTERSTITIAL_AUDIO_STARTED, HZINTERSTITIAL_AUDIO_FINISHED,

        HZVIDEO_SHOW, HZVIDEO_CLICK, HZVIDEO_HIDE, HZVIDEO_FAILED_TO_SHOW, HZVIDEO_AVAILABLE, HZVIDEO_FAILED_TO_FETCH, HZVIDEO_AUDIO_STARTED, HZVIDEO_AUDIO_FINISHED,

        HZINCENTIVIZED_SHOW, HZINCENTIVIZED_CLICK, HZINCENTIVIZED_HIDE, HZINCENTIVIZED_FAILED_TO_SHOW, HZINCENTIVIZED_AVAILABLE, HZINCENTIVIZED_FAILED_TO_FETCH, HZINCENTIVIZED_AUDIO_STARTED, HZINCENTIVIZED_AUDIO_FINISHED, HZINCENTIVIZED_COMPLETE, HZINCENTIVIZED_INCOMPLETE, 

        HZBANNER_LOADED, HZBANNER_CLICKED, HZBANNER_ERROR,

        HZ_NETWORK_CALLBACK,

        HEYZAP_CALLBACK_MAX
    };

    public native void nativeCallback(int callbackIndex, String callbackData);

    public void HeyzapStart(String pubId)
    {
        HeyzapAds.framework = MARMALADE_FRAMEWORK;
        HeyzapAds.start(pubId, LoaderAPI.getActivity());

         InterstitialAd.setOnStatusListener(new HeyzapAds.OnStatusListener() {
            
            @Override
            public void onShow(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_SHOW.ordinal(), tag);
            }
            
            @Override
            public void onHide(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_HIDE.ordinal(), tag);
            }
            
            @Override
            public void onFailedToShow(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_FAILED_TO_SHOW.ordinal(), tag);
            }
            
            @Override
            public void onFailedToFetch(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_FAILED_TO_FETCH.ordinal(), tag);
            }
            
            @Override
            public void onClick(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_CLICK.ordinal(), tag);
            }
            
            @Override
            public void onAvailable(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_AVAILABLE.ordinal(), tag);
            }
            
            @Override
            public void onAudioStarted() {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_AUDIO_STARTED.ordinal(), null);
            }
            
            @Override
            public void onAudioFinished() {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINTERSTITIAL_AUDIO_FINISHED.ordinal(), null);
            }
        });

        VideoAd.setOnStatusListener(new HeyzapAds.OnStatusListener() {
            
            @Override
            public void onShow(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_SHOW.ordinal(), tag);
            }
            
            @Override
            public void onHide(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_HIDE.ordinal(), tag);
            }
            
            @Override
            public void onFailedToShow(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_FAILED_TO_SHOW.ordinal(), tag);
            }
            
            @Override
            public void onFailedToFetch(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_FAILED_TO_FETCH.ordinal(), tag);
            }
            
            @Override
            public void onClick(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_CLICK.ordinal(), tag);
            }
            
            @Override
            public void onAvailable(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_AVAILABLE.ordinal(), tag);
            }
            
            @Override
            public void onAudioStarted() {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_AUDIO_STARTED.ordinal(), null);
            }
            
            @Override
            public void onAudioFinished() {
                Heyzap.this.nativeCallback(HeyzapCallback.HZVIDEO_AUDIO_FINISHED.ordinal(), null);
            }
        });

        IncentivizedAd.setOnStatusListener(new HeyzapAds.OnStatusListener() {
            
            @Override
            public void onShow(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_SHOW.ordinal(), tag);
            }
            
            @Override
            public void onHide(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_HIDE.ordinal(), tag);
            }
            
            @Override
            public void onFailedToShow(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_FAILED_TO_SHOW.ordinal(), tag);
            }
            
            @Override
            public void onFailedToFetch(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_FAILED_TO_FETCH.ordinal(), tag);
            }
            
            @Override
            public void onClick(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_CLICK.ordinal(), tag);
            }
            
            @Override
            public void onAvailable(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_AVAILABLE.ordinal(), tag);
            }
            
            @Override
            public void onAudioStarted() {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_AUDIO_STARTED.ordinal(), null);
            }
            
            @Override
            public void onAudioFinished() {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_AUDIO_FINISHED.ordinal(), null);
            }
        });

        IncentivizedAd.setOnIncentiveResultListener(new HeyzapAds.OnIncentiveResultListener() {
            
            @Override
            public void onIncomplete(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_INCOMPLETE.ordinal(), tag);
            }
            
            @Override
            public void onComplete(String tag) {
                Heyzap.this.nativeCallback(HeyzapCallback.HZINCENTIVIZED_COMPLETE.ordinal(), tag);
            }
        });
        
        BannerAd.setBannerListener(new HeyzapAds.BannerListener() {
            @Override
            public void onAdError(BannerAdView bannerView, HeyzapAds.BannerError error) {
                String tag = null;
                if(bannerView != null) {
                    tag = bannerView.getAdTag();
                }
                Heyzap.this.nativeCallback(HeyzapCallback.HZBANNER_ERROR.ordinal(), tag);
            }

            @Override
            public void onAdLoaded(BannerAdView bannerView) {
                String tag = null;
                if(bannerView != null) {
                    tag = bannerView.getAdTag();
                }
                Heyzap.this.nativeCallback(HeyzapCallback.HZBANNER_LOADED.ordinal(), tag);
            }

            @Override
            public void onAdClicked(BannerAdView bannerView) {
                String tag = null;
                if(bannerView != null) {
                    tag = bannerView.getAdTag();
                }
                Heyzap.this.nativeCallback(HeyzapCallback.HZBANNER_CLICKED.ordinal(), tag);
            }
        });

        HeyzapAds.setNetworkCallbackListener(new HeyzapAds.NetworkCallbackListener() {
            @Override
            public void onNetworkCallback(String network, String callback) {
                String callbackMessage = String.format("%s,%s", network, callback); // callback can be parsed as "network,callback" on the other side
                Heyzap.this.nativeCallback(HeyzapCallback.HZ_NETWORK_CALLBACK.ordinal(), callbackMessage);
            }
        });
    }

    public void HeyzapFetchInterstitial(String tag)
    {
        if(tag.isEmpty()){
            InterstitialAd.fetch();
        }else{
            InterstitialAd.fetch(tag);
        }
    }
    public void HeyzapShowInterstitial(String tag)
    {
        if(tag.isEmpty()){
            InterstitialAd.display(LoaderAPI.getActivity());
        }else{
            InterstitialAd.display(LoaderAPI.getActivity(), tag);
        }
    }
    public void HeyzapFetchVideo(String tag)
    {
        if(tag.isEmpty()){
            VideoAd.fetch();
        }else{
            VideoAd.fetch(tag);
        }
    }
    public void HeyzapShowVideo(String tag)
    {
        if(tag.isEmpty()){
            VideoAd.display(LoaderAPI.getActivity());
        }else{
            VideoAd.display(LoaderAPI.getActivity(), tag);
        }
    }
    public void HeyzapFetchRewarded(String tag)
    {
        if(tag.isEmpty()){
            IncentivizedAd.fetch();
        }else{
            IncentivizedAd.fetch(tag);
        }
    }
    public void HeyzapShowRewarded(String tag)
    {
        if(tag.isEmpty()){
            IncentivizedAd.display(LoaderAPI.getActivity());
        }else{
            IncentivizedAd.display(LoaderAPI.getActivity(), tag);
        }
    }
    public void HeyzapShowBanner(boolean top, String tag)
    {
        int position = (top ? Gravity.TOP : Gravity.BOTTOM);

        if(tag.isEmpty()){
            BannerAd.display(LoaderAPI.getActivity(), position, Constants.DEFAULT_TAG);
        }else{
            BannerAd.display(LoaderAPI.getActivity(), position, tag);
        }
    }
    public void HeyzapHideBanner()
    {
        BannerAd.hide();
    }
    public void HeyzapDestroyBanner()
    {
        BannerAd.destroy();
    }
    public void HeyzapStartTestActivity()
    {
        HeyzapAds.startTestActivity(LoaderAPI.getActivity());
    }
}
