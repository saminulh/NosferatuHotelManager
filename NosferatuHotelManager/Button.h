#pragma once
#include "TextStruct.h"
#include "AnimationClass.h"

//This will be the basic button class that will be managed by the GUI manager
class Button : public Animation
{
	CustomText	m_buttonText;
public:
	Button();
	~Button();

	void CreateButton(std::string _text, std::vector<std::string> _animationsList, sf::Vector2f _pos, sf::Vector2f _relativeTextPos = sf::Vector2f(25, 25));


	void OnMouseOver();

	//Used for tooltips, etc.
	void OnMouseHover();
	void OnMouseClick();

	void Update(sf::Time _deltaTime);

	//Might be unnecessary
	void OnMouseExit();
};