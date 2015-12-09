#include <crtdbg.h>
#include <iostream>
using namespace std;

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include "Game.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	sf::RenderWindow window(sf::VideoMode(800, 800), "Sandbox");

	Game game;
	sf::Clock clock;
	sf::Event event;


	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed: 
					window.close(); 
					break;

				case sf::Event::Resized: 
					break;
			}
		}

		game.setMousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		game.update(clock.restart());

		window.clear();
		window.draw(game);
		window.display();
	}
	


	return 0;
}