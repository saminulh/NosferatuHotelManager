#include "stdafx.h"
#include "TextStruct.h"

CustomText::CustomText()
{
}

void CustomText::CreateCustomText(std::string _text, sf::Vector2f _pos, sf::Color _mainColour, sf::Color _outlineColour, int _fontSize, int _outlineThickness, sf::Font _font)
{
	m_mainText.setCharacterSize(_fontSize);
	m_mainText.setColor(_mainColour);
	m_mainText.setFont(_font);
	m_mainText.setPosition(_pos);
	m_mainText.setString(_text);

	m_outlineTopLeft.setCharacterSize(_fontSize);
	m_outlineTopLeft.setColor(_outlineColour);
	m_outlineTopLeft.setFont(_font);
	m_outlineTopLeft.setPosition(sf::Vector2f(_pos.x - _outlineThickness, _pos.y - _outlineThickness));
	m_outlineTopLeft.setString(_text);

	m_outlineTopRight.setCharacterSize(_fontSize);
	m_outlineTopRight.setColor(_outlineColour);
	m_outlineTopRight.setFont(_font);
	m_outlineTopRight.setPosition(sf::Vector2f(_pos.x + _outlineThickness, _pos.y - _outlineThickness));
	m_outlineTopRight.setString(_text);

	m_outlineBottomLeft.setCharacterSize(_fontSize);
	m_outlineBottomLeft.setColor(_outlineColour);
	m_outlineBottomLeft.setFont(_font);
	m_outlineBottomLeft.setPosition(sf::Vector2f(_pos.x - _outlineThickness, _pos.y + _outlineThickness));
	m_outlineBottomLeft.setString(_text);

	m_outlineBottomRight.setCharacterSize(_fontSize);
	m_outlineBottomRight.setColor(_outlineColour);
	m_outlineBottomRight.setFont(_font);
	m_outlineBottomRight.setPosition(sf::Vector2f(_pos.x + _outlineThickness, _pos.y + _outlineThickness));
	m_outlineBottomRight.setString(_text);
}