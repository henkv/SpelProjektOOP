#include "Animation.h"

#include <iostream>
using namespace std;

Animation::Animation()
{
	reverse_ = false;
}


Animation::~Animation()
{}


void Animation::playAnimation(sf::Time const& duration)
{
	currentFrameDuration_ += duration;

	if (currentFrameDuration_ > frameDuration_)
	{
		currentFrameDuration_ -= frameDuration_;

		if (!reverse_)
		{
			currentFrame_.x++;

			if (currentFrame_.x >= bounds_.width)
			{
				currentFrame_.x = 0;
				currentFrame_.y++;

				if (currentFrame_.y >= bounds_.height)
				{
					currentFrame_.y = 0;
					observer_->onNotify(END, this);
				}
			}
		}
		else
		{
			currentFrame_.x--;

			if (currentFrame_.x < 0)
			{
				currentFrame_.x = bounds_.width - 1;
				currentFrame_.y--;

				if (currentFrame_.y < 0)
				{
					currentFrame_.y = bounds_.height - 1;
					observer_->onNotify(END_REVERSE, this);
				}
			}
		}
		
		observer_->onNotify(NEW_FRAME, this);
	}
}


void Animation::setReverse(bool reverse)
{
	reverse_ = reverse;
}

void Animation::setFrameSize(sf::Vector2i frameSize)
{
	frameSize_ = frameSize;
}

void Animation::setFrameDuration(sf::Time frameDuration)
{
	frameDuration_ = frameDuration;
}


void Animation::setFrame(sf::Vector2i frame)
{
	currentFrame_ = frame;
}

void Animation::setBounds(sf::IntRect bounds)
{
	bounds_ = bounds;
}

void Animation::setObserver(Observer* observer)
{
	observer_ = observer;
}

sf::IntRect Animation::getFrameRect() const
{
	return sf::IntRect(
		(bounds_.left + currentFrame_.x) * frameSize_.x, 
		(bounds_.top  + currentFrame_.y) * frameSize_.y, 
		frameSize_.x, 
		frameSize_.y
	);
}