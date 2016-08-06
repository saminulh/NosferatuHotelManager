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
		m_currentFile = fileName;
		CreateMap(fileName);
	}
	else if (std::getchar() == 'o' || std::getchar() == 'O')
	{
		std::string fileName;
		//User wants to open an existing file
		std::cout << "Please enter the file location to be opened: " << std::endl;
		std::cin >> fileName;
		m_currentFile = fileName;
		LoadMap(fileName);
	}
	else
	{
		std::cout << "Invalid request." << std::endl;
		Init();
	}
}

void Editor::LoadMap(std::string& _fileName)
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

	//Load animations for regular buttons
	std::vector<std::string>	regularButtonAnims;
	regularButtonAnims.push_back("editor-regularDefault.vAnim");
	regularButtonAnims.push_back("editor-regularMouseOver.vAnim");
	regularButtonAnims.push_back("editor-regularMouseClick.vAnim");

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

	//Save button
	Button*						saveButton = new Button();
	void(*saveButtonAction)();
	saveButtonAction = &ButtonActions::buttonSaveMap;
	saveButton->CreateButton("Save", regularButtonAnims, sf::Vector2f(1125.f, 650.f), saveButtonAction, sf::Vector2f(55.f, 5.f));
	saveButton->BeginAnimation("editor-regularDefault.vAnim");
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("saveButton", saveButton));

	//Counter
	CustomText					counter;
	counter.CreateCustomText("0 / 0", sf::Vector2f(1185.f, 350.f));
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("counter", counter));

	//Fps text
	CustomText					fpsText;
	fpsText.CreateCustomText("FPS: 000", sf::Vector2f(1150.f, 25.f));
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("fpsText", fpsText));

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

void Editor::CreateMap(std::string& _fileName)
{
	unsigned int mapSizeX, mapSizeY;
	unsigned int tileSize = 32;

	std::cout << "Enter map size x: ";
	std::cin >> mapSizeX;
	std::cout << "Enter map size y: ";
	std::cin >> mapSizeY;

	sf::Clock		mapGenTimer;

	for (unsigned int cntY = 0; cntY < mapSizeY; cntY++)
	{
		std::vector<MapTile>	buffer;
		for (unsigned int cntX = 0; cntX < mapSizeX; cntX++)
		{
			MapTile	tile;
			tile.LoadAnimation("tile-grassPatch1.vAnim");
			tile.BeginAnimation("tile-grassPatch1.vAnim");

			tile.GetSprite().setPosition((float)(cntY * tileSize), (float)(cntX * tileSize));
			
			//Set default values
			tile.m_xPos					= (float)cntX;
			tile.m_yPos					= (float)cntY;
			tile.m_floorNumber			= 0;
			tile.m_isDoor				= false;
			tile.m_isRoomExit			= false;
			tile.m_isSolid				= false;
			tile.m_tileActivityCode		= 0;
			tile.m_tileID				= 0;

			AddUsedAnimation("tile-grassPatch1.vAnim", &tile);

			buffer.push_back(tile);
		}
		m_roomMap.push_back(buffer);
	}

	SaveMap(m_currentFile);

	debug.Log(2, "Map generation took " + std::to_string(mapGenTimer.getElapsedTime().asMilliseconds()) + " milliseconds to generate " + std::to_string(mapSizeX * mapSizeY) + " tiles.");
}

void Editor::SaveMap(std::string& _fileName)
{
	std::ofstream				file;
	tinyxml2::XMLDocument		doc;

	debug.Log(0, "Saving map to '" + _fileName + "'!");

	//Create root element
	tinyxml2::XMLNode*			root			= doc.NewElement("NosferatuHotelManagerMap");
	doc.InsertFirstChild(root);

	//Save relevant meta info
	tinyxml2::XMLNode*			meta			= doc.NewElement("Meta");
	root->InsertFirstChild(meta);

	//X and Y Map size
	tinyxml2::XMLElement*		mapSizeX		= doc.NewElement("MapSizeX");
	mapSizeX->SetText(m_roomMap[0].size());
	meta->InsertFirstChild(mapSizeX);
	tinyxml2::XMLElement*		mapSizeY = doc.NewElement("MapSizeY");
	mapSizeY->SetText(m_roomMap.size());
	meta->InsertFirstChild(mapSizeY);

	//Animations
	tinyxml2::XMLElement*		animationsUsed	= doc.NewElement("AnimationsUsed");
	root->InsertEndChild(animationsUsed);

	//Save the animations that are used within the map in the 'header'
	for (unsigned int cnt = 0; cnt < m_animationsUsed.size(); cnt++)
	{
		//Create a new node
		tinyxml2::XMLElement*	node			= doc.NewElement("Animation");
		//Set the node's value
		node->SetText(m_animationsUsed[cnt].refAnim.c_str());
		//Add the node to the file
		animationsUsed->InsertEndChild(node);
	}

	//Begin saving the map itself
	tinyxml2::XMLNode*			map				= doc.NewElement("Map");
	root->InsertEndChild(map);

	//Iterate through map Y
	for (unsigned int itr = 0; itr < m_roomMap.size(); itr++)
	{
		//Seperate map rows in the XML
		tinyxml2::XMLNode*		row				= doc.NewElement("Row");
		//Iterate through map X for current map Y
		for (unsigned int cnt = 0; cnt < m_roomMap[itr].size(); cnt++)
		{
			//Create new element for each tile
			tinyxml2::XMLElement*	tile		= doc.NewElement("Tile");

			tile->SetAttribute("isRoomExit", m_roomMap[itr][cnt].m_isRoomExit);
			tile->SetAttribute("isDoor", m_roomMap[itr][cnt].m_isDoor);
			tile->SetAttribute("isSolid", m_roomMap[itr][cnt].m_isSolid);
			tile->SetAttribute("Animation", m_roomMap[itr][cnt].GetCurrentAnim().c_str());

			//Save the tile to the row
			row->InsertEndChild(tile);
		}
		//Save the row to the map
		map->InsertEndChild(row);
	}

	//Save the map to file
	doc.SaveFile(_fileName.c_str());

	debug.Log(0, "Successfully saved FILE '" + _fileName + "'!");
}

void Editor::LoadListOfPossibleAnims(std::string& _fileName)
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

void Editor::AddUsedAnimation(std::string _anim, Animation* _user)
{
	//Search the list of used animations to avoid double-adding
	for (unsigned int cnt = 0; cnt < m_animationsUsed.size(); cnt++)
	{
		//We know it's here so we can exit
		if (m_animationsUsed[cnt].refAnim == _anim)
			return;
	}
	//Add it if it wasn't found
	UsedAnimStruct		anim;
	anim.refAnim = _anim;
	anim.referencesList.push_back(_user);
	m_animationsUsed.push_back(anim);
}

void Editor::RemoveUnusedAnimation(std::string _anim, Animation* _user)
{
	//Find the animation
	for (unsigned int cnt = 0; cnt < m_animationsUsed.size(); cnt++)
	{
		if (m_animationsUsed[cnt].refAnim == _anim)
		{
			//Remove the tile from the list of tiles that use that animation
			for (unsigned int itr = 0; itr < m_animationsUsed[cnt].referencesList.size(); itr++)
			{
				if (m_animationsUsed[cnt].referencesList[itr] == _user)
				{
					m_animationsUsed[cnt].referencesList.erase(m_animationsUsed[cnt].referencesList.begin() + itr);
				}
			}

			//If the list of dependent tiles is empty, remove the entire animation
			if (m_animationsUsed[cnt].referencesList.size() == 0)
			{
				m_animationsUsed.erase(m_animationsUsed.begin() + cnt);
			}
		}
	}
}

MapTile & Editor::GetCurrentTileProperties()
{
	return m_currentTileProperties;
}
