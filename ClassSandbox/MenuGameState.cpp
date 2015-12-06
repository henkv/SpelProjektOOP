#include "MenuGameState.h"
#include <SFML\Window\Mouse.hpp>

MenuGameState::MenuGameState()
{
	playTexture_.loadFromFile("..\\Assets\\Play.png");
	playButton_.getSprite().setTexture(playTexture_);
	playButton_.getHitbox().setSize(sf::Vector2f(15, 5));
	playButton_.getSprite().setOrigin(sf::Vector2f(15, 5) * 0.5f);
	playButton_.getHitbox().setOrigin(sf::Vector2f(15, 5) * 0.5f);

	menuView_.setSize(getWindowSize());
	menuView_.zoom(0.125f);
	menuView_.setCenter(sf::Vector2f());
}

MenuGameState::~MenuGameState()
{}


void MenuGameState::restart()
{
	menuView_.setSize(getWindowSize());
	menuView_.zoom(0.125f);
	menuView_.setCenter(sf::Vector2f());
}
void MenuGameState::update(const sf::Time& deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (playButton_.checkClick(getMousePos())) notify(END);
	}
}
void MenuGameState::draw(sf::RenderTarget& target,
						 sf::RenderStates states) const
{
	target.setView(menuView_);
	target.draw(playButton_, states);
}

void MenuGameState::setWindowSize(sf::Vector2f const& size)
{
	GameState::setWindowSize(size);
	menuView_.setSize(size);
	menuView_.zoom(0.125f);
}
