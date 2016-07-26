#include "GraphicsManager.h"
#include "stdafx.h"
#include "GraphicsManager.h"

bool GraphicsManager::LoadFont(std::string _fileName, std::string _mapIndex)
{
	sf::Font font;

	if (!font.loadFromFile(_fileName))
	{
		///TODO: LOG ERROR
		return false;
	}

	fontsMap.insert(std::pair<std::string, sf::Font>(_mapIndex, font));
	return true;	
}

bool GraphicsManager::LoadTexture(std::string _fileName, std::string _mapIndex)
{
	sf::Texture texture;

	if (!texture.loadFromFile(_fileName))
	{
		///TODO: LOG ERROR
		return false;
	}

	texturesMap.insert(std::pair<std::string, sf::Texture>(_mapIndex, texture));
	return true;
}

std::map<std::string, sf::Font>& GraphicsManager::GetFontsMap()
{
	return fontsMap;
}

std::map<std::string, sf::Texture>& GraphicsManager::GetTexturesMap()
{
	return texturesMap;
}
