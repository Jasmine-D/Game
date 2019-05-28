//
//  SelectRoleScene.cpp
//  helloworld
//
//  Created by apple on 2019/5/28.
//

#include "SelectRoleScene.h"
#include "SelectGameScene.h"
USING_NS_CC;

Scene* SelectRole::createScene()
{
    return SelectRole::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SelectRole::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto backhomepageItem = MenuItemImage::create(
                                                  "menu/helloworld/BackhomepageNormal.png",
                                                  "menu/helloworld/BackhomepageSelected.png",
                                                  CC_CALLBACK_1(SelectRole::menuHomepageCallback, this)
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
    
    
    auto OrangeRoleItem= MenuItemImage::create(
                                           "menu/selectrole/OrangeRoleNormal.png",
                                           "menu/selectrole/OrangeRoleSelected.png",
                                           CC_CALLBACK_1(SelectRole::menuItemEnterCallback1, this)
                                           );
    if (OrangeRoleItem == nullptr ||
        OrangeRoleItem->getContentSize().width <= 0 ||
        OrangeRoleItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectrole/OrangeRoleNormal.png' and 'menu/selectrole/OrangeRoleSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width*1 / 8;
        float y = origin.y + visibleSize.height*4 / 9;
        OrangeRoleItem->setPosition(Vec2(x, y));
    }
    
    
    
    auto LitchiRoleItem = MenuItemImage::create(
                                            "menu/selectrole/LitchiRoleNormal.png",
                                            "menu/selectrole/LitchiRoleSelected.png",
                                                CC_CALLBACK_1(::SelectRole::menuItemEnterCallback1, this)
                                            );
    if (LitchiRoleItem == nullptr ||
        LitchiRoleItem->getContentSize().width <= 0 ||
        LitchiRoleItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectrole/LitchiRoleNormal.png' and 'selectselectrole/LitchiRoleSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width*2 / 4;
        float y = origin.y + visibleSize.height*4 / 9;
        LitchiRoleItem->setPosition(Vec2(x, y));
    }
    
    auto AvocadoRoleItem = MenuItemImage::create(
                                                   "menu/selectrole/AvocadoRoleNormal.png",
                                                   "menu/selectrole/AvocadoRoleSelected.png",
                                                   CC_CALLBACK_1(::SelectRole::menuItemEnterCallback1, this)
                                                   );
    if (AvocadoRoleItem == nullptr ||
        AvocadoRoleItem->getContentSize().width <= 0 ||
        AvocadoRoleItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectrole/AvocadoRoleNormal.png' and 'selectselectrole/AvocadoRoleSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width*6 / 7;
        float y = origin.y + visibleSize.height*4 / 9;
        AvocadoRoleItem->setPosition(Vec2(x, y));
    }
    
    auto PineappleRoleItem = MenuItemImage::create(
                                                "menu/selectrole/PineappleRoleNormal.png",
                                               "menu/selectrole/PineappleRoleSelected.png",
                                                   CC_CALLBACK_1(::SelectRole::menuItemEnterCallback1, this)
                                                );
    if (PineappleRoleItem == nullptr ||
        PineappleRoleItem->getContentSize().width <= 0 ||
        PineappleRoleItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectrole/PineappleRoleNormal.png' and 'selectselectrole/PineappleRoleSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width*30 /100 ;
        float y = origin.y + visibleSize.height*1 / 18;
        PineappleRoleItem->setPosition(Vec2(x, y));
    }
    
    auto MulberryRoleItem = MenuItemImage::create(
                                                  "menu/selectrole/MulberryRoleNormal.png",
                                                  "menu/selectrole/MulberryRoleSelected.png",
                                                  CC_CALLBACK_1(SelectRole::menuItemEnterCallback1, this)
                                                  );
    if (MulberryRoleItem == nullptr ||
        MulberryRoleItem->getContentSize().width <= 0 ||
        MulberryRoleItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/selectrole/MulberryRoleNormal.png' and 'menu/selectrole/MulberryRoleSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width*67 / 100;
        float y = origin.y + visibleSize.height*1 / 15;
        MulberryRoleItem->setPosition(Vec2(x, y));
    }
    
    
    

    auto menu = Menu::create(OrangeRoleItem,LitchiRoleItem,AvocadoRoleItem,PineappleRoleItem,MulberryRoleItem ,backhomepageItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto background = Sprite::create("background/selectrole_bg.png");
    if (background == nullptr)
    {
        problemLoading("'background/selectrole_bg.png'");
    }
    else
    {
        
        background->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + visibleSize.height / 2));
        
        
        this->addChild(background, 0);
    }
    return true;
}


void SelectRole::menuHomepageCallback(Ref*pSender) {
    Director::getInstance()->popToRootScene();
}
void SelectRole::menuItemEnterCallback1(Ref*pSender) {
    auto cj = SelectGame::createScene();
    Director::getInstance()->pushScene(cj);
}


