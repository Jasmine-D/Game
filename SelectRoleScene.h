//
//  SelectRoleScene.hpp
//  helloworld
//
//  Created by apple on 2019/5/28.
//

#ifndef SelectRoleScene_hpp
#define SelectRoleScene_hpp
#include"cocos2d.h"

class SelectRole :public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuHomepageCallback(cocos2d::Ref*pSender);
    void menuItemEnterCallback1(cocos2d::Ref*pSender);
    CREATE_FUNC(SelectRole);
};

#endif /* SelectRoleScene_hpp */
