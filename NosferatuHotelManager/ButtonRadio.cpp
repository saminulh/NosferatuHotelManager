#include "stdafx.h"
#include "ButtonRadio.h"
#include "stdafx.h"
#include "Button.h"
#include "ButtonRadio.h"

ButtonRadio::ButtonRadio()
{
	m_isTicked = false;
}

//Animations list should contain 3 animations in the following order:
//0 - Default False Anim
//1 - Default True Anim
//2 - False Hover Anim
//3 - True Hover Anim
void ButtonRadio::CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, void(*_onClickFunction)(void), sf::Vector2f _relativeTextPos)
{
	//Set button to deselected by default
	m_isSelected = false;
	//Set the button's on-click function to the one passed in as a parameter
	m_onClickFunction = _onClickFunction;

	//Set the button's animations
	LoadAnimation(_animationsList[0]);
	m_falseAnim = _animationsList[0];
	LoadAnimation(_animationsList[1]);
	m_trueAnim = _animationsList[1];
	LoadAnimation(_animationsList[2]);
	m_mouseOverFalseAnim = _animationsList[2];
	LoadAnimation(_animationsList[3]);
	m_mouseOverTrueAnim = _animationsList[3];

	//Set the button's sprite's position
	GetSprite().setPosition(_pos);

	//Create the button text
	m_buttonText.CreateCustomText(_text, sf::Vector2f(_pos.x + _relativeTextPos.x, _pos.y + _relativeTextPos.y));

	//Set button to false by default
	m_isTicked = false;
	//Select corresponding animation
	BeginAnimation(m_falseAnim);
}

void ButtonRadio::OnMouseOver()
{
	//Set button highlight based on button value
	if (m_isTicked)
		BeginAnimation(m_mouseOverTrueAnim);
	else
		BeginAnimation(m_mouseOverFalseAnim);
}

void ButtonRadio::OnMouseClick()
{
	//Log that the button was pressed
	debug.Log(0, "BUTTON '" + m_buttonText.GetMainText().getString() + "' was clicked!");

	//Activate the button's on-click function
	m_onClickFunction();
	m_isTicked = !m_isTicked;

	//Set button to sprite depending on if it's value is true or false
	if (m_isTicked)
		BeginAnimation(m_trueAnim);
	else
		BeginAnimation(m_falseAnim);
}

void ButtonRadio::Update(sf::Time _deltaTime)
{
	//If the mouse is over the button and not clicked
	if (GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Tell the button it has been selected
		m_isSelected = true;

		//To avoid locking the animation to the first frame,
		//check it isn't already playing before playing
		if (GetCurrentAnim() != m_mouseOverFalseAnim || GetCurrentAnim() != m_mouseOverTrueAnim)
			OnMouseOver();
	}
	//If the mouse is over the button, but clicked
	else if (GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		OnMouseClick();
	}
	//If the mouse was previously hovered over by the mouse, but is no longer
	else if (!GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && m_isSelected)
	{
		//Deselect button
		m_isSelected = false;

		//Handle the mouse leaving
		OnMouseExit();
	}


	//This update is Animation's update
	Animation::Update(_deltaTime);
}

void ButtonRadio::OnMouseExit()
{
	//Set button to sprite depending on if it's value is true or false
	if (m_isTicked)
	{
		if (GetCurrentAnim() != m_trueAnim)
			BeginAnimation(m_trueAnim);
	}
	else
	{
		if (GetCurrentAnim() != m_falseAnim)
			BeginAnimation(m_falseAnim);
	}
}
