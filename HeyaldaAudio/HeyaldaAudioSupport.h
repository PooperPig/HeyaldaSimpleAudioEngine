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

#ifndef __HeyaldaAudioSupport__
#define __HeyaldaAudioSupport__

#include <string>

class HeyaldaAudioSupport {
public:
    
    HeyaldaAudioSupport();
    virtual ~HeyaldaAudioSupport();

    void end();

    int playEffect(const std::string & fileName, bool loop, float pitch, float pan, float gain);
    void stopEffect(unsigned int soundID);

    void playMusic(const std::string & fileName, bool loop);
    
    void pauseMusic();
    void resumeMusic();
    void stopMusic();
    
    void enableBackgroundMusic();
    void disableBackgroundMusic();
    
    float getEffectsVolume();
    void  setEffectsVolume(float volume);
    void  setMusicVolume(float volume);

    void setEffectVolume(unsigned int soundID, float volume);
    void setEffectPitch(unsigned int soundID, float pitch);
    void setEffectPriority(unsigned int soundId, int priority);

};

#endif /* defined(__HeyaldaAudioSupport__) */
