#pragma once
#include "AnimationFrame.h"

//This class will represent a single animation
class Animation
{
	sf::Sprite												m_sprite;
	std::map < std::string, std::vector<AnimationFrame>>	m_animations;
public:
	bool LoadAnimation(std::string _fileName);
	bool PlayAnimation(std::string _animationName);
};