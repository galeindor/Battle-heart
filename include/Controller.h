#pragma once
#include "LevelLoader.h"
#include "ScreenManager/Screen.h"

class Controller
{
public:
	Controller();
	void run();

	void setCurrentScreen(ScreenState state) { 
		this->m_currentScreen = state; 
		this->m_changeScreen = true;
	}
	void setCurrLvl(int level) { this->m_currentLevel = level; }
	void setMaxLvlAchieved(int newMax) { 
		if (this->m_maxLevelAchieved < newMax)
			this->m_maxLevelAchieved = newMax;
	}

	int getMaxLvlAchieved() const { return this->m_maxLevelAchieved; }
	int getCurrLvl() const { return this->m_currentLevel; }
	bool getGameWon(int level) const { return this->m_levelLoader.getGameEnded(level); }
	LevelInfo getLevelInfo(int level) const { return this->m_levelLoader.getLevel(level); }
	unsigned int getNumOfLevels() const { return this->m_levelLoader.getMaxLevel(); }

private:
	void initScreens();
	void swapScreen();
	std::vector<std::unique_ptr<Screen>> m_screens;
	ScreenState m_currentScreen = ScreenState::MENU;
	bool m_changeScreen = false;
	int m_currentLevel = 0;
	int m_maxLevelAchieved = 0;
	LevelLoader m_levelLoader;

	// SFML
	sf::RenderWindow m_window;
	sf::Clock m_clock;
};
