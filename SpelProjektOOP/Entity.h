#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\Transformable.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Time.hpp>
#include "AnimatedSprite.h"
#include "List.h"

class Entity : 
	public sf::Drawable
{
	private:
	static size_t nextId;
	size_t id;
	AnimatedSprite sprite;
	sf::Transformable transform;
	sf::Vector2f hitboxPosition;
	sf::Vector2f hitboxBaseOffset;
	sf::Vector2f hitboxOffset;
	sf::FloatRect hitbox;
	SortedList<size_t> collisionList;
	List<string> eventPool;

	public:
	Entity();
	virtual ~Entity();

	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderTarget &target, 
					  sf::RenderStates states) const;

	void setSprite(const AnimatedSprite& sprite);
	void setHitbox(sf::FloatRect hitbox);

	size_t getId() const;
	const sf::FloatRect& getHitbox() const;
	const AnimatedSprite& getSprite() const;
	AnimatedSprite& getSprite();

	void move(const sf::Vector2f& offset);
	void setScale(const sf::Vector2f& factors);
	void setOrigin(const sf::Vector2f& origin);
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f& getPosition() const;

	bool pollEvent(string& eventName);
	void addEvent(string eventName);

	void collisionStart(Entity* entity);
	void collisionEnd(Entity* entity);
	virtual void onCollisionEnter(Entity* entity);
	virtual void onCollisionStay(Entity* entity);
	virtual void onCollisionExit(Entity* entity);

	bool operator==(const Entity& entity) const;
	bool operator<(const Entity& entity) const;
	bool operator>(const Entity& entity) const;
};