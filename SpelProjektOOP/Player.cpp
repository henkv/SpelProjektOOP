#include "Player.h"
#include "SFML\Window\Keyboard.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Player::Player()
	: Creature()
{
	setSpeed(100.0f);
}


Player::~Player()
{}


void Player::update(sf::Time deltaTime)
{
	bool keyDown = false;
	sf::Vector2f direction;
	float radians = 0;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction.y -= 1;
		keyDown = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x -= 1;
		keyDown = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction.y += 1;
		keyDown = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x += 1;
		keyDown = true;
	}

	if (keyDown)
	{
		radians = atan2(direction.x, direction.y) + static_cast<float>(M_PI_2);
		direction.x = -cos(radians);
		direction.y = sin(radians);
		move(getSpeed() * direction * deltaTime.asSeconds());
	}

	//getSprite().playAnimation(deltaTime);
}

void Player::onCollisionEnter(const Entity& entity)
{
	std::cout << "Outch!\n";
}