#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Graphics\RenderStates.hpp"
#include "SFML\Graphics\Transformable.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Time.hpp"
#include "AnimatedSprite.h"
#include "List.h"

class Entity : 
	public sf::Drawable
{
	private:
	static size_t nextId;
	size_t id;
	AnimatedSprite sprite;
	sf::FloatRect hitbox;
	List<size_t> collisionList;

	public:
	Entity();
	virtual ~Entity();

	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void collisionStart(Entity* entity);
	void collisionEnd(Entity* entity);
	virtual void onCollisionEnter(Entity* entity);
	virtual void onCollisionStay(Entity* entity);
	virtual void onCollisionExit(Entity* entity);

	void setSprite(AnimatedSprite sprite);
	void setHitbox(sf::FloatRect hitbox);

	sf::FloatRect& getHitbox();
	AnimatedSprite& getSprite();
	size_t getId() const;

	void move(const sf::Vector2f& offset);
	void setScale(const sf::Vector2f& factors);

	bool operator==(const Entity& entity) const;
	bool operator<(const Entity& entity) const;
	bool operator>(const Entity& entity) const;
};