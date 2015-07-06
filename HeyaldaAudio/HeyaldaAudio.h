#ifndef __Heyalda_HeyaldaAudio__
#define __Heyalda_HeyaldaAudio__
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
#include <string>
#include "HeyaldaAudioSupport.h"

class HeyaldaAudio {
public:
    static HeyaldaAudio * getInstance();
    static void end();
	static bool getShouldStartMusicWhenPauseEnds();
	static void setShouldStartMusicWhenPauseEnds( bool  shouldStartMusicWhenPauseEnds );
    static int  playEffect(const std::string & fileName, bool loop, float pitch, float pan, float gain);
    static int  playEffect(const std::string & fileName, float pitch, float pan, float gain);
    static void stopEffect(unsigned int soundId);
    static void setEffectPriority(unsigned int soundId, int priority);
    static bool isBackgroundMusicEnabled();
	static void stopMusic();
	static void enableBackgroundMusic();
	static void disableBackgroundMusic();
	static void setAudioForPauseMenuState(bool isGamePaused);
	static void pauseMusic();
	static void resumeMusic();
	static void setMusicVolume(float level);
    static void setEffectsVolume(float volumeLevel);
    static void setEffectVolume(unsigned int soundID, float volume);
    static void setEffectPitch(unsigned int soundID, float pitch);
    
private:
    HeyaldaAudio();
    ~HeyaldaAudio();

    static std::string getMusicLoopNameForLoopNumber(int loopNumber);
    
};
#endif // #define __Heyalda_HeyaldaAudio__

