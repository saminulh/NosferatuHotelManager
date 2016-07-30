#include "stdafx.h"
#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
	m_renderWindow.create(sf::VideoMode(640, 480), "Nosferatu Hotel Manager");
}

sf::RenderWindow & ScreensManager::GetWindow()
{
	return m_renderWindow;
}