#pragma once
#include "GameState.h"
#include <SFML\Graphics\Texture.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Food.h"
#include "LinkedList.h"
#include "DirectionalInput.h"
#include "DrawLayer.h"

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

	sf::View gameView_;

	DrawLayer firstLayer_;
	DrawLayer secondLayer_;
	DrawLayer thirdLayer_;

	DirectionalInput playerDirInput_;

	Player player_;
	Food foodPrototype_;
	Enemy enemyPrototype_;

	LinkedList<Food> foods_;
	LinkedList<Enemy> enemies_;

	public:
	PlayGameState();
	virtual ~PlayGameState();

	virtual void restart();
	virtual void update(sf::Time const& deltaTime);
	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;
	
	void checkCollision(Entity& entityOne, Entity& entityTwo);

	void spawnFood();
	void spawnEnemy();

	void updatePlayer(sf::Time const& deltaTime) throw(...);
	void updateFoods(sf::Time const& deltaTime);
	void updateEnemies(sf::Time const& deltaTime);

	void drawPlayerDebug(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawFoodsDebug(sf::RenderTarget& target, sf::RenderStates states) const;
	void drawEnemiesDebug(sf::RenderTarget& target, sf::RenderStates states) const;
};