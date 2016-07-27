#pragma once
#include "stdafx.h"

//This struct is simply a data container for all of the information necessary
//for a single animation frame
struct AnimationFrame
{
public:
	sf::IntRect		m_textureBounds;
	sf::Time		m_frameDuration;

	//Pointer to the texture the frame references; careful about usage
	sf::Texture*	m_texture;
};