#pragma once
#include "AnimationFrame.h"

//This class will represent a single animation
class Animation
{
	sf::Sprite												m_sprite;
	std::map <std::string, std::vector<AnimationFrame>>		m_animations;
	sf::Time												m_timeSinceLastUpdate;
	std::string												m_CurrentAnim;
	unsigned int											m_currentAnimFrame;
	ScreensManager::ScreenTag								m_screenTag;

public:
	bool													LoadAnimation(std::string _fileName);
	bool													BeginAnimation(std::string _animationName);
	std::string&											GetCurrentAnim();
	sf::Sprite&												GetSprite();

	//Update may not need to be virtual ...
	virtual void											Update(sf::Time _deltaTime);
	virtual void											ChangeScreenTag(ScreensManager::ScreenTag _newTag);
	ScreensManager::ScreenTag								GetScreenTag();
};