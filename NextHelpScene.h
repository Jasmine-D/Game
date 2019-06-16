//
//  NextHelpScene.hpp
//  helloworld
//
//  Created by apple on 2019/6/16.
//

#ifndef NextHelpScene_hpp
#define NextHelpScene_hpp
#include"cocos2d.h"
#include <stdio.h>

class NextHelpScene :public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuHomepageCallback(cocos2d::Ref*pSender);  //返回主页按钮
    void menuItemPreviousHelpCallback(cocos2d::Ref*pSender);//上一页
    CREATE_FUNC(NextHelpScene);
};

#endif /* NextHelpScene_hpp */
