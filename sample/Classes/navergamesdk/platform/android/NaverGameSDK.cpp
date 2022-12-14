#include "NaverGameSDK.h"
#include "platform/android/jni/JniHelper.h"

using namespace cocos2d;

namespace nng {
    static bool getStaticMethod(JniMethodInfo &methodinfo, const char *methodName, const char *paramCode) {
        static const char* kCafeSdkClass = "com/navercorp/nng/cocos2dx/sample/NNGSdk";
        return JniHelper::getStaticMethodInfo(methodinfo, kCafeSdkClass, methodName, paramCode);
    }

    static NaverGameSDKListener* sdkListener = nullptr;

    void NaverGameSDK::setSdkListener(NaverGameSDKListener* listener) {
        sdkListener = listener;
    }

    void NaverGameSDK::init(std::string clientId, std::string clientSecret, std::string loungeId) {
        JniMethodInfo t;
        if (getStaticMethod(t, "init","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring _clientId = t.env->NewStringUTF(clientId.c_str());
            jstring _clientSecret = t.env->NewStringUTF(clientSecret.c_str());
            jstring _loungeId = t.env->NewStringUTF(loungeId.c_str());

            t.env->CallStaticVoidMethod(t.classID, t.methodID, _clientId, _clientSecret, _loungeId);

            t.env->DeleteLocalRef(_clientId);
            t.env->DeleteLocalRef(_clientSecret);
            t.env->DeleteLocalRef(_loungeId);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    char* NaverGameSDK::getCountryCode() {
        JniMethodInfo t;
        jstring countryCodeJstr = nullptr;
        if (getStaticMethod(t, "getCountryCode", "()Ljava/lang/String;")) {
            countryCodeJstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }

        auto countryCode = countryCodeJstr == nullptr? "" : JniHelper::jstring2string(countryCodeJstr);
        CCLOG("countryCode = %s", (char*)countryCode.c_str());

        return (char*)countryCode.c_str();
    }

    void NaverGameSDK::startHomeBanner() {
        JniMethodInfo t;
        if (getStaticMethod(t, "startHomeBanner", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void NaverGameSDK::startSorryBanner() {
        JniMethodInfo t;
        if (getStaticMethod(t, "startSorryBanner", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void NaverGameSDK::startBoard(int boardId) {
        JniMethodInfo t;
        if (getStaticMethod(t, "startBoard", "(I)V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, boardId);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void NaverGameSDK::startFeed(int feedId, bool isTempFeedId) {
        JniMethodInfo t;
        if (getStaticMethod(t, "startFeed", "(IZ)V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, feedId,isTempFeedId);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    void NaverGameSDK::setCanWriteFeedByScreenshot(bool isTempFeedId) {
        JniMethodInfo t;
        if (getStaticMethod(t, "enableScreenShotDetector", "(Z)V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID, isTempFeedId);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    void NaverGameSDK::setGameId(std::string gameId) {
        JniMethodInfo t;
        if (getStaticMethod(t, "putGameId","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring _gameId = t.env->NewStringUTF(gameId.c_str());
            t.env->CallStaticVoidMethod(t.classID, t.methodID, _gameId);
            t.env->DeleteLocalRef(_gameId);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void NaverGameSDK::startFeedWriting(int boardId, std::string title, std::string text, std::string imageFilePath) {
        JniMethodInfo t;
        if (getStaticMethod(t, "writeFeed","(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)V")) {
            jstring _title = t.env->NewStringUTF(title.c_str());
            jstring _text = t.env->NewStringUTF(text.c_str());
            jstring _imageFilePath = t.env->NewStringUTF(imageFilePath.c_str());

            t.env->CallStaticVoidMethod(t.classID, t.methodID, boardId,_title, _text, _imageFilePath);

            t.env->DeleteLocalRef(_title);
            t.env->DeleteLocalRef(_text);
            t.env->DeleteLocalRef(_imageFilePath);
            t.env->DeleteLocalRef(t.classID);
        }
    }
    void NaverGameSDK::naverLogout() {
        JniMethodInfo t;
        if (getStaticMethod(t, "logout", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }

    void NaverGameSDK::stopSdk() {
        JniMethodInfo t;
        if (getStaticMethod(t, "stopSdk", "()V")) {
            t.env->CallStaticVoidMethod(t.classID, t.methodID);
            t.env->DeleteLocalRef(t.classID);
        }
    }


    extern "C" {
        JNIEXPORT void JNICALL
        Java_com_navercorp_nng_cocos2dx_sample_NNGSdk_onSdkStarted(JNIEnv* env, jclass thiz) {
            if (sdkListener == nullptr) return;
            sdkListener->onSdkStarted();
        }

        JNIEXPORT void JNICALL
        Java_com_navercorp_nng_cocos2dx_sample_NNGSdk_onSdkStopped(JNIEnv* env, jclass thiz) {
            if (sdkListener == nullptr) return;
            sdkListener->onSdkStopped();
        }

        JNIEXPORT void JNICALL
        Java_com_navercorp_nng_cocos2dx_sample_NNGSdk_onSdkReceiveInGameMenuCode(JNIEnv* env, jclass thiz, jstring inGameMenuCode) {
            if (sdkListener == nullptr) return;
            sdkListener->onSdkReceiveInGameMenuCode(JniHelper::jstring2string(inGameMenuCode));
        }
    }
}   /* namespace nng */
