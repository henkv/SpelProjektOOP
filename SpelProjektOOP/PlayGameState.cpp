#include "PlayGameState.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include "MenuGameState.h"
#include <iostream>
#include <sstream>


PlayGameState::PlayGameState()
{
	humanTexture_.loadFromFile("..\\Assets\\Human.png");
	skeletonTexture_.loadFromFile("..\\Assets\\SkeletonSheet.png");
	carrotTexture_.loadFromFile("..\\Assets\\Carrot.png");
	totemTexture_.loadFromFile("..\\Assets\\Totem.png");
	
	scoreFont_.loadFromFile("..\\Assets\\PressStart2P.ttf");

	scoreText_.setFont(scoreFont_);
	scoreText_.setString("Score: 0");
	scoreText_.setPosition(sf::Vector2f(0, 0));
	scoreText_.setCharacterSize(24);
	scoreText_.setPosition(10, 10);

	player_.getSprite().setTexture(humanTexture_);
	player_.getSprite().setOrigin(sf::Vector2f(5, 20));
	player_.getHitbox().setSize(sf::Vector2f(6, 1));
	player_.getHitbox().setOrigin(sf::Vector2f(3, 0.5f));

	enemyPrototype_.getSprite().setTexture(skeletonTexture_);
	enemyPrototype_.getSprite().setTextureRect(sf::IntRect(0, 0, 10, 20));
	enemyPrototype_.getSprite().setOrigin(sf::Vector2f(5, 20));
	enemyPrototype_.getHitbox().setSize(sf::Vector2f(6, 1));
	enemyPrototype_.getHitbox().setOrigin(sf::Vector2f(3, 0.5));
	enemyPrototype_.getAnimation().setFrameSize(sf::Vector2i(10, 20));
	enemyPrototype_.getAnimation().setFrameDuration(sf::milliseconds(25));
	enemyPrototype_.getAnimation().setBounds(sf::IntRect(0, 0, 20, 1));
	enemyPrototype_.setAggroRadius(100);
	enemyPrototype_.setSpeed(5);

	foodPrototype_.getSprite().setTexture(carrotTexture_);
	foodPrototype_.getSprite().setOrigin(sf::Vector2f(3, 12));
	foodPrototype_.getHitbox().setSize(sf::Vector2f(4, 2));
	foodPrototype_.getHitbox().setOrigin(sf::Vector2f(2, 1));

	gameView_.setSize(150, 150);

	restart();
}
PlayGameState::~PlayGameState()
{
}


void PlayGameState::restart()
{
	score_ = 0;
	foods_.clear();
	enemies_.clear();
	drawStack_.clear();

	player_.setPosition(sf::Vector2f());

	foodPrototype_.setPosition(sf::Vector2f(0, 25));
	foods_.insertFirst(foodPrototype_);
}
void PlayGameState::update(sf::Time const& deltaTime)
{
	updatePlayer(deltaTime);
	updateEnemies(deltaTime);
	updateFoods(deltaTime);

	gameView_.setCenter(player_.getPosition());
}
void PlayGameState::draw(sf::RenderTarget& target,
						 sf::RenderStates states) const
{
	sf::RectangleShape playArea;
	playArea.setFillColor(sf::Color::Transparent);
	playArea.setSize(sf::Vector2f(150, 150));
	playArea.setOutlineColor(sf::Color::Cyan);
	playArea.setOutlineThickness(0.25f);
	playArea.setPosition(sf::Vector2f());
	playArea.setOrigin(sf::Vector2f(150, 150) / 2.f);

	target.setView(gameView_);

	//target.draw(playArea, states);
	//drawFoodsDebug(target, states);
	//drawPlayerDebug(target, states);
	//drawEnemiesDebug(target, states);

	target.draw(drawStack_, states);

	target.setView(uiView_);
	target.draw(scoreText_, states);
}



bool PlayGameState::checkCollision(Entity const& entityOne, Entity const& entityTwo)
{
	return entityOne.getHitbox().intersects(entityTwo.getHitbox());
}


void PlayGameState::spawnFood()
{
	sf::Vector2f const* playerPos = &player_.getPosition();
	sf::Vector2f const* comparePosition = nullptr;
	sf::Vector2f spawnPos;
	sf::Vector2f deltaPos;

	float distanceToClosestNeighbour = 0;
	float compareDistance = 0;
	float minDistance = 50;

	int radius = 50;

	while (distanceToClosestNeighbour < minDistance)
	{
		spawnPos.x = playerPos->x + rand() % (radius * 2 + 1) - radius;
		spawnPos.y = playerPos->y + rand() % (radius * 2 + 1) - radius;

		deltaPos = spawnPos - *playerPos;
		distanceToClosestNeighbour = sqrtf(powf(deltaPos.x, 2.f) + powf(deltaPos.x, 2.f));

		/*FoodNode food = foods_.getFirst();
		while (food != nullptr)
		{
			comparePosition = &food->data.getPosition();
			deltaPos = spawnPos - *comparePosition;
			compareDistance = sqrtf(powf(deltaPos.x, 2.f) + powf(deltaPos.x, 2.f));

			if (compareDistance < distanceToClosestNeighbour)
			{
				distanceToClosestNeighbour = compareDistance;
			}

			food = food->getNext();
		}

		minDistance--;*/
	}
	
	foodPrototype_.setPosition(spawnPos);
	foods_.insertFirst(foodPrototype_);
}
void PlayGameState::spawnEnemy()
{
	sf::Vector2f const* playerPos = &player_.getPosition();
	sf::Vector2f const* comparePosition = nullptr;
	sf::Vector2f spawnPos;
	sf::Vector2f deltaPos;

	float distanceToClosestNeighbour = 0;
	float compareDistance = 0;
	float minDistance = 50;

	int radius = 75;

	while (distanceToClosestNeighbour < minDistance)
	{
		spawnPos.x = playerPos->x + rand() % (radius * 2 + 1) - radius;
		spawnPos.y = playerPos->y + rand() % (radius * 2 + 1) - radius;

		deltaPos = spawnPos - *playerPos;
		distanceToClosestNeighbour = sqrtf(powf(deltaPos.x, 2.f) + powf(deltaPos.x, 2.f));

		/*EnemyNode enemy = enemies_.getFirst();
		while (enemy != nullptr)
		{
			comparePosition = &enemy->data.getPosition();

			deltaPos = spawnPos - *comparePosition;
			compareDistance = sqrtf(powf(deltaPos.x, 2.f) + powf(deltaPos.x, 2.f));

			if (compareDistance < distanceToClosestNeighbour)
			{
				distanceToClosestNeighbour = compareDistance;
			}

			enemy = enemy->getNext();
		}

		minDistance--;*/
	}

	float speed = rand() % 40;
	float speedScale = (1 - speed / 50);

	enemyPrototype_.setPosition(spawnPos);
	enemyPrototype_.setSpeed(speed);
	enemyPrototype_.getSprite().setColor(sf::Color(255, 255 * speedScale, 255 * speedScale));
	enemyPrototype_.setAggroRadius(100 * speedScale);
	enemies_.insertFirst(enemyPrototype_);
}


void PlayGameState::updatePlayer(sf::Time const& deltaTime)
{
	Entity::Event event;
	while (player_.pollEvent(event))
	{
		switch (event)
		{
			case Entity::Event::DEATH:
				notify(END);
				break;
		}
	}

	sf::Vector2f dir = playerDirInput_.getInput();
	player_.move(dir * 40.f * deltaTime.asSeconds());
	player_.update(deltaTime);
	gameView_.setCenter(player_.getPosition());

	drawStack_.add(&player_);
}
void PlayGameState::updateFoods(sf::Time const& deltaTime)
{
	Entity::Event event;
	Node<Food>* food = foods_.getFirst();

	if (food == nullptr) restart();

	while (food != nullptr)
	{

		if (checkCollision(player_, food->data))
		{
			auto next = food->getNext();
			food->remove();
			delete food;
			food = next;

			setScore(score_ + 1);

			spawnFood();
			spawnFood();
			spawnEnemy();
		}
		else
		{
			drawStack_.add(&food->data);
			food = food->getNext();
		}
	}
}
void PlayGameState::updateEnemies(sf::Time const& deltaTime)
{
	Entity::Event event;
	Node<Enemy>* enemy = enemies_.getFirst();

	while (enemy != nullptr)
	{
		
		if (checkCollision(enemy->data, player_))
		{
			notify(Event::END);
			enemy = nullptr;
		}
		else
		{
			enemy->data.update(deltaTime);
			enemy->data.setTargetPos(player_.getPosition());

			drawStack_.add(&enemy->data);
			enemy = enemy->getNext();
		}
	}
}


void PlayGameState::drawPlayerDebug(sf::RenderTarget& target, sf::RenderStates states) const
{

	sf::RectangleShape hitbox;
	hitbox.setOutlineThickness(0.25f);
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setFillColor(sf::Color::Transparent);
	
	hitbox.setSize(player_.getHitbox().getSize());
	hitbox.setOrigin(player_.getHitbox().getOrigin());
	hitbox.setPosition(player_.getHitbox().getPosition());

	target.draw(hitbox, states);
}
void PlayGameState::drawFoodsDebug(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vector2f const& playerPos = player_.getPosition();

	sf::RectangleShape hitbox;
	hitbox.setOutlineThickness(0.25f);
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setFillColor(sf::Color::Transparent);

	Node<Food>* food = foods_.getFirst();
	while (food != nullptr)
	{
		hitbox.setPosition(food->data.getPosition());
		hitbox.setSize(food->data.getHitbox().getSize());
		hitbox.setOrigin(food->data.getHitbox().getOrigin());

		target.draw(hitbox, states);

		food = food->getNext();
	}
}
void PlayGameState::drawEnemiesDebug(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vector2f const& playerPos = player_.getPosition();

	sf::RectangleShape hitbox;
	hitbox.setOutlineThickness(0.25f);
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setFillColor(sf::Color::Transparent);

	sf::CircleShape aggroZone;
	aggroZone.setOutlineThickness(0.25f);
	aggroZone.setOutlineColor(sf::Color::Red);
	aggroZone.setFillColor(sf::Color::Transparent);
	aggroZone.setScale(sf::Vector2f(1, 0.5f));

	Node<Enemy>* enemy = enemies_.getFirst();
	while (enemy != nullptr)
	{
		hitbox.setPosition(enemy->data.getPosition());
		hitbox.setSize(enemy->data.getHitbox().getSize());
		hitbox.setOrigin(enemy->data.getHitbox().getOrigin());

		aggroZone.setRadius(enemy->data.getAggroRadius());
		aggroZone.setPosition(enemy->data.getPosition());
		aggroZone.setOrigin(sf::Vector2f(1.f, 1.f) * enemy->data.getAggroRadius());

		target.draw(hitbox, states);
		target.draw(aggroZone, states);

		enemy = enemy->getNext();
	}
}

int PlayGameState::getScore() const
{
	return score_;
}


void PlayGameState::setScore(int score)
{
	score_ = score;
	
	std::stringstream sstream;
	sstream << score;
	scoreText_.setString("Score: " + sstream.str());	
}