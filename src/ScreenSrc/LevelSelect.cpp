#include "ScreenManager/LevelSelect.h"

void LevelSelect::update(const float deltaTime)
{}

void LevelSelect::init()
{
	this->setBG(_levelSelect);
	this->initButtons();
}

void LevelSelect::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	window.draw(this->m_returnButton);
	window.draw(this->m_startButton);

	for (auto& lvl : this->m_availableLevels)
		window.draw(lvl);

	if (this->m_levelSelected)
		window.draw(this->m_levelSelection);

	if (this->m_levelHovered)
		window.draw(this->m_levelHover);
}

void LevelSelect::manageRowAndCol(int& row, int& col)
{
	
	col += std::pow(-1, row); // increase or decrease 1 based or row

/*
	if (row % 2 == 0)
		col++;
	else
		col--;
*/
	if (col >= LEVELS_CHART_COLS || col < 0)
	{
		row++;

		if (col == LEVELS_CHART_COLS)
			col--;
		else if (col == 0)
			col++;
	}
}

void LevelSelect::initButtons()
{
	sf::Sprite tempSprite;
	sf::Vector2f pos;
	int row = 0, col = 0;
	tempSprite.setTexture(*Resources::instance().getLSTexture(_lvlCompleted));
	for (int i = 0; i < this->m_controller->getCurrLvl() + 1; i++)
	{
		if(i == this->m_controller->getCurrLvl())
			tempSprite.setTexture(*Resources::instance().getLSTexture(_currLvlIcon));

		pos = { lsLevelsStartPos.x + col * lsLevelsOffset.x, 
			    lsLevelsStartPos.y + row * lsLevelsOffset.y };
		tempSprite.setPosition(pos);
		this->m_availableLevels.push_back(tempSprite);
		this->manageRowAndCol(row, col);
	}

	this->m_startButton.setTexture(*Resources::instance().getLSTexture(_startButton));
	this->m_startButton.setPosition(startButtonPos);

	this->m_returnButton.setString("Return");
	this->m_returnButton.setFont(*Resources::instance().getFont());
	this->m_returnButton.setStyle(sf::Text::Style::Bold);
	this->m_returnButton.setCharacterSize(60);
	this->m_returnButton.setPosition(returnButtonPos);

	this->m_levelHover.setTexture(*Resources::instance().getLSTexture(_levelSelection));
	this->m_levelSelection.setTexture(*Resources::instance().getLSTexture(_levelSelection));
}

void LevelSelect::handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window)
{
	if (this->m_startButton.getGlobalBounds().contains(hoverPos))
		this->m_startButton.setTexture(*Resources::instance().getLSTexture(_startButtonHL));
	else
		this->m_startButton.setTexture(*Resources::instance().getLSTexture(_startButton));

	if (this->m_returnButton.getGlobalBounds().contains(hoverPos))
	{
		this->m_returnButton.setOutlineColor(sf::Color::Black);
		this->m_returnButton.setOutlineThickness(4);
	}
	else
		this->m_returnButton.setOutlineThickness(0);

	for (int index = 0; index < this->m_availableLevels.size(); index++)
		if (this->m_availableLevels[index].getGlobalBounds().contains(hoverPos))
		{
			this->m_levelHover.setPosition(this->m_availableLevels[index].getPosition() + lvlSelOffset);
			this->m_levelHovered = true;
			return;
		}
	
	this->m_levelHovered = false;
}

void LevelSelect::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (this->m_startButton.getGlobalBounds().contains(clickPos) && this->m_levelSelected)
		this->m_controller->setCurrentScreen(ScreenState::PLAY);

	if (this->m_returnButton.getGlobalBounds().contains(clickPos))
		this->m_controller->setCurrentScreen(ScreenState::MENU);

	for (int index = 0; index < this->m_availableLevels.size(); index++)
		if (this->m_availableLevels[index].getGlobalBounds().contains(clickPos))
		{
			this->m_levelSelection.setPosition(this->m_availableLevels[index].getPosition() + lvlSelOffset);
			this->m_controller->setCurrLvl(index);
			this->m_levelSelected = true;
		}

}
