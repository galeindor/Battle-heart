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
			this->updatePlayersDeath(player, deltaTime, i);
		else
			this->playerBehavior(player, deltaTime);
		
	}

	for (int j = 0; j < m_enemies.size(); j++)
	{
		auto enemy = m_enemies[j];
		if (!enemy->isAlive())
			this->updateEnemysDeath(enemy, deltaTime, j);
		else if (enemy->getTarget())
		{
			this->enemyBehavior(enemy, deltaTime, firstEnemyDist);
		}

	}

	if (m_players.empty())
	{
		// Lost level, do something.
	}

	if (m_enemies.empty())
	{
		this->m_currWave++;
		if (this->m_currWave >= this->m_enemyWaves.size())
			return true;

		this->initEnemies(this->m_enemyWaves[this->m_currWave]);
		return false;
	}

	return false;
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
		//if (!enemy->getIsMoving() && pos.x >= 0) removed condition in order to allow target swap
		if(pos.x >= 0)
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

void Board::updatePlayersDeath(std::shared_ptr<Player> character, float deltaTime, int& index)
{

	if (m_currPlayer == character)
		m_currPlayer = nullptr;

	this->playerBehavior(character, deltaTime);

	if (!character->getIsDying())
		character->setDying();
	else if (character->handleAnimation({ 0,0 },deltaTime))
	{
		m_players.erase(m_players.begin() + index);
		character.reset();
		index--;
	}
}

//==========================================================

void Board::updateEnemysDeath(std::shared_ptr<Enemy> character, float deltaTime, int& index)
{

	if (!character->getIsDying())
		character->setDying();
	else if (character->handleAnimation({ 0, 0 }, deltaTime))
	{
		m_enemies.erase(m_enemies.begin() + index);
		character.reset();
		index--;
	}
}

//==========================================================

void Board::playerBehavior(std::shared_ptr<Player> character,float deltaTime)
{
	sf::Vector2f steerForce;
	steerForce = character->behaviour()->Arrive(character->getPosition(), character->getVelocity(), character->getMaxVelocity(), character->getMaxForce(), character->getDest(), 10);
	character->update(steerForce, deltaTime, this->m_players, this->m_enemies);
}

//==========================================================

void Board::enemyBehavior(std::shared_ptr<Enemy> enemy, float deltaTime, sf::Vector2f pos)
{
	if (enemy->behaviour()->length(enemy->getTarget()->getVelocity()) == 0.f)
		auto t = 2;
	else
		auto t = enemy->behaviour()->length(pos) / enemy->behaviour()->length(enemy->getTarget()->getVelocity());

	sf::Vector2f steerForce = enemy->behaviour()->CollisionAvoidance(enemy->getPosition(), enemy->getVelocity(), enemy->getMaxVelocity(), enemy->getMaxForce(),
		enemy->getTarget()->getPosition(), createObstaclesVec(), 100);
	this->seperation(enemy.get(), steerForce, deltaTime);
}


////==========================================================

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

bool Board::checkMoving() const
{
	return (m_currPlayer) && (m_currPlayer->getIsMoving());
}

//==========================================================

HashTable<int, shared_ptr<Player>> Board::getPlayersTable()
{
	std::unordered_map<int, shared_ptr<Player>> playersMap = {
		std::make_pair(_cleric, Cleric(startPositions[_cleric]).getType()),
		std::make_pair(_knight, Knight(startPositions[_cleric]).getType()),
		std::make_pair(_archer, Archer(startPositions[_cleric]).getType())
	};
	return playersMap;
}

//==========================================================

HashTable<int, shared_ptr<Enemy>> Board::getEnemiesTable()
{
	std::unordered_map<int, shared_ptr<Enemy>> enemiesMap = {
		std::make_pair(_dummy, Dummy().getType())
	};

	return enemiesMap;
}

//==========================================================

void Board::initPlayers(const bool lvlPlayers[NUM_OF_PLAYERS])
{
	for (int i = 0; i < NUM_OF_PLAYERS; i++)
		if (lvlPlayers[i])
		{
			auto it = this->getPlayersTable().getVal(i);
			this->m_players.push_back(it);
		}
}

//==========================================================

void Board::initEnemies(const std::vector<sf::Vector2i> enemyWave)
{	
	srand(time(NULL));
	for (auto& detail : enemyWave) // for now , will be changed soon 
	{
		for (int i = 0; i < detail.y; i++)
		{
			auto it = this->getEnemiesTable().getVal(detail.x);
			this->m_enemies.push_back(it);
		}
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