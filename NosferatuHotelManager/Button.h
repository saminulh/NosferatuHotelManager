#pragma once

//This will be the basic button class that will be managed by the GUI manager

class Button : public Animation
{
public:
	Button();
	~Button();

	void OnMouseOver();

	//Used for tooltips, etc.
	void OnMouseHover();
	void OnMouseClick();

	void Update(sf::Time _deltaTime);

	//Might be unnecessary
	void OnMouseExit();
};