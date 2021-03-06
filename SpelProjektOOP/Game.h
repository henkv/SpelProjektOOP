#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>
#include "GameState.h"
#include "PlayGameState.h"
#include "MenuGameState.h"
#include "DeathGameState.h"

class Game :
	public sf::Drawable,
	public GameState::Observer
{
	private:
	PlayGameState playState_;
	MenuGameState menuState_;
	DeathGameState deathState_;
	GameState* currentState_;

	bool newHighscore_;
	int highscore_;
	string nameHighscore_;

	public:
	Game();
	virtual ~Game();

	virtual void draw(sf::RenderTarget& target, 
			  sf::RenderStates states) const;
	virtual void update(sf::Time const& deltaTime);
	virtual void setMousePos(sf::Vector2f const& mousePos);

	void onNotify(GameState::Event event, GameState* caller);
	void onWindowEvent(sf::Event event);

	void loadHighscore();
	void saveHighscore();
};

