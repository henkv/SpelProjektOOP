#include "Food.h"



Food::Food()
{
	kcal_ = 0;
}

Food::~Food()
{}



void Food::update(sf::Time const& deltaTime)
{}



int Food::getKcal() const
{
	return kcal_;
}

void Food::setKcal(int kcal)
{
	kcal_ = kcal;
}
