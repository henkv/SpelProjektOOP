#include "Entity.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include <iostream>

size_t Entity::nextId = 0;

Entity::Entity()
{
	this->id = this->nextId++;
}


Entity::~Entity()
{}


void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(this->sprite, states);

	sf::RectangleShape rect;
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(0.5f);
	rect.setSize(sf::Vector2f(hitbox.height, hitbox.width));
	rect.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	rect.setFillColor(sf::Color::Transparent);

	target.draw(rect);
	
}


void Entity::onCollision(const Entity& entity) 
{}


void Entity::setState(int state)
{
	this->state = state;
}


sf::Sprite& Entity::getSprite()
{
	return this->sprite;
}


const sf::Sprite& Entity::getSprite() const
{
	return this->sprite;
}


size_t Entity::getId() const
{
	return this->id;
}


int Entity::getState() const
{
	return this->state;
}


sf::FloatRect& Entity::getHitbox()
{
	return this->hitbox;
}


const sf::FloatRect& Entity::getHitbox() const
{
	return this->hitbox;
}


bool Entity::operator=(const Entity& entity) const
{
	return this->id == entity.id;
}

bool Entity::operator<(const Entity& entity) const
{
	return this->id < entity.id;
}

bool Entity::operator>(const Entity& entity) const
{
	return this->id > entity.id;
}

void Entity::move(float offsetX, float offsetY)
{
	this->hitbox.left += offsetX;
	this->hitbox.top += offsetY;
	this->sprite.move(offsetX, offsetY);
}
void Entity::move(const sf::Vector2f &offset)
{
	this->hitbox.left += offset.x;
	this->hitbox.top += offset.y;
	this->sprite.move(offset);
}