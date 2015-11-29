#pragma once
#include "Creature.h"

class Player :
	public Creature
{
	private:
	int hunger;

	public:
	Player();
	virtual ~Player();

	void update(sf::Time deltaTime);

	void onCollisionEnter(Entity* entity);
	void onCollisionStay(Entity* entity);
	void onCollisionExit(Entity* entity);

};

