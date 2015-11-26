#pragma once
#include "SFML\Graphics\Drawable.hpp"

#include "Entity.h"

class Game :
	public sf::Drawable
{
	private:
	Entity** entityList;

	size_t nrOfEntities;
	size_t entityCap;

	void expandEntityList();

	public:
	Game();
	~Game();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time deltaTime);
	void checkCollision(Entity& entityOne, Entity& entityTwo);
	bool removeEntity(const Entity& entity);
	int  findEntity(const Entity& entity) const;
	void addEntity(Entity* entity);

};

