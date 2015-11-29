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
	size_t length = entityList.length();

	for (size_t i = 0, ii; i < length; i++)
	{
		for (ii = i + 1; ii < length; ii++)
		{
			checkCollision(entityList[i], entityList[ii]);
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
