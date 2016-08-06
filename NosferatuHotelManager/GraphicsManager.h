#pragma once
#include "AnimationFrame.h"

//This manager class will be responsible for loading and managing all graphics-related assets.
class GraphicsManager
{
	std::map<std::string, sf::Font>							fontsMap;
	std::map<std::string, sf::Texture>						texturesMap;
	std::map<std::string, std::vector<AnimationFrame>>		m_globalAnimationsRepository;
public:
	GraphicsManager();


	bool													LoadFont(std::string _fileName);
	bool													LoadTexture(std::string _fileName);

	std::map<std::string, sf::Font>&						GetFontsMap();
	std::map<std::string, sf::Texture>&						GetTexturesMap();
	std::map<std::string, std::vector<AnimationFrame>>&		GetAnimationsRepository();
};