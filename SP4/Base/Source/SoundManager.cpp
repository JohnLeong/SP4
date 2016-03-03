
#include "SoundManager.h"

/********************************************************************************
Constructor
********************************************************************************/
CSoundManager::CSoundManager()
: filename("\0")
, volume(50)
, position(0)
{
	soundEngine = createIrrKlangDevice();
	soundEngineBGM = createIrrKlangDevice();
	currentSound = 0;
	currentBGM = 0;

	if (!soundEngine)
	{
		cout << "Error: Cout not create Sound engine" << endl;
		//exit(0);
	}

	soundEngine->setSoundVolume(1);
}

/********************************************************************************
Overloaded Constructor
********************************************************************************/
CSoundManager::CSoundManager(string soundFile)
: filename("\0")
, volume(50)
, position(0)
{
	soundEngine = createIrrKlangDevice();
	soundEngineBGM = createIrrKlangDevice();
	currentSound = NULL;
	currentBGM = NULL;

	if (!soundEngine)
	{
		cout << "Error: Cout not create Sound engine" << endl;
		//exit(0);
	}
	soundEngine->setSoundVolume(1);
}

/********************************************************************************
Destructor
********************************************************************************/
CSoundManager::~CSoundManager()
{
	if (currentSound)
		currentSound->drop();
	if (soundEngine)
		soundEngine->drop();
	if (soundEngineBGM)
		soundEngineBGM->drop();
}

/********************************************************************************
Play sound Function
********************************************************************************/
void CSoundManager::playSound()
{
	if (filename == "\0")
	{
		cout << "Error: no sound file selected" << endl;
		return;
	}
	currentSound = soundEngine->play2D(filename.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: could not play file" << endl;
		//exit(0);
	}

	position = currentSound->getPlayPosition();

}

/********************************************************************************
Overloaded play sound function with milliseond parameter
********************************************************************************/
void CSoundManager::playSound(int milliseconds)
{
	if (filename == "\0")
	{
		cout << "Error: no sound file selected" << endl;
		return;
	}

	currentSound = soundEngine->play2D(filename.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: could not play file" << endl;
		//exit(0);
	}

	_sleep(milliseconds);

	pause();

}

/********************************************************************************
Overloaded play sound function with file parameter
********************************************************************************/
void CSoundManager::playSound(string soundFile)
{
	SetFileName(soundFile);

	currentSound = soundEngine->play2D(filename.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: could not play file" << endl;
		//exit(0);
	}

	if (!soundEngine->isCurrentlyPlaying(filename.c_str()))
	{
		currentSound = soundEngine->play2D(filename.c_str(), false, false, true);
	}
}

/********************************************************************************
 play background sound function with file parameter
********************************************************************************/
void CSoundManager::playBackgroundSound(string soundFile)
{
	SetFileName(soundFile);

	if (!currentSound)
	{
		cout << "Error: could not play file" << endl;
		//exit(0);
	}

	if (!soundEngineBGM->isCurrentlyPlaying(filename.c_str()))
	{
		currentSound = soundEngineBGM->play2D(filename.c_str(), true, false, true);
	}

	position = currentSound->getPlayPosition();
}

/********************************************************************************
Overloaded play sound function with file and millisecond parameter
********************************************************************************/
void CSoundManager::playSound(string soundFile, int milliseconds)
{
	SetFileName(soundFile);

	currentSound = soundEngine->play2D(filename.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: could not play file" << endl;
		//exit(0);
	}

	_sleep(milliseconds);
	pause();
}

/********************************************************************************
play the sound thread 
********************************************************************************/
void CSoundManager::playSoundThreaded()
{
	currentSound = soundEngine->play2D(filename.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: could not play file" << endl;
		//exit(0);
	}
}

/********************************************************************************
check if there is sound currently playing
********************************************************************************/
bool CSoundManager::isSoundPlaying()
{
	return !currentSound->isFinished();
}

/********************************************************************************
Pause all currently playing sound
********************************************************************************/
void CSoundManager::pause()
{
	//position = currentSound->getPlayPosition();
	soundEngine->setAllSoundsPaused();
	soundEngineBGM->setAllSoundsPaused();
}

/********************************************************************************
Resume all currently playing sound
********************************************************************************/
void CSoundManager::resume()
{
	currentSound = soundEngine->play2D(filename.c_str(), false, false, true);
	currentBGM = soundEngineBGM->play2D(filename.c_str(), false, false, true);
}

/********************************************************************************
Stop all currently playing sound
********************************************************************************/
void CSoundManager::Stop()
{
	soundEngine->stopAllSounds();
	soundEngineBGM->stopAllSounds();
}

/********************************************************************************
Set filename
********************************************************************************/
void CSoundManager::SetFileName(string soundFile)
{
	if (soundFile != "")
		filename = soundFile;
}

/********************************************************************************
Get filename
********************************************************************************/
string CSoundManager::getFileName()
{
	return filename;
}

/********************************************************************************
Set the volume
********************************************************************************/
void CSoundManager::setVolume(int vol)
{
	if (vol < 0 || vol > 100)
		volume = 50;
	else
		volume = vol;

	currentSound->setVolume(volume / 100.0f);

}

/********************************************************************************
increase the volumwe
********************************************************************************/
void CSoundManager::increaseVolume()
{
	volume += 10;

	if (volume > 100)
		volume = 100;

	//currentSound->setVolume(volume / 100.0f);
	if (currentSound)
	{
		currentSound->setVolume(volume / 100.0f);
		return;
	}
	else if (currentBGM)
	{
		currentBGM->setVolume(volume / 100.0f);
		return;
	}
}

/********************************************************************************
overloaded increase the volume
********************************************************************************/
void CSoundManager::increaseVolume(int inc)
{
	volume += inc;

	if (volume > 100)
		volume = 100;

	if (currentSound)
	{
		currentSound->setVolume(volume / 100.0f);
		return;
	}
	else if (currentBGM)
	{
		currentBGM->setVolume(volume / 100.0f);
		return;
	}
	
}

/********************************************************************************
decrease the volume
********************************************************************************/
void CSoundManager::decreaseVolume()
{
	volume -= 10;

	if (volume < 0)
		volume = 0;

	if (currentSound)
	{
		currentSound->setVolume(volume / 100.0f);
		return;
	}
	else if (currentBGM)
	{
		currentBGM->setVolume(volume / 100.0f);
		return;
	}
}

/********************************************************************************
overloaded decrease the volume
********************************************************************************/
void CSoundManager::decreaseVolume(int dec)
{
	volume -= dec;

	if (volume < 0)
		volume = 0;

	currentSound->setVolume(volume / 100.0f);
}

/********************************************************************************
get the current volume
********************************************************************************/
int CSoundManager::GetCurrentVolume()
{
	return volume;
}