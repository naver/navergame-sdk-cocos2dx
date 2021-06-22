/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>

USING_NS_CC;

enum CafeSdkTags {
    kTagHomeBanner,
    kTagSorryBanner,
    kTagFeedList,
    kTagFeed,
};

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }


    initSdkButtons(menu);

    nng::NaverGameSDK::init("UKvNABLDsyEJusJGsXL2", "rK4suc_Qd0", "naver_game_4developer");
    nng::NaverGameSDK::setSdkListener(this);

    return true;
}



void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

void HelloWorld::initSdkButtons(Menu* menu) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto menu1 = MenuItemImage::create("icon1.png", "icon1.png",
                                     CC_CALLBACK_1(HelloWorld::menuCallback, this));
    menu1->setTag(kTagHomeBanner);
    menu1->setPosition(Vec2(
            origin.x + menu1 -> getContentSize().width,
            origin.y + menu1 -> getContentSize().height));
    auto label1 = Label::createWithSystemFont("start\nHome", "", 10);
    label1->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    label1->setTextColor(Color4B::BLACK);
    label1->enableOutline(Color4B::WHITE, 1);
    label1->setPosition(menu1->getContentSize().width * 0.5, menu1->getContentSize().height * 0.5);
    menu1->addChild(label1);
    menu->addChild(menu1);


    auto menu2 = MenuItemImage::create("icon1.png", "icon1.png",
                                       CC_CALLBACK_1(HelloWorld::menuCallback, this));
    menu2->setTag(kTagSorryBanner);
    menu2->setPosition(Vec2(
            menu1->getPositionX() + menu2 -> getContentSize().width * 1.5,
            menu1->getPositionY()));
    auto label2 = Label::createWithSystemFont("start\nSorry", "", 10);
    label2->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    label2->setTextColor(Color4B::BLACK);
    label2->enableOutline(Color4B::WHITE, 1);
    label2->setPosition(menu2->getContentSize().width * 0.5, menu2->getContentSize().height * 0.5);
    menu2->addChild(label2);
    menu->addChild(menu2);


    auto menu3 = MenuItemImage::create("icon1.png", "icon1.png",
                                       CC_CALLBACK_1(HelloWorld::menuCallback, this));
    menu3->setTag(kTagFeedList);
    menu3->setPosition(Vec2(
            menu2->getPositionX() + menu3 -> getContentSize().width * 1.5,
            menu1->getPositionY()));
    auto label3 = Label::createWithSystemFont("start\nBoard", "", 10);
    label3->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    label3->setTextColor(Color4B::BLACK);
    label3->enableOutline(Color4B::WHITE, 1);
    label3->setPosition(menu3->getContentSize().width * 0.5, menu3->getContentSize().height * 0.5);
    menu3->addChild(label3);
    menu->addChild(menu3);


    auto menu4 = MenuItemImage::create("icon1.png", "icon1.png",
                                       CC_CALLBACK_1(HelloWorld::menuCallback, this));
    menu4->setTag(kTagFeed);
    menu4->setPosition(Vec2(
            menu3->getPositionX() + menu4 -> getContentSize().width * 1.5,
            menu1->getPositionY()));
    auto label4 = Label::createWithSystemFont("start\nFeed", "", 10);
    label4->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    label4->setTextColor(Color4B::BLACK);
    label4->enableOutline(Color4B::WHITE, 1);
    label4->setPosition(menu4->getContentSize().width * 0.5, menu4->getContentSize().height * 0.5);
    menu4->addChild(label4);
    menu->addChild(menu4);
}

void HelloWorld::menuCallback(Ref* pSender) {
    auto item = (MenuItemFont*) pSender;

    switch (item->getTag()) {
        case kTagHomeBanner:
            nng::NaverGameSDK::startHomeBanner();
            break;

        case kTagSorryBanner:
            nng::NaverGameSDK::startSorryBanner();
            break;

        case kTagFeedList:
            nng::NaverGameSDK::startBoard(1);
            break;

        case kTagFeed:
            nng::NaverGameSDK::startFeed(50133, false);
            break;

        default:
            break;
    }
}

void HelloWorld::onSdkStarted() {
    std::cout << std::endl << "\"onSdkStarted\"" << std::endl << std::endl;
}

void HelloWorld::onSdkStopped() {
    std::cout << std::endl << "\"onSdkStopped\"" << std::endl << std::endl;
}

void HelloWorld::onSdkReceiveInGameMenuCode(const std::string &inGameMenuCode) {
    std::cout << std::endl << "\"onSdkReceiveInGameMenuCode: \"" << inGameMenuCode << std::endl << std::endl;
}
