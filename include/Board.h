#pragma once

#include "Resources.h"
#include "HealthBar.h"
#include "Cleric.h"
#include "Knight.h"
using namespace std;

class Board 
{
public:
	Board();
	bool handleFirstClick(sf::Vector2f location);
	bool handleSecondClick(sf::Vector2f location);
	void updateBoard(float deltaTime, bool charSelected);
	void drawBoard(sf::RenderWindow& window, bool charSelected);

	/*void nextLevel();
	void resetBoard();*/

	sf::Vector2f adjustLocation(sf::Vector2f location); // move the location inside board boundries
	bool checkMoving();
private:
	vector < unique_ptr < Player > > m_players; // move to board
	unsigned int m_selectedPlayerIndex;
	sf::Sprite m_selected;

	void initPlayers();
	void initSelected();
};