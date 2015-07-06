# HeyaldaSimpleAudioEngine
A wrapper around SimpleAudioEngine that adds modulating pitch and gain of looping sound effects.

The original SimpleAudioEngine was created by Steve Oldmeadow and the Cocos2d-x community.

The benefit of using this version is that you can modulate pitch and gain of a looping sound effect.
The negative aspect of this version is that it might have bugs that have been fixed in other versions of SimpleAudioEngine.

I have it on my TO-DO list to investigate what issues might exist with this version that have been fixed in other versions of SimpleAudioEngine and incorporate significant fixes into this version. Not sure when that will happen though.

This version has been tested on iOS 8, Android 4.4.3, Mac OSX Yosimite 10.10.3.

There is an issue with Windows Phone 8.1 Universal apps where I get a bunch of build errors relating to mmreg.h. Not sure, but I think this has something to do with DirectX or Xaudio. Will look into this more in the future.

To try out this version:

1) Clone this repo.

2) Run the sample program in Xcode for Max or iOS.

3) From within the HeyaldaSimpleAudioEngine folder, on a command prompt, run the sample program using cocos run -p android on an android device (assuming you already setup your Cocos2d-x Android enviornment).

4) Note that on Android, there are C++ files as well as Java src files.
