#include "LevelLoader.h"

LevelLoader::LevelLoader(const string fileName)
{
	this->readFromFile(fileName);
}

std::ifstream LevelLoader::openFile(const string fileName)
{
    std::ifstream file(fileName);
    if (file.fail())
    {
        std::cout << "Can't open file.\n";
        exit(EXIT_FAILURE);
    }
    return file;
}

void LevelLoader::readFromFile(const string fileName)
{
    std::ifstream file = openFile(fileName);
    char c;
    string word;
    struct LevelInfo currLvlInfo = {};
    std::vector<sf::Vector2i> currWave;
    unsigned int currLevel = 0;

    while (file.get(c)) // While there's something to read in the file.
    {
        if (isalpha(c)) // Reads a word.
            word += c;
        // If a number appears after the word then it's enemies or a new level.
        else if (isdigit(c))
        {
            sf::Vector2i feedback = { this->handleEnemyOrLevel(word),
                                      this->readFullNum(file, c) };

            // If new level.
            if (feedback.x == NEW_LEVEL_DETECTED)
            {
                if (currLevel != 0)
                {
                    this->m_levels.push_back(currLvlInfo);
                    currLvlInfo = { 0 };
                }
                currLevel++;
            }
            // If enemies.
            else
                currWave.push_back(feedback);

            word.clear();
        }
        // If player.
        else if (c == '\n')
        {
            currLvlInfo.m_lvlPlayers[this->handlePlayer(word)] = true;
            word.clear();
        }
        // If new wave of enemies.
        else if (c == NEW_WAVE)
        {
            currLvlInfo.m_enemyWaves.push_back(currWave);
            currWave.clear();
        }
    }
    this->m_levels.push_back(currLvlInfo);
    // Might come in use, or not.
    this->m_numOfLevels = currLevel;
}

int LevelLoader::handlePlayer(const string word)
{
    // Maybe find a better way than lots of ifs.
    if (word == "Cleric")
        return _cleric;
    if (word == "Knight")
        return _knight;
    if (word == "Archer")
        return _archer;

    return 0;
}

int LevelLoader::handleEnemyOrLevel(const string word)
{
    // Maybe find a better way than lots of ifs.
    if (word == "Level")
        return NEW_LEVEL_DETECTED;
    if (word == "Dummy")
        return _dummy;
}

int LevelLoader::readFullNum(std::ifstream& file, char c)
{
    char timeLim[2] = { 0 };
    int counter = 0;

    while (isdigit(c))
    {
        timeLim[counter] = c;
        counter++;
        file.get(c);
    }

    return atoi(timeLim);
}