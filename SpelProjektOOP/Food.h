#pragma once
#include "Entity.h"

class Food :
	public Entity
{
	private:
	int kcal;

	public:
	Food();
	virtual ~Food();

	void update(sf::Time deltaTime);

	int getKcal() const;
	void setKcal(int kcal);
};

