#include "Player.h"



Player::Player()
{
}

Player::~Player()
{}



void Player::update(sf::Time const& deltaTime)
{
	
}

void Player::onCollision(Entity& entity)
{
	entity.pushEvent(Entity::Event::DEATH);
}