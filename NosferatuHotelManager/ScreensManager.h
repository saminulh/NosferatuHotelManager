#pragma once

//This manager will be responsible for managing all screens
//Essentially it will be the global handler for accessing the window
class ScreensManager
{
public:
	//Used by graphics objects to identify if they should exist/be drawn
	enum ScreenTag
	{
		MainMenu, SettingsMenu
	};

	const float			m_timePerFrame = 1 / 30.f;
	float				m_elapsedTime;
	sf::Vector2i		m_mousePos;
	sf::Clock			m_timer;
	


	ScreensManager();

	sf::RenderWindow&	GetWindow();
	ScreenTag			GetCurrentScreenTag();
	void				ChangeScreenTag(ScreenTag _newTag);

private:
	sf::RenderWindow	m_renderWindow;
	ScreenTag			m_currentScreen;
};