#include "stdafx.h"
#include "AudioManager.h"

AudioManager::AudioManager()
{
}

bool AudioManager::LoadSound(std::string _fileName)
{
	sf::SoundBuffer	buffer;
	std::string		message;
	std::string		fileLoc;

	//Check if sound file is already loaded before trying to load
	if (soundsMap.find(_fileName) == soundsMap.end())
	{
		fileLoc = "Resources/Sounds/";
		fileLoc += _fileName;

		if (!buffer.loadFromFile(fileLoc))
		{
			message = "Couldn't load SOUND file '";
			message += _fileName;
			message += "'!";
			debug.Log(3, message);
			return false;
		}
		else
		{
			message = "Successfully loaded SOUND file '";
			message += _fileName;
			message += "'!";
			debug.Log(1, message);
		}

		soundsMap.insert(std::pair<std::string, sf::SoundBuffer>(_fileName, buffer));
	}
	else
	{
		message = "Attempted to reload SOUND file '";
		message += _fileName;
		message += "'!";
		debug.Log(0, message);
	}

	return true;
}
/*
bool AudioManager::LoadMusic(std::string _fileName)
{
	sf::Music		music;
	std::string		message;
	std::string		fileLoc;

	//Check if music file is already loaded before trying to load
	if (musicsMap.find(_fileName) == musicsMap.end())
	{
		fileLoc = "Resources/Music/";
		fileLoc += _fileName;

		if (!music.openFromFile(fileLoc))
		{
			message = "Couldn't load MUSIC file '";
			message += _fileName;
			message += "'!";
			debug.Log(3, message);
			return false;
		}
		else
		{
			message = "Successfully loaded MUSIC file '";
			message += _fileName;
			message += "'!";
			debug.Log(1, message);
		}

		musicsMap.insert(std::pair<std::string, sf::Music>(_fileName, music));
	}
	else
	{
		message = "Attempted to reload MUSIC file '";
		message += _fileName;
		message += "'!";
		debug.Log(1, message);
	}

	return true;
}
*/
std::map<std::string, sf::SoundBuffer>& AudioManager::GetSoundsList()
{
	return soundsMap;
}

std::map<std::string, sf::Music>& AudioManager::GetMusicsList()
{
	return musicsMap;
}
