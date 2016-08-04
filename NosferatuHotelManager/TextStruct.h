#pragma once
#include "stdafx.h"

class CustomText
{
	sf::Text					m_mainText;
	sf::Text					m_outlineTopLeft;
	sf::Text					m_outlineTopRight;
	sf::Text					m_outlineBottomLeft;
	sf::Text					m_outlineBottomRight;
	ScreensManager::ScreenTag	m_screenTag;

public:
	CustomText();

	sf::Text&					GetMainText();
	sf::Text&					GetOutlineTopLeft();
	sf::Text&					GetOutlineTopRight();
	sf::Text&					GetOutlineBottomLeft();
	sf::Text&					GetOutlineBottomRight();

	void						CreateCustomText(std::string _text, sf::Vector2f _pos, sf::Color _mainColour = sf::Color::White, 
														sf::Color _outlineColour = sf::Color::Black, int _fontSize = 30, int _outlineThickness = 3, 
															std::string _font = "arial.ttf");
	void						ChangeScreenTag(ScreensManager::ScreenTag& _newTag);
	void						ChangeText(std::string _newText);


	ScreensManager::ScreenTag	GetScreenTag();
};