#pragma once
#include "Entity.h"
#include "Animation.h"


class Enemy :
	public Entity,
	public Animation::Observer
{
	private:
	enum State { SLEEP, WALK, WAKE, RETIER };
	State state_;
	bool sleep_;

	float speed_;
	float aggroRadius_;
	sf::Vector2f targetPos_;

	Animation animation_;

	public:
	Enemy();
	virtual ~Enemy();

	Enemy& operator=(Enemy const& enemy);

	virtual void update(sf::Time const& deltaTime);
	virtual void onCollision(Entity& entity);
	
	float getSpeed() const;
	float getAggroRadius() const;

	Animation& getAnimation();

	void setSpeed(float speed);
	void setAggroRadius(float aggroRadius);
	void setTargetPos(sf::Vector2f const& targetPos);

	void onNotify(Animation::Event, Animation*);
};

