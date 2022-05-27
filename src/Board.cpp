#include "Board.h"

Board::Board()
	: m_playerIndex(0)
{
	this->initPlayers();
	this->initEnemies();
	this->initSelected();
}

//==========================================================

vector<sf::Vector2f> Board::createObstaclesVec()
{
	vector<sf::Vector2f> obstacles;
	for (auto& enemy : this->m_enemies)
		obstacles.push_back(enemy->getPosition());

	for (auto& player : this->m_players)
		obstacles.push_back(player->getPosition());

	return obstacles;
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
		steerForce = player->behaviour()->Arrive(player.get(), player->getDest(), 10);
		player->update(steerForce, deltaTime);
	}

	for (auto& enemy : m_enemies)
	{
		if (enemy->behaviour()->length(enemy->getTarget()->getVelocity()) == 0.f)
			t = 2;
		else
			t = enemy->behaviour()->length(firstEnemyDist) / enemy->behaviour()->length(enemy->getTarget()->getVelocity());

		sf::Vector2f steerForce = enemy->behaviour()->CollisionAvoidance(enemy.get(), enemy->getTarget()->getPosition(), createObstaclesVec(), 10);
		Enemy* enemyPtr = enemy.get();
		this->seperation(enemyPtr, steerForce, deltaTime);
		enemy->update(steerForce, deltaTime);
	}
}

//==========================================================

void Board::updateEnemyDest()
{
	int max = 0;
	sf::Vector2f pos;
	std::shared_ptr<Player> maxPlayer = NULL;

	for (auto& player : m_players)
		if (player->getStat(_hp)> max)
		{
			maxPlayer = player;
			max = player->getStat(_hp);
			pos = player->getPosition();
		}

	for (auto& enemy : m_enemies)
	{
		if (!enemy->getIsMoving())
		{
			enemy->setDestination(pos);

			if(maxPlayer)
				enemy->setTarget(maxPlayer);
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
			if (m_players[m_playerIndex]->setTarget(player))
			{
				this->m_selected.setPosition(player->getPosition());
				this->m_players[m_playerIndex]->setDestination(player->getPosition());
				return true;
			}

	for (auto& enemy : m_enemies)
		if (enemy->checkCollision(location))
			if (m_players[m_playerIndex]->setTarget(enemy))
			{
				this->m_selected.setPosition(enemy->getPosition());
				if(!m_players[m_playerIndex]->targetInRange())
					this->m_players[m_playerIndex]->setDestination(enemy->getPosition());
				return true;
			}

	this->m_players[m_playerIndex]->setAsTarget(nullptr);
	this->m_players[m_playerIndex]->setDestination(adjustLocation(location));
	this->m_selected.setPosition(adjustLocation(location));

	return true;
}

//===================================================================================

void Board::drawBoard(sf::RenderWindow& window, bool charSelected)
{
	bool draw = checkMoving();

	if( draw || charSelected)
		window.draw(this->m_selected);

	this->drawObjects(window);
}

//===================================================================================

void Board::sortObjects()
{
	std::sort(m_players.begin(), m_players.end(), 
			  [](auto obj1, auto obj2) 
				{ return obj1->getPosition().y < obj2->getPosition().y; });

	std::sort(m_enemies.begin(), m_enemies.end(), 
			  [](auto obj1, auto obj2) 
				{ return obj1->getPosition().y < obj2->getPosition().y; });

}
//===================================================================================

void Board::drawObjects(sf::RenderWindow& window)
{
	this->sortObjects();
	int enemyIndex = 0, playerIndex = 0;

	while(enemyIndex < this->m_enemies.size() || playerIndex < this->m_players.size())
	{
		if (enemyIndex < this->m_enemies.size() && playerIndex < this->m_players.size())
		{
			if (this->m_players[playerIndex].get()->getPosition().y > this->m_enemies[enemyIndex].get()->getPosition().y)
				drawObject(false, enemyIndex, window);

			else
				drawObject(true, playerIndex, window);

		}
		else if (enemyIndex < this->m_enemies.size())
			drawObject(false, enemyIndex, window);

		else
			drawObject(true, playerIndex, window);
	}
}

void Board::drawObject(bool player, int& index, sf::RenderWindow& window)
{
	if (player)
		this->m_players[index]->draw(window);
	else
		this->m_enemies[index]->draw(window);

	index++;
}
//==========================================================

//==========================================================

bool Board::checkIntersection(sf::Sprite obj,sf::Sprite secObj)
{
	return obj.getGlobalBounds().intersects(secObj.getGlobalBounds());
}

//==========================================================

bool Board::checkMoving() const
{
	return this->m_players[this->m_playerIndex]->getIsMoving();
}

//==========================================================

void Board::initPlayers()
{
	m_players.push_back(std::make_shared < Cleric >(sf::Vector2f(200,200 )));
	m_players.push_back(std::make_shared < Knight >(sf::Vector2f(200,300 )));
	m_players.push_back(std::make_shared < Archer >(sf::Vector2f(200,400 )));
}

//==========================================================

void Board::initEnemies()
{	
	srand(time(NULL));
	for (int i = 0; i < 3; i++) // for now , will be changed soon 
		this->m_enemies.push_back(std::make_shared <Dummy>());
}

//==========================================================

void Board::initSelected()
{
	m_selected.setTexture(*Resources::instance().getTexture(_select));
	auto origin = m_selected.getOrigin();
	m_selected.setOrigin(origin + selectedOffset);
}

//==========================================================

sf::Vector2f Board::adjustLocation(sf::Vector2f location)
{
	auto newLoc = sf::Vector2f();
	newLoc.x = std::min(location.x, float(WINDOW_WIDTH - CUT_CORNERS));
	newLoc.y = std::min(location.y, float(WINDOW_HEIGHT - 1.5f * CUT_CORNERS));

	newLoc.x = std::max(newLoc.x, float(CUT_CORNERS));
	newLoc.y = std::max(newLoc.y, float(HEIGHT_LIMIT));

	return newLoc;
}