#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include "LinkedList.h"
#include "Entity.h"
#include "Player.h"
#include "Food.h"

class Game :
	public sf::Drawable
{
	enum State { MAIN_MENU, PLAYING, GAME_OVER, HIGH_SCORE };

	private:
	Player* player;
	LinkedList<Food*> foodList;
	sf::Sprite map;
	State state;



	public:
	Game();
	~Game();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time deltaTime);

	void checkCollision(Entity* entityOne, Entity* entityTwo);

	void setPlayer(Player* player);
	void addFood(Food* food);

	sf::Sprite& getMap();




	void gameOver();
	void gameStart();


	void showMainMenu();

};

