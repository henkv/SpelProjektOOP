#pragma once
#include "Creature.h"
#include "Food.h"

class Player :
	public Creature
{
	private:
	int hunger;

	public:
	Player();
	virtual ~Player();

	void update(sf::Time deltaTime);

	void eat(Food* food);

	void onCollisionEnter(Entity* entity);
	void onCollisionStay(Entity* entity);
	void onCollisionExit(Entity* entity);
};

