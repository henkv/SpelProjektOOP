#pragma once
#include "Entity.h"
#include "Animation.h"

class Enemy :
	public Entity,
	public Animation::Observer
{
	private:
	enum State {WAKING_UP, MOVING, GOING_TO_SLEEP, SLEEPING};
	State state_;

	bool sleep_;
	float speed_;
	float aggroRadius_;
	sf::Vector2f targetPos_;

	bool wakingUp_;
	Animation wakeUpAnimation_;

	public:
	Enemy();
	Enemy(Enemy const& copy);
	virtual ~Enemy();

	Enemy& operator=(Enemy const& copy);

	virtual void update(sf::Time const& deltaTime);
	virtual void onCollision(Entity& entity);
	
	float getSpeed() const;
	float getAggroRadius() const;
	
	Animation& getWakeUpAnimation();

	void setSpeed(float speed);
	void setAggroRadius(float aggroRadius);
	void setTargetPos(sf::Vector2f const& targetPos);

	void onNotify(Animation::Event, Animation*);
};

