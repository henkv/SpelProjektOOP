#pragma once
#include "SFML\Graphics\Drawable.hpp"
#include "Entity.h"
#include "List.h"

class Game :
	public sf::Drawable
{
	private:
	List<Entity*> entityList;
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

