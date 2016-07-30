#pragma once

//This manager will be responsible for managing all screens
//Essentially it will be the global handler for accessing the window
class ScreensManager
{
	sf::RenderWindow	m_renderWindow;
public:
	const float			m_timePerFrame = 1 / 30.f;
	float				m_elapsedTime;
	sf::Vector2i		m_mousePos;

	ScreensManager();

	sf::RenderWindow&	GetWindow();
};