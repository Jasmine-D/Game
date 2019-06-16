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
//#include "MyUtility.h"
#include "SelectRoleScene.h"
#include "SocketManager.h"
#include "OnlineGameScene.h"

USING_NS_CC;


Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}


HelloWorld::~HelloWorld()
{
    NotificationCenter::getInstance()->removeAllObservers(this);
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
   
    SocketManager::getInstance()->start();
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(HelloWorld::login), "1", NULL);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "menu/helloworld/StopNormal.png",
                                           "menu/helloworld/StopSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/helloworld/StopNormal.png' and 'menu/helloworld/StopSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }
    auto startItem = MenuItemImage::create(
                                           "menu/helloworld/StartNormal.png",
                                           "menu/helloworld/StartSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuItemSelectCallback,this));
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height/ 2-startItem->getContentSize().height/3;
    startItem->setPosition(Vec2(x, y));
    // create menu, it's an autorelease object
    
    auto menu = Menu::create(startItem,closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    auto background = Sprite::create("background/helloworld_bg.png");
    if (background == nullptr)
    {
        problemLoading("'background/helloworld_bg.png'");
    }
    else
    {
        
        background->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + visibleSize.height/2));
        
        
        this->addChild(background, 0);
    }
    return true;
}

void HelloWorld::login(Ref* pData)
{
    Director::getInstance()->replaceScene(OnlineGame::createScene());
}


void HelloWorld::update(float dt) {
    auto sprite = this->getChildByTag(123);
    sprite->setPosition(sprite->getPosition() + Vec2(0.5, 0.5));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    unscheduleUpdate();
    Director::getInstance()->end();
}

void HelloWorld::menuItemSelectCallback(Ref*pSender) {
    auto cj = SelectRole::createScene();
    Director::getInstance()->pushScene(cj);
}


