#include "Hitbox.h"


Hitbox::Hitbox()
{}


Hitbox::~Hitbox()
{}




sf::Vector2f const& Hitbox::getSize() const
{
	return size_;
}


sf::Vector2f const& Hitbox::getOrigin() const
{
	return origin_;
}


sf::Vector2f const& Hitbox::getPosition() const
{
	return position_;
}




void Hitbox::setSize(const sf::Vector2f& size)
{
	size_ = size;
}


void Hitbox::setOrigin(const sf::Vector2f& origin)
{
	origin_ = origin;
}


void Hitbox::setPosition(const sf::Vector2f& position)
{
	position_ = position;
}


void Hitbox::move(const sf::Vector2f& offset)
{
	position_ += offset;
}




bool Hitbox::contains(const sf::Vector2f& point) const
{
	sf::Vector2f topLeft = position_ - origin_;
	sf::Vector2f bottomRight = topLeft + size_;

	return (
		point.x > topLeft.x &&
		point.y > topLeft.y &&
		point.x < bottomRight.x &&
		point.y < bottomRight.y
	);
}


bool Hitbox::intersects(const Hitbox& hitbox) const
{
	sf::Vector2f myTopLeft = position_ - origin_;
	sf::Vector2f myBottomRight = myTopLeft + size_;
	sf::Vector2f theirTopLeft = hitbox.position_ - hitbox.origin_;
	sf::Vector2f theirBottomRight = theirTopLeft + hitbox.size_;

	return (
		myTopLeft.x < theirBottomRight.x &&
		myTopLeft.y < theirBottomRight.y &&
		myBottomRight.x > theirTopLeft.x &&
		myBottomRight.y > theirTopLeft.y
	);
}

