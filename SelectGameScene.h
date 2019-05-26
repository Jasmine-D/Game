#ifndef _SELECTGAME_SCENE_H_
#define _SELECTGAME_SCENE_H_
#include"cocos2d.h"
class SelectGame :public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuHomepageCallback(cocos2d::Ref*pSender);
	void menuItemEnterCallback1(cocos2d::Ref*pSender);
	void menuItemEnterCallback2(cocos2d::Ref*pSender);
	CREATE_FUNC(SelectGame);
};
#endif
