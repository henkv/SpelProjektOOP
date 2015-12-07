#pragma once
#include <SFML\System\Vector2.hpp>


class Hitbox
{
	private:
	sf::Vector2f size_;
	sf::Vector2f origin_;
	sf::Vector2f position_;

	public:
	Hitbox();
	virtual ~Hitbox();

	sf::Vector2f const& getSize() const;
	sf::Vector2f const& getOrigin() const;
	sf::Vector2f const& getPosition() const;

	void setSize(sf::Vector2f const& size);
	void setOrigin(sf::Vector2f const& origin);
	void setPosition(sf::Vector2f const& position);
	void move(sf::Vector2f const& offset);

	bool contains(sf::Vector2f const& point) const;
	bool intersects(Hitbox const& hitbox) const;
};

