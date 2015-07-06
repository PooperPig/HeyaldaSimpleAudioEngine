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
#include "HeyaldaAudio.h"
#include "HeyaldaSimpleAudioEngine.h"

static HeyaldaAudio  * _instance = nullptr;

HeyaldaAudio * HeyaldaAudio::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new HeyaldaAudio();
    }
    return _instance;
}

static HeyaldaAudioSupport _audioSupport;
static float               _effectGainBeforePause = 1.0;
static bool                _isPlayerWantingMusicPlayed = false;
static bool                _shouldStartMusicWhenPauseEnds = false;
static float               _currentMusicTrackVolume = 0.3;

HeyaldaAudio::HeyaldaAudio(){}

HeyaldaAudio::~HeyaldaAudio(){}

void HeyaldaAudio::end()
{
    _audioSupport.end();
}

void HeyaldaAudio::stopMusic()
{
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void HeyaldaAudio::disableBackgroundMusic()
{
    HeyaldaAudioEngine::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    _isPlayerWantingMusicPlayed = false;
}

void HeyaldaAudio::enableBackgroundMusic()
{
    _isPlayerWantingMusicPlayed = true;
}

bool HeyaldaAudio::isBackgroundMusicEnabled()
{
    return _isPlayerWantingMusicPlayed;
}

int HeyaldaAudio::playEffect(const std::string & fileName, float pitch, float pan, float gain)
{
    return _audioSupport.playEffect(fileName, false, pitch, pan, gain);
}

int HeyaldaAudio::playEffect(const std::string & fileName, bool loop, float pitch, float pan, float gain)
{
    return _audioSupport.playEffect(fileName, loop, pitch, pan, gain);
}

void HeyaldaAudio::setMusicVolume(float level)
{
    float gain = level * _currentMusicTrackVolume;
    _audioSupport.setMusicVolume(gain);
}

void HeyaldaAudio::setEffectsVolume(float volumeLevel)
{
    _audioSupport.setEffectsVolume(volumeLevel);
    _effectGainBeforePause = volumeLevel;
}

void HeyaldaAudio::pauseMusic()
{
    _audioSupport.pauseMusic();
}

void HeyaldaAudio::resumeMusic()
{
        _audioSupport.resumeMusic();
}

void HeyaldaAudio::setAudioForPauseMenuState(bool isGamePaused)
{
    if (isGamePaused)
    {
        _effectGainBeforePause = _audioSupport.getEffectsVolume();
        _audioSupport.pauseMusic();
        _audioSupport.setEffectsVolume(0.0);
    }
    else {
        _audioSupport.resumeMusic();
        _audioSupport.setEffectsVolume(_effectGainBeforePause);
    }
}

bool  HeyaldaAudio::getShouldStartMusicWhenPauseEnds()
{
	return _shouldStartMusicWhenPauseEnds;
}

void HeyaldaAudio::setShouldStartMusicWhenPauseEnds( bool  shouldStartMusicWhenPauseEnds )
{
	_shouldStartMusicWhenPauseEnds = shouldStartMusicWhenPauseEnds;
}

void HeyaldaAudio::setEffectVolume(unsigned int soundID, float volume)
{
    _audioSupport.setEffectVolume(soundID, volume);
}

void HeyaldaAudio::setEffectPitch(unsigned int soundID, float pitch)
{
    _audioSupport.setEffectPitch(soundID, pitch);
}

void HeyaldaAudio::stopEffect(unsigned int soundID)
{
    _audioSupport.stopEffect(soundID);
}

void HeyaldaAudio::setEffectPriority(unsigned int soundId, int priority)
{
    _audioSupport.setEffectPriority(soundId, priority);
}


