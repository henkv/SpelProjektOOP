#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "SFML\Graphics\RenderTarget.hpp"
#include "SFML\Graphics\RenderStates.hpp"
#include "SFML\Graphics\Transformable.hpp"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Rect.hpp"
#include "SFML\System\Time.hpp"

class Entity : 
	public sf::Drawable,
	public sf::Transformable
{
	private:
	static size_t nextId;
	sf::Sprite sprite;
	sf::FloatRect hitbox;
	size_t id;
	int state;

	public:
	Entity();
	virtual ~Entity();

	virtual void update(sf::Time deltaTime) = 0;
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void onCollision(const Entity& entity);

	void setState(int state);
	
	sf::Sprite& getSprite();
	const sf::Sprite& getSprite() const;
	size_t getId() const;
	int getState() const;

	sf::FloatRect& getHitbox();
	const sf::FloatRect& getHitbox() const;

	virtual void move(float offsetX, float offsetY);
	void move(const sf::Vector2f &offset);

	bool operator=(const Entity& entity) const;
	bool operator<(const Entity& entity) const;
	bool operator>(const Entity& entity) const;
};