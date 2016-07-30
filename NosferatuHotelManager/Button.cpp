#include "stdafx.h"
#include "Button.h"
#include "AnimationClass.h"

Button::Button()
{
}

Button::~Button()
{
}

//Animations list should contain 3 animations in the following order:
//0 - Default button image/animation
//1 - Mouse over image/animation
//2 - Mouse click image/animation
void Button::CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, sf::Vector2f _relativeTextPos)
{
	LoadAnimation(_animationsList[0]);
	m_defaultButtonAnim = _animationsList[0];
	LoadAnimation(_animationsList[1]);
	m_mouseOverButtonAnim = _animationsList[1];
	LoadAnimation(_animationsList[2]);
	m_mouseClickedButtonAnim = _animationsList[2];

	GetSprite().setPosition(_pos);

	m_buttonText.CreateCustomText(_text, sf::Vector2f(_pos.x + _relativeTextPos.x, _pos.y + _relativeTextPos.y));

	BeginAnimation(m_defaultButtonAnim);
}

void Button::OnMouseOver()
{
	BeginAnimation(m_mouseOverButtonAnim);
}

void Button::OnMouseHover()
{
	///TODO: Display tooltip
}

void Button::OnMouseClick()
{
	BeginAnimation(m_mouseClickedButtonAnim);
}

void Button::Update(sf::Time _deltaTime)
{
	//This update is Animation's update
	Animation::Update(_deltaTime);
}

void Button::OnMouseExit()
{
	BeginAnimation(m_defaultButtonAnim);
}

CustomText & Button::GetButtonText()
{
	return m_buttonText;
}
