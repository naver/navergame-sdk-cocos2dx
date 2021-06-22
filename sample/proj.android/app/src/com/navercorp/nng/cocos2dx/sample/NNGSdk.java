package com.navercorp.nng.cocos2dx.sample;

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
                onSdkStarted();
            }

            @Override
            public void onSdkDidUnloaded() {
                onSdkStopped();
            }

            @Override
            public void onCallInGameMenuCode(String moveTo) {
                onSdkReceiveInGameMenuCode(moveTo);
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

    public static void stopSdk() {
        NNGLink.finishSdk();
    }

    private static native void onSdkStarted();

    private static native void onSdkStopped();

    private static native void onSdkReceiveInGameMenuCode(String inGameMenuCode);
}
