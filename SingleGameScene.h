#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"
class SingleGame :public cocos2d::Scene {
private:
	cocos2d::Sprite*Player;
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
	void menuItemExitCallback(cocos2d::Ref*pSender);
	CREATE_FUNC(SingleGame);
};
#endif
