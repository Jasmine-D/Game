#include"SingleGameScene.h"
#include"SelectRoleScene.h"
USING_NS_CC;
Scene* SingleGame::createScene()
{
    return SingleGame::create();
}
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool SingleGame::init() {
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    if(name=="orange.png")
    {
        Player = Sprite::create("character/orange.png");
    }
    if(name=="litchi.png")
    {
        Player = Sprite::create("character/litchi.png");
    }
    if(name=="avocado.png")
    {
        Player = Sprite::create("character/avocado.png");
    }
    if(name=="pineapple.png")
    {
        Player = Sprite::create("character/pineapple.png");
    }
    if(name=="mulberry.png")
    {
        Player = Sprite::create("character/mulberry.png");
    }
    Player->setPosition(Vec2(origin.x + visibleSize.width * 4 / 9, origin.y + Player->getContentSize().height / 2));
    addChild(Player, 1, 200);
    
    auto exitItem = MenuItemImage::create(
                                          "menu/singlegame/ExitNormal.png",
                                          "menu/singlegame/ExitSelected.png",
                                          CC_CALLBACK_1(SingleGame::menuItemExitCallback, this)
                                          );
    
    if (exitItem == nullptr ||
        exitItem->getContentSize().width <= 0 ||
        exitItem->getContentSize().height <= 0)
    {
        problemLoading("'menu/singlegame/ExitNormal.png' and 'menu/singlegame/ExitSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width-exitItem->getContentSize().width/2;
        float y = origin.y + exitItem->getContentSize().height/2;
        exitItem->setPosition(Vec2(x, y));
    }
    
    auto UpItem = MenuItemImage::create(
                                        "menu/singlegame/UpNormal.png",
                                        "menu/singlegame/UpSelected.png",
                                        CC_CALLBACK_1(SingleGame::menuItemUp, this)
                                        );
    UpItem->setAnchorPoint(Vec2(0, 0));
    UpItem->setPosition(Vec2(UpItem->getContentSize().width,2*UpItem->getContentSize().height));
    auto DownItem = MenuItemImage::create(
                                          "menu/singlegame/DownNormal.png",
                                          "menu/singlegame/DownSelected.png",
                                          CC_CALLBACK_1(SingleGame::menuItemDown, this)
                                          );
    DownItem->setAnchorPoint(Vec2(0, 0));
    DownItem->setPosition(Vec2(DownItem->getContentSize().width,0));
    auto LeftItem = MenuItemImage::create(
                                          "menu/singlegame/LeftNormal.png",
                                          "menu/singlegame/LeftSelected.png",
                                          CC_CALLBACK_1(SingleGame::menuItemLeft, this)
                                          );
    LeftItem->setAnchorPoint(Vec2(0, 0));
    LeftItem->setPosition(Vec2(0,LeftItem->getContentSize().height));
    
    auto RightItem = MenuItemImage::create(
                                           "menu/singlegame/RightNormal.png",
                                           "menu/singlegame/RightSelected.png",
                                           CC_CALLBACK_1(SingleGame::menuItemRight, this)
                                           );
    RightItem->setAnchorPoint(Vec2(0, 0));
    RightItem->setPosition(Vec2(2*RightItem->getContentSize().width,RightItem->getContentSize().height));
    auto menu = Menu::create(exitItem,UpItem,DownItem,LeftItem,RightItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    auto background = Sprite::create("background/map.png");
    if (background == nullptr)
    {
        problemLoading("'background/map.png'");
    }
    else
    {
        
        background->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + visibleSize.height / 2));
        
        this->addChild(background, 0);
    }
    return true;
}
void SingleGame::menuItemExitCallback(Ref*pSender) {
    Director::getInstance()->popScene();
}

void SingleGame::onEnter() {
    Scene::onEnter();
    log("SingleGameScene onEnter");
    
    auto listener1 = EventListenerMouse::create();
    auto listener2 = EventListenerKeyboard::create();
    
    
    listener1->onMouseDown = [=](Event*event) {
        log("onMouseDown");
        EventMouse*e = (EventMouse*)event;
        auto sprite = this->getChildByTag(200);
        float rx = e->getCursorX() - sprite->getPosition().x;
        float ry = e->getCursorY() - sprite->getPosition().y;
        Size s = sprite->getContentSize();
        
        if (abs(rx)<s.width/2&&abs(ry)<s.width/2) {
            
            attack = true;
        }
        else {
            attack = false;
            //attackfinished = false;
        }
        /*if (attackfinished = true) {
         removeChildByTag(10);
         }*/
    };
    listener1->onMouseUp = [=](Event*event) {
        log("onMouseUp");
        EventMouse*e = (EventMouse*)event;
        
        
        if (attack==true) {
            log("attack true");
            FiniteTimeAction *ac1,*ac2;
            
            auto sprite = this->getChildByTag(200);
            auto weapon = Sprite::create();
            if(name=="orange.png")
            {
                weapon = Sprite::create("weapon/orangearrow.png");
            }
            if(name=="litchi.png")
            {
                weapon = Sprite::create("weapon/litchiarrow.png");
            }
            if(name=="avocado.png")
            {
                weapon = Sprite::create("weapon/avocadoarrow.png");
            }
            if(name=="pineapple.png")
            {
                weapon = Sprite::create("weapon/pineapplearrow.png");
            }
            if(name=="mulberry.png")
            {
                weapon = Sprite::create("weapon/mulberryarrow.png");
            }
            if (weapon == nullptr)
            {
                problemLoading("'weapon/arrow.png'");
            }
            else {
                
                weapon->setPosition(Vec2(sprite->getPosition()));
                this->addChild(weapon,1 );
                
                float rx = e->getCursorX() - sprite->getPosition().x;
                float ry = e->getCursorY() - sprite->getPosition().y;
                weapon->setRotation(90 - atan2(ry, rx)*57.29578);
                sprite->setRotation(90 - atan2(ry, rx)*57.29578);
                ac1= (FiniteTimeAction *) weapon->runAction(MoveBy::create(1,Vec2(160*rx/sqrt(rx*rx+ry*ry),160*ry/sqrt(rx*rx+ry*ry))));
                ac2 = (FiniteTimeAction *)weapon->runAction(FadeOut::create(4));
                weapon->runAction(Sequence::create(ac1, ac2, NULL));
            }
        }
        else {
            
            log("attack false");
        }
        
    };
    listener2->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*event) {
        auto sprite= this->getChildByTag(200);
        FiniteTimeAction *ac1, *ac2;
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            
            sprite->runAction(MoveBy::create(1, Vec2(40, 0)));
            sprite->runAction(RotateTo::create(0.1, 90));
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            
            sprite->runAction(MoveBy::create(1, Vec2(-40, 0)));
            sprite->runAction(RotateTo::create(0.1, -90));
            
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            
            sprite->runAction(MoveBy::create(1, Vec2(0, 40)));
            sprite->runAction(RotateTo::create(0.1, 0));
            
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            
            sprite->runAction(MoveBy::create(1, Vec2(0, -40)));
            sprite->runAction(RotateTo::create(0.1, 180));
            
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
            auto weapon = Sprite::create();
            if(name=="orange.png")
            {
                weapon = Sprite::create("weapon/orangearrow.png");
            }
            if(name=="litchi.png")
            {
                weapon = Sprite::create("weapon/litchiarrow.png");
            }
            if(name=="avocado.png")
            {
                weapon = Sprite::create("weapon/avocadoarrow.png");
            }
            if(name=="pineapple.png")
            {
                weapon = Sprite::create("weapon/pineapplearrow.png");
            }
            if(name=="mulberry.png")
            {
                weapon = Sprite::create("weapon/mulberryarrow.png");
            }
            weapon->setPosition(Vec2(sprite->getPosition()));
            weapon->setRotation(180);
            this->addChild(weapon, 1);
            sprite->setRotation(180);
            ac1 = (FiniteTimeAction *)weapon->runAction(MoveBy::create(1, Vec2(0, -160)));
            ac2 = (FiniteTimeAction *)weapon->runAction(FadeOut::create(4));
            weapon->runAction(Sequence::create(ac1, ac2, NULL));
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
            auto weapon = Sprite::create();
            if(name=="orange.png")
            {
                weapon = Sprite::create("weapon/orangearrow.png");
            }
            if(name=="litchi.png")
            {
                weapon = Sprite::create("weapon/litchiarrow.png");
            }
            if(name=="avocado.png")
            {
                weapon = Sprite::create("weapon/avocadoarrow.png");
            }
            if(name=="pineapple.png")
            {
                weapon = Sprite::create("weapon/pineapplearrow.png");
            }
            if(name=="mulberry.png")
            {
                weapon = Sprite::create("weapon/mulberryarrow.png");
            }
            weapon->setPosition(Vec2(sprite->getPosition()));
            weapon->setRotation(0);
            this->addChild(weapon, 1);
            sprite->setRotation(0);
            ac1 = (FiniteTimeAction *)weapon->runAction(MoveBy::create(1, Vec2(0, 160)));
            ac2 = (FiniteTimeAction *)weapon->runAction(FadeOut::create(4));
            weapon->runAction(Sequence::create(ac1, ac2, NULL));
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
            auto weapon = Sprite::create();
            if(name=="orange.png")
            {
                weapon = Sprite::create("weapon/orangearrow.png");
            }
            if(name=="litchi.png")
            {
                weapon = Sprite::create("weapon/litchiarrow.png");
            }
            if(name=="avocado.png")
            {
                weapon = Sprite::create("weapon/avocadoarrow.png");
            }
            if(name=="pineapple.png")
            {
                weapon = Sprite::create("weapon/pineapplearrow.png");
            }
            if(name=="mulberry.png")
            {
                weapon = Sprite::create("weapon/mulberryarrow.png");
            }
            weapon->setPosition(Vec2(sprite->getPosition()));
            weapon->setRotation(-90);
            this->addChild(weapon, 1);
            sprite->setRotation(-90);
            ac1 = (FiniteTimeAction *)weapon->runAction(MoveBy::create(1, Vec2(-160,0)));
            ac2 = (FiniteTimeAction *)weapon->runAction(FadeOut::create(4));
            weapon->runAction(Sequence::create(ac1, ac2, NULL));
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
            auto weapon = Sprite::create();
            if(name=="orange.png")
            {
                weapon = Sprite::create("weapon/orangearrow.png");
            }
            if(name=="litchi.png")
            {
                weapon = Sprite::create("weapon/litchiarrow.png");
            }
            if(name=="avocado.png")
            {
                weapon = Sprite::create("weapon/avocadoarrow.png");
            }
            if(name=="pineapple.png")
            {
                weapon = Sprite::create("weapon/pineapplearrow.png");
            }
            if(name=="mulberry.png")
            {
                weapon = Sprite::create("weapon/mulberryarrow.png");
            }
            weapon->setPosition(Vec2(sprite->getPosition()));
            weapon->setRotation(90);
            this->addChild(weapon, 1);
            sprite->setRotation(90);
            ac1 = (FiniteTimeAction *)weapon->runAction(MoveBy::create(1, Vec2(160,0)));
            ac2 = (FiniteTimeAction *)weapon->runAction(FadeOut::create(4));
            weapon->runAction(Sequence::create(ac1, ac2, NULL));
        }
        
    };
    
    EventDispatcher*eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, getChildByTag(200));
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, getChildByTag(200));
    
}

void SingleGame::onExit() {
    
    Scene::onExit();
    log("SingleGameScene onExit");
    //Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    auto target = this->getChildByTag(200);
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(target);
    this->removeAllChildren();
}
/*void SingleGame::MouseMove(Event*event) {
 EventMouse*e = (EventMouse*)event;
 log("onMouseMove");
 }
 void SingleGame::MouseDown(Event*event) {
 EventMouse*e = (EventMouse*)event;
 Player->setPosition(Vec2(e->getCursorX(), e->getCursorY()));
 log("onMouseDown");
 }*/
void SingleGame::menuItemUp(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    sprite->runAction(MoveBy::create(1, Vec2(0, 40)));
    sprite->runAction(RotateTo::create(0.1, 0));
}
void SingleGame::menuItemDown(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    sprite->runAction(MoveBy::create(1, Vec2(0, -40)));
    sprite->runAction(RotateTo::create(0.1, 180));
}
void SingleGame::menuItemLeft(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    sprite->runAction(MoveBy::create(1, Vec2(-40, 0)));
    sprite->runAction(RotateTo::create(0.1, -90));
}
void SingleGame::menuItemRight(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    sprite->runAction(MoveBy::create(1, Vec2(40, 0)));
    sprite->runAction(RotateTo::create(0.1, 90));
} 
