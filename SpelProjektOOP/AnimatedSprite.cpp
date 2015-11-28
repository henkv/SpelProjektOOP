#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite()
{
	frameSize.x = 16;
	frameSize.y = 16;
}


AnimatedSprite::~AnimatedSprite()
{}


void AnimatedSprite::playAnimation(sf::Time duration)
{
	currentFrameDuration += duration;

	if (currentFrameDuration > frameDuration)
	{
		currentFrameDuration -= frameDuration;
		currentFrame.x++;

		if (currentFrame.x >= animationBounds.width)
		{
			currentFrame.x %= animationBounds.width;
			++currentFrame.y %= animationBounds.height;
		}

		setTextureRect(sf::IntRect(
			(animationBounds.left + currentFrame.x) * frameSize.x,
			(animationBounds.top + currentFrame.y) * frameSize.y,
			frameSize.x,
			frameSize.y
		));
	}
}


void AnimatedSprite::setFrameSize(sf::Vector2i size)
{
	this->frameSize = size;
}


void AnimatedSprite::setFrameDuration(sf::Time duration)
{
	this->frameDuration = duration;
}


void AnimatedSprite::setAnimationBounds(sf::IntRect bounds)
{
	this->animationBounds = bounds;
	currentFrame.x = 0;
	currentFrame.y = 0;

	setTextureRect(sf::IntRect(
		(animationBounds.left + currentFrame.x) * frameSize.x,
		(animationBounds.top + currentFrame.y) * frameSize.y,
		frameSize.x,
		frameSize.y
	));
}

