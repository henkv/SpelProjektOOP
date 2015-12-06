#include "Button.h"
#include <SFML\Graphics\RenderTarget.hpp>

Button::Button()
{}
Button::~Button()
{}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

Hitbox& Button::getHitbox()
{
	return hitbox_;
}
sf::Sprite& Button::getSprite()
{
	return sprite_;
}

Hitbox const& Button::getHitbox() const
{
	return hitbox_;
}
sf::Sprite const& Button::getSprite() const
{
	return sprite_;
}
sf::Vector2f const& Button::getPosition() const
{
	return hitbox_.getPosition();
}

void Button::setPosition(sf::Vector2f const& position)
{
	hitbox_.setPosition(position);
	sprite_.setPosition(position);
}

bool Button::checkClick(sf::Vector2f const& position)
{
	return hitbox_.contains(position);
}