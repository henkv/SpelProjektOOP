#pragma once
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Time.hpp"

class AnimatedSprite
	: public sf::Sprite
{
	private:
	sf::Time frameDuration;
	sf::Time currentFrameDuration;
	sf::Vector2i currentFrame;
	sf::Vector2i frameSize;
	sf::IntRect animationBounds;

	public:
	AnimatedSprite();
	virtual ~AnimatedSprite();

	void playAnimation(sf::Time duration);

	void setFrameSize(sf::Vector2i size);
	void setFrameDuration(sf::Time duration);
	void setAnimationBounds(sf::IntRect bounds);
};

