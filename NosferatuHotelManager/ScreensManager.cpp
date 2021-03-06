#include "stdafx.h"
#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
	m_renderWindow.create(sf::VideoMode(640, 480), "Nosferatu Hotel Manager");
	m_elapsedTime = 0;
}

sf::RenderWindow & ScreensManager::GetWindow()
{
	return m_renderWindow;
}

ScreensManager::ScreenTag ScreensManager::GetCurrentScreenTag()
{
	return m_currentScreen;
}

void ScreensManager::ChangeScreenTag(ScreenTag _newTag)
{
	m_currentScreen = _newTag;

	///TODO: Add event and event listeners here to tell other graphics elements that the screen has changed!
}