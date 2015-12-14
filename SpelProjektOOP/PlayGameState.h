#pragma once
#include "GameState.h"
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\Text.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "LinkedList.h"
#include "DirectionalInput.h"
#include "DrawLayer.h"
#include "EntityDrawLayer.h"

class PlayGameState :
	public GameState
{
	private:
	typedef Node<Food>* FoodNode;
	typedef Node<Enemy>* EnemyNode;

	sf::Texture humanTexture_;
	sf::Texture totemTexture_;
	sf::Texture carrotTexture_;
	sf::Texture skeletonTexture_;

	sf::Font scoreFont_;

	sf::View gameView_;
	sf::View uiView_;

	sf::Text scoreText_;

	DrawLayer firstLayer_;
	DrawLayer secondLayer_;
	DrawLayer thirdLayer_;
	EntityDrawLayer drawStack_;

	DirectionalInput playerDirInput_;

	Player player_;
	Food foodPrototype_;
	Enemy enemyPrototype_;

	LinkedList<Food> foods_;
	LinkedList<Enemy> enemies_;

	int score_;

	public:
	PlayGameState();
	virtual ~PlayGameState();

	virtual void restart();
	virtual void update(sf::Time const& deltaTime);
	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;
	
	bool checkCollision(Entity const& entityOne, Entity const& entityTwo);

	void spawnFood();
	void spawnEnemy();

	void updatePlayer(sf::Time const& deltaTime) throw(...);
	void updateFoods(sf::Time const& deltaTime);
	void updateEnemies(sf::Time const& deltaTime);

	void drawPlayerDebug(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawFoodsDebug(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawEnemiesDebug(sf::RenderTarget& target, sf::RenderStates states) const;


	int getScore() const;
	void setScore(int score);
};