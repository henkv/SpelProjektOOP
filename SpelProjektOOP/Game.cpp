#include "Game.h"
#include "SFML\Graphics\RenderTarget.hpp"
#include <iostream>

Game::Game()
{
}


Game::~Game()
{
	for (size_t i = 0; i < entityList.length(); i++)
	{
		delete entityList[i];
	}
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(map, states);

	for (size_t i = 0; i < entityList.length(); i++)
	{
		target.draw(*entityList[i], states);
	}
}


void Game::update(sf::Time deltaTime)
{
	string eventName;
	size_t x, y, i, ii;


	for (x = 0; x < entityMap.length(); x++)
	{
		for (y = 0; y < entityMap[x].length(); y++)
		{
			for (i = 0; i < entityMap[x][y].length() - 1; i++)
			{
				for (ii = i + 1; ii < entityMap[x][y].length(); ii++)
				{
					checkCollision(entityList[i], entityList[ii]);
				}
			}
		}
	}

	for (size_t i = 0, ii, iii; i < entityList.length(); i++)
	{
		while (entityList[i]->pollEvent(eventName))
		{
			if (eventName == "DEATH")
			{
				entityList.remove(entityList[i]);
				i--;
			}
		}

		entityList[i]->update(deltaTime);
	}
}


void Game::checkCollision(Entity* entityOne, Entity* entityTwo)
{
	if (entityOne->getHitbox().intersects(entityTwo->getHitbox()))
	{
		entityOne->collisionStart(entityTwo);
		entityTwo->collisionStart(entityOne);
	}
	else
	{
		entityOne->collisionEnd(entityTwo);
		entityTwo->collisionEnd(entityOne);
	}
}

void Game::addEntity(Entity* entity)
{
	entityList.add(entity);
}











sf::Sprite& Game::getMap()
{
	return map;
}
