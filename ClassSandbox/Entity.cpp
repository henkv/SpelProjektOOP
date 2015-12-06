#include "Entity.h"


Entity::Entity()
{}

Entity::~Entity()
{}



void Entity::draw(sf::RenderTarget& target,
				  sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void Entity::onCollision(Entity& entity)
{}



Hitbox& Entity::getHitbox()
{
	return hitbox_;
}

sf::Sprite& Entity::getSprite()
{
	return sprite_;
}



Hitbox const& Entity::getHitbox() const
{
	return hitbox_;
}

sf::Sprite const& Entity::getSprite() const
{
	return sprite_;
}

sf::Vector2f const& Entity::getPosition() const
{
	return hitbox_.getPosition();
}



void Entity::setPosition(sf::Vector2f const& position)
{
	hitbox_.setPosition(position);
	sprite_.setPosition(position);
}

void Entity::move(sf::Vector2f const& offset)
{
	hitbox_.move(offset);
	sprite_.move(offset);
}



bool Entity::pollEvent(Event& event)
{
	return eventQueue_.pop(event);
}

void Entity::pushEvent(Event event)
{
	eventQueue_.push(event);
}