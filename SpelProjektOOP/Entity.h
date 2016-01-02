#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\System\Time.hpp>
#include "Hitbox.h"
#include "Queue.h"

class Entity :
	public sf::Drawable
{
	public:
	static enum Event { DEATH };

	private:
	Hitbox hitbox_;
	sf::Sprite sprite_;
	Queue<Event> eventQueue_;

	public:
	Entity();
	virtual ~Entity();

	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;
	virtual void update(sf::Time const& deltaTime) = 0;
	virtual void onCollision(Entity& entity);

	Hitbox& getHitbox();
	sf::Sprite& getSprite();

	Hitbox const& getHitbox() const;
	sf::Sprite const& getSprite() const;
	sf::Vector2f const& getPosition() const;

	void setPosition(sf::Vector2f const& position);
	void move(sf::Vector2f const& offset);

	bool pollEvent(Event& event);
	void pushEvent(Event event);

};

