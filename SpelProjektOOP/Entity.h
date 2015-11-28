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
	public sf::Drawable,
	public sf::Transformable
{
	private:
	static size_t nextId;
	List<Entity> collisionList;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	size_t id;

	public:
	Entity();
	virtual ~Entity();

	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void collisionStart(Entity* entity);
	void collisionEnd(Entity* entity);
	virtual void onCollisionEnter(const Entity* entity);
	virtual void onCollisionStay(const Entity* entity);
	virtual void onCollisionExit(const Entity* entity);

	void setSprite(sf::Sprite sprite);
	void setHitbox(sf::FloatRect hitbox);

	sf::FloatRect& getHitbox();
	sf::Sprite& getSprite();
	size_t getId() const;


	void setRotation(float angle);
	void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);

	bool operator==(const Entity& entity) const;
	bool operator<(const Entity& entity) const;
	bool operator>(const Entity& entity) const;
};