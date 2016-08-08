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

	char temp = std::getchar();

	if (temp == 'c' || temp == 'C')
	{
		std::string fileName;
		//User wants to create a new file
		std::cout << "Please enter the desired file name: " << std::endl;
		std::cin >> fileName;
		m_currentFile = fileName;
		CreateMap(fileName);
	}
	else if (temp == 'o' || temp == 'O')
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
	unsigned int				mapSizeX, mapSizeY, numAnims;
	sf::Clock					mapLoadTimer;
	std::ifstream				file;
	tinyxml2::XMLDocument		doc;

	debug.Log(0, "Loading map " + _fileName + " ...");

	//Load the actual file (string must be passed as a c-string)
	tinyxml2::XMLError			err = doc.LoadFile(_fileName.c_str());

	if (err != tinyxml2::XML_SUCCESS)
	{
		debug.Log(3, "Error reading XML file!");
	}

	//Get access to root element
	tinyxml2::XMLElement*		root = doc.FirstChildElement("NosferatuHotelManagerMap");

	//Load map size
	mapSizeY = std::stoul(root->FirstChildElement("Meta")->FirstChildElement("MapSizeY")->GetText());
	mapSizeX = std::stoul(root->FirstChildElement("Meta")->FirstChildElement("MapSizeX")->GetText());

	//Load animations that will be needed to display the map
	tinyxml2::XMLElement*		animationsUsedNode;
	animationsUsedNode = root->FirstChildElement("AnimationsUsed");
	numAnims = std::stoul(animationsUsedNode->Attribute("Size"));

	tinyxml2::XMLElement*		currentNode = animationsUsedNode->FirstChildElement("Animation");
	//Actually load the necessary animations now
	for (unsigned int cnt = 0; cnt < numAnims; cnt++)
	{
		//Load animation text
		m_tempLoader.LoadAnimation(currentNode->GetText());
		//Move to next sibling element
		currentNode = currentNode->NextSiblingElement("Animation");
	}
	
	//Now load the map
	tinyxml2::XMLElement*		map;
	tinyxml2::XMLElement*		column;
	map = root->FirstChildElement("Map");
	column = map->FirstChildElement("Column");

	//Iterate through all of the columns in the map
	for (unsigned int cnt = 0; cnt < mapSizeY; cnt++)
	{
		//Create a temp vector to save the tiles
		std::vector<MapTile>	tempVector;
		
		//Set the iterator to the first tile in the current column
		currentNode = column->FirstChildElement("Tile");

		//Iterate through all of the tiles in the column
		for (unsigned int itr = 0; itr < mapSizeX; itr++)
		{
			MapTile				tile;

			//Load and play the tile's animation
			tile.LoadAnimation(currentNode->Attribute("Animation"));
			tile.BeginAnimation(currentNode->Attribute("Animation"));

			//Set the correct screen tag
			tile.ChangeScreenTag(ScreensManager::Editor);

			//Load the other tile attributes
			currentNode->QueryBoolAttribute("isDoor", &tile.m_isDoor);
			currentNode->QueryBoolAttribute("isRoomExit", &tile.m_isRoomExit);
			currentNode->QueryBoolAttribute("isSolid", &tile.m_isSolid);

			//X position is defined by Y, and Y by X - don't ask why
			tile.GetSprite().setPosition((float)(cnt * 32), (float)(itr * 32));

			//Set default values - ignore for now
			tile.m_xPos = (float)cnt;
			tile.m_yPos = (float)itr;

			//Ignore these for now
			tile.m_floorNumber = 0;
			tile.m_tileActivityCode = 0;
			tile.m_tileID = 0;

			//Set the iterator at the next element
			currentNode = currentNode->NextSiblingElement("Tile");
			//Save the tile
			tempVector.push_back(tile);
		}

		//Iterate to the next column
		column = column->NextSiblingElement("Column");
		//Save the previous column 
		m_roomMap.push_back(tempVector);
	}

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
	buttonIsDoor->ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonIsDoor", buttonIsDoor));

	//Radio button for if the tile is a room exit (to be aligned with other room exits)
	ButtonRadio*				buttonIsRoomExit = new ButtonRadio();
	void						(*isRoomExit)(void);
	isRoomExit = &ButtonActions::buttonIsRoomExit;
	buttonIsRoomExit->CreateButton("Room Exit", ticksAnims, sf::Vector2f(1300.f, 550.f), isRoomExit, sf::Vector2f(-200.f, 0.f));
	buttonIsRoomExit->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isRoomExit = false;
	buttonIsRoomExit->ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonIsRoomExit", buttonIsRoomExit));

	//Radio button for if the tile is solid/pathable
	ButtonRadio*				buttonisSolid = new ButtonRadio();
	void(*isTileSolid)(void);
	isTileSolid = &ButtonActions::buttonIsSolid;
	buttonisSolid->CreateButton("Tile Solid", ticksAnims, sf::Vector2f(1300.f, 600.f), isTileSolid, sf::Vector2f(-200.f, 0.f));
	buttonisSolid->BeginAnimation("editor-tickNo.vAnim");
	editor.GetCurrentTileProperties().m_isSolid = false;
	buttonisSolid->ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonRadio*>("buttonisSolid", buttonisSolid));

	//Text field for searching for tiles
	ButtonTextField*			buttonSearchField = new ButtonTextField();
	void(*searchForMatch)(void);
	searchForMatch = &ButtonActions::buttonSearchForAnims;
	buttonSearchField->CreateButton("Search", textFieldAnims, sf::Vector2f(1100.f, 440.f), searchForMatch, sf::Vector2f(0.f, -40.f), sf::Vector2f(10.f, 10.f));
	buttonSearchField->GetSprite().setScale((float)1.3, (float)1);
	buttonSearchField->SetMaxEnterableChars(15);
	buttonSearchField->ChangeScreenTag(ScreensManager::Editor);
	buttonSearchField->GetButtonLabel().ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonTextField*>("buttonSearchField", buttonSearchField));
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("buttonSearchForAnims_label", buttonSearchField->GetButtonLabel()));

	//Increment anims up
	Button*						buttonUpInList = new Button();;
	void(*incrementAnims)();
	incrementAnims = &ButtonActions::buttonUpInAnims;
	buttonUpInList->CreateButton("", sliderUpButtonAnims, sf::Vector2f(1125.f, 350.f), incrementAnims);
	buttonUpInList->ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("buttonUpInList", buttonUpInList));

	//Decrement anims
	Button*						buttonDownInList = new Button();
	void(*decrementAnims)();
	decrementAnims = &ButtonActions::buttonDownInAnims;
	buttonDownInList->CreateButton("", sliderDownButtonAnims, sf::Vector2f(1300.f, 350.f), decrementAnims);
	buttonDownInList->ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("buttonDownInList", buttonDownInList));

	//Save button
	Button*						saveButton = new Button();
	void(*saveButtonAction)();
	saveButtonAction = &ButtonActions::buttonSaveMap;
	saveButton->CreateButton("Save", regularButtonAnims, sf::Vector2f(1125.f, 650.f), saveButtonAction, sf::Vector2f(55.f, 5.f));
	saveButton->BeginAnimation("editor-regularDefault.vAnim");
	saveButton->ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("saveButton", saveButton));

	//Counter
	CustomText					counter;
	counter.CreateCustomText("0 / 0", sf::Vector2f(1185.f, 350.f));
	counter.ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("counter", counter));

	//Fps text
	CustomText					fpsText;
	fpsText.CreateCustomText("FPS: 000", sf::Vector2f(1150.f, 25.f));
	fpsText.ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("fpsText", fpsText));

	//Background panel
	Animation					panelAnim;
	panelAnim.LoadAnimation("editor-sidePanel.vAnim");
	panelAnim.BeginAnimation("editor-sidePanel.vAnim");
	panelAnim.GetSprite().setPosition(1075.f, 0.f);
	panelAnim.GetSprite().setScale((float)3.5, (float)6.98);
	panelAnim.ChangeScreenTag(ScreensManager::Editor);
	guiManager.GetAnimationsMap().insert(std::pair<std::string, Animation>("panelAnim", panelAnim));

	//Preview animation
	Animation					previewAnim;
	previewAnim.LoadAnimation(m_allTilesList[0].GetCurrentAnim());
	previewAnim.BeginAnimation(m_allTilesList[0].GetCurrentAnim());
	previewAnim.GetSprite().setPosition(1185.f, 150.f);
	previewAnim.GetSprite().setScale(4.f, 4.f);
	previewAnim.ChangeScreenTag(ScreensManager::Editor);
	//Load all possible anims to the preview
	for (unsigned int cnt = 0; cnt < m_allTilesList.size(); cnt++)
	{
		previewAnim.LoadAnimation(m_allTilesList[cnt].GetCurrentAnim());
	}
	guiManager.GetAnimationsMap().insert(std::pair<std::string, Animation>("previewAnim", previewAnim));
	guiManager.GetCustomTextsMap()["counter"].ChangeText(std::to_string(editor.m_currentTileInShortList + 1) + " / " + std::to_string(editor.m_shortTilesList.size()));


	m_currentTileInShortList = 0;


	//Create map button
	Button*						createMapButton = new Button();
	void(*createMapButtonAction)();
	createMapButtonAction = &ButtonActions::createMapButton;
	createMapButton->CreateButton("Create New Map", regularButtonAnims, sf::Vector2f(550.f, 375.f), createMapButtonAction, sf::Vector2f(55.f, 5.f));
	createMapButton->BeginAnimation("editor-regularDefault.vAnim");
	createMapButton->GetSprite().setScale(2.f, 1.f);
	createMapButton->ChangeScreenTag(ScreensManager::EditorMainScreen);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("createMapButton", createMapButton));

	//Load map button
	Button*						loadMapButton = new Button();
	void(*loadMapButtonAction)();
	loadMapButtonAction = &ButtonActions::loadMapButton;
	loadMapButton->CreateButton("Load Existing Map", regularButtonAnims, sf::Vector2f(550.f, 450.f), loadMapButtonAction, sf::Vector2f(55.f, 5.f));
	loadMapButton->BeginAnimation("editor-regularDefault.vAnim");
	loadMapButton->GetSprite().setScale(2.f, 1.f);
	loadMapButton->ChangeScreenTag(ScreensManager::EditorMainScreen);
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button*>("loadMapButton", loadMapButton));

	//Text field for entering file name
	ButtonTextField*			buttonFileNameField = new ButtonTextField();
	void(*fileNameFieldAction)(void);
	fileNameFieldAction = &ButtonActions::buttonFileNameField;
	buttonFileNameField->CreateButton("File Name:", textFieldAnims, sf::Vector2f(550.f, 300.f), fileNameFieldAction, sf::Vector2f(0.f, -40.f), sf::Vector2f(10.f, 10.f));
	buttonFileNameField->GetSprite().setScale((float)2, (float)1);
	buttonFileNameField->SetMaxEnterableChars(25);
	buttonFileNameField->ChangeScreenTag(ScreensManager::EditorMainScreen);
	buttonFileNameField->GetButtonLabel().ChangeScreenTag(ScreensManager::EditorMainScreen);
	guiManager.GetButtonsMap().insert(std::pair<std::string, ButtonTextField*>("buttonFileNameField", buttonFileNameField));
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>("buttonFileNameField_label", buttonFileNameField->GetButtonLabel()));

	//Background panel - first menu
	Animation					panelLoginAnim;
	panelLoginAnim.LoadAnimation("editor-sidePanel.vAnim");
	panelLoginAnim.BeginAnimation("editor-sidePanel.vAnim");
	panelLoginAnim.GetSprite().setPosition(450.f, 150.f);
	panelLoginAnim.GetSprite().setScale((float)5.5, (float)3.75);
	panelLoginAnim.ChangeScreenTag(ScreensManager::EditorMainScreen);
	guiManager.GetAnimationsMap().insert(std::pair<std::string, Animation>("panelLoginAnim", panelLoginAnim));

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

			tile.ChangeScreenTag(ScreensManager::Editor);

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
	animationsUsed->SetAttribute("Size", m_animationsUsed.size());
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
		tinyxml2::XMLNode*		row				= doc.NewElement("Column");
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
