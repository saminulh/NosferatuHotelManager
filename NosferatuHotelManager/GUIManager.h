#pragma once

//This singleton class is responsible for managing all Graphical User Interface (GUI) items
//These items include buttons, labels, etc. that are NOT part of the game world itself
class GUIManager
{
	///Possible unnecessary duplication (?)
	std::map<std::string, CustomText>	customTextsMap;
	std::map<std::string, sf::Text>		textsMap;
public:
};