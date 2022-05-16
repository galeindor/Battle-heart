#pragma once

#include "Resources.h"
#include "HealthBar.h"

#include "Cleric.h"
#include "Knight.h"
#include "Dummy.h"

using namespace std;
using std::shared_ptr;

class Board 
{
public:
	Board();
	bool handleFirstClick(sf::Vector2f location);
	bool handleSecondClick(sf::Vector2f location);
	void updateBoard(float deltaTime, bool charSelected);
	void updateEnemyDest();
	void drawBoard(sf::RenderWindow& window, bool charSelected);
	bool checkIntersection(sf::Sprite obj, sf::Sprite secObj); //for collisions..
	/*void nextLevel();
	void resetBoard();*/

	sf::Vector2f adjustLocation(sf::Vector2f location); // move the location inside board boundries
	bool checkMoving();
private:
	vector < shared_ptr < Player > > m_players;
	vector < shared_ptr < Enemy > > m_enemies;

	unsigned int m_selectedPlayerIndex;
	sf::Sprite m_selected;
	void initPlayers();
	void initEnemies();
	void initSelected();
};