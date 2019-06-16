//
//  NextHelpScene.cpp
//  helloworld
//
//  Created by apple on 2019/6/16.
//

#include "NextHelpScene.h"
USING_NS_CC;

Scene* NextHelpScene::createScene()
{
    return NextHelpScene::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool NextHelpScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backhomepageItem = MenuItemImage::create(
                                                  "menu/helloworld/BackhomepageNormal.png",
                                                  "menu/helloworld/BackhomepageSelected.png",
                                                  CC_CALLBACK_1(NextHelpScene::menuHomepageCallback, this)
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
    
    auto previouspageItem = MenuItemImage::create(
                                              "menu/helloworld/PreviousPageNormal.png",
                                              "menu/helloworld/PreviousPageSelected.png",
                                              CC_CALLBACK_1(NextHelpScene::menuItemPreviousHelpCallback, this)
                                              );
    
    if (previouspageItem == nullptr ||
        previouspageItem->getContentSize().width <= 0 ||
        previouspageItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/helloworld/PreviousPageNormal.png' and 'PreviousPageSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - previouspageItem->getContentSize().width*11.6;
        float y = origin.y +previouspageItem->getContentSize().height / 2;
        previouspageItem->setPosition(Vec2(x, y));
    }
    
    auto menu = Menu::create(backhomepageItem,previouspageItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto background = Sprite::create("background/nexthelpscene.png");
    if (background == nullptr)
    {
        problemLoading("'background/nexthelpscene.png'");
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


void NextHelpScene::menuHomepageCallback(Ref*pSender) {
    Director::getInstance()->popToRootScene();
}
void NextHelpScene::menuItemPreviousHelpCallback(Ref*pSender){
    Director::getInstance()->popScene();
}
