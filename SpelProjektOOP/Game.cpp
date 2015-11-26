#include "Game.h"
#include "SFML\Graphics\RenderTarget.hpp"
#include <iostream>

Game::Game()
{
	this->nrOfEntities = 0;
	this->entityCap = 10;
	this->entityList = new Entity*[this->entityCap];

	for (size_t i = 0; i < this->nrOfEntities; i++)
	{
		this->entityList[i] = nullptr;
	}
}


Game::~Game()
{
	for (size_t i = 0; i < this->nrOfEntities; i++)
	{
		delete this->entityList[i];
	}
	delete[] this->entityList;
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < this->nrOfEntities; i++)
	{
		target.draw(*this->entityList[i], states);
	}
}


void Game::update(sf::Time deltaTime)
{

	for (size_t i = 0, ii; i < this->nrOfEntities - 1; i++)
	{
		for (ii = i + 1; ii < this->nrOfEntities; ii++)
		{
			this->checkCollision(*this->entityList[i], *this->entityList[ii]);
		}
		this->entityList[i]->update(deltaTime);
	}
	
	this->entityList[nrOfEntities - 1]->update(deltaTime);
}


void Game::checkCollision(Entity& entityOne, Entity& entityTwo)
{
	if (entityOne.getHitbox().intersects(entityTwo.getHitbox()))
	{
		entityOne.onCollision(entityTwo);
		entityTwo.onCollision(entityOne);
	}

}


bool Game::removeEntity(const Entity& entity)
{
	bool removed = false;
	int position = this->findEntity(entity);

	if (position != -1)
	{
		delete this->entityList[position];

		for (size_t i = position; i < this->nrOfEntities - 1; i++)
		{
			this->entityList[i] = this->entityList[i + 1];
		}

		this->entityList[--this->nrOfEntities] = nullptr;
	}

	return removed;
}


int Game::findEntity(const Entity& entity) const
{
	int position = -1;
	size_t low = 0;
	size_t high = this->nrOfEntities;
	size_t check = 0;

	while (low <= high && position == -1)
	{
		check = (high + low) / 2;

		if (this->entityList[check] == &entity)
		{
			position = check;
		}
		else if (this->entityList[check] < &entity)
		{
			low = check + 1;
		}
		else
		{
			high = check - 1;
		}
	}

	return position;
}


void Game::addEntity(Entity* entity)
{
	if (nrOfEntities >= entityCap) expandEntityList();
	entityList[nrOfEntities++] = entity;
}


void Game::expandEntityList()
{
	entityCap += 10;
	Entity** newList = new Entity*[entityCap];

	for (size_t i = 0; i < nrOfEntities; i++)
	{
		newList[i] = entityList[i];
	}

	delete[] entityList;
	entityList = newList;
}