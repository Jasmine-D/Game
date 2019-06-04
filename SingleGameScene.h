#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"

class SingleGame :public cocos2d::Scene {
private:
    cocos2d::Sprite *Player;
    cocos2d::TMXTiledMap *map;
    cocos2d::TMXLayer *collidable;
    bool attack;
    
    //bool testScope();
    //bool attackfinished;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void menuItemUp(cocos2d::Ref*pSender);
    void menuItemDown(cocos2d::Ref*pSender);
    void menuItemLeft(cocos2d::Ref*pSender);
    void menuItemRight(cocos2d::Ref*pSender);
    /*virtual bool touchBegan(cocos2d::Touch*touch, cocos2d::Event*event);
     void touchMoved(cocos2d::Touch*touch, cocos2d::Event*event);
     void touchEnded(cocos2d::Touch*touch, cocos2d::Event*event);
     void MouseMove(Event*event);
     void MouseDown(Event*event);*/
    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 weaponPosition(cocos2d::Vec2 position,float rx,float ry);
    void menuItemExitCallback(cocos2d::Ref*pSender);
    CREATE_FUNC(SingleGame);
};
#endif
