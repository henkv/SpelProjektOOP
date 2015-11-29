#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Totem.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "List.h"
#include <iostream>
#include <string>
#include "Food.h"
using namespace std;



int main()
{
	Game game;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Food Get!");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));


	sf::Texture mapBg;
	mapBg.loadFromFile("Assets\\wallhaven-151737.jpg");
	mapBg.setSmooth(false);

	game.getMap().setTexture(mapBg);
	game.getMap().setOrigin(1920 / 2, 1080 / 2);

	sf::Texture maroWalk;
	maroWalk.loadFromFile("Assets\\mariowalks-sheet.png");
	maroWalk.setSmooth(false);
	
	AnimatedSprite playerSprite;
	playerSprite.setTexture(maroWalk);
	playerSprite.setFrameSize(sf::Vector2i(16, 32));
	playerSprite.setFrameDuration(sf::milliseconds(100));
	playerSprite.addAnimation(sf::IntRect(0, 0, 8, 1));
	playerSprite.addAnimation(sf::IntRect(0, 1, 8, 1));
	playerSprite.addAnimation(sf::IntRect(0, 2, 8, 1));
	playerSprite.addAnimation(sf::IntRect(0, 3, 8, 1));
	playerSprite.addAnimation(sf::IntRect(0, 4, 8, 1));
	playerSprite.setAnimation(0);

	Player* player = new Player();
	player->setHitbox(sf::FloatRect(2, 26, 12, 6));
	player->setSprite(playerSprite);
	player->setOrigin(sf::Vector2f(8, 16));

	game.addEntity(player);


	sf::Texture foodT;
	foodT.loadFromFile("Assets\\Fruit.png");
	foodT.setSmooth(false);




	for (size_t i = 0; i < 10; i++)
	{
		Food* food = new Food();
		food->getSprite().setTexture(foodT);
		food->setHitbox(sf::FloatRect(12, 2, 18, 12));
		food->setPosition(sf::Vector2f(rand() % 300, rand() % 300));
		food->setOrigin(sf::Vector2f(17, 6));
		game.addEntity(food);
	}

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

		window.setView(gameView);
		window.clear();
		window.draw(game);
		window.display();
	}

	return 0;
}
