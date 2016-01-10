#pragma once
#include "GameState.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include "Animation.h"

class DeathGameState :
	public GameState,
	public Animation::Observer
{
	private:
	enum State { START, DEATH, SLEEP, DONE };
	State state_;

	sf::Texture humanTexture_;
	sf::Texture skeletonTexture_;

	sf::Sprite actor_;
	Animation death_;
	Animation sleep_;

	sf::View view_;

	public:
	DeathGameState();
	virtual ~DeathGameState();

	void draw(sf::RenderTarget& target, 
			  sf::RenderStates states) const;
	virtual void update(sf::Time const& deltaTime);
	virtual void restart();

	void onNotify(Animation::Event, Animation*);
};

