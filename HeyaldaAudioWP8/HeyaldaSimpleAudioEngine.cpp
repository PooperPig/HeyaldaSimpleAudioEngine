/*
* cocos2d-x   http://www.cocos2d-x.org
*
* Copyright (c) 2010-2011 - cocos2d-x community
* 
* Portions Copyright (c) Microsoft Open Technologies, Inc.
* All Rights Reserved
* 
* Portions Copyright (c) 2011-2015 Heyalda Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. 
* You may obtain a copy of the License at 
* 
* http://www.apache.org/licenses/LICENSE-2.0 
* 
* Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an 
* "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
* See the License for the specific language governing permissions and limitations under the License.
*/

#include "HeyaldaSimpleAudioEngine.h"
#include "HeyaldaWP8Audio.h"

#include <map>
//#include "CCCommon.h"
using namespace std;

namespace HeyaldaAudioEngine {

HeyaldaWP8Audio* s_audioController = NULL;
bool s_initialized = false;

SimpleAudioEngine* SimpleAudioEngine::getInstance()
{
    static SimpleAudioEngine s_SharedEngine;
    return &s_SharedEngine;
}


static HeyaldaWP8Audio* sharedAudioController()
{
    if (! s_audioController || !s_initialized)
    {
        if(s_audioController == NULL)
        {
			s_audioController = new HeyaldaWP8Audio;
        }
        s_audioController->Initialize();
        s_audioController->CreateResources();
        s_initialized = true;
    }

    return s_audioController;
}

SimpleAudioEngine::SimpleAudioEngine()
{
}

SimpleAudioEngine::~SimpleAudioEngine()
{
}


void SimpleAudioEngine::end()
{
    sharedAudioController()->StopBackgroundMusic(true);
    sharedAudioController()->StopAllSoundEffects(true);
    sharedAudioController()->ReleaseResources();
    s_initialized = false;
}



//////////////////////////////////////////////////////////////////////////
// BackgroundMusic
//////////////////////////////////////////////////////////////////////////

void SimpleAudioEngine::playBackgroundMusic(const char* pszFilePath, bool bLoop)
{
    if (! pszFilePath)
    {
        return;
    }

    sharedAudioController()->PlayBackgroundMusic(pszFilePath, bLoop);
}

void SimpleAudioEngine::stopBackgroundMusic(bool bReleaseData)
{
    sharedAudioController()->StopBackgroundMusic(bReleaseData);
}

void SimpleAudioEngine::pauseBackgroundMusic()
{
    sharedAudioController()->PauseBackgroundMusic();
}

void SimpleAudioEngine::resumeBackgroundMusic()
{
    sharedAudioController()->ResumeBackgroundMusic();
}

void SimpleAudioEngine::rewindBackgroundMusic()
{
    sharedAudioController()->RewindBackgroundMusic();
}

bool SimpleAudioEngine::willPlayBackgroundMusic()
{
    return false;
}

bool SimpleAudioEngine::isBackgroundMusicPlaying()
{
    return sharedAudioController()->IsBackgroundMusicPlaying();
}

//////////////////////////////////////////////////////////////////////////
// effect function
//////////////////////////////////////////////////////////////////////////

unsigned int SimpleAudioEngine::playEffect(const char* pszFilePath, bool bLoop,float pitch, float pan, float gain)
{
    return sharedAudioController()->playSoundEffect(pszFilePath, bLoop, pitch, pan, gain);
}

void SimpleAudioEngine::setEffectPitch(unsigned int nSoundId, float pitch)
{
    sharedAudioController()->setEffectPitch(nSoundId, pitch);
}
    
void SimpleAudioEngine::setEffectVolume(unsigned int nSoundId, float volume)
{
    sharedAudioController()->setEffectVolume(nSoundId, volume);
}
    
void SimpleAudioEngine::setEffectPriority(unsigned int nSoundId, int priority)
{

}

    
void SimpleAudioEngine::stopEffect(unsigned int nSoundId)
{
    sharedAudioController()->StopSoundEffect(nSoundId);
}

void SimpleAudioEngine::preloadEffect(const char* pszFilePath)
{
    sharedAudioController()->PreloadSoundEffect(pszFilePath);
}

void SimpleAudioEngine::pauseEffect(unsigned int nSoundId)
{
    sharedAudioController()->PauseSoundEffect(nSoundId);
}

void SimpleAudioEngine::resumeEffect(unsigned int nSoundId)
{
    sharedAudioController()->ResumeSoundEffect(nSoundId);
}

void SimpleAudioEngine::pauseAllEffects()
{
    sharedAudioController()->PauseAllSoundEffects();
}

void SimpleAudioEngine::resumeAllEffects()
{
    sharedAudioController()->ResumeAllSoundEffects();
}

void SimpleAudioEngine::stopAllEffects()
{
    sharedAudioController()->StopAllSoundEffects(false);
}

void SimpleAudioEngine::preloadBackgroundMusic(const char* pszFilePath)
{
    UNUSED_PARAM(pszFilePath);
}

void SimpleAudioEngine::unloadEffect(const char* pszFilePath)
{
    sharedAudioController()->UnloadSoundEffect(pszFilePath);
}

//////////////////////////////////////////////////////////////////////////
// volume interface
//////////////////////////////////////////////////////////////////////////

float SimpleAudioEngine::getBackgroundMusicVolume()
{
    return sharedAudioController()->GetBackgroundVolume();
}

void SimpleAudioEngine::setBackgroundMusicVolume(float volume)
{
	sharedAudioController()->SetBackgroundVolume((volume<=0.0f)? 0.0f : volume);
}

float SimpleAudioEngine::getEffectsVolume()
{
    return sharedAudioController()->GetSoundEffectVolume();
}

void SimpleAudioEngine::setEffectsVolume(float volume)
{
    sharedAudioController()->SetSoundEffectVolume((volume<=0.0f)? 0.0f : volume);
}

    
    
    
} // end of namespace CocosDenshion
