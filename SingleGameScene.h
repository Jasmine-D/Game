#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"
struct Select{
	std::string fru;
	std::string weapon;
	bool used;
	short index;
};

class SingleGame :public cocos2d::Scene {
private:
	//cocos2d::TMXTiledMap *map;
	cocos2d::Sprite*Player;
	cocos2d::Sprite*Opponent1;
	cocos2d::Sprite*Opponent2;
	cocos2d::Sprite*Opponent3;
	cocos2d::Sprite*PlayerShow;
	cocos2d::Sprite*OppShow1;
	cocos2d::Sprite*OppShow2;
	cocos2d::Sprite*OppShow3;
	cocos2d::ProgressTimer*PlayerProgress;
	cocos2d::ProgressTimer*OppProgress1;
	cocos2d::ProgressTimer*OppProgress2;
	cocos2d::ProgressTimer*OppProgress3;
	cocos2d::TMXTiledMap*tileMap;
	cocos2d::TMXLayer*collision;
	Select Fruits[5] = {
		{"character/orange.png","weapon/orangearrow.png",false,-1},
	    {"character/litchi.png","weapon/litchiarrow.png",false,-1},
	    {"character/avocado.png","weapon/avocadoarrow.png",false,-1},
	    {"character/pineapple.png","weapon/pineapplearrow.png",false,-1},
	    {"character/mulberry.png","weapon/mulberryarrow.png",false,-1}
	};
	
	float scale;
	float T;
	bool attack;
	std::string direction;
	bool opponent_ismoving[4] = { false };
	//bool opp_attack[4] = { false };
	unsigned int count[4] = { 0 };
	unsigned int OppShootNumber = 0;
	unsigned int ShootNumber = 0;
	//std::vector<Weapon>Opp_weapon;
	cocos2d::Vector<cocos2d::Sprite*>Opp_weapon;
	cocos2d::Vector<cocos2d::Sprite*>Weapon;
	//bool testScope();
	//bool attackfinished;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float dt);
	void myupdate(float dt);
	void attackUpdate(float dt);
	void OppAttackValidityUpdate(float dt);
	void AttackValidityUpdate(float dt);
	//void delay(DWORD delayTime);
	//void waiting();
	//void distanceTest();
	void setPlayerPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 tileCoordFromPosition(cocos2d::Vec2 position);
	cocos2d::Vec2 RandomMovePosition(cocos2d::Sprite*opponent);
	cocos2d::Vec2 weaponPosition(cocos2d::Vec2 position, float rx, float ry);
	void opponentRepeatedlyMove(float dt);
	void menuItemUp(cocos2d::Ref*pSender);
	void menuItemDown(cocos2d::Ref*pSender);
	void menuItemLeft(cocos2d::Ref*pSender);
	void menuItemRight(cocos2d::Ref*pSender);
	
	//void stop(cocos2d::Ref*pSender);
	/*virtual bool touchBegan(cocos2d::Touch*touch, cocos2d::Event*event);
	void touchMoved(cocos2d::Touch*touch, cocos2d::Event*event);
	void touchEnded(cocos2d::Touch*touch, cocos2d::Event*event);
	void MouseMove(Event*event);
	void MouseDown(Event*event);*/
	
	void menuItemExitCallback(cocos2d::Ref*pSender);
	CREATE_FUNC(SingleGame);
};
#endif
