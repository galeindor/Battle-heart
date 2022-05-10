#pragma once

#include "Resources.h"
#include "HealthBar.h"
#include "Cleric.h"
#include "Knight.h"

using std::vector;

class GameController
{
public:
	GameController();
	void run();

	void nextLevel();
	void resetBoard();

private:
	void updatePlayer(int playerIndex, sf::Vector2f dest);
	void drawGame();
	void MouseClick(sf::Vector2f location);

	bool outOfRange(sf::Vector2f location);

	sf::RenderWindow m_window;
	sf::Sprite m_bg;
	sf::Sprite m_selected;

	std::vector < std::unique_ptr < Player > > m_players;

	//Cleric m_cleric;
	//Knight m_knight;

	bool m_charSelected = false;

};


