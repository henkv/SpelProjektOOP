#pragma once
#include "GameState.h"
#include "LinkedList.h"
#include "Button.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Font.hpp>
#include <SFML\Graphics\Text.hpp>

class MenuGameState :
	public GameState
{
	private:
	sf::Font font_;
	sf::Texture playTexture_;

	sf::View menuView_;

	sf::Text highscore_;
	int highScoreValue_;
	string highscoreHolder_;

	Button playButton_;

	public:
	MenuGameState();
	virtual ~MenuGameState();

	virtual void restart();
	virtual void update(sf::Time const& deltaTime);
	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;

	int getHighscoreValue() const;
	string getHighscoreHolder() const;

	void setHighscoreValue(int highscoreValue);
	void setHighscoreHolder(string highscoreHolder);
};

