#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Totem.h"
#include "Player.h"

int main()
{
	Game game;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML works!");


	sf::Texture face;
	face.loadFromFile("Assets\\PlayerFace.png");
	sf::Texture totemPng;
	totemPng.loadFromFile("Assets\\totem.png");



	Player* player = new Player();
	player->getSprite().setTexture(face);
	player->getHitbox().height = 20;
	player->getHitbox().width = 20;

	Totem* totem = new Totem();
	totem->getSprite().setTexture(totemPng);
	totem->getHitbox().height = 50;
	totem->getHitbox().width = 20;

	totem->move(50.0f, 50.0f);

	game.addEntity(totem);
	game.addEntity(player);

	window.setView(sf::View(sf::FloatRect(0, 0, 200, 100)));


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