#pragma once
#include "TextStruct.h"
#include "Button.h"

//This manager class is responsible for managing all Graphical User Interface (GUI) items
//These items include buttons, labels, etc. that are NOT part of the game world itself
class GUIManager
{
	///Possible unnecessary duplication (?)
	std::map<std::string, CustomText>	customTextsMap;
	std::map<std::string, sf::Text>		textsMap;
	std::map<std::string, Animation>	animationsMap;
	std::map<std::string, Button>		buttonsMap;

public:
	GUIManager();
	~GUIManager();

	void Update();
	void DrawToWindow();

	std::map<std::string, CustomText>&	GetCustomTextsMap();
	std::map<std::string, sf::Text>&	GetSFTextsMap();
	std::map<std::string, Animation>&	GetAnimationsMap();
	std::map<std::string, Button>&		GetButtonsMap();
};