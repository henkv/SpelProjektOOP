#include "Food.h"


Food::Food()
{}


Food::~Food()
{}

void Food::update(sf::Time deltaTime)
{

}

int Food::getKcal() const
{
	return kcal;
}
void Food::setKcal(int kcal)
{
	this->kcal = kcal;
}