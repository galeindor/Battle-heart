#include "ScreenManager/LevelSelect.h"

LevelSelect::LevelSelect()
{
}

void LevelSelect::runLevelLoader(sf::RenderWindow& window)
{
	this->m_running = true;

	while (window.isOpen() && this->m_running)
	{
		this->render(window);
		this->pollEvents(window);
	}
}

void LevelSelect::drawLevelLoader(sf::RenderWindow& window)
{
}

void LevelSelect::drawButtons(sf::RenderWindow& window)
{
}

void LevelSelect::pollEvents(sf::RenderWindow& window)
{
}

void LevelSelect::render(sf::RenderWindow& window)
{
}

void LevelSelect::handleClick(sf::Vector2f pos)
{
}

void LevelSelect::hoverButtons(sf::Vector2f pos)
{
}
