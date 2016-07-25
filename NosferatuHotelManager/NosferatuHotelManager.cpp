// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//This will be the entry point of the program.
//There should be no code here except calling
// the 'real' main function

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

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

	//Test stuff

    return 0;
}