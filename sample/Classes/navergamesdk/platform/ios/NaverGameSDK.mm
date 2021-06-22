// NAVER Game SDK for iOS
// Copyright 2021-present NAVER Corp.
//
// Unauthorized use, modification and redistribution of this software are strongly prohibited.
//
// Created by Alan on 2021/04/12.


#import "NaverGameSDK.h"
#import <NNGSDK/NNGSDKManager.h>


using namespace cocos2d;


// The proxy class for NNGSDKDelegate.
@interface NaverGameSDKDelegateProxy: NSObject <NNGSDKDelegate>

@end


// The global proxy object for NNGSDKDelegate.
static NaverGameSDKDelegateProxy *delegate = nil;


namespace nng {

// Delegate-implemeting object for SDK.
static NaverGameSDKListener *sdkListener = nullptr;


// Set the parent view controller and the delegate for SDK.
void setParentViewController() {
    UIWindow *window = UIApplication.sharedApplication.keyWindow;
    [NNGSDKManager.shared setParentViewController:window.rootViewController];
    NNGSDKManager.shared.delegate = delegate;
}


// Set client ID, client secret, and lounge ID for SDK
void NaverGameSDK::init(std::string clientId, std::string clientSecret, std::string loungeId) {
    delegate = [[NaverGameSDKDelegateProxy alloc] init];
    
    NSString *cId = [NSString stringWithUTF8String:clientId.c_str()];
    NSString *cSec = [NSString stringWithUTF8String:clientSecret.c_str()];
    NSString *lId = [NSString stringWithUTF8String:loungeId.c_str()];
    
    [NNGSDKManager.shared setClientId:cId clientSecret:cSec loungeId:lId];
}


// Set the delegate-implementing object for SDK.
void NaverGameSDK::setSdkListener(NaverGameSDKListener* listener) {
    sdkListener = listener;
}


// The ISO_3166-1 alpha-2 country code of each device.
char* NaverGameSDK::getCountryCode() {
    return (char *)NNGSDKManager.shared.countryCode.UTF8String;
}


// Present the banner list.
void NaverGameSDK::startHomeBanner() {
    setParentViewController();
    [NNGSDKManager.shared presentBannerViewController];
}


// Present a notice while your game is not on service.
void NaverGameSDK::startSorryBanner() {
    setParentViewController();
    [NNGSDKManager.shared presentSorryViewController];
}


// Present the list of feeds identified by a predefined board ID which represents a board.
void NaverGameSDK::startBoard(int boardId) {
    setParentViewController();
    [NNGSDKManager.shared presentBoardViewControllerWith:@(boardId)];
}


// Present the feed identified by a feed ID.
void NaverGameSDK::startFeed(int feedId, bool isTempFeedId) {
    setParentViewController();
    [NNGSDKManager.shared presentFeedViewControllerWith:@(feedId) scheduled:isTempFeedId];
}


// Dismiss all SDK-related views.
void NaverGameSDK::stopSdk() {
    [NNGSDKManager.shared dismiss];
}

} /* namespace nng */


@implementation NaverGameSDKDelegateProxy

#pragma mark NNGSDKDelegate

// Implementation for the delegate method -nngSDKViewDidLoad.
- (void)nngSDKDidLoad {
    if (nng::sdkListener == nil) {
        return;
    }
    
    nng::sdkListener->onSdkStarted();
}


// Implementation for the delegate method -nngSDKViewDidUnload.
- (void)nngSDKDidUnload {
    if (nng::sdkListener == nil) {
        return;
    }
    
    nng::sdkListener->onSdkStopped();
}


// Implementation for the delegate method -nngSDKDidReceiveInGameMenuCode:.
- (void)nngSDKDidReceiveInGameMenuCode:(NSString *)inGameMenuCode {
    if (nng::sdkListener == nil) {
        return;
    }
    
    nng::sdkListener->onSdkReceiveInGameMenuCode(std::string(inGameMenuCode.UTF8String));
}

@end
