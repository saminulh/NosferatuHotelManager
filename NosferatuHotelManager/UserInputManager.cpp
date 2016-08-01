#include "stdafx.h"
#include "UserInputManager.h"

UserInputManager::UserInputManager()
{
}

void UserInputManager::Update(sf::Time _deltaTime)
{
}

void UserInputManager::TextEnteredEvent(sf::Event & _event)
{
	//Unicode backspace
	if (_event.text.unicode == 8)
	{

	}
	//Unicode tab
	else if (_event.text.unicode == 9)
	{

	}
	//Unicode newline/enter
	else if (_event.text.unicode == 13)
	{

	}
	//'Regular' text
	else
	{

	}
}
