#include "PlayGameState.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\CircleShape.hpp>
#include "MenuGameState.h"
#include <iostream>


PlayGameState::PlayGameState()
{
	humanTexture_.loadFromFile("..\\Assets\\Human.png");
	skeletonTexture_.loadFromFile("..\\Assets\\Skeleton.png");
	carrotTexture_.loadFromFile("..\\Assets\\Carrot.png");
	totemTexture_.loadFromFile("..\\Assets\\Totem.png");

	gameView_.setSize(getWindowSize());
	gameView_.zoom(0.125f);

	player_.getSprite().setTexture(humanTexture_);
	player_.getSprite().setOrigin(sf::Vector2f(5, 20));
	player_.getHitbox().setSize(sf::Vector2f(6, 1));
	player_.getHitbox().setOrigin(sf::Vector2f(3, 0.5f));

	enemyPrototype_.getSprite().setTexture(skeletonTexture_);
	enemyPrototype_.getSprite().setOrigin(sf::Vector2f(5, 20));
	enemyPrototype_.getHitbox().setSize(sf::Vector2f(6, 1));
	enemyPrototype_.getHitbox().setOrigin(sf::Vector2f(3, 0.5));
	enemyPrototype_.setAggroRadius(100);
	enemyPrototype_.setSpeed(5);

	foodPrototype_.getSprite().setTexture(carrotTexture_);
	foodPrototype_.getSprite().setOrigin(sf::Vector2f(3, 12));
	foodPrototype_.getHitbox().setSize(sf::Vector2f(8, 2));
	foodPrototype_.getHitbox().setOrigin(sf::Vector2f(4, 1));

	restart();
}
PlayGameState::~PlayGameState()
{
}


void PlayGameState::restart()
{
	foods_.clear();
	enemies_.clear();
	firstLayer_.clear();
	secondLayer_.clear();
	thirdLayer_.clear();

	player_.setPosition(sf::Vector2f());
	gameView_.setSize(getWindowSize());
	gameView_.zoom(0.125f);

	for (int i = 0; i < rand() % 8 + 3; i++)
	{
		spawnEnemy();
	}

	for (int i = 0; i < rand() % 8 + 3; i++)
	{
		spawnFood();
	}
}
void PlayGameState::update(sf::Time const& deltaTime)
{
	updatePlayer(deltaTime);
	updateEnemies(deltaTime);
	updateFoods(deltaTime);
}
void PlayGameState::draw(sf::RenderTarget& target,
						 sf::RenderStates states) const
{
	target.setView(gameView_);

	sf::RectangleShape playArea;
	playArea.setFillColor(sf::Color::Transparent);
	playArea.setSize(sf::Vector2f(150, 150));
	playArea.setOutlineColor(sf::Color::Cyan);
	playArea.setOutlineThickness(0.25f);
	playArea.setPosition(sf::Vector2f());
	playArea.setOrigin(sf::Vector2f(150, 150) / 2.f);

	//target.draw(playArea, states);
	//drawFoodsDebug(target, states);
	//drawPlayerDebug(target, states);
	//drawEnemiesDebug(target, states);

	target.draw(firstLayer_, states);
	target.draw(secondLayer_, states);
	target.draw(thirdLayer_, states);
}

void PlayGameState::setWindowSize(sf::Vector2f const& size)
{
	GameState::setWindowSize(size);
	gameView_.setSize(size);
	gameView_.zoom(0.125f);
}


void PlayGameState::checkCollision(Entity& entityOne, Entity& entityTwo)
{
	if (entityOne.getHitbox().intersects(entityTwo.getHitbox()))
	{
		entityOne.onCollision(entityTwo);
	}
}


void PlayGameState::spawnFood()
{
	sf::Vector2f const* comparePosition = nullptr;
	sf::Vector2f spawnPos;
	sf::Vector2f deltaPos;

	float distanceToClosestNeighbour = 0;
	float compareDistance = 0;
	float minDistance = 50;

	while (distanceToClosestNeighbour < minDistance)
	{
		spawnPos.x = rand() % 151 - 75;
		spawnPos.y = rand() % 151 - 75;

		comparePosition = &player_.getPosition();
		deltaPos = spawnPos - *comparePosition;

		distanceToClosestNeighbour = sqrtf(powf(deltaPos.x, 2.f) + powf(deltaPos.x, 2.f));

		FoodNode food = foods_.getFirst();
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

		minDistance--;
	}
	
	foodPrototype_.setPosition(spawnPos);
	foods_.insertFirst(foodPrototype_);
}
void PlayGameState::spawnEnemy()
{
	sf::Vector2f const* comparePosition = nullptr;
	sf::Vector2f spawnPos;
	sf::Vector2f deltaPos;

	float distanceToClosestNeighbour = 0;
	float compareDistance = 0;
	float minDistance = 100;

	while (distanceToClosestNeighbour < minDistance)
	{
		spawnPos.x = rand() % 151 - 75;
		spawnPos.y = rand() % 151 - 75;

		comparePosition = &player_.getPosition();
		deltaPos = spawnPos - *comparePosition;

		distanceToClosestNeighbour = sqrtf(powf(deltaPos.x, 2.f) + powf(deltaPos.x, 2.f));

		EnemyNode enemy = enemies_.getFirst();
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

		minDistance--;
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

	secondLayer_.stack(&player_);
}
void PlayGameState::updateFoods(sf::Time const& deltaTime)
{
	Entity::Event event;
	Node<Food>* food = foods_.getFirst();

	if (food == nullptr) restart();

	while (food != nullptr)
	{
		while (food != nullptr && food->data.pollEvent(event))
		{
			if (event == Entity::Event::DEATH)
			{
				auto next = food->getNext();
				food->remove();
				delete food;
				food = next;
			}
		}

		if (food != nullptr)
		{
			checkCollision(player_, food->data);

			if (food->data.getPosition().y < player_.getPosition().y)
			{
				firstLayer_.stack(&food->data);
			}
			else
			{
				thirdLayer_.stack(&food->data);
			}

			food = food->getNext();
		}
	}
}
void PlayGameState::updateEnemies(sf::Time const& deltaTime)
{
	Entity::Event event = Entity::Event::DEATH;
	Node<Enemy>* enemy = enemies_.getFirst();

	while (enemy != nullptr)
	{
		while (enemy != nullptr && enemy->data.pollEvent(event))
		{
			if (event == Entity::Event::DEATH)
			{
				auto next = enemy->getNext();
				enemy->remove();
				delete enemy;
				enemy = next;
			}
		}

		if (enemy != nullptr)
		{
			enemy->data.update(deltaTime);
			checkCollision(enemy->data, player_);
			enemy->data.setTargetPos(player_.getPosition());

			if (enemy->data.getPosition().y < player_.getPosition().y)
			{
				firstLayer_.stack(&enemy->data);
			}
			else
			{
				thirdLayer_.stack(&enemy->data);
			}

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

	hitbox.setPosition(player_.getPosition());
	hitbox.setSize(player_.getHitbox().getSize());
	hitbox.setOrigin(player_.getHitbox().getOrigin());

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