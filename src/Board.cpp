#include "Board.h"

Board::Board()
	: m_playerIndex(0)
{
	this->initPlayers();
	this->initEnemies();
	this->initSelected();
}

//==========================================================

void Board::seperation(Enemy* enemy, sf::Vector2f steerForce, float deltaTime)
{
	sf::Vector2f alignment, cohesion, seperation;

	for (int index = 1; index < this->m_enemies.size(); index++)
	{
		float farness = enemy->behaviour()->distance(enemy->getPosition(), this->m_enemies[index]->getPosition());
		sf::Vector2f farVec = sf::Vector2f(farness, farness);

		if (this->m_enemies[index]->behaviour()->length(farVec) <= 55) // 50 = radius
		{
			alignment += (this->m_enemies[index]->getVelocity());
			cohesion += this->m_enemies[index]->getPosition();
			seperation += this->m_enemies[index]->getPosition() - enemy->getPosition();
		}
	}

	alignment /= float(this->m_enemies.size() - 1);
	alignment = enemy->behaviour()->Normalize(alignment);

	cohesion /= float(this->m_enemies.size() - 1);;
	cohesion = sf::Vector2f(cohesion.x - enemy->getPosition().x, cohesion.y - enemy->getPosition().y);
	cohesion = enemy->behaviour()->Normalize(cohesion);

	seperation /= float(this->m_enemies.size() - 1);
	seperation *= -1.f;
	seperation = enemy->behaviour()->Normalize(seperation);

	enemy->update(steerForce + seperation * 60.f + cohesion * 25.f + alignment * 20.f, deltaTime);
}

//==========================================================

void Board::updateBoard(float deltaTime, bool charSelected)
{
	this->updateEnemyDest(); // Targets the player with highest max HP.

	float t;
	sf::Vector2f firstEnemyDist = this->m_enemies.begin()->get()->getTarget()->getPosition() - this->m_enemies.begin()->get()->getPosition();

	if (charSelected)
		m_selected.setPosition(m_players[this->m_playerIndex]->getPosition());

	for (auto& player : m_players)
	{
		sf::Vector2f steerForce;

		if(player->getTarget())
			steerForce = player->behaviour()->Arrive(player.get(), player->getTarget()->getPosition(), 10, deltaTime);
		else
			steerForce = player->behaviour()->Arrive(player.get(), player->getDest(), 10, deltaTime);

		player->update(steerForce, deltaTime);
	}

	for (auto& enemy : m_enemies)
	{
		if (enemy->behaviour()->length(enemy->getTarget()->getVelocity()) == 0.f)
			t = 2;
		else
			t = enemy->behaviour()->length(firstEnemyDist) / enemy->behaviour()->length(enemy->getTarget()->getVelocity());

		sf::Vector2f steerForce = enemy->behaviour()->Pursue(enemy.get(), enemy->getTarget()->getPosition() + enemy->getTarget()->getVelocity() * t, 100, deltaTime);
		Enemy* enemyPtr = enemy.get();
		this->seperation(enemyPtr, steerForce, deltaTime);
	}
}

//==========================================================

void Board::updateEnemyDest()
{
	int max = 0;
	sf::Vector2f pos;
	Player* maxPlayer = NULL;

	for (auto& player : m_players)
		if (player->getStat(_hp)> max)
		{
			maxPlayer = player.get();
			max = player->getStat(_hp);
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
	if (m_players[m_playerIndex]->checkSkillClick(location))
		return false;;

	for (int index = 0; index < m_players.size(); index++)
	{
		if (m_players[index]->checkCollision(location))
		{
			m_players[m_playerIndex]->setSelected(false);
			m_players[index]->setSelected(true);
			this->m_playerIndex = index;
			return true;
		}
	}

	return false;
}

//==========================================================

bool Board::handleSecondClick(sf::Vector2f location)
{
	if (m_players[m_playerIndex]->checkSkillClick(location))
		return false;

	for (auto& player : m_players)
		if (player->checkCollision(location))
			if (m_players[m_playerIndex]->setTarget(*player))
			{
				this->m_selected.setPosition(player->getPosition());
				this->m_players[m_playerIndex]->setDestination(player->getPosition());
				return true;
			}

	for (auto& enemy : m_enemies)
		if (enemy->checkCollision(location))
			if (m_players[m_playerIndex]->setTarget(*enemy))
			{
				this->m_selected.setPosition(enemy->getPosition());
				this->m_players[m_playerIndex]->setDestination(enemy->getPosition());
				return true;
			}

	this->m_players[m_playerIndex]->setAsTarget(nullptr);
	this->m_players[m_playerIndex]->setDestination(location);
	this->m_selected.setPosition(location);

	return true;
}

//==========================================================

void Board::drawBoard(sf::RenderWindow& window, bool charSelected)
{
	bool draw = checkMoving();

	if( draw || charSelected)
		window.draw(this->m_selected);

	std::sort(m_players.begin(), m_players.end(), [](auto p1, auto p2) { return p1->getPosition().y < p2->getPosition().y; });
	std::sort(m_enemies.begin(), m_enemies.end(), [](auto p1, auto p2) { return p1->getPosition().y < p2->getPosition().y; });

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

bool Board::checkMoving() const
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
	m_selected.setOrigin(origin + selectedOffset);
}
