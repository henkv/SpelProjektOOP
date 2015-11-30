#pragma once
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\System\Time.hpp"
#include "List.h"

class AnimatedSprite
	: public sf::Sprite
{
	private:
	sf::Time frameDuration;
	sf::Time currentFrameDuration;
	sf::Vector2i currentFrame;
	sf::Vector2i frameSize;
	sf::IntRect animationBounds;
	List<sf::IntRect> animations;
	size_t currentAnimation;

	public:
	AnimatedSprite();
	virtual ~AnimatedSprite();

	void playAnimation(sf::Time duration);

	void setFrameSize(sf::Vector2i size);
	void setFrameDuration(sf::Time duration);
	void setAnimationBounds(sf::IntRect bounds);

	void addAnimation(sf::IntRect animationBounds);
	void setAnimation(size_t id);
	size_t getAnimation() const;
};

