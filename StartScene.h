//
//  StartScene.h
//  MyCppGame
//
//  Created by 丁逸敏 on 2019/6/16.
//

#ifndef StartScene_h
#define StartScene_h

#include "cocos2d.h"

using std::string;
class Start : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void update(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuItemSelectCallback(cocos2d::Ref*pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(Start);

};


#endif /* StartScene_h */
