#include "stdafx.h"
#include "Button.h"
#include "AnimationClass.h"
#include "TextStruct.h"

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
///TODO: double check if order actually matters
void Button::CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, void(*_onClickFunction)(void), sf::Vector2f _relativeTextPos)
{
	//Set button to deselected by default
	m_isSelected = false;
	//Set the button's on-click function to the one passed in as a parameter
	m_onClickFunction = _onClickFunction;

	//Set the button's animations
	LoadAnimation(_animationsList[0]);
	m_defaultButtonAnim = _animationsList[0];
	LoadAnimation(_animationsList[1]);
	m_mouseOverButtonAnim = _animationsList[1];
	LoadAnimation(_animationsList[2]);
	m_mouseClickedButtonAnim = _animationsList[2];

	//Set the button's sprite's position
	GetSprite().setPosition(_pos);

	//Create the button text
	m_buttonText.CreateCustomText(_text, sf::Vector2f(_pos.x + _relativeTextPos.x, _pos.y + _relativeTextPos.y));

	//Start the default animation
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
	//Log that the button was pressed
	debug.Log(0, "BUTTON '" + m_buttonText.GetMainText().getString() + "' was clicked!");

	//Activate the button's on-click function
	m_onClickFunction();

	//Set the button's animation to the clicked animation
	BeginAnimation(m_mouseClickedButtonAnim);
}

void Button::Update(sf::Time _deltaTime)
{
	//If the mouse is over the button and not clicked
	if (GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Tell the button it has been selected
		m_isSelected = true;

		//To avoid locking the animation to the first frame,
		//check it isn't already playing before playing
		if (GetCurrentAnim() != m_mouseOverButtonAnim)
			OnMouseOver();
	}
	//If the mouse is over the button, but clicked
	else if (GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Same as above
		if (GetCurrentAnim() != m_mouseClickedButtonAnim)
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

void Button::OnMouseExit()
{
	BeginAnimation(m_defaultButtonAnim);
}

CustomText & Button::GetButtonText()
{
	return m_buttonText;
}

bool Button::IsBeingEdited()
{
	return false;
}