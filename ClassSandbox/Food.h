#pragma once
#include "Entity.h"
class Food :
	public Entity
{
	private:
	int kcal_;

	public:
	Food();
	virtual ~Food();

	virtual void update(sf::Time const& deltaTime);

	int getKcal() const;
	void setKcal(int kcal);
};

