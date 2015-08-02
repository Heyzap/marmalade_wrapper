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
1. First, you'll need the Android NDK to compile the native (C++) part of the extension. Then, in your `~/.bash_profile` or elsewhere, set the environment variable `NDK_ROOT` to the root of the installation:

	```shell
	export NDK_ROOT="/Users/you/install_directory_for_android-ndk"
	```
1. You also want to use [JDK 1.7 (Java 7)](http://www.oracle.com/technetwork/java/javase/downloads/java-archive-downloads-javase7-521261.html) to compile the Java part of the extension. Otherwise, [Marmalade might freak out later](https://answers.madewithmarmalade.com/questions/30921/edk-android-unexpected-top-level-exception.html). To do this, set JAVA_HOME to your installation of JDK 1.7 prior to running the `mkb` commands below.
1. Open `Heyzap_android_java.mkb` and `Heyzap_android.mkb`. The former compiles the Java side of the extension, and the latter compiles the C++ side of the extension. Alternatively, you can run these commands directly:

    ```shell
    mkb '/path/to/this/mkb/file/Heyzap_android_java.mkb'
    mkb '/path/to/this/mkb/file/Heyzap_android_.mkb'
    ```

#### iOS:
1. Open `Heyzap_iphone.mkb`. Because of a special instruction in this file, this should open Xcode. Alternatively, you can run this command directly:

	```shell
	mkb '/path/to/this/mkb/file/Heyzap_iphone.mkb' --buildenv=xcode
	```
1. Build the Xcode project that opens for you. It's located in `build_heyzap_iphone_iphone_xcode`. If there are no errors, this will update the lib at `lib/libHeyzap_d.a`
	1. The `_d` designates that the lib was built in the "Debug" configuration. You can build the "Release" configuration by [changing the scheme of the build](http://stackoverflow.com/a/5387158/2544629). You should do both.


### Android specifics
#### Adding extra jars (for other networks supported by Heyzap Mediation)
1. Put the `.jar` in the "incoming" directory  
1. Add it to Heyzap.mkf as an `android-external-jars` 
1. Add it to Heyzap_android_java.mkb as a `librarypath`
1. Add any required manifest additions to an `xml` file in `android_manifests/` (permissions in `{network}.xml` and activities in `{network}_application.xml` is the naming convention, they are separate because they go in different sections of the manifest XML.
1. Add the required manifest files as `android-extra-application-manifest=""` and `android-extra-manifest=""` in Heyzap.mkf
1. If more changes need to be made to the manifest that don't go under the `<manifest>` or `<application>` tags, you'll need to add those to your app's manifest instead (see `heyzaptest/heyzap_manifest.xml`)
	1. For example, AdColony and Chartboost require `android:hardwareAccelerated="true"` as an attribute of the `<application>` tag in the manifest. This has been added in the test app's manifest override.
	1. In order to use this manifest instead of the Marmalade default, go to the Android configuration -> Advanced tab, and browse for your replacement manifest file. You should start with the Marmalade default file, which can be found at `/Applications/Marmalade.app/Contents/s3e/deploy/plugins/android/AndroidManifest.xml`.

**Note about Google Play Services:** If you update the `.jar` for Google Play Services (found at `{androidsdk-root}/extras/google/google_play_services/libproject/google-play-services_lib/libs`), also update the `version.xml` included with it in the `google-play-services_lib/res/values/` directory. 

**Note about Vungle:** Vungle's iOS SDK requires that a bunch of assets be included (pngs of their buttons, etc.). I couldn't figure out how to do this in Marmalade inside any of the iOS-specific files, so it had to be done in `Heyzap.mkf`. This means that these files will be included on Android builds, and the filenames clash with the Android SDK `.jar` from Vungle. So, you have to comment out these lines when building the extension for Android (and uncomment them when building for iOS) until we come up with a different solution. UnityAds also has a bundle that has to be included for iOS, but it doesn't cause issues in the Android build (but can still be commented out for Android builds).

### iOS specifics
#### Adding extra frameworks/libs (for other networks supported by Heyzap Mediation)
##### Networks that distribute a `Network.framework` and nothing else
1. Add your `.framework` file to `incoming/`.
1. Add the framework to the list of extra libs in `Heyzap.mkf`, and also add any of the iOS frameworks it depends on.

##### Networks that distribute a `libNetwork.a` file with an associated `Headers` directory
1. Make a folder in `incoming/` for the network. Add the `.a` and the `Headers/` here.
1. In the `deployments` section of `Heyzap.mkf`, add the folder using `iphone-link-libdir="your/directory/here"` (relative to the `.mkf` file you're editing), and then add the lib with `iphone-link-lib=Network`. Marmalade will automatically add the `lib` and the `.a` to `Network` in this latter addition. Example:

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

**Note about Vungle:** Vungle's iOS SDK requires that a bunch of assets be included (pngs of their buttons, etc.). I couldn't figure out how to do this in Marmalade inside any of the iOS-specific files, so it had to be done in `Heyzap.mkf`. This means that these files will be included on Android builds, and the filenames clash with the Android SDK `.jar` from Vungle. So, you have to comment out these lines when building the extension for Android (and uncomment them when building for iOS) until we come up with a different solution. UnityAds also has a bundle that has to be included for iOS, but it doesn't cause issues in the Android build (but can still be commented out for Android builds).


##The Heyzap Test App for Marmalade

There is a test app in this repo, in the top-level directory named `heyzaptest`, that demonstrates the HeyzapSDK working in Marmalade. You can open this project in the Marmalade Hub (C++). There are a few settings to mind:

1. The bundle identifier/package name can be set in the build configuration in the Basic tab for both Android and iOS. Click the Configuration dropdown and edit the current configuration to find this setting.
1. The Android Manifest can be modified via the configuration settings as well. Activities for Heyzap and other mediated networks should be added in this manner (see `heyzap_manifest.xml`).
1. Running the sample app in the Marmalade simulator won't work properly. Please run on a device (iOS and Android only).

####Building the test app
1. Make sure you've compiled the Heyzap extension using the steps above prior to building the test app. The output of that build is in the `lib/` directory of the extension.
1. Open the project (inside the `heyzaptest/` folder of this repo) in the Marmalade Hub C++.
1. Click the "Build" button in the Marmalade Hub. See the full log for details in case of a failure.
1. Click the "Package, Install" (or whatever you have the button set to do). Again, see the full log in case of failure.
1. Use the test app on the device.
	1. The UI is lacking on the test app. You can see the code for it in `heyzaptest/heyzaptest.cpp`. Feel free to improve on it.


## Currently tested / included SDK versions:
#### iOS
* Heyzap `9.0.6`
* AdColony `2.5.3`
* AppLovin `3.0.2`
* Chartboost `5.5.1`
* Facebook Audience Network ?
* AdMob (Google Mobile Ads) `7.3.1`
* HyprMX ? (not to be confused with HyprMediate)
* UnityAds `1.4.7`
* Vungle `3.1.2`

#### Android
* Heyzap `9.0.6`
* AdColony `2.2.2`
* AppLovin `6.0.1`
* Chartboost `5.3.0`
* Facebook Audience Network `4.4.1`
* AdMob (Google Mobile Ads) (included in Android)
* UnityAds `1.4.7`
* Vungle `3.3.1`

Documentation on implemented methods in the Heyzap Marmalade extension
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
