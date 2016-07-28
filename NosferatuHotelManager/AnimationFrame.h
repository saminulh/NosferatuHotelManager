#pragma once
#include "stdafx.h"

//This struct is simply a data container for all of the information necessary
//for a single animation frame
class AnimationFrame
{
public:
	sf::IntRect		m_textureBounds;
	sf::Time		m_frameDuration;
	std::string		m_soundEffect;

	//Pointer to the texture the frame references; careful about usage
	sf::Texture*	m_texture;

	AnimationFrame();

	void SetTextureBounds(sf::IntRect _newBounds);
	void SetTextureBounds(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height);

	void SetFrameDuration(unsigned int _ms);
};