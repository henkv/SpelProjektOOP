#include <iostream>
#include <string>
using namespace std;
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>


#include "Game.h"
#include "Totem.h"
#include "Player.h"
#include "AnimatedSprite.h"
#include "List.h"
#include "Food.h"






#define SCALE 2.f

int main()
{
	Game game;
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Food Get!");
	sf::View gameView(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x / SCALE, window.getSize().y / SCALE));
	sf::View uiView(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));

	sf::Font font;
	font.loadFromFile("Assets\\PressStart2P.ttf");

	sf::Text playerHunger;
	playerHunger.setFont(font);
	playerHunger.setCharacterSize(20);
	playerHunger.setPosition(sf::Vector2f(-100, -100));
	playerHunger.setString("Hunger~!");
	playerHunger.setColor(sf::Color::Red);

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

	game.setPlayer(player);

	sf::Texture foodT;
	foodT.loadFromFile("Assets\\Fruit.png");
	foodT.setSmooth(false);
	
	for (size_t i = 0; i < 100; i++)
	{
		Food* food = new Food();
		food->setKcal(rand() % 10);
		food->getSprite().setTexture(foodT);
		food->setHitbox(sf::FloatRect(12, 2, 18, 12));
		food->setPosition(sf::Vector2f(rand() % 800, rand() % 800));
		food->setOrigin(sf::Vector2f(17, 6));
		game.addFood(food);
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)  window.close();
			else if (event.type == sf::Event::Resized)
			{
				gameView.setSize(event.size.width / SCALE, event.size.height / SCALE);
				uiView.setSize(event.size.width, event.size.height);
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				player->setTargetPos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
			}
		}

		game.update(clock.restart());


		
		gameView.setCenter(player->getSprite().getPosition());
		window.setView(gameView);
		window.clear();
		window.draw(game);


		playerHunger.setString(player->getHungerString());
		window.setView(uiView);
		window.draw(playerHunger);

		window.display();
	}

	return 0;
}



//#include "WeightedMap.h"
//
//
//void main()
//{
//	int width = 1000;
//	int height = 1000;
//	WeightedMap map(width, height);
//	float x = 0;
//	float y = 0;
//
//	map.addMass(500, rand() % width, rand() % height);
//	map.addMass(500, rand() % width, rand() % height);
//	map.getCenterOfMass(x, y);
//	cout << "Center of Mass: " << x << ", " << y << endl;
//
//
//	for (size_t i = 0; i < 10; i++)
//	{
//		map.addMass(-100000000, x, y);
//		map.getCenterOfMass(x, y);
//		cout << "Center of Mass: " << x << ", " << y << endl;
//	}
//
//
//
//	system("pause");
//}