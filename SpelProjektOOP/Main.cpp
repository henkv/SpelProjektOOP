#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Totem.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "List.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	Game game;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Food Get!");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	sf::Texture maroWalk;
	maroWalk.loadFromFile("Assets\\mariowalks-sheet.png");

	Player* player = new Player();
	player->setHitbox(sf::FloatRect(-5, -10, 10, 10));
	player->getSprite().setTexture(maroWalk);
	player->getSprite().setFrameSize(sf::Vector2i(16, 32));
	player->getSprite().setOrigin(sf::Vector2f(8, 32));
	player->getSprite().setFrameDuration(sf::milliseconds(100));

	player->getSprite().addAnimation(sf::IntRect(0, 0, 8, 1));
	player->getSprite().addAnimation(sf::IntRect(0, 1, 8, 1));
	player->getSprite().addAnimation(sf::IntRect(0, 2, 8, 1));
	player->getSprite().addAnimation(sf::IntRect(0, 3, 8, 1));
	player->getSprite().addAnimation(sf::IntRect(0, 4, 8, 1));

	player->getSprite().setAnimation(0);

	Totem* totem = new Totem();
	totem->setHitbox(sf::FloatRect(20, 20, 10, 10));
	Totem* totem2 = new Totem();
	totem2->setHitbox(sf::FloatRect(28, 20, 10, 10));
	
	game.addEntity(player);
	game.addEntity(totem);
	game.addEntity(totem2);
	game.addEntity(totem2);
	game.addEntity(totem2);
	game.addEntity(totem2);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::Resized) gameView.setSize(event.size.width / 2.f, event.size.height / 2.f);
		}

		game.update(clock.restart());

		gameView.setCenter(player->getSprite().getPosition());
		gameView.move(sf::Vector2f(0, -16));

		window.setView(gameView);
		window.clear();
		window.draw(game);
		window.display();
	}

	return 0;
}
