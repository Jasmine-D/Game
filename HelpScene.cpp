//
//  HelpScene.cpp
//  helloworld
//
//  Created by apple on 2019/6/2.
//

#include "HelpScene.h"
#include "NextHelpScene.h"
USING_NS_CC;

Scene* HelpScene::createScene()
{
    return HelpScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelpScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backhomepageItem = MenuItemImage::create(
                                                  "menu/helloworld/BackhomepageNormal.png",
                                                  "menu/helloworld/BackhomepageSelected.png",
                                                  CC_CALLBACK_1(HelpScene::menuHomepageCallback, this)
                                                  );
    
    if (backhomepageItem == nullptr ||
        backhomepageItem->getContentSize().width <= 0 ||
        backhomepageItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/helloworld/BackhomepageNormal.png' and 'BackhomepageSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - backhomepageItem->getContentSize().width / 2;
        float y = origin.y +backhomepageItem->getContentSize().height / 2;
        backhomepageItem->setPosition(Vec2(x, y));
    }
    
    auto nextpageItem = MenuItemImage::create(
                                                  "menu/helloworld/NextPageNormal.png",
                                                  "menu/helloworld/NextPageSelected.png",
                                              CC_CALLBACK_1(::HelpScene::menuItemNextHelpCallback, this)
                                                  );
    
    if (nextpageItem == nullptr ||
        nextpageItem->getContentSize().width <= 0 ||
        nextpageItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/helloworld/NextPageNormal.png' and 'NextPageSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - nextpageItem->getContentSize().width *11.6;
        float y = origin.y +nextpageItem->getContentSize().height / 2;
        nextpageItem->setPosition(Vec2(x, y));
    }
    
    auto menu = Menu::create(backhomepageItem,nextpageItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto background = Sprite::create("background/HelpScene.png");
    if (background == nullptr)
    {
        problemLoading("'background/HelpScene.png'");
    }
    else
    {
        
        background->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + visibleSize.height / 2));
        
        
        this->addChild(background, 0);
    }
    
    auto listener = cocos2d::EventListenerMouse::create();
    listener ->onMouseDown = [](Event * event){
    };
    return true;
}


void HelpScene::menuHomepageCallback(Ref*pSender) {
    Director::getInstance()->popToRootScene();
}

void HelpScene::menuItemNextHelpCallback(Ref*pSender){
    auto next = NextHelpScene::createScene();
    Director::getInstance()->pushScene(next);
}
