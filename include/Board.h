#pragma once

#include "Resources.h"
#include "Characters/Cleric.h"
#include "Characters/Knight.h"
#include "Characters/Archer.h"
#include "Characters/Dummy.h"
#include "HashTable.h"
using namespace std;
using std::shared_ptr;

class Board 
{
public:
	Board(const LevelInfo& currLevelInfo);
	bool handleFirstClick(sf::Vector2f location);
	bool handleSecondClick(sf::Vector2f location);
	bool checkIntersection(sf::Sprite obj, sf::Sprite secObj); //for collisions..
	bool checkMoving() const;

	vector<sf::Vector2f> createObstaclesVec();
	void seperation(Enemy* enemy, sf::Vector2f steerForce, float deltaTime);
	bool updateBoard(float deltaTime, bool charSelected);
	void updateEnemyDest();
	void drawBoard(sf::RenderWindow& window, bool charSelected);
	void updatePlayersDeath(std::shared_ptr<Player> character, float deltaTime,int& index);
	void updateEnemysDeath(std::shared_ptr<Enemy> character, float deltaTime, int& index);

	void playerBehavior(std::shared_ptr<Player> character,float deltaTime);
	void enemyBehavior(std::shared_ptr<Enemy> enemy, float deltaTime, sf::Vector2f pos);

	template <class Type>
	Type sortObjects(Type vector);
	void deleteObject(std::shared_ptr<Character> obj);

	void drawObjects(sf::RenderWindow& window);
	void drawObject(bool player, int& index, sf::RenderWindow& window);
	sf::Vector2f adjustLocation(sf::Vector2f location);

private:
	// Members
	vector<shared_ptr<Player>> m_players;
	vector<shared_ptr<Enemy>> m_enemies;
	int m_currLvl;
	int m_currWave;
	std::shared_ptr<Player> m_currPlayer;
	sf::Sprite m_selected;
	std::vector<std::vector<sf::Vector2i>> m_enemyWaves;

	// Funcs
	HashTable<int, Player*> getPlayersTable();
	HashTable<int, Enemy*> getEnemiesTable();

	void initPlayers(const bool lvlPlayers[NUM_OF_PLAYERS]);
	void initEnemies(const std::vector<sf::Vector2i> enemyWave);
	void createChar(const unsigned int index);
	void initSelected();
};

template <class Type>
inline Type Board::sortObjects(Type vector)
{
	auto copy = vector;
	std::sort(copy.begin(), copy.end(),
		[](auto obj1, auto obj2)
		{ return obj1->getPosition().y < obj2->getPosition().y; });
	return copy;
}