/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2013-2014 Chukong Technologies Inc.
Portions Copyright (c) 2011-2015 Heyalda Corporation

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

package com.heyalda.tools.audio;

import java.io.FileInputStream;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.media.MediaPlayer;
import android.util.Log;

public class HeyaldaMusic {
	// ===========================================================
	// Constants
	// ===========================================================

	private static final String TAG = HeyaldaMusic.class.getSimpleName();

	// ===========================================================
	// Fields
	// ===========================================================

	private final Context mContext;
	private MediaPlayer mBackgroundMediaPlayer;
	private float mLeftVolume;
	private float mRightVolume;
	private boolean mPaused;// whether music is paused state.
	private boolean mManualPaused = false;// whether music is paused manually before the program is switched to the background.
	private String mCurrentPath;
	static public HeyaldaMusic me = null;
	// ===========================================================
	// Constructors
	// ===========================================================

	public HeyaldaMusic(final Context pContext) {
		this.mContext = pContext;
		me = this;
		this.initData();
	}

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	static public void preloadBackgroundMusic(final String pPath) {
		me.preloadBackgroundMusicMethod(pPath);
	}
	
	public void preloadBackgroundMusicMethod(final String pPath) {
		if ((this.mCurrentPath == null) || (!this.mCurrentPath.equals(pPath))) {
			// preload new background music

			// release old resource and create a new one
			if (this.mBackgroundMediaPlayer != null) {
				this.mBackgroundMediaPlayer.release();
			}

			this.mBackgroundMediaPlayer = this.createMediaplayer(pPath);

			// record the path
			this.mCurrentPath = pPath;
		}
	}

	static 	public void playBackgroundMusic(final String pPath, final boolean isLoop) {
		me.playBackgroundMusicMethod(pPath, isLoop);
	}
	
	public void playBackgroundMusicMethod(final String pPath, final boolean isLoop) {
		if (this.mCurrentPath == null) {
			// it is the first time to play background music or end() was called
			this.mBackgroundMediaPlayer = this.createMediaplayer(pPath);
			this.mCurrentPath = pPath;
		} else {
			if (!this.mCurrentPath.equals(pPath)) {
				// play new background music

				// release old resource and create a new one
				if (this.mBackgroundMediaPlayer != null) {
					this.mBackgroundMediaPlayer.release();
				}
				this.mBackgroundMediaPlayer = this.createMediaplayer(pPath);

				// record the path
				this.mCurrentPath = pPath;
			}
		}

		if (this.mBackgroundMediaPlayer == null) {
			Log.e(HeyaldaMusic.TAG, "playBackgroundMusic: background media player is null");
		} else {
			// if the music is playing or paused, stop it
			this.mBackgroundMediaPlayer.stop();

			this.mBackgroundMediaPlayer.setLooping(isLoop);

			try {
				this.mBackgroundMediaPlayer.prepare();
				this.mBackgroundMediaPlayer.seekTo(0);
				this.mBackgroundMediaPlayer.start();

				this.mPaused = false;
			} catch (final Exception e) {
				Log.e(HeyaldaMusic.TAG, "playBackgroundMusic: error state");
			}
		}
	}

	static 	public void stopBackgroundMusic() {
		me.stopBackgroundMusicMethod();
	}
	
	public void stopBackgroundMusicMethod() {
		if (this.mBackgroundMediaPlayer != null) {
			this.mBackgroundMediaPlayer.stop();

			// should set the state, if not, the following sequence will be error
			// play -> pause -> stop -> resume
			this.mPaused = false;
		}
	}

	static public void pauseBackgroundMusic() {
		me.pauseBackgroundMusicMethod();
	}
	
	public void pauseBackgroundMusicMethod() {
		if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.isPlaying()) {
			this.mBackgroundMediaPlayer.pause();
			this.mPaused = true;
			this.mManualPaused = true;
		}
	}

	static 	public void resumeBackgroundMusic() {
		me.resumeBackgroundMusicMethod();
	}
	
	public void resumeBackgroundMusicMethod() {
		if (this.mBackgroundMediaPlayer != null && this.mPaused) {
			this.mBackgroundMediaPlayer.start();
			this.mPaused = false;
			this.mManualPaused = false;
		}
	}

	static public void rewindBackgroundMusic() {
		me.rewindBackgroundMusicMethod();
	}

	public void rewindBackgroundMusicMethod() {
		if (this.mBackgroundMediaPlayer != null) {
			this.mBackgroundMediaPlayer.stop();

			try {
				this.mBackgroundMediaPlayer.prepare();
				this.mBackgroundMediaPlayer.seekTo(0);
				this.mBackgroundMediaPlayer.start();

				this.mPaused = false;
			} catch (final Exception e) {
				Log.e(HeyaldaMusic.TAG, "rewindBackgroundMusic: error state");
			}
		}
	}

	static public boolean isBackgroundMusicPlaying() {
		return me.isBackgroundMusicPlayingMethod();
	}

	public boolean isBackgroundMusicPlayingMethod() {
		boolean ret = false;

		if (this.mBackgroundMediaPlayer == null) {
			ret = false;
		} else {
			ret = this.mBackgroundMediaPlayer.isPlaying();
		}

		return ret;
	}


	static public void end() {
		me.endMethod();
	}

	public void endMethod() {
		if (this.mBackgroundMediaPlayer != null) {
			this.mBackgroundMediaPlayer.release();
		}

		this.initData();
	}

	static public float getBackgroundMusicVolume() {
		return me.getBackgroundMusicVolumeMethod();
	}

	public float getBackgroundMusicVolumeMethod() {
		if (this.mBackgroundMediaPlayer != null) {
			return (this.mLeftVolume + this.mRightVolume) / 2;
		} else {
			return 0.0f;
		}
	}

	static public void setBackgroundMusicVolume(float pVolume) {
		me.setBackgroundMusicVolumeMethod(pVolume);
	}

	public void setBackgroundMusicVolumeMethod(float pVolume) {
		if (pVolume < 0.0f) {
			pVolume = 0.0f;
		}

		if (pVolume > 1.0f) {
			pVolume = 1.0f;
		}

		this.mLeftVolume = this.mRightVolume = pVolume;
		if (this.mBackgroundMediaPlayer != null) {
			this.mBackgroundMediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
		}
	}

	public void onEnterBackground(){
		if (this.mBackgroundMediaPlayer != null && this.mBackgroundMediaPlayer.isPlaying()) {
			this.mBackgroundMediaPlayer.pause();
			this.mPaused = true;
		}
	}
	
	public void onEnterForeground(){
		if(!this.mManualPaused){
			if (this.mBackgroundMediaPlayer != null && this.mPaused) {
				this.mBackgroundMediaPlayer.start();
				this.mPaused = false;
			}
		}
	}
	
	private void initData() {
		this.mLeftVolume = 0.5f;
		this.mRightVolume = 0.5f;
		this.mBackgroundMediaPlayer = null;
		this.mPaused = false;
		this.mCurrentPath = null;
	}

	/**
	 * create mediaplayer for music
	 * 
	 * @param pPath
	 *            the pPath relative to assets
	 * @return
	 */
	private MediaPlayer createMediaplayer(final String pPath) {
		MediaPlayer mediaPlayer = new MediaPlayer();

		try {
			if (pPath.startsWith("/")) {
				final FileInputStream fis = new FileInputStream(pPath);
				mediaPlayer.setDataSource(fis.getFD());
				fis.close();
			} else {
				final AssetFileDescriptor assetFileDescritor = this.mContext.getAssets().openFd(pPath);
				mediaPlayer.setDataSource(assetFileDescritor.getFileDescriptor(), assetFileDescritor.getStartOffset(), assetFileDescritor.getLength());
			}

			mediaPlayer.prepare();

			mediaPlayer.setVolume(this.mLeftVolume, this.mRightVolume);
		} catch (final Exception e) {
			mediaPlayer = null;
			Log.e(HeyaldaMusic.TAG, "error: " + e.getMessage(), e);
		}

		return mediaPlayer;
	}

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
}
