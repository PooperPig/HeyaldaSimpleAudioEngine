#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float dt);
    CREATE_FUNC(HelloWorld);
    
private:
    int _soundID;
    float _pitch;
    float _gain;
    float _pitchDirection;
    float _gainDirection;
    float _pitchStep;
    float _gainStep;
};

#endif // __HELLOWORLD_SCENE_H__
