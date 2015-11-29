#include "Player.h"
#include "SFML\Window\Keyboard.hpp"
#include "AnimatedSprite.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "SFML\Graphics\Texture.hpp"
#include "SFML\Window\Mouse.hpp"
#include "Game.h"

Player::Player()
	: Creature()
{
	setSpeed(100.0f);

}


Player::~Player()
{
}


void Player::update(sf::Time deltaTime)
{
	bool keyDown = false;
	sf::Vector2f direction;
	
	if		(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { direction.y =  1; keyDown = true; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { direction.y = -1; keyDown = true; }

	if		(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { direction.x = -1; keyDown = true; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { direction.x =  1; keyDown = true; }

	if (keyDown)
	{
		float radians = atan2(direction.x, direction.y);
		direction.x = sin(radians);
		direction.y = -cos(radians);
		move(getSpeed() * direction * deltaTime.asSeconds());

		float degs = radians * 180 / M_PI;
		float absDegs = abs(degs);
		int anim = getSprite().getAnimation();

		if		(absDegs < 22.5f)  { if (anim != 4) getSprite().setAnimation(4); }
		else if (absDegs < 67.5f)  { if (anim != 3) getSprite().setAnimation(3); }
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
	hunger += food->getKcal();
	food->setScale(sf::Vector2f(0.25f, 0.25f));
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
