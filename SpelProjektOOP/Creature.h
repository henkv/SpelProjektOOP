#pragma once
#include "Entity.h"

class Creature
	: public Entity
{
	private:
	int health;
	float speed;

	public:
	Creature();
	virtual ~Creature();

	virtual void update(sf::Time deltaTime) = 0;

	int getHealth() const;
	float getSpeed() const;

	void setHealth(int health);
	void setSpeed(float speed);

};

