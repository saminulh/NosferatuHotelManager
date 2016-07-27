#include "stdafx.h"
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
}

bool GraphicsManager::LoadFont(std::string _fileName, std::string _mapIndex)
{
	sf::Font		font;
	std::string		message;

	if (!font.loadFromFile(_fileName))
	{
		///TODO: LOG ERROR
		message = "Couldn't load FONT file '";
		message += _fileName;
		message += "'!\n";
		debug.Log(3, message);
		return false;
	}

	fontsMap.insert(std::pair<std::string, sf::Font>(_mapIndex, font));
	return true;	
}

bool GraphicsManager::LoadTexture(std::string _fileName, std::string _mapIndex)
{
	sf::Texture		texture;
	std::string		message;

	if (!texture.loadFromFile(_fileName))
	{
		///TODO: LOG ERROR
		message = "Couldn't load TEXTURE file '";
		message += _fileName;
		message += "'!\n";
		debug.Log(3, message);
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
