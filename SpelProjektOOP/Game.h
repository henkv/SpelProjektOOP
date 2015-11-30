#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "Entity.h"
#include "List.h"
#include "KeyValuePair.h"

class Game :
	public sf::Drawable
{
	private:
	List<List<SortedList<Entity*>>> entityMap;

	SortedList<Entity*> entityList;
	sf::Sprite map;

	public:
	Game();
	~Game();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time deltaTime);

	void checkCollision(Entity* entityOne, Entity* entityTwo);
	void addEntity(Entity* entity);

	sf::Sprite& getMap();

};

