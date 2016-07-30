#include "stdafx.h"
#include "Button.h"
#include "TextStruct.h"
#include "AnimationClass.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, sf::Vector2f _relativeTextPos)
{
}

void Button::OnMouseOver()
{
}

void Button::OnMouseHover()
{
}

void Button::OnMouseClick()
{
}

void Button::Update(sf::Time _deltaTime)
{
	//This update is Animation's update
	Update(_deltaTime);
}

void Button::OnMouseExit()
{
}
