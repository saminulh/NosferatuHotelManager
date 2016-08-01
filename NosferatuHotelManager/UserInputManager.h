#pragma once

class UserInputManager
{
public:
	std::string		m_enteredText;

	UserInputManager();

	void			Update(sf::Time _deltaTime);
	void			TextEnteredEvent(sf::Event& _event);
};