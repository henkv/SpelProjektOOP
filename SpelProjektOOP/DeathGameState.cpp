#include "DeathGameState.h"


DeathGameState::DeathGameState()
{
	state_ = START;

	humanTexture_.loadFromFile("..\\Assets\\HumanDeath.png");
	skeletonTexture_.loadFromFile("..\\Assets\\SkeletonSheet.png");

	actor_.setOrigin(sf::Vector2f(5, 20));

	death_.setBounds(sf::IntRect(0, 0, 9, 1));
	death_.setFrameDuration(sf::milliseconds(100));
	death_.setFrameSize(sf::Vector2i(10, 20));
	death_.setObserver(this);

	sleep_.setBounds(sf::IntRect(0, 0, 20, 1));
	sleep_.setFrameDuration(sf::milliseconds(50));
	sleep_.setFrameSize(sf::Vector2i(10, 20));
	sleep_.setObserver(this);
	
	view_.setSize(150, 150);
	view_.setCenter(0, 0);
}


DeathGameState::~DeathGameState()
{}


void DeathGameState::draw(sf::RenderTarget& target, 
						  sf::RenderStates states) const
{
	target.setView(view_);
	target.draw(actor_);
}
void DeathGameState::update(sf::Time const& deltaTime)
{
	switch (state_)
	{
		case DeathGameState::START:
			actor_.setTexture(humanTexture_);
			death_.setFrame(sf::Vector2i(0, 0));
			actor_.setTextureRect(death_.getFrameRect());
			state_ = DEATH;
			break;

		case DeathGameState::DEATH:
			death_.playAnimation(deltaTime);
			break;

		case DeathGameState::SLEEP:
			sleep_.playAnimationReverse(deltaTime);
			break;

		case DeathGameState::DONE:
			break;
	}
}
void DeathGameState::restart()
{
	state_ = START;
}

void DeathGameState::onNotify(Animation::Event event, Animation* caller)
{
	switch (event)
	{
		case Animation::NEW_FRAME:
			actor_.setTextureRect(caller->getFrameRect());
			break;

		case Animation::END:
			sleep_.setFrame(sf::Vector2i(19, 0));
			death_.setFrame(sf::Vector2i(19, 0));
			actor_.setTexture(skeletonTexture_);
			state_ = SLEEP;
			break;

		case Animation::END_REVERSE:
			sleep_.setFrame(sf::Vector2i(0, 0));
			state_ = DONE;
			notify(GameState::END);
			break;
	}
}