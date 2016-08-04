// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AnimationClass.h"

#include "Button.h"
#include "ButtonActions.h"

#include "Utilities.h"

DebugLogManager		debug;
GraphicsManager		graphicsManager;
AudioManager		audioManager;
ScreensManager		screensManager;
GUIManager			guiManager;
ActivityManager		activityManager;
NPCManager			npcManager;

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

	guiManager.GetButtonsMap().insert(std::pair<std::string, Button>("TEST!", button));
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button>("Play", playButton));
	guiManager.GetButtonsMap().insert(std::pair<std::string, Button>("Settings", settingsButton));

	//Restart timer so that it's zero when the window actually starts
	screensManager.m_timer.restart();
	while (screensManager.GetWindow().isOpen())
	{
		screensManager.m_elapsedTime += screensManager.m_timer.restart().asSeconds();
		if (screensManager.m_elapsedTime >= screensManager.m_timePerFrame)
		{
			screensManager.m_elapsedTime -= screensManager.m_timePerFrame;

		sf::Event event;
		while (screensManager.GetWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				screensManager.GetWindow().close();
		}

			screensManager.m_mousePos = sf::Mouse::getPosition(screensManager.GetWindow());

			vampLoading.Update(sf::seconds(screensManager.m_timePerFrame));

			Utilities::Update();

			guiManager.Update();

			/*********** Clear the screen ******************/
		screensManager.GetWindow().clear();


			screensManager.GetWindow().draw(testBackground);
			screensManager.GetWindow().draw(vampLoading.GetSprite());

			/*********** Draw the GUI to the screen ******************/
			guiManager.DrawToWindow();

			/*********** Display the screen ******************/
		screensManager.GetWindow().display();
	}
}
}

int main()
{
	Init();

    return 0;
}

