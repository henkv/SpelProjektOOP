#include "Creature.h"


Creature::Creature()
	: Entity()
{}


Creature::~Creature()
{
	
}


int Creature::getHealth() const
{
	return health;
}
float Creature::getSpeed() const
{
	return speed;
}

void Creature::setHealth(int health)
{
	this->health = health;
}
void Creature::setSpeed(float speed)
{
	this->speed = speed;
}