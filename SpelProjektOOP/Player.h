#pragma once
#include "Creature.h"
#include "Food.h"

class Player :
	public Creature
{
	private:
	float hunger;
	sf::Vector2f targetPos;
	bool goToTarget;

	public:
	Player();
	virtual ~Player();

	void update(sf::Time deltaTime);

	void eat(Food* food);
	void setTargetPos(sf::Vector2f targetPos);


	void setHunger(float hunger);
	float getHunger() const;
	string getHungerString() const;

	void onCollisionEnter(Entity* entity);
	void onCollisionStay(Entity* entity);
	void onCollisionExit(Entity* entity);
};

