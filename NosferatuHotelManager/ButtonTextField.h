#pragma once
#include "stdafx.h"
#include "Button.h"
#include "TextStruct.h"

class ButtonTextField : public Button
{
	CustomText		m_text;
	bool			m_isBeingEdited;
public:
	ButtonTextField();
	~ButtonTextField();

	void			CreateButton(std::string _text, std::vector<std::string>& _animationsList, sf::Vector2f _pos, void(*_onClickFunction)(void), 
								sf::Vector2f _relativeTextPos = sf::Vector2f(25, 25), sf::Vector2f _relativeUserTextPos = sf::Vector2f(25,25));

	void			OnMouseOver();
	void			OnMouseClick();

	//Used for tooltips, etc.
	void			OnMouseHover();

	void			Update(sf::Time& _deltaTime);
	//Might be unnecessary
	void			OnMouseExit();

	bool			IsBeingEdited();

	//Returns the custom text inherited from button
	CustomText&		GetButtonLabel();
	//Returns the contents of the text field
	CustomText&		GetButtonText();
};