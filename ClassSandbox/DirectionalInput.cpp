#include "DirectionalInput.h"
#include <cmath>


DirectionalInput::DirectionalInput()
{
	upKey_ = sf::Keyboard::W;
	downKey_ = sf::Keyboard::S;
	leftKey_ = sf::Keyboard::A;
	rightKey_ = sf::Keyboard::D;
}

DirectionalInput::~DirectionalInput()
{}



sf::Vector2f const& DirectionalInput::getInput() const
{
	bool keyDown = false;
	sf::Vector2f direction;

	if (sf::Keyboard::isKeyPressed(upKey_))
	{
		direction.y = -1;
		keyDown = true;
	}
	else if (sf::Keyboard::isKeyPressed(downKey_))
	{
		direction.y = 1;
		keyDown = true;
	}

	if (sf::Keyboard::isKeyPressed(leftKey_))
	{
		direction.x = -1;
		keyDown = true;
	}
	else if (sf::Keyboard::isKeyPressed(rightKey_))
	{
		direction.x = 1;
		keyDown = true;
	}

	if (keyDown)
	{
		float radians = atan2(direction.y, direction.x);
		direction.x = cos(radians);
		direction.y = sin(radians);
	}

	return direction;
}