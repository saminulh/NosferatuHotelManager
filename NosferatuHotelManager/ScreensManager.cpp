#include "stdafx.h"
#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
	m_renderWindow.create(sf::VideoMode(400, 400), "SFML works!");
}

sf::RenderWindow & ScreensManager::GetWindow()
{
	return m_renderWindow;
}
