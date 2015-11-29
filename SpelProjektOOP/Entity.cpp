#include "Entity.h"
#include "SFML\Graphics\RectangleShape.hpp"
#include <iostream>

#define DEBUG


size_t Entity::nextId = 0;

Entity::Entity()
{
	this->id = this->nextId++;
}
Entity::~Entity()
{}

void Entity::draw(sf::RenderTarget &target, 
				  sf::RenderStates states) const
{
	target.draw(sprite, states);


	#ifdef DEBUG

	sf::RectangleShape origin;
	origin.setFillColor(sf::Color::Green);
	origin.setSize(sf::Vector2f(1, 1));
	origin.setPosition(transform.getPosition());
	origin.setFillColor(sf::Color::Magenta);

	target.draw(origin);

	sf::RectangleShape rect;
	rect.setOutlineColor(sf::Color::Green);
	rect.setOutlineThickness(0.5f);
	rect.setSize(sf::Vector2f(hitbox.width, hitbox.height));
	rect.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
	rect.setFillColor(sf::Color::Transparent);

	target.draw(rect);
	#endif	
}


void Entity::setSprite(const AnimatedSprite& sprite)
{
	this->sprite = sprite;
}
void Entity::setHitbox(sf::FloatRect hitbox)
{
	this->hitbox = hitbox;
	hitboxBaseOffset.x = hitbox.left;
	hitboxBaseOffset.y = hitbox.top;
	hitbox.left = hitboxPosition.x + hitboxOffset.x + hitboxBaseOffset.x;
	hitbox.top = hitboxPosition.y + hitboxOffset.y + hitboxBaseOffset.y;
}


size_t Entity::getId() const
{
	return this->id;
}
const sf::FloatRect& Entity::getHitbox() const
{
	return this->hitbox;
}
const AnimatedSprite& Entity::getSprite() const
{
	return this->sprite;
}
AnimatedSprite& Entity::getSprite() 
{
	return this->sprite;
}


void Entity::move(const sf::Vector2f &offset)
{
	transform.move(offset);
	sprite.move(offset);

	hitboxPosition += offset;
	hitbox.left = hitboxPosition.x + hitboxOffset.x + hitboxBaseOffset.x;
	hitbox.top = hitboxPosition.y + hitboxOffset.y + hitboxBaseOffset.y;
}
void Entity::setScale(const sf::Vector2f& factors)
{
	transform.setScale(factors);
	sprite.setScale(factors);
}
void Entity::setOrigin(const sf::Vector2f& origin)
{
	transform.setOrigin(origin);
	sprite.setOrigin(origin);
	hitboxOffset.x = -origin.x;
	hitboxOffset.y = -origin.y;
	hitbox.left = hitboxPosition.x + hitboxOffset.x + hitboxBaseOffset.x;
	hitbox.top = hitboxPosition.y + hitboxOffset.y + hitboxBaseOffset.y;
}
void Entity::setPosition(const sf::Vector2f& position)
{
	transform.setPosition(position);
	sprite.setPosition(position);
	hitboxPosition.x = position.x;
	hitboxPosition.y = position.y;
	hitbox.left = hitboxPosition.x + hitboxOffset.x;
	hitbox.top = hitboxPosition.y + hitboxOffset.y;
}
const sf::Vector2f& Entity::getPosition() const
{
	return transform.getPosition();
}

void Entity::collisionStart(Entity* entity)
{
	if (collisionList.exists(entity->getId()))
	{
		onCollisionStay(entity);
	}
	else
	{
		collisionList.add(entity->getId());
		onCollisionEnter(entity);
	}
}
void Entity::collisionEnd(Entity* entity)
{
	if (collisionList.exists(entity->getId()))
	{
		collisionList.remove(entity->getId());
		onCollisionExit(entity);
	}
}
void Entity::onCollisionEnter(Entity* entity) {}
void Entity::onCollisionStay(Entity* entity)  {}
void Entity::onCollisionExit(Entity* entity)  {}


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