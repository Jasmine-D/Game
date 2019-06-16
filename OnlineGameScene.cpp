#include "OnlineGameScene.h"
#include "SocketManager.h"
#include "ODSocket.h"
#include <iostream>
#include "JsonData.h"
#include "json/writer.h"

USING_NS_CC;
Scene* OnlineGame::createScene()
{
    return OnlineGame::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

OnlineGame::~OnlineGame()
{
}

bool OnlineGame::init() {
    if (!Scene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    tileMap = TMXTiledMap::create("tileMap.tmx");
    scale = visibleSize.height / tileMap->getContentSize().height;
    tileMap->setScale(scale);
    tileMap->setAnchorPoint(Vec2::ZERO);
    tileMap->setPosition(Vec2::ZERO);
    this->addChild(tileMap, -1);
    collision = tileMap->getLayer("collision");
    collision->setVisible(false);
    
    auto exitItem = MenuItemImage::create(
                                          "menu/onlinegame/ExitNormal.png",
                                          "menu/onlinegame/ExitSelected.png",
                                          CC_CALLBACK_1(OnlineGame ::menuItemExitCallback, this)
                                          );
    if (exitItem == nullptr ||
        exitItem->getContentSize().width <= 0 ||
        exitItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/onlinegame/ExitNormal.png' and 'menu/onlinegame/ExitSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - exitItem->getContentSize().width / 2;
        float y = origin.y + exitItem->getContentSize().height / 2;
        exitItem->setPosition(Vec2(x, y));
    }
    auto menu = Menu::create(exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void OnlineGame::menuItemExitCallback(Ref*pSender) {
    Director::getInstance()->popScene();
}

