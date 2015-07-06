#include "HelloWorldScene.h"
#include "HeyaldaAudio.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    _pitch = 0.5;
    _gain = 1.0;
    _pitchDirection = 1.0;
    _gainDirection = -1.0;
    _pitchStep = 0.01;
    _gainStep = 0.1;
    _soundID = HeyaldaAudio::playEffect("buzz.wav", true, 0.5, 0.0, 1.0);
    HeyaldaAudio::setEffectPriority(_soundID, 1000);

    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}

void HelloWorld::update(float dt)
{
    if (_pitchDirection > 0)
    {
        _pitch += _pitchStep;
    }
    else if (_pitchDirection < 0)
    {
        _pitch -= _pitchStep;
    }

    if (_gainDirection > 0)
    {
        _gain += _gainStep;
    }
    else if (_gainDirection < 0)
    {
        _gain -= _gainStep;
    }

    if (_pitch >= 1.0)
    {
        _pitchDirection = -1.0;
    }
    else if (_pitch < 0.1)
    {
        _pitchDirection = 1.0;
    }
    
    if (_gain >= 1.0)
    {
        _gainDirection = -1.0;
    }
    else if (_gain < 0.1)
    {
        _gainDirection = 1.0;
    }

    HeyaldaAudio::setEffectPitch(_soundID, _pitch);
    HeyaldaAudio::setEffectVolume(_soundID, _gain);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
