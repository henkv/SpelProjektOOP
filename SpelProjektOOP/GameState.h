#pragma once
#include <SFML\Graphics\Drawable.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\System\Time.hpp>
#include "LinkedList.h"
#include "Observer.h"

class GameState :
	public sf::Drawable
{
	public:
	static enum Event 
	{ 
		END
	};
	typedef Observer<Event, GameState*> Observer;

	private:
	sf::Vector2f mousePos_;
	sf::Vector2f windowSize_;
	LinkedList<Observer*> observers_;

	public:
	GameState();
	virtual ~GameState();

	virtual void update(sf::Time const& deltaTime) = 0;
	virtual void restart() = 0;

	virtual void setMousePos(sf::Vector2f const& mousePos);
	virtual void setWindowSize(sf::Vector2f const& windowSize);
	sf::Vector2f const& getMousePos() const;
	sf::Vector2f const& getWindowSize() const;

	void addObserver(Observer* observer);
	void notify(Event event);
};



