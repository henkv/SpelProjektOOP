#include "DrawLayer.h"
#include <SFML\Graphics\RenderTarget.hpp>

DrawLayer::DrawLayer()
{}


DrawLayer::~DrawLayer()
{}

void DrawLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Node<sf::Drawable*>* node = drawList_.getFirst();
	Node<sf::Drawable*>* next = nullptr;

	while (node != nullptr)
	{
		next = node->getNext();
		node->remove();
		target.draw(*node->data, states);
		delete node;
		node = next;
	}
}

void DrawLayer::stack(sf::Drawable* drawable)
{
	drawList_.insertFirst(drawable);
}

LinkedList<sf::Drawable*>& DrawLayer::getDrawList()
{
	return drawList_;
}

void DrawLayer::clear()
{
	drawList_.clear();
}