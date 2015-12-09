#include "Game.h"
#include "PlayGameState.h"
#include "MenuGameState.h"
#include <iostream>
using namespace std;


Game::Game()
{
	playState_.addObserver(this);
	menuState_.addObserver(this);
	currentState_ = &menuState_;
}
Game::~Game()
{
}


void Game::draw(sf::RenderTarget& target,
				sf::RenderStates states) const
{
	target.draw(*currentState_, states);
}
void Game::update(sf::Time const& deltaTime)
{
	currentState_->update(deltaTime);
}


void Game::setMousePos(sf::Vector2f const& mousePos)
{
	currentState_->setMousePos(mousePos);
}


void Game::onNotify(GameState::Event event, GameState* caller)
{
	if (event == GameState::Event::END)
	{
		if (caller == &menuState_)
		{
			cout << "State Transition: Menu > Play" << endl;
			currentState_ = &playState_;
			currentState_->restart();
		}
		else if (caller == &playState_)
		{
			cout << "State Transition: Play > Menu" << endl;
			currentState_ = &menuState_;
			currentState_->restart();
		}
	}
}