#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "LinkedList.h"
#include "Entity.h"
#include "Player.h"
#include "Food.h"

class Game :
	public sf::Drawable
{
	private:
	Player* player;
	LinkedList<Food*> foodList;

	sf::Sprite map;

	public:
	Game();
	~Game();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time deltaTime);

	void checkCollision(Entity* entityOne, Entity* entityTwo);

	void setPlayer(Player* player);
	void addFood(Food* food);

	sf::Sprite& getMap();

};

