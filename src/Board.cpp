#include "Board.h"

Board::Board()
	: m_selectedPlayerIndex(0)
{
	this->initPlayers();
	this->initEnemies();
	this->initSelected();
}

//==========================================================

void Board::updateBoard(float deltaTime, bool charSelected)
{
	this->updateEnemyDest();

	if (charSelected)
		m_selected.setPosition(m_players[this->m_selectedPlayerIndex]->getPosition());

	for (auto& player : m_players)
		player->update(deltaTime);

	for (auto& enemy : m_enemies)
	{
		enemy->update(deltaTime);
		this->checkEnemyCollision(*enemy);
	}
}

//==========================================================

void Board::updateEnemyDest()
{
	int max = 0;
	sf::Vector2f pos;
	Player* maxPlayer = NULL;

	for (auto& player : m_players)
		if (player->getHp()> max)
		{
			maxPlayer = player.get();
			max = player->getHp();
			pos = player->getPosition();
		}

	for (auto& enemy : m_enemies)
	{
		if (!enemy->getIsMoving())
		{
			enemy->setDestination(pos);

			if(maxPlayer)
				enemy->setTarget(*maxPlayer);
		}
	}
}

//==========================================================

bool Board::handleFirstClick(sf::Vector2f location)
{
	if (m_players[m_selectedPlayerIndex]->checkSkillClick(location))
		return false;;

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

bool Board::handleSecondClick(sf::Vector2f location)
{
	if (m_players[m_selectedPlayerIndex]->checkSkillClick(location))
		return false;

	for (auto& player : m_players)
		if (player->checkCollision(location))
			if (m_players[m_selectedPlayerIndex]->setTarget(*player))
			{
				this->m_players[m_selectedPlayerIndex]->setDestination(player->getPosition());
				return true;
			}

	for (auto& enemy : m_enemies)
		if (enemy->checkCollision(location))
			if (m_players[m_selectedPlayerIndex]->setTarget(*enemy))
			{
				this->m_players[m_selectedPlayerIndex]->setDestination(enemy->getPosition());
				return true;
			}

	location = adjustLocation(location);
	this->m_players[m_selectedPlayerIndex]->setDestination(location);
	this->m_selected.setPosition(location);

	return true;
}

//==========================================================

void Board::drawBoard(sf::RenderWindow& window, bool charSelected)
{
	bool draw = checkMoving();

	if( draw || charSelected)
		window.draw(this->m_selected);

	for (auto &player : m_players)
		player->draw(window);

	for (auto& enemy : m_enemies)
		enemy->draw(window);
}

//==========================================================

bool Board::checkIntersection(sf::Sprite obj,sf::Sprite secObj)
{
	return obj.getGlobalBounds().intersects(secObj.getGlobalBounds());
}

//==========================================================

void Board::checkEnemyCollision(Enemy& enemy)
{
	for (auto& other : m_enemies)
		if (other->collidesWith(enemy))
			other->handleCollision(enemy);
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
	m_players.push_back(std::make_shared < Cleric >(sf::Vector2f(200, 200)));
	m_players.push_back(std::make_shared < Knight >(sf::Vector2f(300, 300)));
}

//==========================================================

void Board::initEnemies()
{	
	srand(time(NULL));
	for (int i = 0; i < 3; i++) // for now , will be changed soon 
	this->m_enemies.push_back(std::make_shared <Dummy >());
}

//==========================================================

void Board::initSelected()
{
	m_selected.setTexture(*Resources::instance().getTexture(_select));
	auto origin = m_selected.getOrigin();
	m_selected.setOrigin(origin.x + 45, origin.y - 20);
}
