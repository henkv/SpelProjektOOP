#include "Game.h"
#include <SFML\Graphics\RenderTarget.hpp>
#include <iostream>

Game::Game()
{
}


Game::~Game()
{
	
}


void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(map, states);
	
	auto foodNode = foodList.getFirst();
	while (foodNode != nullptr)
	{
		target.draw(*foodNode->data, states);
		foodNode = foodNode->getNext();
	}

	if (player != nullptr)
		target.draw(*player, states);
}


void Game::update(sf::Time deltaTime)
{
	string event;
	auto foodNode = foodList.getFirst();

	if (player != nullptr)
	{
		player->update(deltaTime);
		if (player->getHunger() > 100.0f)
		{
			gameOver();
		}
	}

	while (foodNode != nullptr)
	{
		while (foodNode != nullptr && foodNode->data->pollEvent(event))
		{
			if (event == "DEATH")
			{
				foodNode->remove();
				delete foodNode->data;
				auto   next = foodNode->getNext();
				delete foodNode;
				foodNode = next;
			}
		}
		if (foodNode != nullptr)
		{
			if (player != nullptr)
				checkCollision(player, foodNode->data);

			foodNode->data->update(deltaTime);
			foodNode = foodNode->getNext();
		}
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


void Game::setPlayer(Player* player)
{
	this->player = player;
}


void Game::addFood(Food* food)
{
	auto node = new Node<Food*>(food);
	foodList.insertFirst(node);
}


sf::Sprite& Game::getMap()
{
	return map;
}


void Game::gameOver()
{

}


void Game::gameStart()
{

}


void Game::showMainMenu()
{
	state = State::MAIN_MENU;
}
