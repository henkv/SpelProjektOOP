#include "GameState.h"



GameState::GameState()
{}

GameState::~GameState()
{}



void GameState::setMousePos(sf::Vector2f const& mousePos)
{
	mousePos_ = mousePos;
}


sf::Vector2f const& GameState::getMousePos() const
{
	return mousePos_;
}

void GameState::addObserver(Observer* observer)
{
	observers_.insertFirst(observer);
}

void GameState::notify(Event event)
{
	auto observer = observers_.getFirst();
	while (observer != nullptr)
	{
		observer->data->onNotify(event, this);

		observer = observer->getNext();
	}
}