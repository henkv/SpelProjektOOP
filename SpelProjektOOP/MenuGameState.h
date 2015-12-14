#pragma once
#include "GameState.h"
#include "LinkedList.h"
#include "Button.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>
#include <string>
#include "Hitbox.h"
using namespace std;

class MenuGameState :
	public GameState
{
	private:
	sf::Texture playTexture_;
	sf::Font font_;

	sf::View menuView_;

	sf::Text highscoreText_;
	sf::Text scoreText_;
	sf::Text playText_;

	Hitbox playHitbox_;

	public:
	MenuGameState();
	virtual ~MenuGameState();

	virtual void restart();
	virtual void update(sf::Time const& deltaTime);
	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;

	void setHighscore(string name, int score);
};

