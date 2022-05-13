#include "Board.h"

Board::Board()
	: m_selectedPlayerIndex(0)
{
	this->initPlayers();
	this->initSelected();
}

//==========================================================

void Board::updateBoard(float deltaTime, bool charSelected)
{
	if (charSelected)
		m_selected.setPosition(m_players[this->m_selectedPlayerIndex]->getSprite().getPosition());

	for (int index = 0; index < m_players.size(); index++)
		this->m_players[index]->updatePlayer(deltaTime);

	// Enemies

}

//==========================================================

bool Board::handleFirstClick(sf::Vector2f location)
{
	for (int index = 0; index < m_players.size(); index++)
	{
		if (m_players[index]->checkCollision(location))
		{
			m_players[m_selectedPlayerIndex]->setSelected(false);
			m_players[index]->setSelected(true);
			this->m_selectedPlayerIndex = index;
			return true;
		}
	}

	return false;
}

//==========================================================

void Board::handleSecondClick(sf::Vector2f location)
{
	for (int index = 0; index < m_players.size(); index++)
	{
		if (this->m_players[index]->checkCollision(location))
		{
		}
	}

	// Enemies loop

	location=adjustLocation(location);

	this->m_players[this->m_selectedPlayerIndex]->setDestination(location);
	this->m_selected.setPosition(location);

}

//==========================================================

void Board::drawBoard(sf::RenderWindow& window, bool charSelected)
{
	bool draw = checkMoving();

	if(draw || charSelected)
		window.draw(this->m_selected);

	for (int i = 0; i < m_players.size(); i++)
		m_players[i]->draw(window);
}

//==========================================================

sf::Vector2f Board::adjustLocation(sf::Vector2f location)
{
	auto newLoc = sf::Vector2f();
	newLoc.x = min(location.x, float(WINDOW_WIDTH  - CUT_CORNERS));
	newLoc.y = min(location.y, float(WINDOW_HEIGHT - 1.5f * CUT_CORNERS));

	newLoc.x = max(newLoc.x, float(CUT_CORNERS));
	newLoc.y = max(newLoc.y, float(HEIGHT_LIMIT));

	return newLoc;
}


//==========================================================

bool Board::checkMoving()
{
	for (int i = 0; i < m_players.size(); i++)
		if (this->m_players[i]->getIsMoving())
			return true;

	return false;
}

//==========================================================

void Board::initPlayers()
{
	m_players.push_back(std::make_unique < Cleric >(sf::Vector2f(200, 200)));
	m_players.push_back(std::make_unique < Knight >(sf::Vector2f(300, 300)));
}

//==========================================================

void Board::initSelected()
{
	m_selected.setTexture(*Resources::instance().getTexture(_select));
	auto origin = m_selected.getOrigin();
	m_selected.setOrigin(origin.x + 45, origin.y - 20);
}
