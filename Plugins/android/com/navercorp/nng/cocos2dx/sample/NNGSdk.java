package com.navercorp.nng.cocos2dx.sample;

import android.widget.Toast;

import com.navercorp.nng.android.sdk.NNGCallbackListener;
import com.navercorp.nng.android.sdk.NNGLink;

import org.cocos2dx.lib.Cocos2dxActivity;

public class NNGSdk {

    public static Cocos2dxActivity getActivity() {
        return (Cocos2dxActivity) Cocos2dxActivity.getContext();
    }

    public static void runOnGLThread(Runnable r) {
        getActivity().runOnGLThread(r);
    }

    public static void init(String clientId, String clientSecret, String loungeId) {
        NNGLink.initModule(getActivity(), loungeId, clientId, clientSecret);
        initListeners();
    }

    private static void initListeners() {

        NNGLink.setSdkLoadListener(new NNGCallbackListener() {
            @Override
            public void onSdkDidLoaded() {

            }

            @Override
            public void onSdkDidUnloaded() {

            }

            @Override
            public void onCallInGameMenuCode(String inGameMenuCode) {
                Toast.makeText(getActivity(),"onCallInGameMenuCode [" + inGameMenuCode + "]",Toast.LENGTH_LONG).show();
            }

            @Override
            public void onNaverLoggedIn() {

            }

            @Override
            public void onNaverLoggedOut() {

            }
        });
    }

    public static String getCountryCode() {
        return NNGLink.getCountryCode(getActivity());
    }

    public static void startHomeBanner() {
        NNGLink.startHome(getActivity());
    }

    public static void startSorryBanner() {
        NNGLink.startSorry(getActivity());
    }

    public static void startBoard(int boardId) {
        NNGLink.startBoard(getActivity(), boardId);
    }

    public static void startFeed(int feedId, boolean isTempFeedId) {
        NNGLink.startFeed(getActivity(), feedId, isTempFeedId);
    }
    public static void putGameId(String gameId) {
        NNGLink.putGameId(getActivity(), gameId);
    }

    public static void enableScreenShotDetector(Boolean enable) {
        NNGLink.enableScreenShotDetector(enable);
    }

    public static void logout() {
        NNGLink.logout(getActivity());
    }

    public static void writeFeed(int boardId,
                                 String title,
                                 String content,
                                 String imageUri) {
        NNGLink.writeFeed(getActivity(), boardId,title,content,imageUri);
    }
    public static void writeFeed() {
        NNGLink.writeFeed(getActivity());
    }

    public static void stopSdk() {
        NNGLink.finishSdk();
    }

    private static native void onSdkStarted();

    private static native void onSdkStopped();

    private static native void onSdkReceiveInGameMenuCode(String inGameMenuCode);
}
