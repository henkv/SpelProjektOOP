#pragma once
#include "Entity.h"

class Totem
	: public Entity
{
	private:

	public:
	Totem();
	virtual ~Totem();

	void update(sf::Time deltaTime);
};

