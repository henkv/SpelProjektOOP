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
	sf::Clock clock;
	sf::Event event;

	Game game;

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
					//game.setWindowSize(sf::Vector2f(event.size.width, event.size.height));
					break;

				case sf::Event::MouseButtonPressed:
					game.setMousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
					
					break;
			}
		}

		game.update(clock.restart());

		window.clear();
		window.draw(game);
		window.display();
	}
	


	return 0;
}