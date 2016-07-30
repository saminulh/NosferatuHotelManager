#pragma once
#include "stdafx.h"

//This struct is simply a data container for all of the information necessary
//for a single animation frame
class AnimationFrame
{

	sf::IntRect			m_textureBounds;
	sf::Time			m_frameDuration;
	std::string			m_soundEffect;
	std::string			m_texture;

public:
	AnimationFrame();

	void				SetTextureBounds(sf::IntRect _newBounds);
	void				SetTextureBounds(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height);
	void				SetFrameDuration(unsigned int _ms);
	void				SetTexture(std::string _texture);

	sf::IntRect&		GetTextureBounds();
	sf::Time&			GetFrameDuration();
	std::string&		GetSoundEffect();
	std::string&		GetTexture();
};