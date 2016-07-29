#include "stdafx.h"
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager()
{
	LoadFont("arial.ttf");
}

bool GraphicsManager::LoadFont(std::string _fileName)
{
	sf::Font		font;
	std::string		message;
	std::string		fileLoc;

	//Check if font file is already loaded before trying to load
	if (fontsMap.find(_fileName) == fontsMap.end())
	{
		fileLoc = "Resources/Fonts/";
		fileLoc += _fileName;

		if (!font.loadFromFile(fileLoc))
		{
			message = "Couldn't load FONT file '";
			message += _fileName;
			message += "'!";
			debug.Log(3, message);
			return false;
		}
		else
		{
			message = "Successfully loaded FONT file '";
			message += _fileName;
			message += "'!";
			debug.Log(0, message);
		}

		fontsMap.insert(std::pair<std::string, sf::Font>(_fileName, font));
	}
	else
	{
		message = "Attempted to reload FONT file '";
		message += _fileName;
		message += "'!";
		debug.Log(0, message);
	}
	
	return true;	
}

bool GraphicsManager::LoadTexture(std::string _fileName)
{
	sf::Texture		texture;
	std::string		message;
	std::string		fileLoc;

	//Check if texture file is already loaded before trying to laod
	if (texturesMap.find(_fileName) == texturesMap.end())
	{
		fileLoc = "Resources/Textures/";
		fileLoc += _fileName;

		if (!texture.loadFromFile(fileLoc))
		{
			message = "Couldn't load TEXTURE file '";
			message += _fileName;
			message += "'!";
			debug.Log(3, message);
			return false;
		}
		else
		{
			message = "Successfully loaded TEXTURE file '";
			message += _fileName;
			message += "'!";
			debug.Log(0, message);
		}

		texturesMap.insert(std::pair<std::string, sf::Texture>(_fileName, texture));
	}
	else
	{
		message = "Attempted to reload TEXTURE file '";
		message += _fileName;
		message += "'!";
		debug.Log(0, message);
	}
	
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
