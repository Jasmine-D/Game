#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"

class SingleGame :public cocos2d::Scene {
private:
    cocos2d::Sprite *Player;
    cocos2d::Sprite *Weapon_1;
    cocos2d::Sprite *Weapon_2;
    cocos2d::TMXTiledMap *Tmap;
    cocos2d::TMXLayer *collidable;
    bool attack;
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void menuItemUp(cocos2d::Ref*pSender);
    void menuItemDown(cocos2d::Ref*pSender);
    void menuItemLeft(cocos2d::Ref*pSender);
    void menuItemRight(cocos2d::Ref*pSender);
    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 weaponPosition(cocos2d::Vec2 position,float rx,float ry);
    void myupdate(float dt);
    void popWeapon(int weaponPosRand,int weaponRand_1,int weaponRand_2);
    void fadeWeapon();
    void pickupWeapon();
    void menuItemExitCallback(cocos2d::Ref*pSender);
    CREATE_FUNC(SingleGame);
};
#endif
