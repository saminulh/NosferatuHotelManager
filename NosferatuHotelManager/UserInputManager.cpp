#include "stdafx.h"
#include "UserInputManager.h"

UserInputManager::UserInputManager()
{
	m_minTimeToScroll = sf::seconds((float)0.15);
	m_timeMouseInScrollArea = sf::Time::Zero;
	m_scrollSpeed = 5;
}

void UserInputManager::Update(sf::Time _deltaTime)
{
	m_addedTime = false;

	//Mouse on far left of screen
	if ((unsigned int)sf::Mouse::getPosition(screensManager.GetWindow()).x < screensManager.GetWindow().getSize().x / 12)
	{
		if (!m_addedTime)
		{
			m_timeMouseInScrollArea += _deltaTime;
			m_addedTime = true;
		}
		
		if (m_timeMouseInScrollArea >= m_minTimeToScroll)
		{
			//Scroll left
			screensManager.ScrollView(-m_scrollSpeed, 0.f);
		}
	}
	//Mouse on far right of screen
	if ((unsigned int)sf::Mouse::getPosition(screensManager.GetWindow()).x > screensManager.GetWindow().getSize().x * 11 / 12)
	{
		if (!m_addedTime)
		{
			m_timeMouseInScrollArea += _deltaTime;
			m_addedTime = true;
		}

		if (m_timeMouseInScrollArea >= m_minTimeToScroll)
		{
			//Scroll right
			screensManager.ScrollView(m_scrollSpeed, 0.f);
		}
	}
	//Mouse on far top of screen
	if ((unsigned int)sf::Mouse::getPosition(screensManager.GetWindow()).y < screensManager.GetWindow().getSize().y / 7)
	{
		if (!m_addedTime)
		{
			m_timeMouseInScrollArea += _deltaTime;
			m_addedTime = true;
		}

		if (m_timeMouseInScrollArea >= m_minTimeToScroll)
		{
			//Scroll up
			screensManager.ScrollView(0.f, -m_scrollSpeed);
		}
	}
	//Mouse on far left of screen
	//if (screensManager.m_mousePos.y > screensManager.GetWindow().getSize().y * 6 / 7)
	if ((unsigned int)sf::Mouse::getPosition(screensManager.GetWindow()).y > screensManager.GetWindow().getSize().y * 6 / 7)
	{
		if (!m_addedTime)
		{
			m_timeMouseInScrollArea += _deltaTime;
			m_addedTime = true;
		}

		if (m_timeMouseInScrollArea >= m_minTimeToScroll)
		{
			//Scroll down
			screensManager.ScrollView(0.f, m_scrollSpeed);
		}
	}

	if (!m_addedTime)
	{
		//Mouse isn't in scroll area
		m_timeMouseInScrollArea = sf::Time::Zero;
	}
}

void UserInputManager::TextEnteredEvent(sf::Event & _event)
{
	//Unicode backspace
	if (_event.text.unicode == 8)
	{
		for (auto& itr : guiManager.GetButtonsMap())
		{
			//Only the text field being editted should return true here
			//The user also shouldn't be able to have more than one text field active at a time
			if (itr.second->IsBeingEdited())
			{
				//Remove the last character
				itr.second->GetButtonText().ChangeText(itr.second->GetButtonText().GetMainText().getString().substring((size_t)0, 
					(size_t)itr.second->GetButtonText().GetMainText().getString().getSize()-1));
			}
		}
	}
	//Unicode tab
	else if (_event.text.unicode == 9)
	{
		//For now, don't do anything
	}
	//Unicode newline/enter
	else if (_event.text.unicode == 13)
	{
		//Treat this the same as the user 'accepting' the change
		for (auto& itr : guiManager.GetButtonsMap())
		{
			//Only the text field being editted should return true here
			//The user also shouldn't be able to have more than one text field active at a time
			if (itr.second->IsBeingEdited())
			{
				itr.second->OnMouseExit();
			}
		}
	}
	//'Regular' text
	else
	{
		for (auto& itr : guiManager.GetButtonsMap())
		{
			//Only the text field being editted should return true here
			//The user also shouldn't be able to have more than one text field active at a time
			if (itr.second->IsBeingEdited())
			{
				itr.second->GetButtonText().ChangeText(itr.second->GetButtonText().GetMainText().getString() + static_cast<char>(_event.text.unicode));
			}
		}
	}
}
