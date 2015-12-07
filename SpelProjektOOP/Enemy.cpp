#include "Enemy.h"
#include <iostream>
using namespace std;



Enemy::Enemy()
{
	sleep_ = true;
	speed_ = 0.0f;
	aggroRadius_ = 0.0f;
}
Enemy::~Enemy()
{}


void Enemy::update(sf::Time const& deltaTime)
{
	if (!sleep_)
	{
		sf::Vector2f deltaPos = targetPos_ -  getPosition();
		float distance = sqrtf(powf(deltaPos.x, 2.0f) + powf(deltaPos.y * 2.f, 2.0f));

		if (distance < aggroRadius_ && distance > 1.0f)
		{
			float radians = atan2(deltaPos.y, deltaPos.x);
			sf::Vector2f direction(cos(radians), sin(radians));
			move(direction * speed_ * deltaTime.asSeconds());
		}
		else
		{
			sleep_ = true;
		}
	}


}
void Enemy::onCollision(Entity& entity)
{
	entity.pushEvent(Entity::Event::DEATH);
}


float Enemy::getSpeed() const
{
	return speed_;
}
float Enemy::getAggroRadius() const
{
	return aggroRadius_;
}


void Enemy::setSpeed(float speed)
{
	speed_ = speed;
}
void Enemy::setAggroRadius(float aggroRadius)
{
	aggroRadius_ = aggroRadius;
}
void Enemy::setTargetPos(sf::Vector2f const& targetPos)
{
	sleep_ = false;
	targetPos_ = targetPos;
}
