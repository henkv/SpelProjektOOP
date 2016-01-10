#pragma once
#include "Entity.h"

class Particle :
	public Entity
{
	private:
	float velocity_;
	
	sf::Time age_;
	sf::Time duration_;
	sf::Vector2f direction_;

	public:
	Particle();
	virtual ~Particle();

	void update(sf::Time const& deltaTime);

	float velocity() const;
	sf::Time const& age() const;
	sf::Time const& duration() const;
	sf::Vector2f const& direction() const;

	void velocity(float _velocity);
	void age(sf::Time const& _age);
	void duration(sf::Time const& _duration);
	void direction(sf::Vector2f const& _direction);
};

