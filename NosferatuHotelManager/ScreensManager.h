#pragma once

//This manager will be responsible for managing all screens
//Essentially it will be the global handler for accessing the window
class ScreensManager
{
	sf::RenderWindow	m_renderWindow;
public:
	ScreensManager();

	sf::RenderWindow&	GetWindow();
};