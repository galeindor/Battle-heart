#include "ScreenManager/Gameplay.h"

Gameplay::Gameplay(Controller* controller)
	: m_currLvl(0), m_board(Board(controller->getLevelInfo(0))),
	  m_controller(controller)
{}

void Gameplay::update(const float deltaTime)
{
	if (this->m_board.updateBoard(deltaTime, this->m_charSelected))
		if (!this->winLevel())
			this->winGame();
}

void Gameplay::init()
{
	this->setBG((this->m_currLvl % (this->m_controller->getNumOfLevels()) + _firstLevel));
}

void Gameplay::draw(sf::RenderWindow& window)
{
	this->drawBG(window);
	this->m_board.drawBoard(window, this->m_charSelected);
}

bool Gameplay::winLevel()
{
	this->m_currLvl++;
	if (this->m_controller->getGameWon(this->m_currLvl))
		return false;

	this->m_board = Board(this->m_controller->getLevelInfo(this->m_currLvl));
}

void Gameplay::winGame()
{
	exit(EXIT_SUCCESS);
}

void Gameplay::handleHover(const sf::Vector2f& hoverPos, sf::RenderWindow& window)
{
}

void Gameplay::handleMouseClick(const sf::Vector2f& clickPos, sf::RenderWindow& window)
{
	if (!this->m_charSelected)
		this->m_charSelected = this->m_board.handleFirstClick(clickPos);

	else // if a click made the player move - charSelected is no longer true
		this->m_charSelected = !m_board.handleSecondClick(clickPos);
}
