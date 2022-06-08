#pragma once
#include "Resources.h"
#include "HashTable.h"

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
	HashTable<string, int> m_table;
	void readFromFile(const string fileName);

	int readFullNum(std::ifstream& word, char c);
};