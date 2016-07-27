// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "AnimationClass.h"

DebugLogManager debug;

void Init()
{
	debug.Start();

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);


	Animation anim;
	anim.LoadAnimation("testAnim.xml");








	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
}

int main()
{
	Init();

    return 0;
}

