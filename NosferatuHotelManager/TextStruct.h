#pragma once
#include "stdafx.h"

class CustomText
{
public:
	sf::Text	m_mainText;
	sf::Text	m_outlineTopLeft;
	sf::Text	m_outlineTopRight;
	sf::Text	m_outlineBottomLeft;
	sf::Text	m_outlineBottomRight;

	CustomText();

	void CreateCustomText(std::string _text, sf::Vector2f _pos, sf::Color _mainColour = sf::Color::White, sf::Color _outlineColour = sf::Color::Black, int _fontSize = 20, int _outlineThickness = 5, sf::Font _font = graphicsManager.GetFontsMap()["arial.ttf"]);
};