//// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
//// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//// PARTICULAR PURPOSE.
////
//// Copyright (c) Microsoft Corporation. All rights reserved
//   Portions Copyright (c) 2011-2015 Heyalda Corporation

// For licensing information relating to this distribution please see Third Party Notices file.

#pragma once

#include <wrl.h>
#include <d3d11_1.h>
#include <agile.h>
#include <DirectXMath.h>
#include <memory>

#define XAUDIO2_HEYALDA_HELPER_FUNCTIONS 1
#include <xaudio2.h>
#include <map>

static const int HEYALDA_STREAMING_BUFFER_SIZE = 65536;
static const int HEYALDA_MAX_BUFFER_COUNT = 3;

#define UNUSED_PARAM(unusedparam) (void)unusedparam

struct HeyaldaSoundEffectData
{
	unsigned int				m_soundID;
	IXAudio2SourceVoice*		m_soundEffectSourceVoice;
	XAUDIO2_BUFFER				m_audioBuffer;
	byte*						m_soundEffectBufferData;
	uint32						m_soundEffectBufferLength;
	uint32						m_soundEffectSampleRate;
	float                       m_soundEffectVolume;
	bool						m_soundEffectStarted;
};

class  HeyaldaWP8Audio;
class HeyaldaAudioEngineCallbacks: public IXAudio2EngineCallback
{
private: 
     HeyaldaWP8Audio *m_audio;

public :
    HeyaldaAudioEngineCallbacks(){};
	void Initialize(HeyaldaWP8Audio* audio);

    // Called by XAudio2 just before an audio processing pass begins.
    void _stdcall OnProcessingPassStart(){};

    // Called just after an audio processing pass ends.
    void  _stdcall OnProcessingPassEnd(){};

    // Called in the event of a critical system error which requires XAudio2
    // to be closed down and restarted.  The error code is given in Error.
    void  _stdcall OnCriticalError(HRESULT Error);
};

struct  HeyaldaStreamingVoiceContext : public IXAudio2VoiceCallback
{
    STDMETHOD_(void, OnVoiceProcessingPassStart)(UINT32){}
    STDMETHOD_(void, OnVoiceProcessingPassEnd)(){}
    STDMETHOD_(void, OnStreamEnd)(){}
    STDMETHOD_(void, OnBufferStart)(void*)
    {
        ResetEvent(hBufferEndEvent);
    }
    STDMETHOD_(void, OnBufferEnd)(void* pContext)
    {
		//Trigger the event for the music stream.
		if (pContext == 0) {
            SetEvent(hBufferEndEvent);
        }
    }
    STDMETHOD_(void, OnLoopEnd)(void*){}
    STDMETHOD_(void, OnVoiceError)(void*, HRESULT){}

    HANDLE hBufferEndEvent;
     HeyaldaStreamingVoiceContext() : hBufferEndEvent(CreateEventEx(NULL, FALSE, FALSE, NULL))
    {
    }
    virtual ~ HeyaldaStreamingVoiceContext()
    {
        CloseHandle(hBufferEndEvent);
    }
};

class  HeyaldaWP8Audio 
{
private:
    void PlaySoundEffect(const char* pszFilePath, bool bLoop, unsigned int& sound, bool isMusic = false);
    
	IXAudio2*					m_musicEngine;
	IXAudio2*					m_soundEffectEngine;
	IXAudio2MasteringVoice*		m_musicMasteringVoice;
	IXAudio2MasteringVoice*		m_soundEffectMasteringVoice;

     HeyaldaStreamingVoiceContext       m_voiceContext;

    typedef std::map<unsigned int, HeyaldaSoundEffectData> EffectList;
    typedef std::pair<unsigned int, HeyaldaSoundEffectData> Effect;
	EffectList				    m_soundEffects;         

    unsigned int                m_backgroundID;       
    std::string                 m_backgroundFile;       
    bool                        m_backgroundLoop;

    float                       m_soundEffctVolume;
    float                       m_backgroundMusicVolume;
    float                       m_maxFrequencyRatio;
    
    bool                        m_engineExperiencedCriticalError;
    HeyaldaAudioEngineCallbacks        m_musicEngineCallback;
    HeyaldaAudioEngineCallbacks        m_soundEffectEngineCallback;

    unsigned int Hash(const char* key);

    
public:
     HeyaldaWP8Audio();

    void Initialize();
    void CreateResources();
    void ReleaseResources();
    void Start();
    void Render();

    // This flag can be used to tell when the audio system is experiencing critial errors.
    // XAudio2 gives a critical error when the user unplugs their headphones, and a new
    // speaker configuration is generated.
    void SetEngineExperiencedCriticalError()
    {
        m_engineExperiencedCriticalError = true;
    }

    bool HasEngineExperiencedCriticalError()
    {
        return m_engineExperiencedCriticalError;
    }

    void PlayBackgroundMusic(const char* pszFilePath, bool bLoop);
    void StopBackgroundMusic(bool bReleaseData);
    void PauseBackgroundMusic();
    void ResumeBackgroundMusic();
    void RewindBackgroundMusic();
    bool IsBackgroundMusicPlaying();

    void SetBackgroundVolume(float volume);
    float GetBackgroundVolume();
    void SetSoundEffectVolume(float volume);
    float GetSoundEffectVolume();

    unsigned int  HeyaldaWP8Audio::playSoundEffect(const char* pszFilePath, bool bLoop, float pitch, float pan, float gain);
    void setEffectPitch(unsigned int sound, float pitch);
    void setEffectVolume(unsigned int sound, float volume);

    void PlaySoundEffect(unsigned int sound);
	bool IsSoundEffectStarted(unsigned int sound);
	void StopSoundEffect(unsigned int sound);
    void PauseSoundEffect(unsigned int sound);
    void ResumeSoundEffect(unsigned int sound);
    void RewindSoundEffect(unsigned int sound);

    void PauseAllSoundEffects();
    void ResumeAllSoundEffects();
    void StopAllSoundEffects(bool bReleaseData);

    void PreloadSoundEffect(const char* pszFilePath, bool isMusic = false);
    void UnloadSoundEffect(const char* pszFilePath);
    void UnloadSoundEffect(unsigned int sound);

private:
    void RemoveFromList(unsigned int sound);
};
