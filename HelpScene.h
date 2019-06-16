//
//  HelpScene.hpp
//  helloworld
//
//  Created by apple on 2019/6/2.
//

#ifndef HelpScene_hpp
#define HelpScene_hpp
#include <stdio.h>
#include"cocos2d.h"


class HelpScene :public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuHomepageCallback(cocos2d::Ref*pSender);  //返回主页按钮
    void menuItemNextHelpCallback(Ref*pSender);//下一页
    CREATE_FUNC(HelpScene);
};

#endif /* HelpScene_hpp */
