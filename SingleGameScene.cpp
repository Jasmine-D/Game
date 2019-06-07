#include"SingleGameScene.h"
#include"SelectRoleScene.h"
#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;
USING_NS_CC;
float scale;
TMXObjectGroup * group_1;
vector<string>weapon = {"weapon/bullet.png","weapon/dart.png","weapon/defence.png","weapon/fire.png","weapon/laser.png","weapon/snowball.png"};
vector<string>weaponPos = {"weapon1","weapon2","weapon3","weapon4","weapon5","weapon6","weapon7","weapon8"};
map<string,string>collectable;

void mapInit(){
    for(int i = 0;i < 8;i++){
        collectable[weaponPos[i]] = "false";
    }
}

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
    
    Tmap = TMXTiledMap::create("tileddmap.tmx");
    scale = visibleSize.height/Tmap->getContentSize().height;
    Tmap->setScale(scale);
    addChild(Tmap,0,100);
    
    TMXObjectGroup * group = Tmap->getObjectGroup("role");
    ValueMap spawnPoint = group->getObject("AI");
    float x = spawnPoint["x"].asFloat()*scale;
    float y = spawnPoint["y"].asFloat()*scale;
    
    /*float x1 = (x/map->getTileSize().width) * scale ;
    float x2 = (((map->getMapSize().height *map->getTileSize().height)-y)/
    map->getTileSize().height) * scale;
    cout << x1 << " "<< x2 << '\n';
    cout << x <<" "<< y << '\n';*/
    
    Player->setPosition(Vec2(x,y));
    addChild(Player, 2, 200);
    
    collidable =Tmap->getLayer("wall");
    
    group_1 = Tmap->getObjectGroup("weapon");
    
    this->schedule( schedule_selector(SingleGame::myupdate), 20.0f, 20, 5.0f);
    
    mapInit();
    //Player->setPosition(Vec2(origin.x + visibleSize.width * 4 / 9, origin.y + Player->getContentSize().height / 2));
    //addChild(Player, 1, 200);
    
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
    
    return true;
}

void SingleGame::setPlayerPosition(Vec2 position)
{
    Vec2 tileCoord = this->tileCoordFromPosition(position);
    int tileGid = collidable->getTileGIDAt(tileCoord);
    if(tileGid > 0){
        //Value prop = map->getPropertiesForGID(tileGid);
        //ValueMap propValueMap = prop.asValueMap();
        //std::string collision = propValueMap["collidable"].asString();
        //if(collidable == "true"){
            log("collision check succeed!");
            float x1 = position.x/Tmap->getTileSize().width;
            float x2 = ((Tmap->getMapSize().height *Tmap->getTileSize().height)-position.y)/
            Tmap->getTileSize().height;
            cout<< x1 << " " << x2;
            return;
        //}
    }
    Player->setPosition(position);
}

Vec2 SingleGame::tileCoordFromPosition(Vec2 pos)
{
    int x = pos.x/Tmap->getTileSize().width;
    int y = ((Tmap->getMapSize().height *Tmap->getTileSize().height)-pos.y)/
    Tmap->getTileSize().height;
    return Vec2(x,y);
}

int flag = 0;
Vec2 SingleGame::weaponPosition(Vec2 position,float rx,float ry)
{
    float x = 32*rx/sqrt(rx*rx+ry*ry);
    float y = 32*ry/sqrt(rx*rx+ry*ry);
    Vec2 tileCoord; //= this->tileCoordFromPosition(position);
    int tileGid; //= collidable->getTileGIDAt(tileCoord);
    for(int i = 1; i < 6; i++){
        position.x += x;
        position.y += y;
        tileCoord = this->tileCoordFromPosition(position);
        tileGid = collidable->getTileGIDAt(tileCoord);
        if(tileGid>0){
            flag = i;
            cout << flag;
            position.x -= x;
            position.y -= y;
            return(position);
        }
        else continue;
    }
    flag = 5;
    cout << flag;
    position.x -= x;
    position.y -= y;
    return(position);
}

void SingleGame::myupdate(float dt)
{
    int weaponPosRand = rand()%(4);
    int weaponRand_1 = rand()%(6);
    int weaponRand_2 = rand()%(6);
    popWeapon(weaponPosRand,weaponRand_1,weaponRand_2);
    auto cutAction = CallFunc::create(CC_CALLBACK_0(SingleGame::fadeWeapon,this));
    FiniteTimeAction *action = Sequence::create(DelayTime::create(10),cutAction,NULL);
    Weapon_1->runAction(action);
    //Weapon_2->runAction(action);
    collectable[weaponPos[weaponPosRand]] = "false";
    collectable[weaponPos[weaponPosRand+4]] = "false";
}

void SingleGame::popWeapon(int weaponPosRand,int weaponRand_1,int weaponRand_2){
    //int weaponPosRand = rand()%(4);
    //int weaponRand_1 = rand()%(6);
    //int weaponRand_2 = rand()%(6);
    group_1 = Tmap->getObjectGroup("weapon");
    Weapon_1 = Sprite::create(weapon[weaponRand_1]);
    Weapon_2 = Sprite::create(weapon[weaponRand_2]);
    ValueMap spawnPoint_1 = group_1->getObject(weaponPos[weaponPosRand]);
    ValueMap spawnPoint_2 = group_1->getObject(weaponPos[weaponPosRand+4]);
    float x1 = spawnPoint_1["x"].asFloat() * scale;
    float y1 = spawnPoint_1["y"].asFloat() * scale;
    float x2 = spawnPoint_2["x"].asFloat() * scale;
    float y2 = spawnPoint_2["y"].asFloat() * scale;
    cout<<weaponPos[weaponPosRand]<<" "<<weaponPos[weaponPosRand+4]<<'\n';
    cout<<x1<<" "<<y1<<'\n';
    cout<<x2<<" "<<y2<<'\n';
    Weapon_1->setPosition(Vec2(x1,y1));
    addChild(Weapon_1);
    Weapon_2->setPosition(Vec2(x2,y2));
    addChild(Weapon_2);
    
    collectable[weaponPos[weaponPosRand]] = "true";
    collectable[weaponPos[weaponPosRand+4]] = "true";
}

void SingleGame::fadeWeapon(){
    Weapon_1->runAction(FadeOut::create(0.5));
    Weapon_2->runAction(FadeOut::create(0.5));
}


void SingleGame::pickupWeapon(){
    
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
            weapon->setPosition(Vec2(sprite->getPosition()));
            this->addChild(weapon,1 );
            
            float rx = e->getCursorX() - sprite->getPosition().x;
            float ry = e->getCursorY() - sprite->getPosition().y;
            weapon->setRotation(90 - atan2(ry, rx)*57.29578);
            sprite->setRotation(90 - atan2(ry, rx)*57.29578);
            Vec2 weaponRange = this->weaponPosition(Vec2(sprite->getPosition()),rx,ry);
            ac1= (FiniteTimeAction *) weapon->runAction(MoveBy::create(1,Vec2(24*flag*rx/sqrt(rx*rx+ry*ry),24*flag*ry/sqrt(rx*rx+ry*ry))));
            ac2 = (FiniteTimeAction *)weapon->runAction(FadeOut::create(4));
            weapon->runAction(Sequence::create(ac1, ac2, NULL));
        }
        else {
            log("attack false");
        }
    };
    
    listener2->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event*event) {
        auto sprite= this->getChildByTag(200);
        FiniteTimeAction *ac1, *ac2;
        Vec2 playerPos = Player->getPosition();
        if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
            
            playerPos.x += Tmap->getTileSize().width;
            //sprite->runAction(MoveBy::create(1, Vec2(40, 0)));
            sprite->runAction(RotateTo::create(0.1, 90));
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
            
            playerPos.x -= Tmap->getTileSize().width;
            //sprite->runAction(MoveBy::create(1, Vec2(-40, 0)));
            sprite->runAction(RotateTo::create(0.1, -90));
            
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
            
            playerPos.y += Tmap->getTileSize().height;
            //sprite->runAction(MoveBy::create(1, Vec2(0, 40)));
            sprite->runAction(RotateTo::create(0.1, 0));
            
        }
        else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
            
            playerPos.y -= Tmap->getTileSize().height;
            //sprite->runAction(MoveBy::create(1, Vec2(0, -40)));
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
        
        this->setPlayerPosition(playerPos);
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
    
    Vec2 playerPos = Player->getPosition();
    playerPos.y += Tmap->getTileSize().width;
    this->setPlayerPosition(playerPos);
    //sprite->runAction(MoveBy::create(1, Vec2(0, 40)));
    sprite->runAction(RotateTo::create(0.1, 0));
}
void SingleGame::menuItemDown(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    
    Vec2 playerPos = Player->getPosition();
    playerPos.y -= Tmap->getTileSize().width;
    this->setPlayerPosition(playerPos);
    //sprite->runAction(MoveBy::create(1, Vec2(0, -40)));
    sprite->runAction(RotateTo::create(0.1, 180));
}
void SingleGame::menuItemLeft(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    
    Vec2 playerPos = Player->getPosition();
    playerPos.x -= Tmap->getTileSize().height;
    this->setPlayerPosition(playerPos);
    //sprite->runAction(MoveBy::create(1, Vec2(-40, 0)));
    sprite->runAction(RotateTo::create(0.1, -90));
}
void SingleGame::menuItemRight(cocos2d::Ref*pSender) {
    auto sprite = this->getChildByTag(200);
    
    Vec2 playerPos = Player->getPosition();
    playerPos.x += Tmap->getTileSize().height;
    this->setPlayerPosition(playerPos);
    //sprite->runAction(MoveBy::create(1, Vec2(40, 0)));
    sprite->runAction(RotateTo::create(0.1, 90));
} 
