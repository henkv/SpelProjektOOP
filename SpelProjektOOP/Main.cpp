#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Totem.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "List.h"
#include <iostream>
using namespace std;

int main()
{
	Game game;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setView(sf::View(sf::FloatRect(0, 0, 400, 400)));

	Player* player = new Player();
	player->setHitbox(sf::FloatRect(0, 0, 10, 10));

	Totem* totem = new Totem();
	totem->setHitbox(sf::FloatRect(20,20,10, 10));
	
	game.addEntity(player);
	game.addEntity(totem);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		game.update(clock.restart());
		window.clear();
		window.draw(game);
		window.display();
	}

	return 0;
}