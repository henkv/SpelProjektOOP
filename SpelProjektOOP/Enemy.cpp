#include "Enemy.h"
#include <iostream>
using namespace std;



Enemy::Enemy()
{
	state_ = SLEEP;
	sleep_ = true;
	speed_ = 0.0f;
	aggroRadius_ = 0.0f;
}
Enemy::~Enemy()
{}

Enemy& Enemy::operator=(Enemy const& enemy)
{
	Entity::operator=(enemy);
	state_ = enemy.state_;
	sleep_ = enemy.sleep_;
	speed_ = enemy.speed_;
	aggroRadius_ = enemy.aggroRadius_;
	targetPos_ = enemy.targetPos_;
	animation_ = enemy.animation_;
	animation_.setObserver(this);

	return *this;
}

void Enemy::update(sf::Time const& deltaTime)
{
	sf::Vector2f deltaPos, direction;
	float radians;

	switch (state_)
	{
		case Enemy::SLEEP:
			break;

		case Enemy::WALK:
			deltaPos = targetPos_ - getPosition();
			radians = atan2(deltaPos.y, deltaPos.x);
			direction.x = cos(radians);
			direction.y = sin(radians);
			move(direction * speed_ * deltaTime.asSeconds());
			break;

		case Enemy::WAKE:
			animation_.playAnimation(deltaTime);
			break;

		case Enemy::RETIER:
			animation_.playAnimationReverse(deltaTime);
			break;

		default:
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

Animation& Enemy::getAnimation()
{
	return animation_;
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
		case Enemy::RETIER:
		case Enemy::SLEEP:
			if (distance < aggroRadius_) state_ = WAKE;
			break;

		case Enemy::WAKE:
		case Enemy::WALK:
			if (distance > aggroRadius_) state_ = RETIER;
			break;
	}
}


void Enemy::onNotify(Animation::Event event, Animation* caller)
{

	switch (event)
	{
		case Animation::NEW_FRAME:
			cout << "Event: NEW_FRAME" << endl;
			break;
		case Animation::END:
			cout << "Event: END" << endl;
			break;
		case Animation::END_REVERSE:
			cout << "Event: END_REVERSE" << endl;
			break;
		case Animation::LAST_FRAME:
			cout << "Event: LAST_FRAME" << endl;
			break;
		case Animation::FIRST_FRAME:
			cout << "Event: FIRST_FRAME" << endl;
			break;
		default:
			cout << "Event: " << event << endl;
			break;
	}
	switch (event)
	{
		case Animation::NEW_FRAME:
			getSprite().setTextureRect(animation_.getFrameRect());
			break;
		case Animation::END:
			state_ = WALK;
			animation_.setFrame(sf::Vector2i(19, 0));
			break;
		case Animation::END_REVERSE:
			state_ = SLEEP;
			animation_.setFrame(sf::Vector2i(0, 0));
			break;
	}
}