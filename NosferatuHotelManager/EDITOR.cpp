#include "stdafx.h"
#include "EDITOR.h"
#include "MapTile.h"
#include "ButtonActions.h"
#include "ButtonRadio.h"

Editor::Editor()
{
}

void Editor::Init()
{
	std::cout << "Would you like to [C]reate or [O]pen a file?" << std::endl;

	if (std::getchar() == 'c' || std::getchar() == 'C')
	{
		std::string fileName;
		//User wants to create a new file
		std::cout << "Please enter the desired file name: " << std::endl;
		std::cin >> fileName;
		//CreateMap(fileName);
	}
	else if (std::getchar() == 'o' || std::getchar() == 'O')
	{
		std::string fileName;
		//User wants to open an existing file
		std::cout << "Please enter the file location to be opened: " << std::endl;
		std::cin >> fileName;
		LoadMap(fileName);
	}
	else
	{
		std::cout << "Invalid request." << std::endl;
		Init();
	}
}

void Editor::LoadMap(std::string _fileName)
{
}

void Editor::LoadEditorResources()
{
	ButtonRadio*				buttonIsDoor = new ButtonRadio();
	std::vector<std::string>	ticksAnims;
	ticksAnims.push_back("editor-tickNo.vAnim");
	ticksAnims.push_back("editor-tickYes.vAnim");
	ticksAnims.push_back("editor-tickNoHover.vAnim");
	ticksAnims.push_back("editor-tickYesHover.vAnim");
	void						(*isDoor)(void);
	isDoor = &ButtonActions::buttonIsDoor;
	buttonIsDoor->CreateButton("Is Door", ticksAnims, sf::Vector2f(400.f,200.f), isDoor, sf::Vector2f(-200.f, 0.f));
	buttonIsDoor->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isDoor = false;
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonIsDoor", buttonIsDoor));


	ButtonRadio*				buttonIsRoomExit = new ButtonRadio();
	void						(*isRoomExit)(void);
	isRoomExit = &ButtonActions::buttonIsRoomExit;
	buttonIsRoomExit->CreateButton("Is Room Exit", ticksAnims, sf::Vector2f(400.f, 250.f), isRoomExit, sf::Vector2f(-200.f, 0.f));
	buttonIsRoomExit->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isRoomExit = false;
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonIsRoomExit", buttonIsRoomExit));

}

void Editor::LoadResources()
{
}

void Editor::CreateMap(std::string _fileName)
{
}

void Editor::SaveMap(std::string _FileName)
{
}

MapTile & Editor::GetCurrentTileProperties()
{
	return m_currentTileProperties;
}
