#include "Player.h"
#include "SFML\Window\Keyboard.hpp"
#include <iostream>

Player::Player()
	: Creature()
{
	setSpeed(20.0f);
}


Player::~Player()
{}


void Player::update(sf::Time deltaTime)
{
	sf::Vector2f direction;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		direction.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		direction.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		direction.y += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		direction.x += 1;
	}

	move(getSpeed() * direction * deltaTime.asSeconds());
}

void Player::onCollision(const Entity& entity)
{
	std::cout << "Outch!\n";
}