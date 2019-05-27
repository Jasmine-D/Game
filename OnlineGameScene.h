#ifndef _ONLINEGAME_SCENE_
#define _ONLINEGAME_SCENE_
#include"cocos2d.h"
class OnlineGame :public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuItemExitCallback(cocos2d::Ref*pSender);
	CREATE_FUNC(OnlineGame);
};
#endif

