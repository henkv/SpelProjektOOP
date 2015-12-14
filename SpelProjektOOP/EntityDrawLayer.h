#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include "Entity.h"
#include "LinkedList.h"

class EntityDrawLayer :
	public sf::Drawable
{
	private:
	LinkedList<Entity*> drawList_;

	public:
	EntityDrawLayer();
	virtual ~EntityDrawLayer();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void add(Entity* drawable);

	void clear();
};

