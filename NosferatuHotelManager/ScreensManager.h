#pragma once

//This singleton will be responsible for managing all screens
class ScreensManager
{
	sf::RenderWindow	m_renderWindow;
public:
	ScreensManager();



	sf::RenderWindow& GetWindow();
};