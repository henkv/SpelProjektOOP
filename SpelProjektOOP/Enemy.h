#pragma once
#include "Entity.h"


class Enemy :
	public Entity
{
	private:
	bool sleep_;
	float speed_;
	float aggroRadius_;
	sf::Vector2f targetPos_;

	public:
	Enemy();
	virtual ~Enemy();

	virtual void update(sf::Time const& deltaTime);
	virtual void onCollision(Entity& entity);
	
	float getSpeed() const;
	float getAggroRadius() const;

	void setSpeed(float speed);
	void setAggroRadius(float aggroRadius);
	void setTargetPos(sf::Vector2f const& targetPos);


};

