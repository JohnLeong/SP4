
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <iostream>
#include <string>

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;
using namespace std;

class CSoundManager
{

public:
	CSoundManager(void);
	//Doesn't play sound, only initialize filename
	CSoundManager(string soundfile); 
	~CSoundManager(void);

	//Plays entire sound file
	void playSound();
	//Plays for x number of milliseconds
	void playSound(int milliseconds);

	//Plays entire specified sound file
	void playSound(string soundFile);
	void playSound(string soundFile, int milliseconds);

	//plays the entire specified background file (soundengineBGM)
	void playBackgroundSound(string soundFile);

	//Starts playing sound but program continues
	void playSoundThreaded();

	//returns true if music is still playing
	bool isSoundPlaying();

	//Pause
	void pause();
	//Resume
	void resume();

	//Stop
	void Stop();

	//Set sound file to be played
	void SetFileName(string soundFile);
	//Get sound file to be played
	string getFileName(void);

	//Set the volume 
	void setVolume(int newVol);

	//Increase the volume
	void increaseVolume();
	void increaseVolume(int inc);

	//Decrease the volume
	void decreaseVolume();
	void decreaseVolume(int dec);

	//Get current volume
	int GetCurrentVolume();

protected:
	ISoundEngine* soundEngine;
	ISoundEngine* soundEngineBGM;
	ISound* currentSound;
	ISound* currentBGM;
	string filename;
	int volume;
	int position;

};

#endif

