# Heyzap Mediation Marmalade Wrapper
A Marmalade wrapper for the Heyzap Mediation SDK

### Files you should edit to make changes to the wrapper
#### All platforms:
* Heyzap.s4e (changes here will need to be manually propagated to source/h/Heyzap_internal.h and source/generic/Heyzap.cpp, and a few other files will be auto-updated from changes here when you run Heyzap_`platform`.mkb)

#### Android:
* source/android/*

####iOS:
* source/iphone/*  	

Everything else is auto-generated / internal to Marmalade.

### After making changes
Once you make changes to the wrapper, you must re-compile the wrapper into the library file that will be used by developers. Instructions on how to do this for each platform are below.

#### Android:
1. First, you'll need the Android NDK to compile the native (C) part of the extension. Then, in your `~/.bash_profile` or elsewhere, set the environment variable `NDK_ROOT` to the root of the installation:
```shell
export NDK_ROOT="/Users/you/install_directory_for_android-ndk"
```
1. Open `Heyzap_android_java.mkb` and `Heyzap_android.mkb`. (TODO: This process is yet to be confirmed)

#### iOS:
1. Open `Heyzap_iphone.mkb`. Because of a special instruction in this file, this should open Xcode. Alternatively, you can run this command directly:
```shell
mkb '/path/to/this/mkb/file/Heyzap_iphone.mkb' --buildenv=xcode
```
1. Build the Xcode project that opens for you. It's located in `build_heyzap_iphone_iphone_xcode`. If there are no errors, this will update the lib at `lib/libHeyzap_d.a`
    1. The `_d` designates that the lib was built in the "Debug" configuration. You can build the "Release" configuration by [changing the scheme of the build](http://stackoverflow.com/a/5387158/2544629). You should do both.


### Android specifics
#### Adding extra jars (for other networks supported by Heyzap Mediation)
1. put it in the "incoming" directory  
1. add it to Heyzap.mkf as an `android-external-jars` and  
1. add it to Heyzap_android_java.mkb as a `librarypath`  

### iOS specifics
#### Adding extra frameworks/libs (for other networks supported by Heyzap Mediation)
##### Networks that distribute a `Network.framework` and nothing else
1. Add your `.framework` file to `incoming/`.
1. Add the framework to the list of extra libs in `Heyzap.mkf`, and also add any of the iOS frameworks it depends on.

##### Networks that distribute a `libNetwork.a` file with an associated `Headers` directory
1. Make a folder in `incoming/` for the network. Add the `.a` and the `Headers/` here.
1. In the `deployments` section of `Heyzap.mkf`, add the folder using `iphone-link-libdir="your/directory/here" (relative to the `.mkf` file you're editing), and then add the lib with `iphone-link-lib=Network`. Marmalade will automatically add the `lib` and the `.a` to `Network` in this latter addition. Example:
```
	# AppLovin has a `.a` file, not a .framework
    iphone-link-libdir = "incoming/AppLovin"
    iphone-link-lib="AppLovinSdk" # marmalade prepends `lib` and prepends `.a` to this file name
```

##### Networks that don't play nicely
1. Take whatever files the network requires (i.e.: `UnityAds.bundle`, Vungle's PNGs and `.db` files) and try adding them to `Heyzap.mkf`'s `assets` section. The format is:
```
assets
{
	["Name_of_the_folder_in_Xcode_that_will_contain_these_assets"]
	(filepath/relative/to/this/file/that/contains/assets)
	Asset.png
	OtherAsset.bundle
}
```
1. Cross your fingers. 
1. If this doesn't work (it won't for code that needs to be compiled with the extension, for example), you can try adding the files to `Heyzap_build.mkf` in the iOS `files` section, using a similar format. We had to do this with the `HZAdMobBannerSupport.h/m` files that are currently required for AdMob banners via HeyzapMediation. YMMV.


Documentation on implemented methods
-------------------------------------------

``` c_cpp
/**
 * Registers a callback to be called for an operating system event.
 *
 * The available callback types are listed in @ref HeyzapCallback.
 * @param cbid ID of the event for which to register.
 * @param fn callback function.
 * @param userdata Value to pass to the @e userdata parameter of @e NotifyFunc.
 * @return
 *  - @ref S3E_RESULT_SUCCESS if no error occurred.
 *  - @ref S3E_RESULT_ERROR if the operation failed.
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
 * Show a banner ad with the given position and tag.
 * @param top Set to true if you want the banner on the top of the screen, false if you want it on the bottom.
 * @param tag tag to fetch with, empty string is the default tag.
 */
void HeyzapShowBanner(bool top, const char* tag);

/**
 * Hide the currently showing banner. Another call to HeyzapShowBanner after this method will show the same banner.
 */
void HeyzapHideBanner();

/**
 * Destroy the currently showing banner. Another call to HeyzapShowBanner after this method will attempt to fetch and show a new banner.
 */
void HeyzapDestroyBanner();

/**
 * Start the Heyzap Mediation Test Activity. This activity allows you to test the integration of other networks into the heyzap waterfall
 * @note This code should not be used in production, it is for testing purposes only.
 */
void HeyzapStartTestActivity();
```
