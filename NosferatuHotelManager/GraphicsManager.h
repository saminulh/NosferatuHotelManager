#pragma once
#include "stdafx.h"

//This singleton class will be responsible for handling ALL graphics that must be loaded
class GraphicsManager
{
	std::map<std::string, sf::Font> fontsMap;
	std::map<std::string, sf::Texture> texturesMap;
public:
	GraphicsManager();

	bool LoadFontFile(std::string _fileName, std::string _mapIndex);
	bool LoadTexture(std::string _fileName, std::string _mapIndex);
};