//
//  HeyaldaAudioSupport.cpp
//  CSR2014-3.1rc0
//
//  Created by James Range on 5/23/14.
//
//

#include "HeyaldaAudioSupport.h"
#include "HeyaldaSimpleAudioEngine.h"
#include "cocos2d.h"

HeyaldaAudioSupport::HeyaldaAudioSupport() {
    
}

HeyaldaAudioSupport::~HeyaldaAudioSupport() {
    HeyaldaAudioEngine::SimpleAudioEngine::end(); // Frees all CocosDension Singleton and related auido stuff, including
}

void HeyaldaAudioSupport::end() {
    HeyaldaAudioEngine::SimpleAudioEngine::end();
}

int HeyaldaAudioSupport::playEffect(const std::string & fileName, bool loop, float pitch, float pan, float gain) {
    return HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->playEffect(fileName.c_str(), loop, pitch, pan, gain);
}

void HeyaldaAudioSupport::stopEffect(unsigned int soundID) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->stopEffect(soundID);
}

void HeyaldaAudioSupport::playMusic(const std::string & fileName, bool loop) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->playBackgroundMusic(fileName.c_str(), loop);
}

void HeyaldaAudioSupport::stopMusic() {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void HeyaldaAudioSupport::pauseMusic() {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void HeyaldaAudioSupport::resumeMusic() {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void HeyaldaAudioSupport::setMusicVolume(float volume) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}

float HeyaldaAudioSupport::getEffectsVolume() {
    return HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void HeyaldaAudioSupport::setEffectsVolume(float volumeLevel) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectsVolume(volumeLevel);
}

void HeyaldaAudioSupport::setEffectVolume(unsigned int soundId, float volume) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectVolume(soundId, volume);
}

void HeyaldaAudioSupport::setEffectPitch(unsigned int soundId, float pitch) {
    //cocos2d::log("HeyaldaAudioSupport::setEffectPitch %d %.2f", soundId, pitch);
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectPitch(soundId, pitch);
}

void HeyaldaAudioSupport::setEffectPriority(unsigned int soundId, int priority) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectPriority(soundId, priority);
}

