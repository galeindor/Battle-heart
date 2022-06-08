#pragma once
#include "Resources.h"

class LevelLoader
{
public:
	LevelLoader(const string fileName);
	~LevelLoader() = default;

	std::ifstream openFile(const string fileName);
	LevelInfo getLevel(const int levelNum) { return this->m_levels[levelNum]; };
private:
	std::vector<LevelInfo> m_levels = {};
	unsigned int m_numOfLevels;

	void readFromFile(const string fileName);
	int handlePlayer(const string word);
	int handleEnemyOrLevel(const string word);
	int readFullNum(std::ifstream& word, char c);
};