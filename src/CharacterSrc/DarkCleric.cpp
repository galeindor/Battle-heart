#include "Characters/DarkCleric.h"

//================================================================
// Constructor.
DarkCleric::DarkCleric()
	:Enemy(_darkCleric)
{
	this->initSkills(_darkCleric);
	setScale(SPRITE_SCALE);
}

//================================================================
// Inits skills.
void DarkCleric::initSkills(const int index)
{
	this->createSkill(index, _basic, _heal, AttackType::Multi, !onPlayer, !isActive, _energy); // basic heal on all enemies
	this->createSkill(index, _skill1, _teleport, AttackType::Self, !onPlayer, !isActive, _none); // teleport
}

//====================================================================================
// Unique update function.
void DarkCleric::update(sf::Vector2f steerForce, const float deltaTime,
	vector<std::shared_ptr<Player>> m_players, vector<std::shared_ptr<Enemy>> m_enemies)
{
	this->setAsTarget(findClosestEnemy(m_enemies));
	Enemy::update(steerForce, deltaTime, m_players, m_enemies);

	if (useSkill(_skill1, this->getPosition()))
		this->setPosition(this->randEnemyPos());
}

//====================================================================================
// Dark cleric will target the enemy with the lowest hp at the moment.
std::shared_ptr<Enemy> DarkCleric::findClosestEnemy(vector<std::shared_ptr<Enemy>> enemies)
{
	auto copy = enemies;

	// sort the enemies by x values and find one that isn't dead
	std::sort(copy.begin(), copy.end(),
		[](auto e1 , auto e2) {return e1->getPosition().x < e2->getPosition().x; });

	auto i = 0;

	while (i < copy.size()) // target the first not dead enemy
	{
		if(copy[i]->isAlive())
			return copy[i];
		i++;
	}
}

//===============================================================================

sf::Vector2f DarkCleric::randEnemyPos()
{
	auto pos = Enemy::randEnemyPos();

	pos.x = rand() % (WINDOW_WIDTH - CUT_CORNERS);

	return pos;
}