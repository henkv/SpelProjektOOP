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
	target.draw(sprite, states);

	sf::RectangleShape rect;
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(0.5f);
	rect.setSize(sf::Vector2f(hitbox.width, hitbox.height));
	rect.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	rect.setFillColor(sf::Color::Transparent);

	target.draw(rect);
	
}


void Entity::setSprite(sf::Sprite sprite)
{
	this->sprite = sprite;
}
void Entity::setHitbox(sf::FloatRect hitbox)
{
	this->hitbox = hitbox;
}

sf::Sprite& Entity::getSprite()
{
	return this->sprite;
}


size_t Entity::getId() const
{
	return this->id;
}


sf::FloatRect& Entity::getHitbox()
{
	return this->hitbox;
}


bool Entity::operator==(const Entity& entity) const
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

void Entity::setRotation(float angle)
{
	sprite.setRotation(angle);
}


void Entity::collisionStart(Entity* entity)
{
	if (collisionList.exists(entity))
	{
		onCollisionStay(entity);
	}
	else
	{
		std::cout << getId() << " srt col with " << entity->getId() << "\n";
		collisionList.add(entity);
		onCollisionEnter(entity);
	}
}
void Entity::collisionEnd(Entity* entity)
{
	if (collisionList.exists(entity))
	{
		std::cout << getId() << " end col with " << entity->getId() << "\n";
		collisionList.remove(entity);
		onCollisionExit(entity);
	}
}

void Entity::onCollisionEnter(const Entity* entity) {}
void Entity::onCollisionStay(const Entity* entity)  {}
void Entity::onCollisionExit(const Entity* entity)  {}
