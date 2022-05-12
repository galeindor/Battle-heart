#pragma once
#include "Board.h"

class Controller
{
public:
	Controller();
	void run();
	void update(float deltaTime);


private:
	void drawGame();
	void handleMouseClick(sf::Vector2f location);

	Board m_board;

	// SFML
	sf::RenderWindow m_window;
	sf::Sprite m_bg; // move to utility
	sf::Clock m_clock;

	bool m_charSelected = false;
};


