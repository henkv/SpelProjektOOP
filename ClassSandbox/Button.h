#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "Hitbox.h"

class Button :
	public sf::Drawable
{
	private:
	Hitbox hitbox_;
	sf::Sprite sprite_;
	
	public:
	Button();
	virtual ~Button();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Hitbox& getHitbox();
	sf::Sprite& getSprite();

	Hitbox const& getHitbox() const;
	sf::Sprite const& getSprite() const;
	sf::Vector2f const& getPosition() const;

	void setPosition(sf::Vector2f const& position);

	bool checkClick(sf::Vector2f const& position);
};

