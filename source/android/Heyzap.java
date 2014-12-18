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
import com.heyzap.sdk.ads.*;
// Comment in the following line if you want to use ResourceUtility
// import com.ideaworks3d.marmalade.ResourceUtility;

class Heyzap
{
    public native void nativeCallback(int status);

    public void start(String pubId)
    {
        HeyzapAds.start(pubId, LoaderAPI.getActivity());
        HeyzapAds.OnStatusListener listener = new HeyzapAds.OnStatusListener() {
            
            @Override
            public void onShow(String tag) {
                Heyzap.this.nativeCallback(0);
            }
            
            @Override
            public void onHide(String tag) {
                Heyzap.this.nativeCallback(1);
            }
            
            @Override
            public void onFailedToShow(String tag) {
                Heyzap.this.nativeCallback(2);
            }
            
            @Override
            public void onFailedToFetch(String tag) {
                Heyzap.this.nativeCallback(3);
            }
            
            @Override
            public void onClick(String tag) {
                Heyzap.this.nativeCallback(4);
            }
            
            @Override
            public void onAvailable(String tag) {
                Heyzap.this.nativeCallback(5);
            }
            
            @Override
            public void onAudioStarted() {
                Heyzap.this.nativeCallback(6);
            }
            
            @Override
            public void onAudioFinished() {
                Heyzap.this.nativeCallback(7);
            }
        };
        
        HeyzapAds.OnIncentiveResultListener incentiveListener = new HeyzapAds.OnIncentiveResultListener() {
            
            @Override
            public void onIncomplete(String tag) {
                Heyzap.this.nativeCallback(8);
            }
            
            @Override
            public void onComplete(String tag) {
                Heyzap.this.nativeCallback(9);
            }
        };
        InterstitialAd.setOnStatusListener(listener);
        VideoAd.setOnStatusListener(listener);
        IncentivizedAd.setOnStatusListener(listener);
        IncentivizedAd.setOnIncentiveResultListener(incentiveListener);

    }
    public void fetchInterstitial(String tag)
    {
        if(tag.isEmpty()){
            InterstitialAd.fetch();
        }else{
            InterstitialAd.fetch(tag);
        }
    }
    public void showInterstitial(String tag)
    {
        if(tag.isEmpty()){
            InterstitialAd.display(LoaderAPI.getActivity());
        }else{
            InterstitialAd.display(LoaderAPI.getActivity(), tag);
        }
    }
    public void fetchVideo(String tag)
    {
        if(tag.isEmpty()){
            VideoAd.fetch();
        }else{
            VideoAd.fetch(tag);
        }
    }
    public void showVideo(String tag)
    {
        if(tag.isEmpty()){
            VideoAd.display(LoaderAPI.getActivity());
        }else{
            VideoAd.display(LoaderAPI.getActivity(), tag);
        }
    }
    public void fetchRewarded(String tag)
    {
        if(tag.isEmpty()){
            IncentivizedAd.fetch();
        }else{
            IncentivizedAd.fetch(tag);
        }
    }
    public void showRewarded(String tag)
    {
        if(tag.isEmpty()){
            IncentivizedAd.display(LoaderAPI.getActivity());
        }else{
            IncentivizedAd.display(LoaderAPI.getActivity(), tag);
        }
    }
    public void startTestActivity()
    {
        HeyzapAds.startTestActivity(LoaderAPI.getActivity());
    }
}
