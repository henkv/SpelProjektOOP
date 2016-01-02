#include "Enemy.h"
#include <iostream>
using namespace std;



Enemy::Enemy()
{
	sleep_ = true;
	wakingUp_ = false;

	speed_ = 0.0f;
	aggroRadius_ = 0.0f;

	wakeUpAnimation_.setObserver(this);

	state_ = SLEEPING;
}

Enemy::Enemy(Enemy const& copy)
{
	state_ = copy.state_;
	speed_ = copy.speed_;
	aggroRadius_ = copy.aggroRadius_;
	wakeUpAnimation_ = copy.wakeUpAnimation_;
	wakeUpAnimation_.setObserver(this);
}

Enemy::~Enemy()
{}

Enemy& Enemy::operator=(Enemy const& copy)
{
	state_ = copy.state_;
	speed_ = copy.speed_;
	aggroRadius_ = copy.aggroRadius_;
	wakeUpAnimation_ = copy.wakeUpAnimation_;
	wakeUpAnimation_.setObserver(this);

	return *this;
}

void Enemy::update(sf::Time const& deltaTime)
{
	switch (state_)
	{
		case Enemy::WAKING_UP:
		case Enemy::GOING_TO_SLEEP:
			//wakeUpAnimation_.playAnimation(deltaTime);
			break;

		case Enemy::MOVING:
			sf::Vector2f deltaPos = targetPos_ - getPosition();
			float radians = atan2(deltaPos.y, deltaPos.x);
			sf::Vector2f direction(cos(radians), sin(radians));
			move(direction * speed_ * deltaTime.asSeconds());
			break;
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
	targetPos_ = targetPos;

	sf::Vector2f deltaPos = targetPos_ - getPosition();
	float distance = sqrtf(powf(deltaPos.x, 2.0f) + powf(deltaPos.y * 2.f, 2.0f));

	switch (state_)
	{
		case Enemy::MOVING:
		case Enemy::WAKING_UP:
			if (distance > aggroRadius_)
			{
				state_ = GOING_TO_SLEEP;
				wakeUpAnimation_.setReverse(true);
			}
			break;

		case Enemy::SLEEPING:
		case Enemy::GOING_TO_SLEEP:
			if (distance < aggroRadius_)
			{
				state_ = WAKING_UP;
				wakeUpAnimation_.setReverse(false);
			}
			break;
	}
}


ostream& operator<<(ostream& out, sf::IntRect rect)
{
	out << "( " << rect.left << ", " << rect.top << ", " << rect.width << ", " << rect.height << " )";
	return out;
}

void Enemy::onNotify(Animation::Event event, Animation* caller)
{
	switch (event)
	{
		case Animation::NEW_FRAME:
			//getSprite().setTextureRect(wakeUpAnimation_.getFrameRect());
			cout << caller << " NEW_FRAME " << wakeUpAnimation_.getFrameRect() << endl;
			break;

		case Animation::END:
			state_ = MOVING;
			getSprite().setTextureRect(sf::IntRect(0, 0, 10, 20));
			cout << caller << " END" << endl;
			break;

		case Animation::END_REVERSE:
			state_ = SLEEPING;
			cout << caller << " END_REVERSE" << endl;
			break;
	}
}

Animation& Enemy::getWakeUpAnimation()
{
	return wakeUpAnimation_;
}