#pragma once
#include "Entity.h"
class Player :
	public Entity
{
	private:

	public:
	Player();
	virtual ~Player();

	virtual void update(sf::Time const& deltaTime);
	virtual void onCollision(Entity& entity);
};

