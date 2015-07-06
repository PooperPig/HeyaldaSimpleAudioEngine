/*
 Copyright (c) 2010 Steve Oldmeadow
 Portions Copyright (c) 2011-2015 Heyalda Corporation
 
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
 
 $Id$
 */

#import "HeyaldaSimpleAudioEngine_objc.h"

@implementation HeyaldaSimpleAudioEngine

static HeyaldaSimpleAudioEngine *sharedEngine = nil;
static CDHeyaldaSoundEngine* soundEngine = nil;
static CDHeyaldaAudioManager *am = nil;
static CDHeyaldaBufferManager *bufferManager = nil;

// Init
+ (HeyaldaSimpleAudioEngine *) sharedEngine
{
    @synchronized(self)     {
        if (!sharedEngine)
            sharedEngine = [[HeyaldaSimpleAudioEngine alloc] init];
    }
    return sharedEngine;
}

+ (id) alloc
{
    @synchronized(self)     {
        NSAssert(sharedEngine == nil, @"Attempted to allocate a second instance of a singleton.");
        return [super alloc];
    }
    return nil;
}

-(id) init
{
    if((self=[super init])) {
        am = [CDHeyaldaAudioManager sharedManager];
        soundEngine = am.soundEngine;
        bufferManager = [[CDHeyaldaBufferManager alloc] initWithEngine:soundEngine];
        mute_ = NO;
        enabled_ = YES;
    }
    return self;
}

// Memory
- (void) dealloc
{
    am = nil;
    soundEngine = nil;
    bufferManager = nil;
    [super dealloc];
}

+(void) end 
{
    am = nil;
    [CDHeyaldaAudioManager end];
    [bufferManager release];
    [sharedEngine release];
    sharedEngine = nil;
}    

#pragma mark HeyaldaSimpleAudioEngine - background music

-(void) preloadBackgroundMusic:(NSString*) filePath {
    [am preloadBackgroundMusic:filePath];
}

-(void) playBackgroundMusic:(NSString*) filePath
{
    [am playBackgroundMusic:filePath loop:TRUE];
}

-(void) playBackgroundMusic:(NSString*) filePath loop:(BOOL) loop
{
    [am playBackgroundMusic:filePath loop:loop];
}

-(void) stopBackgroundMusic
{
    [am stopBackgroundMusic];
}

-(void) pauseBackgroundMusic {
    [am pauseBackgroundMusic];
}    

-(void) resumeBackgroundMusic {
    [am resumeBackgroundMusic];
}    

-(void) rewindBackgroundMusic {
    [am rewindBackgroundMusic];
}

-(BOOL) isBackgroundMusicPlaying {
    return [am isBackgroundMusicPlaying];
}    

-(BOOL) willPlayBackgroundMusic {
    return [am willPlayBackgroundMusic];
}

#pragma mark HeyaldaSimpleAudioEngine - sound effects

-(ALuint) playEffect:(NSString*) filePath loop:(BOOL) loop
{
    return [self playEffect:filePath loop:loop pitch:1.0f pan:0.0f gain:1.0f];
}

-(ALuint) playEffect:(NSString*) filePath loop:(BOOL) loop pitch:(Float32) pitch pan:(Float32) pan gain:(Float32) gain
{
    int soundId = [bufferManager bufferForFile:filePath create:YES];
    if (soundId != kCDNoBuffer) {
        return [soundEngine playSound:soundId sourceGroupId:0 pitch:pitch pan:pan gain:gain loop:loop];
    } else {
        return CD_Heyalda_MUTE;
    }    
}

-(void) stopEffect:(ALuint) soundId {
    [soundEngine stopSound:soundId];
}    

-(void) pauseEffect:(ALuint) soundId {
  [soundEngine pauseSound: soundId];
}

-(void) pauseAllEffects {
  [soundEngine pauseAllSounds];
}

-(void) resumeEffect:(ALuint) soundId {
  [soundEngine resumeSound: soundId];
}

-(void) resumeAllEffects {
  [soundEngine resumeAllSounds];
}

-(void) stopAllEffects {
  [soundEngine stopAllSounds];
}

-(void) preloadEffect:(NSString*) filePath
{
    int soundId = [bufferManager bufferForFile:filePath create:YES];
    if (soundId == kCDNoBuffer) {
        CDLOG(@"HeyaldaAudioEngine::SimpleAudioEngine sound failed to preload %@",filePath);
    }
}

-(void) unloadEffect:(NSString*) filePath
{
    CDLOGINFO(@"HeyaldaAudioEngine::SimpleAudioEngine unloadedEffect %@",filePath);
    [bufferManager releaseBufferForFile:filePath];
}

#pragma mark Audio Interrupt Protocol
-(BOOL) mute
{
    return mute_;
}

-(void) setMute:(BOOL) muteValue
{
    if (mute_ != muteValue) {
        mute_ = muteValue;
        am.mute = mute_;
    }    
}

-(BOOL) enabled
{
    return enabled_;
}

-(void) setEnabled:(BOOL) enabledValue
{
    if (enabled_ != enabledValue) {
        enabled_ = enabledValue;
        am.enabled = enabled_;
    }    
}


#pragma mark SimpleAudioEngine - BackgroundMusicVolume
-(float) backgroundMusicVolume
{
    return am.backgroundMusic.volume;
}    

-(void) setBackgroundMusicVolume:(float) volume
{
    am.backgroundMusic.volume = volume;
}    

#pragma mark SimpleAudioEngine - EffectsVolume
-(float) effectsVolume
{
    return am.soundEngine.masterGain;
}    

-(void) setEffectsVolume:(float) volume
{
    am.soundEngine.masterGain = volume;
}    

-(CDHeyaldaSoundSource *) soundSourceForFile:(NSString*) filePath {
    int soundId = [bufferManager bufferForFile:filePath create:YES];
    if (soundId != kCDNoBuffer) {
        CDHeyaldaSoundSource *result = [soundEngine soundSourceForSound:soundId sourceGroupId:0];
        CDLOGINFO(@"HeyaldaAudioEngine::SimpleAudioEngine sound source created for %@",filePath);
        return result;
    } else {
        return nil;
    }    
}    

@end 
