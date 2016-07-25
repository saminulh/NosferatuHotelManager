#include "GraphicsManager.h"
#include "stdafx.h"
#include "GraphicsManager.h"

bool GraphicsManager::LoadFont(std::string _fileName, std::string _mapIndex)
{
	sf::Font font;

	if (!font.loadFromFile(_fileName))
	{
		//LOG ERROR
		return false;
	}

	fontsMap.insert(std::pair<std::string, sf::Font>(_mapIndex, font));
	return true;	
}

bool GraphicsManager::LoadTexture(std::string _fileName, std::string _mapIndex)
{
	return false;
}

std::map<std::string, sf::Font>& GraphicsManager::GetFontsMap()
{
	// TODO: insert return statement here
}

std::map<std::string, sf::Texture>& GraphicsManager::GetTexturesMap()
{
	// TODO: insert return statement here
}
