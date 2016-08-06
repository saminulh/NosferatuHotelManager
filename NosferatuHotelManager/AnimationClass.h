#pragma once
#include "AnimationFrame.h"

//This class will represent a single drawn entity - ie. a single character
//It will contain all animations for that character
class Animation
{
	sf::Sprite												m_sprite;


	//CANNOT HAVE MORE THAN 256 sf::Sound AND sf::Music instances at any given time!
	//Going to have to fix this somehow...
	///sf::Sound												m_sound;
	std::map <std::string, std::vector<AnimationFrame>>		m_animations;
	std::map<std::string, sf::SoundBuffer>					m_soundEffects;
	sf::Time												m_timeSinceLastUpdate;
	std::string												m_CurrentAnim;
	unsigned int											m_currentAnimFrame;
	ScreensManager::ScreenTag								m_screenTag;
	unsigned int											m_audioPriority;

public:
	Animation();
	Animation(const Animation &_obj);
	~Animation();

	bool													LoadAnimation(std::string _fileName);
	bool													BeginAnimation(std::string _animationName);
	std::string&											GetCurrentAnim();
	sf::Sprite&												GetSprite();
	std::string&											GetSoundEffect();

	//Update may not need to be virtual ...
	virtual void											Update(sf::Time& _deltaTime);
	virtual void											ChangeScreenTag(ScreensManager::ScreenTag _newTag);
	ScreensManager::ScreenTag								GetScreenTag();

	void													AssignAnimation(std::string& _anim, Animation &_ref);

	void													SetAudioPriority(unsigned int _newPriority);
	unsigned int											GetAudioPriority();
};

struct SoundHolder
{
	sf::Sound												m_sound;
	Animation*												m_source;
};