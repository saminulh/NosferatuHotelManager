#pragma once
#include "stdafx.h"
#include "Button.h"

class ButtonRadio : public Button
{
	bool			m_isTicked;
	std::string		m_trueAnim;
	std::string		m_falseAnim;
	std::string		m_mouseOverTrueAnim;
	std::string		m_mouseOverFalseAnim;
public:
	ButtonRadio();

	void			CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, void(*_onClickFunction)(void), 
									sf::Vector2f _relativeTextPos = sf::Vector2f(25, 25));

	void			OnMouseOver();
	void			OnMouseClick();

	void			Update(sf::Time _deltaTime);
	//Might be unnecessary
	void			OnMouseExit();
};