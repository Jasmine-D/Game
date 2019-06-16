#ifndef SelectRoleScene_hpp
#define SelectRoleScene_hpp
#include"cocos2d.h"
using std::string;
extern string name;

class SelectRole :public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuHomepageCallback(cocos2d::Ref*pSender);  //返回主页按钮
    void menuItemselectorangerole(cocos2d::Ref*pSender); //进入下一界面按钮
    void menuItemselectlitchirole(cocos2d::Ref*pSender);
    void menuItemselectavocadorole(cocos2d::Ref*pSender);
    void menuItemselectpineapplerole(cocos2d::Ref*pSender);
    void menuItemselectmulberryrole(cocos2d::Ref*pSender);
    
    CREATE_FUNC(SelectRole);
    
};

#endif /* SelectRoleScene_hpp */
