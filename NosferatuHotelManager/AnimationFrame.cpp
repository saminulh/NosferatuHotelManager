#include "stdafx.h"
#include "AnimationFrame.h"

AnimationFrame::AnimationFrame()
{
}

void AnimationFrame::SetTextureBounds(sf::IntRect _newBounds)
{
	m_textureBounds = _newBounds;
}

void AnimationFrame::SetTextureBounds(unsigned int _x, unsigned int _y, unsigned int _width, unsigned int _height)
{
	m_textureBounds.top = _x;
	m_textureBounds.left = _y;
	m_textureBounds.width = _width;
	m_textureBounds.height = _height;
}

void AnimationFrame::SetFrameDuration(unsigned int _ms)
{
	m_frameDuration = sf::milliseconds(_ms);
}
