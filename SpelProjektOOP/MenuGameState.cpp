#include "MenuGameState.h"
#include <SFML\Window\Mouse.hpp>

MenuGameState::MenuGameState()
{
	playTexture_.loadFromFile("..\\Assets\\Play.png");
	playButton_.getSprite().setTexture(playTexture_);
	playButton_.getHitbox().setSize(sf::Vector2f(15, 5));
	playButton_.getSprite().setOrigin(sf::Vector2f(15, 5) * 0.5f);
	playButton_.getHitbox().setOrigin(sf::Vector2f(15, 5) * 0.5f);
	playButton_.setPosition(sf::Vector2f(0, 0)) ;

	menuView_.setSize(sf::Vector2f(800, 800));
	menuView_.setCenter(sf::Vector2f(0, 0));
	menuView_.zoom(0.125f);
}

MenuGameState::~MenuGameState()
{}


void MenuGameState::restart()
{
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
}
