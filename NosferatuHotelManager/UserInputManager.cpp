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
