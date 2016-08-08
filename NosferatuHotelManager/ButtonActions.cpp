#include "stdafx.h"
#include "ButtonActions.h"

void ButtonActions::TestButtonAction()
{
	debug.Log(2, "Function pointers work!");
}

void ButtonActions::buttonIsDoor()
{
	editor.GetCurrentTileProperties().m_isDoor = !editor.GetCurrentTileProperties().m_isDoor;
	if (editor.GetCurrentTileProperties().m_isDoor)
		debug.Log(1, "Door set to true");
	else
		debug.Log(1, "Door set to false");
}

void ButtonActions::buttonIsRoomExit()
{
	editor.GetCurrentTileProperties().m_isRoomExit = !editor.GetCurrentTileProperties().m_isRoomExit;
	if (editor.GetCurrentTileProperties().m_isRoomExit)
		debug.Log(1, "Room exit set to true");
	else
		debug.Log(1, "Room exit set to false");
}

void ButtonActions::buttonIsSolid()
{
	editor.GetCurrentTileProperties().m_isSolid = !editor.GetCurrentTileProperties().m_isSolid;
	if (editor.GetCurrentTileProperties().m_isSolid)
		debug.Log(1, "Tile is solid set to true");
	else
		debug.Log(1, "Tile is solid set to false");
}

void ButtonActions::buttonSearchForAnims()
{
	std::string temp = guiManager.GetButtonsMap()["buttonSearchField"]->GetButtonText().GetMainText().getString();

	//Clear the last search
	editor.m_shortTilesList.clear();

	//Find all tiles that match the phrase
	for (unsigned int cnt = 0; cnt < editor.m_allTilesList.size(); cnt++)
	{
		//If the searched string is found in this tile's animation (ie. name) add it to the short list
		if (editor.m_allTilesList[cnt].GetCurrentAnim().find(temp) != std::string::npos)
		{
			editor.m_shortTilesList.push_back(editor.m_allTilesList[cnt]);
		}
	}
	//If there were no matches, go back to the full list
	if (editor.m_shortTilesList.size() == 0)
	{
		editor.m_shortTilesList = editor.m_allTilesList;
	}


	//Update status of cursor
	editor.m_currentTileInShortList = 0;
	guiManager.GetCustomTextsMap()["counter"].ChangeText(std::to_string(editor.m_currentTileInShortList + 1) + " / " + std::to_string(editor.m_shortTilesList.size()));
	guiManager.GetAnimationsMap()["previewAnim"].BeginAnimation(editor.m_shortTilesList[editor.m_currentTileInShortList].GetCurrentAnim());
}

void ButtonActions::buttonUpInAnims()
{
	editor.m_currentTileInShortList++;
	if (editor.m_currentTileInShortList >= editor.m_shortTilesList.size())
	{
		editor.m_currentTileInShortList = 0;
	}
	guiManager.GetAnimationsMap()["previewAnim"].BeginAnimation(editor.m_shortTilesList[editor.m_currentTileInShortList].GetCurrentAnim());
	guiManager.GetCustomTextsMap()["counter"].ChangeText(std::to_string(editor.m_currentTileInShortList + 1) + " / " + std::to_string(editor.m_shortTilesList.size()));
}

void ButtonActions::buttonDownInAnims()
{
	if (editor.m_currentTileInShortList == 0)
	{
		editor.m_currentTileInShortList = editor.m_shortTilesList.size() - 1;
	}
	else
	{
		editor.m_currentTileInShortList--;
	}
	guiManager.GetAnimationsMap()["previewAnim"].BeginAnimation(editor.m_shortTilesList[editor.m_currentTileInShortList].GetCurrentAnim());
	guiManager.GetCustomTextsMap()["counter"].ChangeText(std::to_string(editor.m_currentTileInShortList + 1) + " / " + std::to_string(editor.m_shortTilesList.size()));
}

void ButtonActions::buttonSaveMap()
{
	std::cout << "Saving ... " << std::endl;
	editor.SaveMap(editor.m_currentFile);
	std::cout << "Saved successfully!" << std::endl;
}

void ButtonActions::buttonFileNameField()
{
}

void ButtonActions::createMapButton()
{
	//Debug only
	std::cout << "File name text field says: " << std::string(guiManager.GetButtonsMap()["buttonFileNameField"]->GetButtonText().GetMainText().getString()) << std::endl;
	//Change the screen tag to the relevant one
	screensManager.ChangeScreenTag(ScreensManager::Editor);
	//Center the view on the map, in case it has scrolled in the mean time
	screensManager.GetView().setCenter(screensManager.GetWindow().getSize().x / 2, screensManager.GetWindow().getSize().y / 2);
	//Create the map
	editor.CreateMap(std::string(guiManager.GetButtonsMap()["buttonFileNameField"]->GetButtonText().GetMainText().getString()));
}

void ButtonActions::loadMapButton()
{
	//Debug only
	std::cout << "File name text field says: " << std::string(guiManager.GetButtonsMap()["buttonFileNameField"]->GetButtonText().GetMainText().getString()) << std::endl;
	//Change the screen tag to the relevant one
	screensManager.ChangeScreenTag(ScreensManager::Editor);
	//Center the view on the map, in case it has scrolled in the mean time
	screensManager.GetView().setCenter(screensManager.GetWindow().getSize().x / 2, screensManager.GetWindow().getSize().y / 2);
	//Load the requested file
	editor.LoadMap(std::string(guiManager.GetButtonsMap()["buttonFileNameField"]->GetButtonText().GetMainText().getString()));
}
