#pragma once

//Forward declarations
struct SoundHolder;
class Animation;

//This singleton class will be responsible for the loading and unloading of all audio resources
class AudioManager
{
	//Sounds are light-weight and should suffer no lag - ex. gunshots, footsteps
	std::map<std::string, sf::SoundBuffer>		soundsMap;

	//Not to be confused with the map
	std::vector<SoundHolder>					soundInstancesList;

	//Music is streamed from file, should be larger files
	std::map<std::string, sf::Music>			musicsMap;
public:
	AudioManager();

	bool										LoadSound(std::string _fileName);
	//bool										LoadMusic(std::string _fileName);

	unsigned int								EnqueueSound(int _priority, sf::SoundBuffer& _buffer, Animation* _source);

	std::map<std::string, sf::SoundBuffer>&		GetSoundsList();
	std::map<std::string, sf::Music>&			GetMusicsList();

	std::vector<SoundHolder>&					GetSoundInstancesList();
};