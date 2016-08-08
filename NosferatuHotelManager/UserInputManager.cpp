#include "stdafx.h"
#include "UserInputManager.h"

UserInputManager::UserInputManager()
{
	m_minTimeToScroll = sf::seconds((float)0.15);
	m_timeMouseInScrollArea = sf::Time::Zero;
	m_scrollSpeed = 5;

	m_minTimeBetweenClicks = sf::seconds((float)(0.1));
	m_timeSinceMouseClick = sf::Time::Zero;
}

void UserInputManager::Update(sf::Time& _deltaTime)
{
	m_addedTime = false;

	/*-------- Begin Mouse Scroll Code ---------------*/
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
	/*-------- End Mouse Scroll Code -----------------*/


	/*-------- Begin Mouse Click Code ---------------*/
	//If enough time has passed and the user is pressing the left mouse button
	if (m_timeSinceMouseClick >= m_minTimeBetweenClicks &&
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
		screensManager.GetCurrentScreenTag() == ScreensManager::Editor)
	{
		//If the mouse isn't over the side panel
		if (!guiManager.GetAnimationsMap()["panelAnim"].GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)))
		{
			mouseLeftClickOnMap();
			m_timeSinceMouseClick = sf::Time::Zero;
		}
	}

	//If enough time has passed and the user is pressing the right mouse button
	if (m_timeSinceMouseClick >= m_minTimeBetweenClicks &&
		sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) &&
		screensManager.GetCurrentScreenTag() == ScreensManager::Editor)
	{
		//If the mouse isn't over the side panel
		if (!guiManager.GetAnimationsMap()["panelAnim"].GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)))
		{
			mouseRightClickOnMap();
			m_timeSinceMouseClick = sf::Time::Zero;
		}
	}

	m_timeSinceMouseClick += _deltaTime;
	/*-------- End Mouse Click Code -----------------*/
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
			if (itr.second->IsBeingEdited() &&
				itr.second->GetScreenTag() == screensManager.GetCurrentScreenTag())
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
			if (itr.second->IsBeingEdited() &&
				itr.second->GetScreenTag() == screensManager.GetCurrentScreenTag())
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
			if (itr.second->IsBeingEdited() &&
				itr.second->GetScreenTag() == screensManager.GetCurrentScreenTag() &&
				itr.second->GetButtonText().GetMainText().getString().getSize() < itr.second->GetMaxEnterableChars())
			{
				itr.second->GetButtonText().ChangeText(itr.second->GetButtonText().GetMainText().getString() + static_cast<char>(_event.text.unicode));
			}
		}
	}
}

void UserInputManager::mouseLeftClickOnMap()
{
	//std::cout << "Pressed mouse left at " << screensManager.m_mousePos.x << ", " << screensManager.m_mousePos.y << std::endl;

	//Ensure that the mouse press was within map bounds
	if ((screensManager.m_mousePos.x >= 0 && screensManager.m_mousePos.y >= 0) &&
		(screensManager.m_mousePos.y < editor.m_roomMap[0].size() * 32 && screensManager.m_mousePos.x < editor.m_roomMap.size() * 32))
	{
		//Remove this tile's reference to the previous animation it had
		editor.RemoveUnusedAnimation(editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].GetCurrentAnim(), 
			&editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)]);
		
		//Clear the tile's loaded animations (a tile should only have one animation)
		editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].ClearCurrentAnimations();

		//Load the correct animation into the tile
		editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].
			LoadAnimation(guiManager.GetAnimationsMap()["previewAnim"].GetCurrentAnim());

		//Assign the tile the preview animation (the one displayed on the center left of the editor panel)
		editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].
			BeginAnimation(guiManager.GetAnimationsMap()["previewAnim"].GetCurrentAnim());

		//Add this tile's reference to the new animation it is using
		editor.AddUsedAnimation(guiManager.GetAnimationsMap()["previewAnim"].GetCurrentAnim(), 
			&editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)]);

		//Copy tile properties
		editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].
			m_isRoomExit = editor.GetCurrentTileProperties().m_isRoomExit;

		editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].
			m_isDoor = editor.GetCurrentTileProperties().m_isDoor;

		editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].
			m_isSolid = editor.GetCurrentTileProperties().m_isSolid;
	}
}

void UserInputManager::mouseRightClickOnMap()
{
	//std::cout << "Pressed mouse right!" << std::endl;

	//Ensure that the mouse press was within map bounds
	if ((screensManager.m_mousePos.x >= 0 && screensManager.m_mousePos.y >= 0) &&
		(screensManager.m_mousePos.y < editor.m_roomMap[0].size() * 32 && screensManager.m_mousePos.x < editor.m_roomMap.size() * 32))
	{
		//No references need to be modified here - Ensure animation is loaded
		guiManager.GetAnimationsMap()["previewAnim"].LoadAnimation(
			editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].GetCurrentAnim());
		//Start playing the correct animation
		guiManager.GetAnimationsMap()["previewAnim"].BeginAnimation(
			editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].GetCurrentAnim());

		//Copy tile properties - and set the buttons to the correct animation!
		editor.GetCurrentTileProperties().m_isRoomExit = 
			editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].m_isRoomExit;
		//Animation
		guiManager.GetButtonsMap()["buttonIsRoomExit"]->UpdateTick(editor.GetCurrentTileProperties().m_isRoomExit);

		//Is Door
		editor.GetCurrentTileProperties().m_isDoor = 
			editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].m_isDoor;
		//Animation
		guiManager.GetButtonsMap()["buttonIsDoor"]->UpdateTick(editor.GetCurrentTileProperties().m_isDoor);

		//Is Solid - BE CAREFUL - THIS ONE HAS A LOWERCASE I
		editor.GetCurrentTileProperties().m_isSolid = 
			editor.m_roomMap[(unsigned int)(screensManager.m_mousePos.x / 32)][(unsigned int)(screensManager.m_mousePos.y / 32)].m_isSolid;
		//Animation
		guiManager.GetButtonsMap()["buttonisSolid"]->UpdateTick(editor.GetCurrentTileProperties().m_isSolid);
	}
}
