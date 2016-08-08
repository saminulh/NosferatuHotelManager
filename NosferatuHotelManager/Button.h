#pragma once
#include "TextStruct.h"
#include "AnimationClass.h"

//This will be the basic button class that will be managed by the GUI manager
class Button : public Animation
{
protected:
	CustomText				m_buttonText;
	std::string				m_defaultButtonAnim;
	std::string				m_mouseOverButtonAnim;
	std::string				m_mouseClickedButtonAnim;
	bool					m_isSelected;
	void					(*m_onClickFunction)(void);
	sf::Time				m_timeSinceToggle;
	sf::Time				m_timeBetweenToggles;

public:
	Button();
	~Button();

	virtual void			CreateButton(std::string _text, std::vector<std::string>& _animationsList, sf::Vector2f _pos, void (*_onClickFunction)(void), 
										sf::Vector2f _relativeTextPos = sf::Vector2f(10.f, 10.f));

	virtual void			OnMouseOver();
	virtual void			OnMouseClick();

	//Used for tooltips, etc.
	virtual void			OnMouseHover();
	
	virtual void			UpdateTick(bool _newStatus);
	virtual void			Update(sf::Time& _deltaTime);
	//Might be unnecessary
	virtual void			OnMouseExit();

	virtual unsigned int	GetMaxEnterableChars();

	//Virtual function stub for text fields - don't remove
	virtual bool			IsBeingEdited();
	virtual CustomText&		GetButtonText();
};