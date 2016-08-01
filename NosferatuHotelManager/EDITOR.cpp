#include "stdafx.h"
#include "EDITOR.h"
#include "MapTile.h"
#include "ButtonActions.h"
#include "ButtonRadio.h"
#include "ButtonTextField.h"

Editor::Editor()
{
	m_tilesList = "Resources/Editor/rezList1.txt";
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

	//Load animations for increment buttons
	std::vector<std::string>	sliderUpButtonAnims;
	sliderUpButtonAnims.push_back("editor-upMouseDefaultButton.vAnim");
	sliderUpButtonAnims.push_back("editor-upMouseOverButton.vAnim");
	sliderUpButtonAnims.push_back("editor-upMouseClickButton.vAnim");
	std::vector<std::string>	sliderDownButtonAnims;
	sliderDownButtonAnims.push_back("editor-downMouseDefaultButton.vAnim");
	sliderDownButtonAnims.push_back("editor-downMouseOverButton.vAnim");
	sliderDownButtonAnims.push_back("editor-downMouseClickButton.vAnim");

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
	void(*searchForMatch)(void);
	searchForMatch = &ButtonActions::buttonSearchForAnims;
	buttonSearchField->CreateButton("Search", textFieldAnims, sf::Vector2f(1100.f, 440.f), searchForMatch, sf::Vector2f(0.f, -40.f), sf::Vector2f(10.f, 10.f));
	buttonSearchField->GetSprite().setScale((float)1.3, (float)1);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonTextField*>("buttonSearchField", buttonSearchField));
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("buttonSearchForAnims_label", buttonSearchField->GetButtonLabel()));

	//Increment anims up
	Button*						buttonUpInList = new Button();;
	void(*incrementAnims)();
	incrementAnims = &ButtonActions::buttonUpInAnims;
	buttonUpInList->CreateButton("", sliderUpButtonAnims, sf::Vector2f(1125.f, 350.f), incrementAnims);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("buttonUpInList", buttonUpInList));

	//Decrement anims
	Button*						buttonDownInList = new Button();
	void(*decrementAnims)();
	decrementAnims = &ButtonActions::buttonDownInAnims;
	buttonDownInList->CreateButton("", sliderDownButtonAnims, sf::Vector2f(1300.f, 350.f), decrementAnims);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("buttonDownInList", buttonDownInList));

	//Counter
	CustomText					counter;
	counter.CreateCustomText("0 / 0", sf::Vector2f(1185.f, 350.f));
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("counter", counter));

	//Background panel
	Animation					panelAnim;
	panelAnim.LoadAnimation("editor-sidePanel.vAnim");
	panelAnim.BeginAnimation("editor-sidePanel.vAnim");
	panelAnim.GetSprite().setPosition(1075.f, 0.f);
	panelAnim.GetSprite().setScale((float)3.5, (float)6.98);
	guiManager.GetAnimationsMap().insert(std::pair<std::string, Animation>("panelAnim", panelAnim));

	//Preview animation
	Animation					previewAnim;
	previewAnim.LoadAnimation(m_allTilesList[0].GetCurrentAnim());
	previewAnim.BeginAnimation(m_allTilesList[0].GetCurrentAnim());
	previewAnim.GetSprite().setPosition(1185.f, 150.f);
	previewAnim.GetSprite().setScale(4.f, 4.f);
	//Load all possible anims to the preview
	for (unsigned int cnt = 0; cnt < m_allTilesList.size(); cnt++)
	{
		previewAnim.LoadAnimation(m_allTilesList[cnt].GetCurrentAnim());
	}
	guiManager.GetAnimationsMap().insert(std::pair<std::string, Animation>("previewAnim", previewAnim));
	guiManager.GetCustomTextsMap()["counter"].ChangeText(std::to_string(editor.m_currentTileInShortList + 1) + " / " + std::to_string(editor.m_shortTilesList.size()));


	m_currentTileInShortList = 0;

}

void Editor::LoadResources()
{
}

void Editor::CreateMap(std::string _fileName)
{
	unsigned int mapSizeX, mapSizeY;
	unsigned int tileSize = 32;

	std::cout << "Enter map size x: ";
	std::cin >> mapSizeX;
	std::cout << "Enter map size y: ";
	std::cin >> mapSizeY;



	for (unsigned int cntY = 0; cntY < mapSizeY; cntY++)
	{
		std::vector<MapTile>	buffer;
		for (unsigned int cntX = 0; cntX < mapSizeX; cntX++)
		{
			MapTile	tile;
			tile.LoadAnimation("tile-grassPatch1.vAnim");
			tile.BeginAnimation("tile-grassPatch1.vAnim");
			tile.GetSprite().setPosition((float)(cntX * tileSize), (float)(cntY * tileSize));
			tile.m_xPos = (float)cntX;
			tile.m_yPos = (float)cntY;
			tile.m_floorNumber = 0;
			tile.m_isDoor = false;
			tile.m_isRoomExit = false;
			tile.m_isSolid = false;
			tile.m_tileActivityCode = 0;
			tile.m_tileID = 0;

			buffer.push_back(tile);
		}
		m_roomMap.push_back(buffer);
	}
}

void Editor::SaveMap(std::string _FileName)
{
}

void Editor::LoadListOfPossibleAnims(std::string _fileName)
{
	std::ifstream	list;
	unsigned int	size;
	std::string		temp;

	//Try to open the file
	list.open(_fileName);
	if (list.is_open())
	{
		//Read number of elements (as integer in the header)
		list >> size;

		//For all elements in the list, load them up!
		for (unsigned int cnt = 0; cnt < size; cnt++)
		{
			list >> temp;

			Animation anim;
			anim.LoadAnimation(temp);
			anim.BeginAnimation(temp);
			
			//Save into both lists because copying is wonky
			m_allTilesList.push_back(anim);
			m_shortTilesList.push_back(anim);
		}
	}
}

MapTile & Editor::GetCurrentTileProperties()
{
	return m_currentTileProperties;
}
