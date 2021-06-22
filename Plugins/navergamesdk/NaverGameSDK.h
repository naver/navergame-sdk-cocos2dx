#ifndef _JNI_NAVER_GAME_SDK_H_
#define _JNI_NAVER_GAME_SDK_H_

#include <string>

namespace nng {

    class NaverGameSDKListener {
    public:
        virtual void onSdkStarted() = 0;
        virtual void onSdkStopped() = 0;
        virtual void onSdkReceiveInGameMenuCode(const std::string &inGameMenuCode) = 0;
    };

    class NaverGameSDK {
    public:
        /* 네아로 정보와 라운지 아이디로 sdk 초기화 합니다. */
        static void init(std::string clientId, std::string clientSecret, std::string loungeId);

        static void setSdkListener(NaverGameSDKListener* listener);

        static void startHomeBanner();

        static void startSorryBanner();

        static void startBoard(int boardId);

        static void startFeed(int feedId);
        
        static void stopSdk();

    };
} /* namespace nng */

#endif /* _JNI_NAVER_GAME_SDK_H_ */
