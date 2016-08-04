#pragma once

class UserInputManager
{
public:
	std::string		m_enteredText;
	sf::Time		m_minTimeToScroll;
	sf::Time		m_timeMouseInScrollArea;
	bool			m_addedTime;
	float			m_scrollSpeed;

	UserInputManager();

	void			Update(sf::Time& _deltaTime);
	void			TextEnteredEvent(sf::Event& _event);
};