#include "GameBoard.h"

GameBoard::GameBoard()
	: m_selectedPlayerIndex(0)
{
	this->initPlayers();
	this->initSelected();
}

//==========================================================

void GameBoard::updateBoard(float deltaTime, bool charSelected)
{
	if (charSelected)
		m_selected.setPosition(m_players[this->m_selectedPlayerIndex]->getPosition());

	for (int index = 0; index < m_players.size(); index++)
		this->m_players[index]->updatePlayer(deltaTime);

	// Enemies
}

//==========================================================

bool GameBoard::handleFirstClick(sf::Vector2f location)
{
	for (int index = 0; index < m_players.size(); index++)
	{
		if (m_players[index]->checkCollision(location))
		{
			this->m_selectedPlayerIndex = index;
			return true;
		}
	}

	return false;
}

//==========================================================

void GameBoard::handleSecondClick(sf::Vector2f location)
{
	for (int index = 0; index < m_players.size(); index++)
	{
		if (this->m_players[index]->checkCollision(location))
		{
		}
	}

	// Enemies loop

	if (!this->outOfRange(location))
	{
		this->m_players[this->m_selectedPlayerIndex]->setDestination(location);
		this->m_selected.setPosition(location);
	}
}

//==========================================================

void GameBoard::drawBoard(sf::RenderWindow& window, bool charSelected)
{
	bool draw = checkMoving();

	if(draw || charSelected)
		window.draw(this->m_selected);

	for (int i = 0; i < m_players.size(); i++)
		m_players[i]->draw(window);
}

//==========================================================

bool GameBoard::outOfRange(sf::Vector2f location)
{
	return (location.x >= WINDOW_WIDTH - CUT_CORNERS || location.x <= CUT_CORNERS ||
		location.y >= WINDOW_HEIGHT - CUT_CORNERS || location.y <= HEIGHT_LIMIT);
}

//==========================================================

bool GameBoard::checkMoving()
{
	for (int i = 0; i < m_players.size(); i++)
		if (this->m_players[i]->getIsMoving())
			return true;

	return false;
}

//==========================================================

void GameBoard::initPlayers()
{
	m_players.push_back(std::make_unique < Cleric >(sf::Vector2f(200, 200)));
	m_players.push_back(std::make_unique < Knight >(sf::Vector2f(300, 300)));
}

//==========================================================

void GameBoard::initSelected()
{
	m_selected.setTexture(*Resources::instance().getTexture(_select));
	auto origin = m_selected.getOrigin();
	m_selected.setOrigin(origin.x + 45, origin.y - 20);
}
