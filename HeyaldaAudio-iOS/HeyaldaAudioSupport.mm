/*
 Copyright (c) 2011-2015 Heyalda Corporation
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "HeyaldaAudioSupport.h"
#include "HeyaldaSimpleAudioEngine.h"

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

void HeyaldaAudioSupport::setEffectVolume(unsigned int soundID, float volume) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectVolume(soundID, volume);
}

void HeyaldaAudioSupport::setEffectPitch(unsigned int soundId, float pitch) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectPitch(soundId, pitch);
}

void HeyaldaAudioSupport::setEffectPriority(unsigned int soundId, int priority) {
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->setEffectPriority(soundId, priority);
}


