#include "EntityDrawLayer.h"


EntityDrawLayer::EntityDrawLayer()
{}


EntityDrawLayer::~EntityDrawLayer()
{}

void EntityDrawLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Node<Entity*>* node = drawList_.getFirst();
	Node<Entity*>* next = nullptr;

	while (node != nullptr)
	{
		next = node->getNext();
		node->remove();
		target.draw(*node->data, states);
		delete node;
		node = next;
	}
}

void EntityDrawLayer::add(Entity* entity)
{
	float y = entity->getPosition().y;
	auto node = drawList_.getFirst();
	if (node != nullptr)
	{
		while (node != nullptr &&
			   y > node->data->getPosition().y)
		{
			if (node->getNext() != nullptr)
			{
				node = node->getNext();
			}
			else
			{
				node->append(new Node<Entity*>(entity));
				node = nullptr;
			}
		}

		if (node != nullptr)
		{
			node->prepend(new Node<Entity*>(entity));
		}
	}
	else
	{
		drawList_.insertFirst(entity);
	}
}

void EntityDrawLayer::clear()
{
	drawList_.clear();
}