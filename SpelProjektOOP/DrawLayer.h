#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include "LinkedList.h"

class DrawLayer : 
	public sf::Drawable
{
	private:
	LinkedList<sf::Drawable*> drawList_;
	
	public:
	DrawLayer();
	virtual ~DrawLayer();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void stack(sf::Drawable* drawable);

	LinkedList<sf::Drawable*>& getDrawList();

	void clear();
};

