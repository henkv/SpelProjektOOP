#include "Particle.h"


Particle::Particle()
{
	velocity_ = 0.f;
}


Particle::~Particle()
{}


void Particle::update(sf::Time const& deltaTime)
{
	age_ += deltaTime;

	if (age_ < duration_)
	{
		getSprite().setPosition(getPosition() + (direction_ * velocity_ * age_.asSeconds()));
	}
	else
	{
		pushEvent(DEATH);
	}
}

float Particle::velocity() const
{
	return velocity_;
}
sf::Time const& Particle::age() const
{
	return age_;
}
sf::Time const& Particle::duration() const
{
	return duration_;
}
sf::Vector2f const& Particle::direction() const
{
	return direction_;
}

void Particle::velocity(float _velocity)
{
	velocity_ = _velocity;
}
void Particle::age(sf::Time const& _age)
{
	age_ = _age;
}
void Particle::duration(sf::Time const& _duration)
{
	duration_ = _duration;
}
void Particle::direction(sf::Vector2f const& _direction)
{
	direction_ = _direction;
}