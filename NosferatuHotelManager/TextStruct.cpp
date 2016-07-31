#include "stdafx.h"
#include "TextStruct.h"

CustomText::CustomText()
{
}

sf::Text& CustomText::GetMainText()
{
	return m_mainText;
}

sf::Text& CustomText::GetOutlineTopLeft()
{
	return m_outlineTopLeft;
}

sf::Text& CustomText::GetOutlineTopRight()
{
	return m_outlineTopRight;
}

sf::Text& CustomText::GetOutlineBottomLeft()
{
	return m_outlineBottomLeft;
}

sf::Text& CustomText::GetOutlineBottomRight()
{
	return m_outlineBottomRight;
}

void CustomText::CreateCustomText(std::string _text, sf::Vector2f _pos, sf::Color _mainColour, sf::Color _outlineColour, int _fontSize, int _outlineThickness, std::string _font)
{
	//Ensure the requested font file is loaded in memory
	if (graphicsManager.GetFontsMap().find(_font) == graphicsManager.GetFontsMap().end())
	{
		debug.Log(2, "Could not find FONT '" + _font + "' in the loaded fonts map!");
		return;
	}

	//Set up the texts
	m_mainText.setCharacterSize(_fontSize);
	m_mainText.setColor(_mainColour);
	m_mainText.setFont(graphicsManager.GetFontsMap()[_font]);
	m_mainText.setPosition(_pos);
	m_mainText.setString(_text);
	m_mainText.setStyle(sf::Text::Bold);

	m_outlineTopLeft.setCharacterSize(_fontSize);
	m_outlineTopLeft.setColor(_outlineColour);
	m_outlineTopLeft.setFont(graphicsManager.GetFontsMap()[_font]);
	m_outlineTopLeft.setPosition(sf::Vector2f(_pos.x - _outlineThickness, _pos.y - _outlineThickness));
	m_outlineTopLeft.setString(_text);
	m_outlineTopLeft.setStyle(sf::Text::Bold);

	m_outlineTopRight.setCharacterSize(_fontSize);
	m_outlineTopRight.setColor(_outlineColour);
	m_outlineTopRight.setFont(graphicsManager.GetFontsMap()[_font]);
	m_outlineTopRight.setPosition(sf::Vector2f(_pos.x + _outlineThickness, _pos.y - _outlineThickness));
	m_outlineTopRight.setString(_text);
	m_outlineTopRight.setStyle(sf::Text::Bold);

	m_outlineBottomLeft.setCharacterSize(_fontSize);
	m_outlineBottomLeft.setColor(_outlineColour);
	m_outlineBottomLeft.setFont(graphicsManager.GetFontsMap()[_font]);
	m_outlineBottomLeft.setPosition(sf::Vector2f(_pos.x - _outlineThickness, _pos.y + _outlineThickness));
	m_outlineBottomLeft.setString(_text);
	m_outlineBottomLeft.setStyle(sf::Text::Bold);

	m_outlineBottomRight.setCharacterSize(_fontSize);
	m_outlineBottomRight.setColor(_outlineColour);
	m_outlineBottomRight.setFont(graphicsManager.GetFontsMap()[_font]);
	m_outlineBottomRight.setPosition(sf::Vector2f(_pos.x + _outlineThickness, _pos.y + _outlineThickness));
	m_outlineBottomRight.setString(_text);
	m_outlineBottomRight.setStyle(sf::Text::Bold);
}

void CustomText::ChangeScreenTag(ScreensManager::ScreenTag _newTag)
{
	m_screenTag = _newTag;
}

ScreensManager::ScreenTag CustomText::GetScreenTag()
{
	return m_screenTag;
}
