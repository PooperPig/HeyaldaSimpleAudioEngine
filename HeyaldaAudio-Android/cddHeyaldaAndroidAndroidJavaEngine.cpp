/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

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
 ****************************************************************************/

#include "cddHeyaldaAndroidAndroidJavaEngine.h"
#include "platform/android/jni/JniHelper.h"
#include "ccdHeyaldaAndroidUtils.h"
#include <android/log.h>
#include <jni.h>

// logging
#define  LOG_TAG    "heyaldaAudioEngine::android::AndroidJavaEngine"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

// Java class
#define  EFFECTS_CLASS_NAME "com/heyalda/tools/audio/HeyaldaSound"
#define  MUSIC_CLASS_NAME "com/heyalda/tools/audio/HeyaldaMusic"

namespace HeyaldaAudioEngine {
namespace android {

bool AndroidJavaEngine::getSoundEffectJNIStaticMethodInfo(
		cocos2d::JniMethodInfo &methodinfo, const char *methodName,
		const char *paramCode) {
	return cocos2d::JniHelper::getStaticMethodInfo(methodinfo,
	EFFECTS_CLASS_NAME, methodName, paramCode);
}

bool AndroidJavaEngine::getMusicJNIStaticMethodInfo(
        cocos2d::JniMethodInfo &methodinfo, const char *methodName,
        const char *paramCode) {
    return cocos2d::JniHelper::getStaticMethodInfo(methodinfo,
    MUSIC_CLASS_NAME, methodName, paramCode);
}

AndroidJavaEngine::~AndroidJavaEngine() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "end", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::preloadBackgroundMusic(const char* pszFilePath) {
	std::string fullPath =
			HeyaldaAudioEngine::android::getFullPathWithoutAssetsPrefix(pszFilePath);

	// void playBackgroundMusic(String,boolean)
	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "preloadBackgroundMusic",
			"(Ljava/lang/String;)V")) {
		return;
	}

	jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, stringArg);
	methodInfo.env->DeleteLocalRef(stringArg);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::playBackgroundMusic(const char* pszFilePath,
		bool bLoop) {
	std::string fullPath =
			HeyaldaAudioEngine::android::getFullPathWithoutAssetsPrefix(pszFilePath);

	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "playBackgroundMusic",
			"(Ljava/lang/String;Z)V")) {
		return;
	}

	jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, stringArg, bLoop);
	methodInfo.env->DeleteLocalRef(stringArg);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::stopBackgroundMusic(bool bReleaseData) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "stopBackgroundMusic", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::pauseBackgroundMusic() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "pauseBackgroundMusic", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::resumeBackgroundMusic() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "resumeBackgroundMusic", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::rewindBackgroundMusic() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "rewindBackgroundMusic", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

bool AndroidJavaEngine::willPlayBackgroundMusic() {
	return true;
}

bool AndroidJavaEngine::isBackgroundMusicPlaying() {
	cocos2d::JniMethodInfo methodInfo;
	jboolean ret = false;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "isBackgroundMusicPlaying",
			"()Z")) {
		return ret;
	}

	ret = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	return ret;
}

float AndroidJavaEngine::getBackgroundMusicVolume() {
	cocos2d::JniMethodInfo methodInfo;
	jfloat ret = -1.0;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "getBackgroundMusicVolume",
			"()F")) {
		return ret;
	}

	ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	return ret;
}

void AndroidJavaEngine::setBackgroundMusicVolume(float volume) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getMusicJNIStaticMethodInfo(methodInfo, "setBackgroundMusicVolume",
			"(F)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, volume);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

float AndroidJavaEngine::getEffectsVolume() {
	cocos2d::JniMethodInfo methodInfo;
	jfloat ret = -1.0;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "getEffectsVolume", "()F")) {
		return ret;
	}

	ret = methodInfo.env->CallStaticFloatMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	return ret;
}

void AndroidJavaEngine::setEffectsVolume(float volume) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "setEffectsVolume", "(F)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, volume);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

unsigned int AndroidJavaEngine::playEffect(const char* pszFilePath, bool bLoop,
		float pitch, float pan, float gain) {
	cocos2d::JniMethodInfo methodInfo;
	int ret = 0;
	std::string fullPath =
			HeyaldaAudioEngine::android::getFullPathWithoutAssetsPrefix(pszFilePath);

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "playEffect",
			"(Ljava/lang/String;ZFFF)I")) {
		return ret;
	}

	jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
	ret = methodInfo.env->CallStaticIntMethod(methodInfo.classID,
			methodInfo.methodID, stringArg, bLoop, pitch, pan, gain);
	methodInfo.env->DeleteLocalRef(stringArg);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);

	return (unsigned int) ret;
}

void AndroidJavaEngine::setEffectVolume(unsigned int soundID, float volume) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "setEffectVolume", "(IF)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, (int) soundID, volume);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::setEffectPitch(unsigned int soundId, float pitch) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "setEffectPitch", "(IF)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, (int) soundId, pitch);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::setEffectPriority(unsigned int soundId, int priority) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "setEffectPriority", "(II)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, (int) soundId, priority);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::pauseEffect(unsigned int nSoundId) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "pauseEffect", "(I)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, (int) nSoundId);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::pauseAllEffects() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "pauseAllEffects", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::resumeEffect(unsigned int nSoundId) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "resumeEffect", "(I)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, (int) nSoundId);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::resumeAllEffects() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "resumeAllEffects", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::stopEffect(unsigned int nSoundId) {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "stopEffect", "(I)V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, (int) nSoundId);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::stopAllEffects() {
	cocos2d::JniMethodInfo methodInfo;

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "stopAllEffects", "()V")) {
		return;
	}

	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::preloadEffect(const char* pszFilePath) {
	cocos2d::JniMethodInfo methodInfo;
	std::string fullPath =
			HeyaldaAudioEngine::android::getFullPathWithoutAssetsPrefix(pszFilePath);

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "preloadEffect",
			"(Ljava/lang/String;)V")) {
		return;
	}

	jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, stringArg);
	methodInfo.env->DeleteLocalRef(stringArg);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

void AndroidJavaEngine::unloadEffect(const char* pszFilePath) {
	cocos2d::JniMethodInfo methodInfo;
	std::string fullPath =
			HeyaldaAudioEngine::android::getFullPathWithoutAssetsPrefix(pszFilePath);

	if (!getSoundEffectJNIStaticMethodInfo(methodInfo, "unloadEffect",
			"(Ljava/lang/String;)V")) {
		return;
	}

	jstring stringArg = methodInfo.env->NewStringUTF(fullPath.c_str());
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID,
			methodInfo.methodID, stringArg);
	methodInfo.env->DeleteLocalRef(stringArg);
	methodInfo.env->DeleteLocalRef(methodInfo.classID);
}
}
}
