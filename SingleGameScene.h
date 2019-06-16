#ifndef _SINGLEGAME_SCENE_
#define _SINGLEGAME_SCENE_
#include"cocos2d.h"
struct Select{
    std::string fru;
    std::string weapon;
    bool used;
    short index;
};
struct popWeapon {
    std::string weaponPickup;
    std::string newCharacter;
    std::string weaponShoot;
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
    cocos2d::LabelTTF*Timettf;
    cocos2d::ProgressTimer*PlayerProgress;
    cocos2d::ProgressTimer*OppProgress1;
    cocos2d::ProgressTimer*OppProgress2;
    cocos2d::ProgressTimer*OppProgress3;
    cocos2d::ProgressTimer*CountDownProgress;
    cocos2d::TMXTiledMap*tileMap;
    cocos2d::TMXLayer*collision;
    Select Fruits[5] = {
        {"character/orange.png","weapon/orangearrow.png",false,-1},
        {"character/litchi.png","weapon/litchiarrow.png",false,-1},
        {"character/avocado.png","weapon/avocadoarrow.png",false,-1},
        {"character/pineapple.png","weapon/pineapplearrow.png",false,-1},
        {"character/mulberry.png","weapon/mulberryarrow.png",false,-1}
    };
    popWeapon Pop[6] = {
        {"weapon/dart.png"," ","weapon/dart.png"},
        {"weapon/fire.png"," ","weapon/fire.png"},
        {"weapon/gun.png"," ","weapon/bullet.png"},
        {"weapon/laser_gun.png"," ","weapon/laser.png"},
        {"weapon/snowball.png"," ","weapon/snowball.png"},
        {" "," "," "}
    };
    std::string Orange[5] = {
        {"character/orange_dart.png"},
        {"character/orange_fire.png"},
        {"character/orange_gun.png"},
        {"character/orange_laser.png"},
        {"character/orange_snowball.png"}
    };
    std::string Litchi[5] = {
        {"character/litchi_dart.png"},
        {"character/litchi_fire.png"},
        {"character/litchi_gun.png"},
        {"character/litchi_laser.png"},
        {"character/litchi_snowball.png"}
    };
    std::string Avocado[5] = {
        {"character/avocado_dart.png"},
        {"character/avocado_fire.png"},
        {"character/avocado_gun.png"},
        {"character/avocado_laser.png"},
        {"character/avocado_snowball.png"}
    };
    std::string Pineapple[5] = {
        {"character/pineapple_dart.png"},
        {"character/pineapple_fire.png"},
        {"character/pineapple_gun.png"},
        {"character/pineapple_laser.png"},
        {"character/pineapple_snowball.png"}
    };
    std::string Mulberry[5] = {
        {"character/mulberry_dart.png"},
        {"character/mulberry_fire.png"},
        {"character/mulberry_gun.png"},
        {"character/mulberry_laser.png"},
        {"character/mulberry_snowball.png"}
    };
    std::string PopName[8] = {
        "weapon1","weapon2","weapon3","weapon4","weapon5","weapon6","weapon7","weapon8"
    };
    float scale;
    float T;
    bool attack;
    std::string direction;
    bool opponent_ismoving[4] = { false };
    bool oppDead[4] = { false };
    bool showWeapon[8] = { false };
    bool Over=false;
    
    //bool opp_attack[4] = { false };
    unsigned int count[4] = { 0 };
    unsigned int timeDelay = 0;
    short weaponIndex=5;
    float aggressivity[6] = {1.5f,2.0f,2.5f,3.0f,1.5f, 1.0f };
    cocos2d::Vector<cocos2d::Sprite*>Opp_weapon;
    cocos2d::Vector<cocos2d::Sprite*>Weapon;
    cocos2d::Vector<cocos2d::Sprite*>PopWeapon;
    std::vector<int>index1;
    std::vector<int>index2;
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
    void TestResultUpdate(float dt);
    void PopWeaponUpdate(float dt);
    void TestPickWeaponUpdate(float dt);
    void CountDownUpdate(float dt);
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
