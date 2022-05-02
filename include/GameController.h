#pragma once

#include "Resources.h"
#include "HealthBar.h"
#include "Cleric.h"

using std::vector;

class GameController
{
public:
	GameController();
	void run();

	void nextLevel();
	void resetBoard();

private:
	void movePlayer(sf::Vector2f dest);
	void drawGame();
	void MouseClick(sf::Vector2f location);

	sf::RenderWindow m_window;
	sf::Sprite m_bg;
	sf::Sprite m_selected;
	Cleric m_cleric;

	bool m_charSelected = false;

};


