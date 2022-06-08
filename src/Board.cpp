#include "Board.h"

Board::Board(const LevelInfo& currLevelInfo)
	:	m_currPlayer(nullptr), m_currLvl(0), m_currWave(0),
		m_enemyWaves(currLevelInfo.m_enemyWaves)
{
	this->initPlayers(currLevelInfo.m_lvlPlayers);
	this->initEnemies(currLevelInfo.m_enemyWaves[this->m_currWave]);
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

	enemy->update(steerForce + seperation * 60.f + cohesion * 25.f + alignment * 20.f,
				  deltaTime, this->m_players, this->m_enemies);
}

//==========================================================
// Need to split this.

bool Board::updateBoard(float deltaTime, bool charSelected)
{
	this->updateEnemyDest(); // Targets the player with highest max HP.
	
	float t;
	sf::Vector2f firstEnemyDist = { 0,0 };
	if (!m_enemies.empty() && m_enemies.begin()->get()->getTarget())
		firstEnemyDist = this->m_enemies.begin()->get()->getTarget()->getPosition() - this->m_enemies.begin()->get()->getPosition();

	if (m_currPlayer)
	{
		if (charSelected)
			m_selected.setPosition(m_currPlayer->getPosition());
		else if (m_currPlayer->getTarget())
			m_selected.setPosition(m_currPlayer->getTarget()->getPosition());
	}

	for (int i = 0; i < m_players.size(); i++)
	{
		auto player = m_players[i];
		if (!player->isAlive())
		{
			deleteObject(player);
			player->handleAnimation({ 0, 0 }, deltaTime);

			if (m_currPlayer == player)
				m_currPlayer = nullptr;

			if (!player->getIsDying())
				player->setDying();
			else if (player->handleDeath())
			{
				m_players.erase(m_players.begin() + i);
				player.reset();
				i--;
			}
		}
		else
		{
			sf::Vector2f steerForce;
			steerForce = player->behaviour()->Arrive(player->getPosition(), player->getVelocity(), player->getMaxVelocity(), player->getMaxForce(), player->getDest(), 10);
			player->update(steerForce, deltaTime, this->m_players, this->m_enemies);
		}
	}

	for (int j = 0; j < m_enemies.size(); j++)
	{
		auto enemy = m_enemies[j];
		if (!enemy->isAlive())
		{
			deleteObject(enemy);
			if (!enemy->getIsDying())
				enemy->setDying();
			else if (enemy->handleDeath())
			{
				m_enemies.erase(m_enemies.begin() + j);
				enemy.reset();
				j--;
			}
		}
		else if (enemy->getTarget())
		{
			if (enemy->behaviour()->length(enemy->getTarget()->getVelocity()) == 0.f)
				t = 2;
			else
				t = enemy->behaviour()->length(firstEnemyDist) / enemy->behaviour()->length(enemy->getTarget()->getVelocity());

			sf::Vector2f steerForce = enemy->behaviour()->CollisionAvoidance(enemy->getPosition(), enemy->getVelocity(), enemy->getMaxVelocity(), enemy->getMaxForce(),
			enemy->getTarget()->getPosition(), createObstaclesVec(), 100);
			this->seperation(enemy.get(), steerForce, deltaTime);
		}

	}

	if (m_enemies.empty())
	{
		this->m_currWave++;
		if (this->m_currWave >= this->m_enemyWaves.size())
			return true;

		this->initEnemies(this->m_enemyWaves[this->m_currWave]);
		return false;
	}
}

//==========================================================

void Board::updateEnemyDest()
{
	sf::Vector2f pos = { -1,-1 };
	std::shared_ptr<Player> closePlayer = NULL;

	for (auto& enemy : m_enemies)
	{
		float min = INFINITY;
		auto enemyPos = enemy->getPosition();
		for (auto& player : m_players)
		{
			if (!player->isAlive())
				continue;

			auto playerPos = player->getPosition();

			float distance = std::sqrt(std::pow(playerPos.x - enemyPos.x, 2) +
									  std::pow(playerPos.y - enemyPos.y, 2));
			if (distance < min)
			{
				closePlayer = player;
				min = distance;
				pos = player->getPosition();
			}
		}
		if (!enemy->getIsMoving() && pos.x >= 0)
		{
			enemy->setDestination(pos);

			if (closePlayer)
				enemy->setTarget(closePlayer);
		}
	}
}

//==========================================================

bool Board::handleFirstClick(sf::Vector2f location)
{
	if (m_currPlayer && m_currPlayer->checkSkillClick(location))
		return false;

	for (auto& player : m_players)
	{
		if (player->checkCollision(location))
		{
			if(m_currPlayer)
				m_currPlayer->setSelected(false);
			player->setSelected(true);
			m_currPlayer = player;
			return true;
		}
	}

	return false;
}

//==========================================================

bool Board::handleSecondClick(sf::Vector2f location)
{
	if (!m_currPlayer)
		return true;

	if (m_currPlayer->checkSkillClick(location))
		return false;

	for (auto& player : m_players)
		if (player->checkCollision(location))
			if (m_currPlayer->setTarget(player))
				return true;

	for (auto& enemy : m_enemies)
		if (enemy->checkCollision(location))
			if (m_currPlayer->setTarget(enemy))
				return true;

	m_currPlayer->setAsTarget(nullptr);
	m_currPlayer->setDestination(adjustLocation(location));
	this->m_selected.setPosition(adjustLocation(location));
	return true;
}

//==========================================================
void Board::drawBoard(sf::RenderWindow& window, bool charSelected)
{
	bool draw = checkMoving();

	if( draw || charSelected)
		window.draw(this->m_selected);

	this->drawObjects(window);
}

//==========================================================

void Board::drawObjects(sf::RenderWindow& window)
{
	auto playersCopy = this->sortObjects(m_players);
	auto enemiesCopy = this->sortObjects(m_enemies);

	int enemyIndex = 0, playerIndex = 0;

	while (enemyIndex < enemiesCopy.size() || playerIndex < playersCopy.size())
	{
		if (enemyIndex < enemiesCopy.size() && playerIndex < playersCopy.size())
		{
			if (playersCopy[playerIndex]->getPosition().y > enemiesCopy[enemyIndex]->getPosition().y)
				enemiesCopy[enemyIndex++]->draw(window);
			else
				playersCopy[playerIndex++]->draw(window);
		}
		else if (enemyIndex < this->m_enemies.size())
			enemiesCopy[enemyIndex++]->draw(window);

		else
			playersCopy[playerIndex++]->draw(window);
	}
}

//==========================================================

void Board::drawObject(bool player, int& index, sf::RenderWindow& window)
{
	if (player)
		this->m_players[index]->draw(window);
	else
		this->m_enemies[index]->draw(window);

	index++;
}

//==========================================================

bool Board::checkIntersection(sf::Sprite obj,sf::Sprite secObj)
{
	return obj.getGlobalBounds().intersects(secObj.getGlobalBounds());
}

//==========================================================

bool Board::checkMoving() const
{
	return (m_currPlayer) && (m_currPlayer->getIsMoving());
}

//==========================================================

HashTable<int, Player*> Board::getPlayersTable()
{
	std::unordered_map<int, Player*> playersMap = {
		std::make_pair(_cleric, new Cleric(startPositions[_cleric])),
		std::make_pair(_knight, new Knight(startPositions[_knight])),
		std::make_pair(_archer, new Archer(startPositions[_archer]))
	};
	return playersMap;
}

//==========================================================

HashTable<int, Enemy*> Board::getEnemiesTable()
{
	std::unordered_map<int, Enemy*> enemiesMap = {
		std::make_pair(_dummy, new Dummy())
	};
	return enemiesMap;
}

//==========================================================

void Board::initPlayers(const bool lvlPlayers[NUM_OF_PLAYERS])
{
	for (int i = 0; i < NUM_OF_PLAYERS; i++)
		if (lvlPlayers[i])
			this->createChar(i);
}

//==========================================================

void Board::initEnemies(const std::vector<sf::Vector2i> enemyWave)
{	
	srand(time(NULL));
	for (auto& detail : enemyWave) // for now , will be changed soon 
	{
		for (int i = 0; i < detail.y; i++)
		{
			/*
			auto it = this->m_enemiesTable.getVal(detail.x);
			auto take = *it;
			auto ptr = std::make_shared<Enemy>(take);
			this->m_enemies.push_back(ptr);
			*/
			this->createChar(detail.x);
		}
	}
}

//==========================================================

void Board::createChar(const unsigned int index)
{
	switch (index)
	{
	case _cleric:
		m_players.push_back(std::make_shared < Cleric >(sf::Vector2f(200, 200)));
		break;
	case _knight:
		m_players.push_back(std::make_shared < Knight >(sf::Vector2f(200, 300)));
		break;
	case _archer:
		m_players.push_back(std::make_shared < Archer >(sf::Vector2f(200, 400)));
		break;
	case _dummy:
		this->m_enemies.push_back(std::make_shared<Dummy>());
		break;

	default:
		break;
	}
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

//==========================================================

void Board::deleteObject(std::shared_ptr<Character> obj)
{
	for (auto& enemy : m_enemies)
	{
		if (enemy->getTarget() == obj.get())
		{
			enemy->setAsTarget(nullptr);
			enemy->setMoving(false);
		}
	}

	for (auto& player : m_players)
	{
		if (player->getTarget() == obj.get())
		{
			player->setAsTarget(nullptr);
			player->setDestination(player->getPosition());
		}
	}
}