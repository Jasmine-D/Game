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
//#include "SimpleAudioEngine.h"
#include "SelectRoleScene.h"
#include "HelpScene.h"
//#include "ODSocket.h"

/*#include <stdio.h>
#include <thread>
#include<stdlib.h>*/
USING_NS_CC;


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
bool HelloWorld::init(){
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    // connectServer();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    
    auto helpItem = MenuItemImage::create(
                                           "menu/helloworld/HelpNormal.png",
                                           "menu/helloworld/HelpSelected.png",
                                          CC_CALLBACK_1(::HelloWorld::menuItemHelpCallback, this));
    
    if (helpItem == nullptr ||
        helpItem->getContentSize().width <= 0 ||
        helpItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/helloworld/HelpNormal.png' and 'menu/helloworld/HelpSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - helpItem->getContentSize().width/2;
        float y = origin.y + helpItem->getContentSize().height*1.6;
        helpItem->setPosition(Vec2(x,y));
    }
    
    
    
    
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
    float y = origin.y + visibleSize.height*2/ 5-startItem->getContentSize().height/4;
    startItem->setPosition(Vec2(x, y));
    // create menu, it's an autorelease object
    
    auto menu = Menu::create(startItem,closeItem,helpItem,NULL);
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

// Socker连接
/*void HelloWorld::connectServer()
{
    // 初始化
    //ODSocket socket;
    socket.Init();
    socket.Create(AF_INET, SOCK_STREAM, 0);
    
    // 设置服务器的IP地址，端口号
    // 并连接服务器 Connect
    const char* ip = "127.0.0.1";
    int port = 12345;
    bool result = socket.Connect(ip, port);
    
    // 发送数据 Send
    socket.Send("login", 5);
    
    if (result) {
        CCLOG("connect to server success!");
        // 开启新线程，在子线程中，接收数据
        std::thread recvThread = std::thread(&HelloWorld::receiveData, this);
        recvThread.detach(); // 从主线程分离
    }
    else {
        CCLOG("can not connect to server");
        return;
    }
}

// 接收数据
void HelloWorld::receiveData()
{
    // 因为是强联网
    // 所以可以一直检测服务端是否有数据传来
    while (true) {
        // 接收数据 Recv
        char data[512] = "";
        int result = socket.Recv(data, 512, 0);
        printf("%d", result);
        // 与服务器的连接断开了
        if (result <= 0) break;
        
        CCLOG("%s", data);
    }
    // 关闭连接
    socket.Close();
}*/



void HelloWorld::update(float dt) {
    auto spirit = this->getChildByTag(123);
    spirit->setPosition(spirit->getPosition() + Vec2(0.5, 0.5));
    
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
void HelloWorld::menuItemHelpCallback(Ref*pSender){
    auto aid = HelpScene::createScene();
    Director::getInstance()->pushScene(aid);
}
