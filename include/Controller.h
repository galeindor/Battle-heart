#pragma once
#include "LevelLoader.h"
#include "ScreenManager/Screen.h"

class Controller
{
public:
	Controller();
	void run();

	void setCurrentScreen(ScreenState state) { this->m_currentScreen = state; }
	void setChangeScreen(bool change) { this->m_changeScreen = change; }

	bool getGameWon(int level) const { return this->m_levelLoader.getGameEnded(level); }
	LevelInfo getLevelInfo(int level) const { return this->m_levelLoader.getLevel(level); }
	unsigned int getNumOfLevels() const { return this->m_levelLoader.getMaxLevel(); }
private:
	void initScreens();
	void swapScreen();
	std::vector<std::unique_ptr<Screen>> m_screens;
	ScreenState m_currentScreen = ScreenState::MENU;
	bool m_changeScreen = false;

	LevelLoader m_levelLoader;

	// SFML
	sf::RenderWindow m_window;
	sf::Clock m_clock;
};
