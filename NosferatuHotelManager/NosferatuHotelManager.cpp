// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "AnimationClass.h"

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


	sf::Clock timer;
	const float timePerFrame = 1 / 30.f;
	float elapsedTime = 0;
	while (screensManager.GetWindow().isOpen())
	{
		elapsedTime += timer.restart().asSeconds();
		if (elapsedTime >= timePerFrame)
		{
			elapsedTime -= timePerFrame;

			sf::Event event;
			while (screensManager.GetWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					screensManager.GetWindow().close();
			}

			vampLoading.Update(sf::seconds(timePerFrame));

			screensManager.GetWindow().clear();
			screensManager.GetWindow().draw(testBackground);
			screensManager.GetWindow().draw(vampLoading.GetSprite());
			screensManager.GetWindow().display();
		}
	}
}

int main()
{
	Init();

	return 0;
}

