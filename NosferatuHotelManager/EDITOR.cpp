#include "stdafx.h"
#include "EDITOR.h"
#include "MapTile.h"
#include "ButtonActions.h"
#include "ButtonRadio.h"
#include "ButtonTextField.h"

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
		CreateMap(fileName);
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
	//Load animations for radio button states
	std::vector<std::string>	ticksAnims;
	ticksAnims.push_back("editor-tickNo.vAnim");
	ticksAnims.push_back("editor-tickYes.vAnim");
	ticksAnims.push_back("editor-tickNoHover.vAnim");
	ticksAnims.push_back("editor-tickYesHover.vAnim");

	//Load animations for text field button
	std::vector<std::string>	textFieldAnims;
	textFieldAnims.push_back("editor-textFieldDefault.vAnim");
	textFieldAnims.push_back("editor-textFieldMouseOver.vAnim");
	textFieldAnims.push_back("editor-textFieldClicked.vAnim");

	//Radio button for if the tile is a door
	ButtonRadio*				buttonIsDoor = new ButtonRadio();
	void						(*isDoor)(void);
	isDoor = &ButtonActions::buttonIsDoor;
	buttonIsDoor->CreateButton("Door", ticksAnims, sf::Vector2f(1300.f,500.f), isDoor, sf::Vector2f(-200.f, 0.f));
	buttonIsDoor->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isDoor = false;
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonIsDoor", buttonIsDoor));

	//Radio button for if the tile is a room exit (to be aligned with other room exits)
	ButtonRadio*				buttonIsRoomExit = new ButtonRadio();
	void						(*isRoomExit)(void);
	isRoomExit = &ButtonActions::buttonIsRoomExit;
	buttonIsRoomExit->CreateButton("Room Exit", ticksAnims, sf::Vector2f(1300.f, 550.f), isRoomExit, sf::Vector2f(-200.f, 0.f));
	buttonIsRoomExit->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isRoomExit = false;
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonIsRoomExit", buttonIsRoomExit));

	//Radio button for if the tile is solid/pathable
	ButtonRadio*				buttonisSolid = new ButtonRadio();
	void(*isTileSolid)(void);
	isTileSolid = &ButtonActions::buttonIsSolid;
	buttonisSolid->CreateButton("Tile Solid", ticksAnims, sf::Vector2f(1300.f, 600.f), isTileSolid, sf::Vector2f(-200.f, 0.f));
	buttonisSolid->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isSolid = false;
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonisSolid", buttonisSolid));

	//Text field for searching for tiles
	ButtonTextField*			buttonSearchField = new ButtonTextField();
	buttonSearchField->CreateButton("Search", textFieldAnims, sf::Vector2f(1100.f, 440.f), NULL, sf::Vector2f(0.f, -40.f), sf::Vector2f(10.f, 10.f));
	buttonSearchField->GetSprite().setScale((float)1.3, (float)1);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonTextField*>("buttonSearchField", buttonSearchField));

	//Background panel
	Animation					panelAnim;
	panelAnim.LoadAnimation("editor-sidePanel.vAnim");
	panelAnim.BeginAnimation("editor-sidePanel.vAnim");
	panelAnim.GetSprite().setPosition(1075.f, 0.f);
	panelAnim.GetSprite().setScale((float)3.5, (float)6.98);
	guiManager.GetAnimationsMap().insert(std::pair<std::string, Animation>("panelAnim", panelAnim));

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
