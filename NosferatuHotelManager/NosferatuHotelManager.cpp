// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "AnimationClass.h"

DebugLogManager debug;
GraphicsManager graphicsManager;
AudioManager	audioManager;
ScreensManager	screensManager;
ActivityManager activityManager;

void Init()
{
	debug.Start();

	srand((unsigned int)time(NULL));

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	Animation anim;
	anim.LoadAnimation("testAnim.xml");








	while (screensManager.GetWindow().isOpen())
	{
		sf::Event event;
		while (screensManager.GetWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				screensManager.GetWindow().close();
		}

		screensManager.GetWindow().clear();
		screensManager.GetWindow().draw(shape);
		screensManager.GetWindow().display();
	}
}

int main()
{
	Init();

    return 0;
}

