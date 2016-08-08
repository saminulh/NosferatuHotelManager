#include "stdafx.h"
#include "ScreensManager.h"

ScreensManager::ScreensManager()
{
	m_renderWindow.create(sf::VideoMode(1366, 768), "Map Editor");
	m_elapsedTime = 0;
	m_currentScreen = ScreensManager::EditorMainScreen;
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

std::vector<unsigned int> ScreensManager::GetViewCullingBounds()
{
	std::vector<unsigned int>	bounds;
	unsigned int				centerX, centerY;

	centerX = ((unsigned int)m_mainView.getCenter().x / 32);
	centerY = ((unsigned int)m_mainView.getCenter().y / 32);

	//Divide by 32 because tile size, and 2 because you only care about one half - add two at the end so theres never unrendered area being viewed
	bounds.push_back(centerX - ((unsigned int)(m_mainView.getSize().x / (32 * 2)) + 2));
	bounds.push_back(centerX + ((unsigned int)(m_mainView.getSize().x / (32 * 2)) + 2));

	bounds.push_back(centerY - ((unsigned int)(m_mainView.getSize().y / (32 * 2)) + 2));
	bounds.push_back(centerY + ((unsigned int)(m_mainView.getSize().y / (32 * 2)) + 2));

	if (editor.m_roomMap.size() > 0)
	{
		if (editor.m_roomMap[0].size() > 0)
		{
			if (bounds[0] > 100000)
				bounds[0] = 0;
			if (bounds[1] > editor.m_roomMap.size())
				bounds[1] = editor.m_roomMap.size() - 1;
			if (bounds[2] > 100000)
				bounds[2] = 0;
			if (bounds[3] > editor.m_roomMap[0].size())
				bounds[3] = editor.m_roomMap[0].size() - 1;
		}
	}
	else
	{
		debug.Log(3, "No room map loaded!");
		bounds[0] = 0;
		bounds[1] = 0;
		bounds[2] = 0;
		bounds[3] = 0;
	}
	

	return			bounds;
}