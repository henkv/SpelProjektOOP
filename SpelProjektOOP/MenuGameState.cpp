#include "MenuGameState.h"
#include <SFML\Window\Mouse.hpp>
#include <sstream>
#include <SFML\Graphics\RectangleShape.hpp>

MenuGameState::MenuGameState()
{
	sf::FloatRect textRect;

	font_.loadFromFile("..\\Assets\\PressStart2P.ttf");
	
	const_cast<sf::Texture&>(font_.getTexture(32)).setSmooth(false);

	lastTryText_.setFont(font_);
	lastTryText_.setPosition(0, 150);
	lastTryText_.setCharacterSize(32);

	highscoreText_.setFont(font_);
	highscoreText_.setPosition(0, -150);
	highscoreText_.setCharacterSize(32);
	highscoreText_.setString("HIGHSCORE");

	textRect = highscoreText_.getLocalBounds();
	highscoreText_.setOrigin(textRect.width / 2, textRect.height / 2);

	scoreText_.setFont(font_);
	scoreText_.setPosition(0, -100);
	scoreText_.setCharacterSize(32);

	const_cast<sf::Texture&>(font_.getTexture(48)).setSmooth(false);

	playText_.setFont(font_);
	playText_.setPosition(0, 0);
	playText_.setCharacterSize(48);
	playText_.setString("PLAY!");

	textRect = playText_.getLocalBounds();
	playText_.setOrigin(textRect.width / 2, textRect.height / 2);

	playHitbox_.setSize(sf::Vector2f(240, 54));
	playHitbox_.setOrigin(playHitbox_.getSize() * 0.5f);

	menuView_.setCenter(0, 0);
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

		if (playHitbox_.contains(getMousePos()))
		{
			 notify(END);
		}
	}
}

void MenuGameState::draw(sf::RenderTarget& target,
						 sf::RenderStates states) const
{
	target.setView(menuView_);

	//sf::RectangleShape hitbox;
	//hitbox.setOutlineThickness(1);
	//hitbox.setOutlineColor(sf::Color::Green);
	//hitbox.setFillColor(sf::Color::Transparent);
	//hitbox.setPosition(playHitbox_.getPosition());
	//hitbox.setSize(playHitbox_.getSize());
	//hitbox.setOrigin(playHitbox_.getOrigin());
	//target.draw(hitbox, states);

	target.draw(highscoreText_, states);
	target.draw(scoreText_, states);
	target.draw(playText_, states);
	target.draw(lastTryText_, states);
}

void MenuGameState::setHighscore(string name, int score)
{
	stringstream str;
	str << score;

	scoreText_.setString(name + " " + str.str());

	sf::FloatRect const& textRect = scoreText_.getLocalBounds();
	scoreText_.setOrigin(textRect.width / 2, textRect.height / 2);
}

void MenuGameState::setLastTry(int score)
{
	stringstream str;
	str << score;

	lastTryText_.setString("SCORE: " + str.str());

	sf::FloatRect const& textRect = lastTryText_.getLocalBounds();
	lastTryText_.setOrigin(textRect.width / 2, textRect.height / 2);
}