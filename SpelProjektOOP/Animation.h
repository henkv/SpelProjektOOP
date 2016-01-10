#pragma once
#include <string>
#include <SFML\System\Time.hpp>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Rect.hpp>
#include "Observer.h"
#include "LinkedList.h"

class Animation
{
	public:
	enum Event { NEW_FRAME, END, END_REVERSE, LAST_FRAME, FIRST_FRAME };
	typedef Observer<Event, Animation*> Observer;

	private:
	std::string name_;
	bool reverse_;

	sf::Time frameDuration_;
	sf::Time currentFrameDuration_;

	sf::Vector2i frameSize_;
	sf::Vector2i currentFrame_;
	sf::IntRect bounds_;

	Observer* observer_;

	public:
	Animation();
	virtual ~Animation();
	
	void playAnimation(sf::Time const& duration);
	void playAnimationReverse(sf::Time const& duration);

	void setReverse(bool reverse);
	void setFrameSize(sf::Vector2i frameSize);
	void setFrameDuration(sf::Time frameDuration);

	void setFrame(sf::Vector2i frame);
	void setBounds(sf::IntRect bounds);

	void setObserver(Observer* observer);

	sf::IntRect getFrameRect() const;
};

