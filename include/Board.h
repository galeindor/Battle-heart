#pragma once

#include "Resources.h"
#include "Characters/Cleric.h"
#include "Characters/Knight.h"
#include "Characters/Archer.h"
#include "Characters/Dummy.h"
#include "Characters/Imp.h"
#include "HashTable.h"

using namespace std;
using std::shared_ptr;

class Board 
{
public:
	Board(const LevelInfo& currLevelInfo);
	bool handleFirstClick(sf::Vector2f location);
	bool handleSecondClick(sf::Vector2f location);
	void hoverEnemies(const sf::Vector2f& hoverPos);
	void hoverPlayers(const sf::Vector2f& hoverPos);
	bool checkMoving() const;
	bool checkCleric() { 
		Player* player = this->m_currPlayer.get();
		return dynamic_cast<Cleric*>(player); 
	}
	vector<sf::Vector2f> createObstaclesVec();
	void seperation(Enemy* enemy, sf::Vector2f steerForce, float deltaTime);
	int updateBoard(float deltaTime, bool charSelected);
	void updateEnemyDest();
	void updatePlayersDeath(std::shared_ptr<Player> character, float deltaTime,int& index);
	void updateEnemysDeath(std::shared_ptr<Enemy> character, float deltaTime, int& index);

	void playerBehavior(std::shared_ptr<Player> character,float deltaTime);
	void enemyBehavior(std::shared_ptr<Enemy> enemy, float deltaTime, sf::Vector2f pos);

	template <class Type>
	bool checkHover(Type character, const sf::Vector2f pos);

	template <class Type>
	Type sortObjects(Type vector);

	template <typename Vec , typename deathFunc , typename behaviorFunc >
	void deathHandler(Vec characters, deathFunc dfunc, behaviorFunc bfunc, float deltaTime);

	void drawBoard(sf::RenderWindow& window, bool charSelected);
	void drawObjects(sf::RenderWindow& window);
	void drawObject(bool player, int& index, sf::RenderWindow& window);
	sf::Vector2f adjustLocation(sf::Vector2f location);

private:
	// Members
	vector<shared_ptr<Player>> m_players;
	vector<shared_ptr<Enemy>> m_enemies;
	int m_currWave;
	std::shared_ptr<Player> m_currPlayer;
	std::vector<std::vector<sf::Vector2i>> m_enemyWaves;
	sf::Sprite m_selected;
	sf::Sprite m_hovered;
	bool m_isHovered = false;

	// Funcs
	HashTable<int, shared_ptr<Player>> getPlayersTable();
	HashTable<int, shared_ptr<Enemy>> getEnemiesTable();

	void initPlayers(const bool lvlPlayers[NUM_OF_PLAYERS]);
	void initEnemies(const std::vector<sf::Vector2i> enemyWave);
	void initSelected();
	void initHovered();
};

template<class Type>
inline bool Board::checkHover(Type character, const sf::Vector2f pos)
{
	if (character->getSprite().getGlobalBounds().contains(pos))
	{
		this->m_hovered.setPosition(adjustLocation(character->getPosition()));
		this->m_isHovered = true;
		return true;
	}
	return false;
}

template <class Type>
inline Type Board::sortObjects(Type vector)
{
	auto copy = vector;
	std::sort(copy.begin(), copy.end(),
		[](auto obj1, auto obj2)
		{ return obj1->getPosition().y < obj2->getPosition().y; });
	return copy;
}

template <typename Vec,typename deathFunc,typename behaviorFunc >
inline void Board::deathHandler(Vec characters, deathFunc dfunc, behaviorFunc bfunc , float deltaTime)
{
	for (int i = 0; i < characters.size(); i++)
	{
		auto obj = characters[i];
		if (!obj->isAlive())
			dfunc(obj, deltaTime, i);
		else
			bfunc(obj, deltaTime);
	}
}
