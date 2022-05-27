#pragma once

#include "Resources.h"

#include "Cleric.h"
#include "Knight.h"
#include "Archer.h"

#include "Dummy.h"
using namespace std;
using std::shared_ptr;

class Board 
{
public:
	Board();
	bool handleFirstClick(sf::Vector2f location);
	bool handleSecondClick(sf::Vector2f location);
	bool checkIntersection(sf::Sprite obj, sf::Sprite secObj); //for collisions..
	bool checkMoving() const;

	vector<sf::Vector2f> createObstaclesVec();
	void seperation(Enemy* enemy, sf::Vector2f steerForce, float deltaTime);
	void updateBoard(float deltaTime, bool charSelected);
	void updateEnemyDest();
	void drawBoard(sf::RenderWindow& window, bool charSelected);
	void sortObjects();
	void drawObjects(sf::RenderWindow& window);
	void drawObject(bool player, int& index, sf::RenderWindow& window);
	sf::Vector2f adjustLocation(sf::Vector2f location);
	/*void nextLevel();
	void resetBoard();*/

private:
	vector<shared_ptr<Player>> m_players;
	vector<shared_ptr<Enemy>> m_enemies;

	unsigned int m_playerIndex;
	sf::Sprite m_selected;
	void initPlayers();
	void initEnemies();
	void initSelected();
};