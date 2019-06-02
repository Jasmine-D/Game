#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"
class SingleGame :public cocos2d::Scene {
private:
    cocos2d::TMXTiledMap *map;
    cocos2d::Sprite *player;
    cocos2d::TMXLayer *collidable;
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    /*virtual bool touchBegan(cocos2d::Touch*touch, cocos2d::Event*event);
     void touchMoved(cocos2d::Touch*touch, cocos2d::Event*event);
     void touchEnded(cocos2d::Touch*touch, cocos2d::Event*event);
     void MouseMove(Event*event);
     void MouseDown(Event*event);*/
    void setPlayerPosition(cocos2d::Vec2 position);
    cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
    void menuItemExitCallback(cocos2d::Ref*pSender);
    CREATE_FUNC(SingleGame);
};
#endif
