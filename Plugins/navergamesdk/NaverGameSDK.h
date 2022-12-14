#ifndef _JNI_NAVER_GAME_SDK_H_
#define _JNI_NAVER_GAME_SDK_H_
#include <string>

namespace nng {
    class NaverGameSDKListener {
    public:
        // Sdk 시작시에 이벤트.
        virtual void onSdkStarted() = 0;

        // Sdk 종료시에 이벤트.
        virtual void onSdkStopped() = 0;

        // Sdk 실행 중에 유저가 특정 액션을 하게되면 귀사에서 설정한 string을 파라미터로 받는 이벤트.
        virtual void onSdkReceiveInGameMenuCode(const std::string &inGameMenuCode) = 0;
    };

    class NaverGameSDK {
    public:
        /* 네아로 정보와 라운지 아이디로 sdk 초기화 합니다. */
        static void init(std::string clientId, std::string clientSecret, std::string loungeId);

        // Sdk에서 보내오는 각종 이벤트를 받는 리스너를 등록합니다.
        static void setSdkListener(NaverGameSDKListener* listener);

        // Sdk를 실행하는 기기의 국가코드를 가져옵니다.
        static char* getCountryCode();

        // Sdk의 홈배너를 실행합니다.
        static void startHomeBanner();

        // Sdk의 점검배너를 실행합니다.
        static void startSorryBanner();

        // Sdk의 라운지 boardId와 매핑되는 글목록을 실행합니다.
        static void startBoard(int boardId);

        // Sdk의 라운지 FeedId와 매핑되는 글상세를 실행합니다.
        static void startFeed(int feedId, bool isTempFeedId);

        static void setCanWriteFeedByScreenshot(bool Enabled);
        static void setGameId(std::string GameId);
        static void startFeedWriting(int BoardId, std::string Title, std::string Text, std::string ImageFilePath);
        static void naverLogout();

        // Sdk를 종료시킵니다.
        static void stopSdk();
    };
} /* namespace nng */
#endif /* _JNI_NAVER_GAME_SDK_H_ */
