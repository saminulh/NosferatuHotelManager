#pragma once

//This singleton class will be responsible for the loading and unloading of all audio resources
class AudioManager
{
	//Sounds are light-weight and should suffer no lag - ex. gunshots, footsteps
	std::map<std::string, sf::SoundBuffer> soundsMap;

	//Music is streamed from file, should be larger files
	std::map<std::string, sf::Music> musicsMap;
public:
	AudioManager();

	bool LoadSound(std::string _fileName);
	//bool LoadMusic(std::string _fileName);

	std::map<std::string, sf::SoundBuffer>& GetSoundsList();
	std::map<std::string, sf::Music>& GetMusicsList();
};