#include "stdafx.h"
#include "ButtonTextField.h"

ButtonTextField::ButtonTextField()
{
}

ButtonTextField::~ButtonTextField()
{
}

//Pass the function that should be executed if/when the user hits enter or releases the textbox - it will be treated as the OnMouseExit event
void ButtonTextField::CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, void(*_onClickFunction)(void), sf::Vector2f _relativeTextPos, sf::Vector2f _relativeUserTextPos)
{
	//Set button to deselected by default
	m_isSelected = false;
	m_isBeingEdited = false;

	//Set a minimum time between on and off
	m_timeBetweenToggles = sf::seconds(float(0.15));
	m_timeSinceToggle = sf::Time::Zero;

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

	//Create the text that the user will edit
	m_text.CreateCustomText("Test", sf::Vector2f(_pos.x + _relativeUserTextPos.x, _pos.y + _relativeUserTextPos.y), sf::Color::White, sf::Color::Black, 20);
	guiManager.GetCustomTextsMap().insert(std::pair<std::string, CustomText>(_text + "Label", m_text));

	//Start the default animation
	BeginAnimation(m_defaultButtonAnim);
}

void ButtonTextField::OnMouseOver()
{
	BeginAnimation(m_mouseOverButtonAnim);
}

void ButtonTextField::OnMouseClick()
{
	//Log that the button was pressed
	debug.Log(0, "TEXT FIELD '" + m_buttonText.GetMainText().getString() + "' was clicked!");

	//User clicked the text field, therefore wants to edit it
	m_isBeingEdited = true;

	//Activate the button's on-click function - text fields have no on-click; they interact through m_isBeingEdited or through the OnMouseExit event
	//m_onClickFunction();

	//Set the button's animation to the clicked animation
	BeginAnimation(m_mouseClickedButtonAnim);
}

void ButtonTextField::OnMouseHover()
{
}

void ButtonTextField::Update(sf::Time _deltaTime)
{
	//If the mouse is over the button and not clicked
	if (GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//Tell the button it has been selected
		m_isSelected = true;

		//To avoid locking the animation to the first frame,
		//check it isn't already playing before playing
		if (GetCurrentAnim() != m_mouseOverButtonAnim && !m_isBeingEdited)
			OnMouseOver();
	}
	//If the mouse is over the button, but clicked
	else if (GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
		m_timeSinceToggle >= m_timeBetweenToggles)
	{
		//Same as above
		if (GetCurrentAnim() != m_mouseClickedButtonAnim)
			OnMouseClick();
	}
	//If the button was previously hovered over by the mouse, but is no longer - user must press outside the text field to stop editing
	else if (!GetSprite().getGlobalBounds().contains(sf::Vector2f(screensManager.m_mousePos)) && 
		//Deselect if mouse is off and it isn't being edited, or if the mouse clicks away while it is being edited
		((!m_isBeingEdited) || (m_isBeingEdited && sf::Mouse::isButtonPressed(sf::Mouse::Left))))
	{
		//Deselect button
		m_isSelected = false;

		//Handle the mouse leaving
		OnMouseExit();
	}


	//This update is Animation's update
	Animation::Update(_deltaTime);
	m_timeSinceToggle += _deltaTime;
}

void ButtonTextField::OnMouseExit()
{
	//User left the text field
	m_isBeingEdited = false;
	BeginAnimation(m_defaultButtonAnim);

	if (m_onClickFunction != NULL)
		m_onClickFunction();
}

bool ButtonTextField::IsBeingEdited()
{
	return m_isBeingEdited;
}

CustomText & ButtonTextField::GetButtonLabel()
{
	return m_buttonText;
}

CustomText & ButtonTextField::GetButtonText()
{
	return m_text;
}
