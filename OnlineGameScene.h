#ifndef _ONLINEGAME_SCENE_
#define _ONLINEGAME_SCENE_
#include"cocos2d.h"

class OnlineGame :public cocos2d::Scene {
public:
    ~OnlineGame();
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    void menuItemExitCallback(cocos2d::Ref*pSender);
    void menuItemSelectCallback(cocos2d::Ref*pSender);
    
    int connectThreadStart();
    void connectServer();
    void receiveData();
    
    CREATE_FUNC(OnlineGame);
    
private:
    cocos2d::TMXTiledMap*tileMap;
    cocos2d::TMXLayer*collision;
    float scale;
};



#endif
