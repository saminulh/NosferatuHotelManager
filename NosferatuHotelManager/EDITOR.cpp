#include "stdafx.h"
#include "EDITOR.h"
#include "MapTile.h"
#include "ButtonActions.h"

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
	Button buttonIsDoor;
	std::vector<std::string> ticksAnims;
	ticksAnims.push_back("editor-tickNo.vAnim");
	ticksAnims.push_back("editor-tickYes.vAnim");
	void (*isDoor)(void);
	isDoor = & ButtonActions::buttonIsDoor();

	buttonIsDoor.CreateButton("Is Room Exit", ticksAnims, sf::Vector2f(400.f,200.f), isDoor, sf::Vector2f(-100.f, 20.f));
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
