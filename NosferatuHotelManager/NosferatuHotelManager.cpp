// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AnimationClass.h"

#include "Button.h"
#include "ButtonActions.h"

DebugLogManager debug;
GraphicsManager graphicsManager;
AudioManager	audioManager;
ScreensManager	screensManager;

void Init()
{
	debug.Start();

	srand((unsigned int)time(NULL));


	Animation anim;
	anim.LoadAnimation("testAnim.vAnim");

	Animation	vampLoading;
	vampLoading.LoadAnimation("VampLoadingAnim.vAnim");
	graphicsManager.LoadTexture("HotelEntrance.png");

	sf::Sprite testBackground;
	testBackground.setTexture(graphicsManager.GetTexturesMap()["HotelEntrance.png"]);

	vampLoading.BeginAnimation("VampLoadingAnim.vAnim");
	vampLoading.GetSprite().setPosition(400, 230);


	std::vector<std::string> tempButtonAnims;
	tempButtonAnims.push_back("testButtonDefaultAnim.vAnim");
	tempButtonAnims.push_back("testButtonMouseOverAnim.vAnim");
	tempButtonAnims.push_back("testButtonMouseClickedAnim.vAnim");


	void(*testOnClick)(void);
	testOnClick = &ButtonActions::TestButtonAction;

	Button button;
	button.CreateButton("TEST!", tempButtonAnims, sf::Vector2f(50, 50), testOnClick, sf::Vector2f(40,15));
	button.GetSprite().setScale((float)1.5, (float)1.5);

	Button playButton;
	playButton.CreateButton("Play", tempButtonAnims, sf::Vector2f(50, 150), testOnClick, sf::Vector2f(40, 15));
	playButton.GetSprite().setScale((float)1.5, (float)1.5);

	Button settingsButton;
	settingsButton.CreateButton("Settings", tempButtonAnims, sf::Vector2f(50, 250), testOnClick, sf::Vector2f(40, 15));
	settingsButton.GetSprite().setScale((float)1.5, (float)1.5);

	sf::Clock timer;
	
	float elapsedTime = 0;
	while (screensManager.GetWindow().isOpen())
	{
		elapsedTime += timer.restart().asSeconds();
		if (elapsedTime >= screensManager.m_timePerFrame)
		{
			elapsedTime -= screensManager.m_timePerFrame;

			sf::Event event;
			while (screensManager.GetWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					screensManager.GetWindow().close();
			}

			screensManager.m_mousePos = sf::Mouse::getPosition(screensManager.GetWindow());

			vampLoading.Update(sf::seconds(screensManager.m_timePerFrame));

			//Test button
			button.Update(sf::seconds(screensManager.m_timePerFrame));
			//Play button
			playButton.Update(sf::seconds(screensManager.m_timePerFrame));
			//Settings button
			settingsButton.Update(sf::seconds(screensManager.m_timePerFrame));

			screensManager.GetWindow().clear();
			screensManager.GetWindow().draw(testBackground);
			screensManager.GetWindow().draw(vampLoading.GetSprite());

			//Test button
			screensManager.GetWindow().draw(button.GetSprite());
			
			screensManager.GetWindow().draw(button.GetButtonText().GetOutlineTopRight());
			screensManager.GetWindow().draw(button.GetButtonText().GetOutlineTopLeft());
			screensManager.GetWindow().draw(button.GetButtonText().GetOutlineBottomRight());
			screensManager.GetWindow().draw(button.GetButtonText().GetOutlineBottomLeft());
			screensManager.GetWindow().draw(button.GetButtonText().GetMainText());


			//Play button
			screensManager.GetWindow().draw(playButton.GetSprite());

			screensManager.GetWindow().draw(playButton.GetButtonText().GetOutlineTopRight());
			screensManager.GetWindow().draw(playButton.GetButtonText().GetOutlineTopLeft());
			screensManager.GetWindow().draw(playButton.GetButtonText().GetOutlineBottomRight());
			screensManager.GetWindow().draw(playButton.GetButtonText().GetOutlineBottomLeft());
			screensManager.GetWindow().draw(playButton.GetButtonText().GetMainText());


			//Settings button
			screensManager.GetWindow().draw(settingsButton.GetSprite());

			screensManager.GetWindow().draw(settingsButton.GetButtonText().GetOutlineTopRight());
			screensManager.GetWindow().draw(settingsButton.GetButtonText().GetOutlineTopLeft());
			screensManager.GetWindow().draw(settingsButton.GetButtonText().GetOutlineBottomRight());
			screensManager.GetWindow().draw(settingsButton.GetButtonText().GetOutlineBottomLeft());
			screensManager.GetWindow().draw(settingsButton.GetButtonText().GetMainText());

			screensManager.GetWindow().display();
		}
	}
}

int main()
{
	Init();

	return 0;
}

