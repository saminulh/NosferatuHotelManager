#include "stdafx.h"
#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
	m_renderWindow.create(sf::VideoMode(1366, 768), "Map Editor");
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
sf::View & ScreensManager::GetView()
{
	return m_mainView;
}

void ScreensManager::ScrollView(float _x, float _y)
{
	guiManager.ScrollGUI(_x, _y);
	m_mainView.move(_x, _y);
}