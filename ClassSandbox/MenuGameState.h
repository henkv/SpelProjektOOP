#pragma once
#include "GameState.h"
#include "LinkedList.h"
#include "Button.h"
#include <SFML\Graphics\Texture.hpp>

class MenuGameState :
	public GameState
{
	private:
	sf::Texture playTexture_;

	sf::View menuView_;

	Button playButton_;

	public:
	MenuGameState();
	virtual ~MenuGameState();

	virtual void restart();
	virtual void update(sf::Time const& deltaTime);
	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;

	virtual void setWindowSize(sf::Vector2f const& size);

};

