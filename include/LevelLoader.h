#pragma once
#include "Resources.h"
#include "HashTable.h"

class LevelLoader
{
public:
	LevelLoader(const string fileName);
	~LevelLoader() = default;

	std::ifstream openFile(const string fileName);
	LevelInfo getLevel(const int levelNum) const { return this->m_levels[levelNum]; }
	bool getGameEnded(const int currLv) const { return currLv >= this->m_levels.size(); }
	unsigned int getMaxLevel() const { return this->m_numOfLevels; }
private:
	std::vector<LevelInfo> m_levels = {};

	unsigned int m_numOfLevels;
	HashTable<string, int> m_table;
	void readFromFile(const string fileName);
	std::vector<sf::Vector2i> readWave(std::ifstream& file);
	int readFullNum(std::ifstream& file, char c);
};