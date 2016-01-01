#include "Game.h"
#include "PlayGameState.h"
#include "MenuGameState.h"
#include <iostream>
#include <fstream>
using namespace std;


Game::Game()
{
	newHighscore_ = false;
	loadHighscore();

	playState_.addObserver(this);
	menuState_.addObserver(this);
	menuState_.setHighscore(nameHighscore_, highscore_);

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
			playState_.setScore(0);
		}
		else if (caller == &playState_)
		{
			menuState_.setLastTry(playState_.getScore());

			if (playState_.getScore() > highscore_)
			{
				highscore_ = playState_.getScore();
				cout << "New Highscore: " << highscore_ << " carrots" << endl;
				menuState_.setHighscore("_", highscore_);
				nameHighscore_ = "";
				newHighscore_ = true;
			}
			cout << "State Transition: Play > Menu" << endl;
			currentState_ = &menuState_;
		}
	}
}

void Game::onWindowEvent(sf::Event event)
{
	if (event.type == sf::Event::TextEntered && newHighscore_)
	{
		if (event.text.unicode == 8)
		{
			if (nameHighscore_.length() > 0)
			{
				nameHighscore_.erase(nameHighscore_.length() - 1);
				menuState_.setHighscore(nameHighscore_ + "_", highscore_);
			}
		}
		else if (nameHighscore_.length() < 2)
		{
			nameHighscore_ += toupper(static_cast<char>(event.text.unicode));
			menuState_.setHighscore(nameHighscore_ + "_", highscore_);
		}
		else
		{
			nameHighscore_ += toupper(static_cast<char>(event.text.unicode));
			menuState_.setHighscore(nameHighscore_, highscore_);
			newHighscore_ = false;
			saveHighscore();
		}
	}
}

void Game::loadHighscore()
{
	ifstream file;

	char name[4] = "NAN";
	int score = 0;

	file.open("highscore.bin", ios::in | ios::binary);
	file.read((char*)& name, sizeof(name));
	file.read((char*)& score, sizeof(score));
	file.close();

	nameHighscore_ = name;
	highscore_ = score;
}


void Game::saveHighscore()
{
	ofstream file;

	char name[4] = {
		nameHighscore_[0],
		nameHighscore_[1],
		nameHighscore_[2],
		'\0'
	};

	int score = highscore_;

	file.open("highscore.bin", ios::out | ios::binary);
	file.write((char*)& name, sizeof(name));
	file.write((char*)& score, sizeof(score));
	file.close();
}