#pragma once
#include "Board.h"
#include "Menu.h"
#include "LevelLoader.h"
class Controller
{
public:
	Controller();
	void run();
	void update(float deltaTime);
	bool winLevel();
	void winGame();
private:
	void drawGame();
	void handleMouseClick(sf::Vector2f location);

	LevelLoader m_levelLoader;
	Board m_board;
	Menu m_menu;
	
	// SFML
	sf::RenderWindow m_window;
	sf::Sprite m_bg; // move to utility
	sf::Clock m_clock;

	// Management 
	bool m_charSelected = false;
	unsigned int m_currLvl;
};
