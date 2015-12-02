#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>

#include <SFML\Graphics\Texture.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Graphics\CircleShape.hpp>

#include "AnimatedSprite.h"
#include "Player.h"
#include "Game.h"



Player::Player()
	: Creature()
{
	setSpeed(100.0f);
	goToTarget = false;
	hunger = 90.0f;
}


Player::~Player()
{
}


void Player::update(sf::Time deltaTime)
{
	hunger += deltaTime.asSeconds();

	bool keyDown = false;
	sf::Vector2f direction;
	
	if		(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { direction.y =  1; keyDown = true; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { direction.y = -1; keyDown = true; }

	if		(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { direction.x = -1; keyDown = true; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { direction.x =  1; keyDown = true; }

	if (keyDown)
	{
		goToTarget = false;
		float radians = atan2(direction.x, direction.y);
		direction.x = sin(radians);
		direction.y = -cos(radians);
		move(getSpeed() * direction * deltaTime.asSeconds());

		float degs = radians * 180 / M_PI;
		float absDegs = abs(degs);
		int anim = getSprite().getAnimation();

		if		(absDegs <  22.5f) { if (anim != 4) getSprite().setAnimation(4); }
		else if (absDegs <  67.5f) { if (anim != 3) getSprite().setAnimation(3); }
		else if (absDegs < 112.5f) { if (anim != 2) getSprite().setAnimation(2); }
		else if (absDegs < 157.5f) { if (anim != 1) getSprite().setAnimation(1); }
		else					   { if (anim != 0) getSprite().setAnimation(0); }

		if (degs < 0) { setScale(sf::Vector2f(-1, 1)); }
		else		  { setScale(sf::Vector2f( 1, 1)); }

		getSprite().playAnimation(deltaTime);
	}
}

void Player::eat(Food* food)
{
	hunger -= food->getKcal();
	food->addEvent("DEATH");
}


void Player::setTargetPos(sf::Vector2f targetPos)
{
	this->targetPos = targetPos;
	goToTarget = true;
}



void Player::setHunger(float hunger)
{
	this->hunger = hunger;
}

float Player::getHunger() const
{
	return hunger;
}
string Player::getHungerString() const
{
	stringstream stream;
	stream << hunger;
	return stream.str();
}


void Player::onCollisionEnter(Entity* entity)
{
	Food* food = dynamic_cast<Food*>(entity);
	if (food != nullptr)
	{
		eat(food);
		std::cout << "Yum!\n";
	}
	else
	{
		std::cout << "Outch!\n";
	}
}
void Player::onCollisionStay(Entity* entity) 
{
	//std::cout << "!";
}
void Player::onCollisionExit(Entity* entity)
{
	Food* food = dynamic_cast<Food*>(entity);
	if (food == nullptr)
	{
		std::cout << "Whew!\n";
	}
}
