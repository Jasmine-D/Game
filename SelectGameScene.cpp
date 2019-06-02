#include "SelectGameScene.h"
#include "SingleGameScene.h"
#include "OnlineGameScene.h"
USING_NS_CC;
Scene* SelectGame::createScene()
{
    return SelectGame::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SelectGame::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backhomepageItem = MenuItemImage::create(
                                                  "menu/helloworld/selectrolecallbackNormal.png",
                                                  "menu/helloworld/selectrolecallbackSelected.png",
                                                  CC_CALLBACK_1(SelectGame::menuselectroleCallback, this)
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
    auto singleItem= MenuItemImage::create(
                                           "menu/selectgame/SingleNormal.png",
                                           "menu/selectgame/SingleSelected.png",
                                           CC_CALLBACK_1(SelectGame::menuItemEnterCallback1, this)
                                           );
    if (singleItem == nullptr ||
        singleItem->getContentSize().width <= 0 ||
        singleItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectgame/SingleNormal.png' and 'selectgame/SingleSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width/4;
        float y = origin.y + visibleSize.height/2;
        singleItem->setPosition(Vec2(x, y));
    }
    auto onlineItem = MenuItemImage::create(
                                            "menu/selectgame/OnlineNormal.png",
                                            "menu/selectgame/OnlineSelected.png",
                                            CC_CALLBACK_1(SelectGame::menuItemEnterCallback2, this)
                                            );
    if (onlineItem == nullptr ||
        onlineItem->getContentSize().width <= 0 ||
        onlineItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectgame/OnlineNormal.png' and 'selectgame/OnlineSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width*3 / 4;
        float y = origin.y + visibleSize.height / 2;
        onlineItem->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(singleItem,onlineItem,backhomepageItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto background = Sprite::create("background/selectgame_bg.png");
    if (background == nullptr)
    {
        problemLoading("'background/selectgame_bg.png'");
    }
    else
    {
        
        background->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + visibleSize.height / 2));
        
        
        this->addChild(background, 0);
    }
    return true;
}
void SelectGame::menuselectroleCallback(Ref*pSender) {
    Director::getInstance()->popScene();
}
void SelectGame::menuItemEnterCallback1(Ref*pSender) {
    auto cj = SingleGame::createScene();
    Director::getInstance()->pushScene(cj);
}
void SelectGame::menuItemEnterCallback2(Ref*pSender) {
    auto cj = OnlineGame::createScene();
    Director::getInstance()->pushScene(cj);
}



