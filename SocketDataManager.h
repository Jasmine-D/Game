#ifndef SocketDataManager_H
#define SocketDataManager_H

#include "cocos2d.h"
USING_NS_CC;

class SocketDataManager : public Ref
{
public:
    SocketDataManager();
    ~SocketDataManager();
    static SocketDataManager* getInstance();
    CREATE_FUNC(SocketDataManager);
    virtual bool init();
    
    virtual void update(float dt);
    
    void pushMsg(const char* msg);  /* 添加一条数据到缓存中 */
private:
    static SocketDataManager* m_SocketDataManager;
    
    std::mutex m_mutex;; /* 线程锁 */
    ValueVector m_msgList; /* 存放所有接收到的数据 */
};

#endif
