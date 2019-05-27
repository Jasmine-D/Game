#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"
class SingleGame :public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuItemExitCallback(cocos2d::Ref*pSender);
	CREATE_FUNC(SingleGame);
};
#endif
